/*
 * mutex.h
 *
 * Created: 01-Jul-21
 *  Author: Ahmed Azazy
 */ 

#ifndef MUTEX_H_
#define MUTEX_H_

typedef enum status
{
	FAIL = 0 ,
	PASS
}status_t;

typedef struct mutex mutex_t;
typedef struct eventItem eventItem_t;

struct eventItem
{
	uint8_t queueIndex;
	TaskTCB_t * pTCB;
};


struct mutex
{
	eventItem_t ** waitQueue[PRIORITY_NUM];
	uint8_t head[PRIORITY_NUM ];
	uint8_t tail[PRIORITY_NUM ];
	uint8_t value;
	uint8_t numOfWaitingItems[PRIORITY_NUM ];	
};



void mutexCreate(mutex_t *mutex , uint8_t initialValue);

status_t mutexTake(mutex_t * mutex , uint64_t delayTime);

void mutexEnqueue(mutex_t * mutex ,eventItem_t * item);

eventItem_t * mutexDequeue(mutex_t * mutex);

void mutexRelease(mutex_t * mutex);

#endif /* MUTEX_H_ */