/* User Defined Header File */

#include "header.h"

/* Standard C Libraries */

#include <string.h>                     // bzero
#include <unistd.h>                     // read / write

/* System Libraries */

#include <sys/socket.h>                 // socket / bind / connect / accept
#include <sys/types.h>
#include <arpa/inet.h>                  // htons / htonl
#include <pthread.h>                    // pthread_create / pthread_join

/* MACRO Definations */

#define PORT 8000

/* Global API Definations */

/*
 *
 * Description : to start tcp connection
 *
 * in  param  : void
 * out param  : void
 * return     : int - file descriptor of created socket type
 *
 */

uint32_t tcpConnectServer(void);
uint32_t tcpConnectClient(void);

/*
 *
 * Description : to start udp connection
 *
 * in  param : struct sockaddr_in *
 * out param : void
 * return    : int - file descriptor of created socket type
 *
 */

uint32_t udpConnectServer(void);
uint32_t udpConnectClient(struct sockaddr_in *);

/*
 *
 * Description : to start tcp and udp both connections parallally
 *
 * in param : struct frame *
 *
 */

uint32_t tcp_udp_connect(struct commandframe *);


