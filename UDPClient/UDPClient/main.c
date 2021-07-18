/*
	Simple udp client
*/
#include<stdio.h>	//printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#include <unistd.h>
#include <signal.h>
#include "die.h"
#define SERVER "127.0.0.1"
#define BUFLEN 512	//Max length of buffer
#define PORT 8888	//The port on which to send data
static volatile int continueFlag=1;   // sync main.c with interrupt handler

void  INThandler(int sig)
{
     char  c;

     signal(sig, SIG_IGN);
     printf("OUCH, did you hit Ctrl-C?\n"
            "Do you really want to quit? [y/n] ");
     c = getchar();
     if (c == 'y' || c == 'Y')
          continueFlag=0;
     else
          signal(SIGINT, INThandler);
     //getchar(); // Get new line character
}

int main(void)
{
    struct sockaddr_in si_other;
    int s, slen=sizeof(si_other);
    char buf[BUFLEN];
    char message[BUFLEN];
    signal(SIGINT, INThandler);

    if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        DIE("socket",s);
    }

    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);

    if (inet_aton(SERVER, &si_other.sin_addr) == 0)
    {
        fprintf(stderr, "inet_aton() failed\n");
        return(1);
    }

    while(continueFlag)
    {
        printf("Enter message :\n");
        printf("Press CTRL C for exit\n");
        fgets(message,sizeof(message),stdin);

        //send the message
        if (sendto(s, message, strlen(message), 0, (struct sockaddr *) &si_other, slen)==-1)
        {
            DIE("sendto()",s);
        }

        //receive a reply and print it
        //clear the buffer by filling null, it might have previously received data
        memset(buf,'\0', BUFLEN);
        //try to receive some data, this is a blocking call
        if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, (socklen_t *restrict)&slen) == -1)
        {
            DIE("recvfrom()",s);
        }

        puts(buf);
    }
    printf("before closing socket\n");
    close(s);
    return 0;
}
