/*************** Library Inclusion **************/

#include "msgQ.h"

/*************** Function Defination ***************/

mqd_t msgQ_open(const char *mqName, uint32_t mqSize){
	
	struct mq_attr attr;
	
	int mqFlag      = O_RDWR | O_CREAT;
	mode_t mqMode   = S_IRWXU;
	attr.mq_msgsize = mqSize;

	return mq_open(mqName, mqFlag, mqMode, &attr);
}

int msgQ_send(mqd_t mqd, const char *mPtr, size_t mPtr_size){
	return mq_send(mqd, mPtr, mPtr_size, 0);
}

ssize_t msgQ_receive(mqd_t mqd, char *mPtr, size_t mPtr_size){
	return mq_receive(mqd, mPtr, mPtr_size, NULL);
}

int msgQ_unlink(const char *mqName){
	return mq_unlink(mqName);
}
