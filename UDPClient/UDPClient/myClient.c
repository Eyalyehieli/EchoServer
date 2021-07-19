#include<stdio.h>	//printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#include <unistd.h>
#include <signal.h>
#include "die.h"
//#define SERVER "127.0.0.1"
#define BUFLEN 512	//Max length of buffer
#define PORT 8888	//The port on which to send data
#include "myClient.h"


static volatile int continueFlag=1;   // sync main.c with interrupt handler
struct sockaddr_in si_other;
int s, slen;
char buf[BUFLEN];
char message[BUFLEN];
ClientErrorCode ClientErrorCodeType;


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






ClientErrorCode initClient(int PortNumber,ServerType ServerT,char *SERVER)
{
    slen = sizeof(si_other);
    signal(SIGINT, INThandler);
    if (ServerT!=ReplayType)
       return ProcessTypeNotImplemented;

    if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        ClientErrorCodeType = ErrorWhileCreatingUDPSocket;
		return ErrorWhileCreatingUDPSocket;

    }

    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);

    if (inet_aton(SERVER, &si_other.sin_addr) == 0)
    {
        ClientErrorCodeType = Errorinetaton_failed;
        return Errorinetaton_failed;
    }

   return ClientOK;
}




ClientErrorCode ProcessingClient(void)
{
    while(continueFlag)
    {
        printf("Enter message :\n");
        printf("Press CTRL C for exit\n");
        fgets(message,sizeof(message),stdin);

        //send the message
        if (sendto(s, message, strlen(message), 0, (struct sockaddr *) &si_other, slen)==-1)
        {
            ClientErrorCodeType = ErrorWhileSendTOUDPSocket;
			return ErrorWhileSendTOUDPSocket;
        }

        //receive a reply and print it
        //clear the buffer by filling null, it might have previously received data
        memset(buf,'\0', BUFLEN);
        //try to receive some data, this is a blocking call
        if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, (socklen_t *restrict)&slen) == -1)
        {
            ClientErrorCodeType = ErrorWhileRecvFromUDPSocket;
			return ErrorWhileRecvFromUDPSocket;

        }

        puts(buf);
    }
    ClientErrorCodeType = ClientOK;
    return ClientOK;
}



ClientErrorCode closeClient(void)
{
   switch (ClientErrorCodeType)
   {
      case ProcessTypeNotImplemented:
           perror("Process Type is not implemented");
             break;
      case ErrorWhileCreatingUDPSocket:
             DIE("socket",s);
             break;
      case ErrorWhileBindingUDPSocket:
             DIE("bind",s);
             break;
       case ErrorWhileRecvFromUDPSocket:
             DIE("recvfrom()",s);
             break;
       case ErrorWhileSendTOUDPSocket:
             DIE("sendto()",s);
             break;
      case ClientOK:
             DIE("Server Finish OK ",s);
             break;
        case Errorinetaton_failed:
             DIE("inet_aton() failed\n",s)
             break;

    }

    return ClientErrorCodeType;
}



