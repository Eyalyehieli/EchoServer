#ifndef DIE_H_INCLUDED
#define DIE_H_INCLUDED

#include<stdio.h>	//printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#include <unistd.h>

#define DIE(error_string,socket) {\
        perror(error_string);\
        close(socket);\
        return(1);\
        }

#endif // DIE_H_INCLUDED
