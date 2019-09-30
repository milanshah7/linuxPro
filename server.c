/* User Defined Header Files */

#ifndef HEADER_H
#define HEADER_H

#endif

#include "sock.h"

int main(){
	pid_t pid;
	uint32_t serv_sock_fd, ret;
	struct commandframe serv_cFrame;
	struct responseframe serv_rFrame;
	struct sockaddr_in cliaddr;
	socklen_t addrlen = sizeof(struct sockaddr_in);

	bzero(&serv_cFrame, SIZE_OF_COMMAND);
	bzero(&serv_rFrame, SIZE_OF_RESPONSE);
	bzero(&cliaddr, addrlen);

	pid = fork();
	if(pid == 0){
		printf("Child Process has started (TCP Connection) with pid: %d\n", getpid());

		serv_sock_fd = tcpConnectServer();

		ret = read(serv_sock_fd, &serv_cFrame, SIZE_OF_COMMAND);
		if(ret == FAILURE)
			DEATH("recvfrom");

		printf("\n************** Response Frame ***************\n");
		printf("seqNum: %d\n", serv_cFrame.seqNum);
		printf("inSockTyep: %d\n", serv_cFrame.inSockType);
		printf("msgCode: %d\n", serv_cFrame.mCode);
		printf("outSockType: %d\n", serv_cFrame.outSockType);
		printf("\n**************************************************\n");

		/* Construct Response Frame Structure */

		serv_rFrame.resSeqNum = serv_cFrame.seqNum;
		serv_rFrame.status = 1;

		ret = write(serv_sock_fd, &serv_rFrame, SIZE_OF_RESPONSE);
		if(ret == FAILURE)
			DEATH("sendto");

	}
	else{

		printf("Parent Process has started (UDP Process) with pid: %d", getpid());

		serv_sock_fd = udpConnectServer();

		ret = recvfrom(serv_sock_fd, &serv_cFrame, SIZE_OF_COMMAND, 0, (struct sockaddr *)&cliaddr, &addrlen);
		if (ret == FAILURE)
			DEATH("readfrom");

		printf("\n************** readfrom Socket ***************\n");
		printf("seqNum: %d\n", serv_cFrame.seqNum);
		printf("inSockTyep: %d\n", serv_cFrame.inSockType);
		printf("msgCode: %d\n", serv_cFrame.mCode);
		printf("outSockType: %d\n", serv_cFrame.outSockType);
		printf("\n**************************************************\n");

		/* Construct Response Frame Structure */

		serv_rFrame.resSeqNum = serv_cFrame.seqNum;
		serv_rFrame.status = true;

		ret = sendto(serv_sock_fd, &serv_rFrame, SIZE_OF_RESPONSE, 0, (const struct sockaddr *)&cliaddr , addrlen);
		if (ret == FAILURE)
			DEATH("sendto");
	}

	return 0;
}
