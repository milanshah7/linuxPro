/* User-Defined Library */ 

#ifndef _HEADER_H_
#define _HEADER_H_

#endif

#include "sock.h"

/* MACRO definations */

#define MSG_SIZE 20

/* Local API definations */

static void initializeFrameAndPayload(struct commandframe *);
static void initializePayload(struct commandframe *);
static int32_t processCommand(struct commandframe *);

int main(){

	/* Define and Initialize frame structure with appropriate values */

	struct commandframe cli_frame;

	initializeFrameAndPayload(&cli_frame);

	processCommand(&cli_frame);

	return 0;
}

int32_t processCommand(struct commandframe *commandPtr){

	int32_t socketfd, ret;
	struct sockaddr_in cliaddr;
	struct responseframe rFrame;
	socklen_t addrlen = sizeof(struct sockaddr_in);

	bzero(&cliaddr , addrlen);
	bzero(&rFrame, SIZE_OF_RESPONSE);

	printf("\n************** Command Frame ***************\n");
	printf("seqNum: %d\n", commandPtr -> seqNum);
	printf("Input Socket Type: %d\n", commandPtr -> inSockType);
	printf("Operation to perform: %d\n", commandPtr -> mCode);
	printf("Output Socket Type: %d\n", commandPtr -> outSockType);
	printf("\n********************************************\n");

	if ((commandPtr->inSockType == TCP_SOCK) && (commandPtr->outSockType == TCP_SOCK)){

		socketfd = tcpConnectClient();

		ret = write(socketfd, commandPtr, SIZE_OF_COMMAND);		
		if(ret == FAILURE)
			DEATH("sendto");

		ret = read(socketfd, &rFrame, SIZE_OF_RESPONSE);
		if(ret == FAILURE)
			DEATH("recvfrom");

	}
	else if ((commandPtr->inSockType == UDP_SOCK) && (commandPtr->outSockType == UDP_SOCK)){

		socketfd = udpConnectClient();

		ret = send(socketfd, commandPtr, SIZE_OF_COMMAND, 0); 
		if (ret == FAILURE)
			DEATH("send");

		ret = recv(socketfd, &rFrame, SIZE_OF_RESPONSE, 0);
		if (ret == FAILURE)
			DEATH("recv");

	}
	else{
		ret = tcp_udp_connect(commandPtr);
	}

	printf("\n************** Response Frame ***************\n");
	printf("seqNum: %u\n", rFrame.resSeqNum);
	printf("status: %u\n", rFrame.status);
	printf("\n**************************************************\n");

	return ret;
}

static void initializeFrameAndPayload(struct commandframe *fptr){

	static uint8_t seqN = 10;

	printf("\nWhat type of socket to be used to send data ?\n");
	printf("TCP Socket : Press 1\n");
	printf("UDP Socket : Press 2\n");

	printf("Your Value: ");
	scanf("%hu", &fptr->inSockType);

	printf("\nWhat type of operation need to perform on server side ?\n");
	printf("Doubly Linked List         : Press 1\n");
	printf("Multi-threading Operations : Press 2\n");
	printf("Fork Operation             : Press 3\n");
	printf("IPC Operation              : Press 4\n");

	printf("Your Value: ");
	scanf("%hu", (uint16_t *)&fptr->mCode);

	printf("\nWhat type of socket to be used to receive data ?\n");
	printf("TCP Socket : Press 1\n");
	printf("UDP Socket : Press 2\n");

	printf("Your Value: ");
	scanf("%hu", &fptr->outSockType);

	fptr -> seqNum = seqN++;

	initializePayload(fptr);

}

static void initializePayload(struct commandframe *pptr){
	uint8_t choice = pptr->mCode;
	union payloadData pData;

	pptr->payloadSize = sizeof(union payloadData);

	switch(choice){
		case 1:

			printf("\nAs you want doubly linked list operation on server side\n");
			printf("\nHow many node you want to create ? - ");
			scanf("%hhu", &pData.nodeNums);

			pptr->payload = &pData.nodeNums;

			break;

		case 2:

			printf("\nAs you want to create multiple thread\n");
			printf("\nPlease entre total number of threads you want to create... : ");
			scanf("%hhu", &pData.threadNums);

			pptr->payload = &pData.threadNums;

			break;
		case 3:

			printf("\nAs you want to work with fork operations\n");
			printf("\nPlease entre total number of processes you want to create... : ");
			scanf("%hhu", &pData.forkNums);

			pptr->payload = &pData.forkNums;

			break;
		case 4:

			printf("\nAs you want to send message through ipc\n");
			printf("\nPlease Enter the message... : ");
			scanf("%20s", pData.msgPtr);

			pptr->payload = pData.msgPtr;

			break;
		default:
			printf("Your Choice was invalid\n");
			break;

	}
}

