/* User Defined Libraries */

#include "sock.h"

/* Function Declaration */

static void *tcp_thread(void *);
static void *udp_thread(void *);

uint32_t tcpConnectServer(){

	uint32_t sockfd;

	struct sockaddr_in servaddr, cliaddr;
	socklen_t socklen = sizeof(struct sockaddr_in);


	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		DEBUG_ERROR("socket", __func__);

	bzero(&servaddr, socklen);
	bzero(&cliaddr , socklen);

	servaddr.sin_family = AF_INET;                      // for IPv4
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);       // refers to local host 127.0.0.1
	servaddr.sin_port = htons(PORT1);

	if(bind(sockfd, (struct sockaddr *)&servaddr, socklen) == FAILURE)
		DEBUG_ERROR("bind", __func__);

	if(listen(sockfd, 5) == FAILURE)
		DEBUG_ERROR("listen", __func__);

	if((sockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &socklen)) == FAILURE)
		DEBUG_ERROR("accept", __func__);

	printf("File Descriptor: %d...\n", sockfd);
	printf("Got Connection from %s....\n", inet_ntoa(cliaddr.sin_addr));

	return sockfd;
}

uint32_t tcpConnectClient(){

	uint32_t sockfd;

	struct sockaddr_in servaddr;
	socklen_t addrlen = sizeof(servaddr);

	if((sockfd = socket(AF_INET,SOCK_STREAM, 0)) == FAILURE)
		DEBUG_ERROR("socket", __func__)

	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;                      // for IPv4
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);       // refers to local host 0.0.0.0
	servaddr.sin_port = htons(PORT1);


	if(connect(sockfd, (struct sockaddr *)&servaddr, addrlen) == FAILURE)
		DEBUG_ERROR("connect", __func__);

	return sockfd;
}

uint32_t udpConnectServer(){
	uint32_t sockfd;
	struct sockaddr_in servaddr;
	socklen_t addrlen = sizeof(struct sockaddr_in);

	bzero(&servaddr, addrlen);

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == FAILURE)
		DEBUG_ERROR("socket", __func__);

	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	servaddr.sin_port        = htons(PORT2);

	if(bind(sockfd, (const struct sockaddr *)&servaddr, addrlen) == FAILURE)
		DEBUG_ERROR("bind", __func__);

	return sockfd;
}

uint32_t udpConnectClient(struct sockaddr_in *udpPtr){
	uint32_t sockfd;
	struct sockaddr_in servaddr;
	socklen_t addrlen = sizeof(struct sockaddr_in);

	bzero(&servaddr, addrlen);

	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == FAILURE)
		DEBUG_ERROR("socket", __func__);

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
		DEBUG_ERROR("pthread_create_tcpConnect", __func__);

	ret = pthread_create(&p_udp, NULL, udp_thread, NULL);
	if (ret == FAILURE)
		DEBUG_ERROR("pthread_create_udpConnect", __func__);

	ret = pthread_join(p_tcp, NULL);
	if (ret == FAILURE)
		DEBUG_ERROR("pthread_join_tcpConnect", __func__);

	ret = pthread_join(p_udp, NULL);
	if (ret == FAILURE)
		DEBUG_ERROR("pthread_join_udpConnect", __func__);

	return ret;

}

static void *tcp_thread(void *targ){
	tcpConnectServer();
	return NULL;
}

static void *udp_thread(void *uarg){
	udpConnectServer();
	return NULL;
}
