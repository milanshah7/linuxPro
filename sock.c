/* User Defined Libraries */

#include "sock.h"

/* Function Declaration */

static void *tcp_thread(void *);
static void *udp_thread(void *);

uint32_t tcpConnectServer(){

	uint32_t sockfd;
	int32_t ret = SUCCESS;

	struct sockaddr_in servaddr, cliaddr;
	socklen_t socklen = sizeof(struct sockaddr_in);


	ret = sockfd = socket(AF_INET, SOCK_STREAM, 0);           // for TCP Socket
	if(ret == FAILURE)
		DEBUG_ERROR("socket");

	bzero(&servaddr, socklen);
	bzero(&cliaddr , socklen);

	servaddr.sin_family = AF_INET;                      // for IPv4
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);       // refers to local host 127.0.0.1
	servaddr.sin_port = htons(PORT1);

	ret = bind(sockfd, (struct sockaddr *)&servaddr, socklen);
	if(ret == FAILURE)
		perror("bind");

	ret = listen(sockfd, 5);
	if(ret == FAILURE)
		perror("listen");

	ret = sockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &socklen);
	if(ret == FAILURE)
		perror("accept");

	printf("File Descriptor: %d...\n", ret);
	printf("Got Connection from %s....\n", inet_ntoa(cliaddr.sin_addr));

	return ret;
}

uint32_t tcpConnectClient(){

	uint32_t sockfd;
	int32_t ret = SUCCESS;

	struct sockaddr_in servaddr;
	socklen_t addrlen = sizeof(servaddr);

	ret = sockfd = socket(AF_INET,SOCK_STREAM, 0);          // for tcp socket
	if(ret == FAILURE)
		DEBUG_ERROR("socket")

			bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;                      // for IPv4
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);       // refers to local host 0.0.0.0
	servaddr.sin_port = htons(PORT1);

	ret = connect(sockfd, (struct sockaddr *)&servaddr, addrlen);
	if(ret = FAILURE)
		DEBUG_ERROR("connect");

	return sockfd;
}

uint32_t udpConnectServer(){
	uint32_t sockfd, ret = 0;
	struct sockaddr_in servaddr;
	socklen_t addrlen = sizeof(struct sockaddr_in);

	bzero(&servaddr, addrlen);

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);           // for UDP SOcket
	if (sockfd == FAILURE)
		perror("socket");

	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	servaddr.sin_port        = htons(PORT2);

	ret = bind(sockfd, (const struct sockaddr *)&servaddr, addrlen);
	if(ret == FAILURE)
		perror("bind");

	return sockfd;
}

uint32_t udpConnectClient(struct sockaddr_in *udpPtr){
	uint32_t sockfd;
	struct sockaddr_in servaddr;
	socklen_t addrlen = sizeof(struct sockaddr_in);

	bzero(&servaddr, addrlen);

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);           // for UDP Socket
	if(sockfd == FAILURE)
		perror("socket");

	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	servaddr.sin_port        = htons(PORT2);

	udpPtr = &servaddr;

	return sockfd;
}

uint32_t tcp_udp_connect(struct commandframe *tcpUdpPtr){
	pthread_t p_tcp, p_udp;
	uint32_t ret;

	ret = pthread_create(&p_tcp, NULL, tcp_thread, NULL);
	if (ret == FAILURE)
		perror("pthread_create_tcpConnect");

	ret = pthread_create(&p_udp, NULL, udp_thread, NULL);
	if (ret = FAILURE)
		perror("pthread_create_udpConnect");

	ret = pthread_join(p_tcp, NULL);
	if (ret = FAILURE)
		perror("pthread_join_tcpConnect");

	ret = pthread_join(p_udp, NULL);
	if (ret = FAILURE)
		perror("pthread_join_udpConnect");

	return ret;

}

static void *tcp_thread(void *targ){
	(void)tcpConnectServer();
}

static void *udp_thread(void *uarg){
	(void)udpConnectServer();
}
