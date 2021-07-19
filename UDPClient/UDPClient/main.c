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
#include "myClient.h"

//#define SERVER "127.0.0.1"
#define BUFLEN 512	//Max length of buffer
#define PORT 8888	//The port on which to send data

int main(void)
{
    ClientErrorCode ClientErrorCodeReturn;
    // init client module
    ClientErrorCodeReturn =  initClient(PORT,ReplayType,"127.0.0.1");
    // in case of error close client module
    if (ClientErrorCodeReturn!=ClientOK)
        return(closeClient());
    // processing until finishing by CTRL-C  or error occurs
    if (ProcessingClient())
    {
       printf("seccess");
    }
    closeClient();

}
