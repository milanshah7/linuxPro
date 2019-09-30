#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <stdarg.h>

/* MACRO Definations */

#define SUCCESS   0
#define FAILURE  -1

#define TCP_SOCK 1
#define UDP_SOCK 2

#define PORT1 20000
#define PORT2 20001

#define DEBUG_ERROR(fmt, args...) { \
        if(errno == 0){ \
                fprintf(stderr, "%s: %d: ", ##args, __LINE__); \
                perror(fmt); \
        } \
}

#define DEATH(msg) \
{  \
	perror(msg); \
	exit(errno); \
}

#define SIZE_OF_COMMAND    sizeof(struct commandframe)
#define SIZE_OF_RESPONSE   sizeof(struct responseframe)

/* Definition of global defined data */ 

enum msgCode{
	doublyLinkedList = 1,
	multithreadingOps,
	forkOps,
	ipcOps,
};

/*
 * This is a frame structre which consist of following fields.
 * 1. Sequence Num. : byte field which is uniquely given in every message request. 
 *         In a response to request, same sequence number will be used which was sent in message request.
 * 2. UDP/TCP       : Decides whether UDP socket or TCP socket used at client side
 * 3. Message Code  : enum
 * 4. Payload       : void pointer
 * 5. Payload Size  : total size of payload
 */

struct commandframe{
	uint8_t seqNum;
	uint16_t inSockType;     // TCP or UDP
	enum msgCode mCode;
	uint16_t outSockType;    // TCP or UDP
	void *payload;
	uint16_t payloadSize;
};

struct responseframe{
	uint8_t resSeqNum;
	bool status;
};

union payloadData{
	uint8_t nodeNums;
	uint8_t threadNums;
	uint8_t forkNums;
	uint8_t *msgPtr;
};
