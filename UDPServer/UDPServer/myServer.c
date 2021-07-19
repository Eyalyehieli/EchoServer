#include<stdio.h>	//printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#include <unistd.h>
#include "die.h"
#define BUFLEN 512	//Max length of buffer
//#define PORT 8888	//The port on which to listen for incoming data
#include "myServer.h"

static struct sockaddr_in si_me, si_other;

static int s, slen  , recv_len;
static char buf[BUFLEN];
static ServerErrorCode ServerErrorCodeType;

ServerErrorCode initServer(int PortNumber,ServerType ServerT)
{

    slen = sizeof(si_other);
    if (ServerT!=ReplayType)
       return ProcessTypeNotImplemented;

    //create a UDP socket
	if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		ServerErrorCodeType = ErrorWhileCreatingUDPSocket;
		return ErrorWhileCreatingUDPSocket;
	}

	// zero out the structure
	memset((char *) &si_me, 0, sizeof(si_me));

	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(PortNumber);
	si_me.sin_addr.s_addr = htonl(INADDR_ANY);

	//bind socket to port
	if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
	{
		ServerErrorCodeType = ErrorWhileBindingUDPSocket;
		return ErrorWhileBindingUDPSocket;
	}
   return ServerOK;
}


/*
   cleaning module open resources.
   should be called when any error is returned by the Server module.

*/

ServerErrorCode closeServer(void)
{
   switch (ServerErrorCodeType)
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
        case ServerOK:
             DIE("Server Finish OK ",s);
             break;
   }
   return ServerErrorCodeType;

}


/*
    Written By Eyal.Yehieli
      Currently only replay mode is supported.
      future feature that the server optionally will support is related to new requirements.
      The Server is running for ever and return back only if error is happening.

*/
ServerErrorCode ProcessingServer(void)
{
   // this function should run for ever unless error is happening
   	while(1)
	{
		printf("Waiting for data...\n");
		printf("Press CTRL C for exit\n");
		fflush(stdout);

		//try to receive some data, this is a blocking call
		if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, (socklen_t *restrict)&slen)) == -1)
		{
			ServerErrorCodeType = ErrorWhileRecvFromUDPSocket;
			return ErrorWhileRecvFromUDPSocket;
        }

        //buf[recv_len]='\0';
		//print details of the client/peer and the data received
		printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
		printf("Data: %s\n" , buf);

		//now reply the client with the same data
		if (sendto(s, buf, recv_len, 0, (struct sockaddr*) &si_other, slen) == -1)
		{
			ServerErrorCodeType = ErrorWhileRecvFromUDPSocket;
			return ErrorWhileSendTOUDPSocket;
		}

	}
	ServerErrorCodeType = ServerOK;


}


