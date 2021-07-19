/*
	Simple udp server
*/
#include<stdio.h>	//printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#include <unistd.h>
#include "die.h"
#include "myServer.h"
#define PORT 8888	//The port on which to listen for incoming data

int main(void)
{
    ServerErrorCode ServerErrorCodeReturn;
    // init server module
    ServerErrorCodeReturn =  initServer(PORT,ReplayType);
    // in case of error close server module
    if (ServerErrorCodeReturn!=ServerOK)
        return(closeServer());
    // processing until finish or error occurs
    if (ProcessingServer())
        return(closeServer());

}
