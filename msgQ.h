/************* Library Inclusion ****************/

#include "header.h"
#include <mqueue.h>

/************** MACRO Defination ****************/

#define MSG_ID                 1
#define MSG_ID_LINKED_LIST     (MSG_ID << 0)
#define MSG_ID_PTHREAD_OPS     (MSG_ID << 1)
#define MSG_ID_FORK_OPS        (MSG_ID << 2)
#define MSG_ID_IPC_OPS         (MSG_ID << 3)

#define MSGQ_NAME              "/myqueue"
#define MSGQ_DATA_SIZE         sizeof(struct msgQ_struct)

/*************** Variable Declarations ***************/

struct msgQ_struct{
	uint32_t msgid;
	bool bstatus;
	union payloadData msgData;
};

/************* Function Declarations *************/

/*
 * msgQ_open - to open a message queue
 *
 * in param   :
 * 		mqName - message queue name
 * 		mqSize - Data size which to be tranmissted over message queue
 * out param  : 
 * 		None
 * return val :
 * 		message queue descriptor on success, else -1 to indicate failure
 *
 */

mqd_t msgQ_open(const char *mqName, uint32_t mqSize);

/*
 * msgQ_send - to send some data over message queue
 *
 * in param   : 
 * 		mqd       - message queue descriptor
 * 		mPtr      - pointer to the data which needs to be transmitted
 * 		mPtr_size - size of the data
 * out param  : 
 * 		None
 * return val : 
 * 		0 on success, else -1 to indicate failure
 *
 */

int msgQ_send(mqd_t mqd, const char *mPtr, size_t mPtr_size);

/*
 * msgQ_receive - to receive a message over message queue
 *
 * in param   : 
 * 		mqd       - message queue descriptor
 * 		mPtr      - pointer to the data which is to be received
 * 		mPtr_size - size of the data
 * out param  : 
 * 		None
 * return val :
 * 		no. of bytes in the received message, else -1 to indicate failure
 *
 */

ssize_t msgQ_receive(mqd_t mqd, char *mPtr, size_t mPtr_size);

/*
 * msgQ_unlink - to remove a message queue
 *
 * in param   :
 * 		mqName - message queue name
 * out param  :
 * 		None
 * return val :
 * 		0 on success, else -1 to indicate failure
 *
 */

int msgQ_unlink(const char *mqName);
