/*
 * threads.h
 *
 * Created: 23-Jun-21
 *  Author: Ahmed Azazy
 */ 


#ifndef THREADS_H_
#define THREADS_H_


typedef struct TaskTCB TaskTCB_t;
#include "mutex.h"
/************************************
*			Typedefs
***********************************/
typedef void (*taskFunc_t)(void );
typedef uint8_t stack_t[STACK_SIZE];
typedef struct item item_t;
typedef struct list list_t;

struct item
{
	struct item * pNext;
	struct item *pPrev;
	list_t * pList;
	TaskTCB_t * pTCB;
	uint64_t timerDelay;
};

struct TaskTCB
{
	uint16_t stackPtr;
	uint8_t priority;
	item_t TCB_Item;
	eventItem_t event;
};

struct list
{
	item_t * pIndex;
	item_t End;
	uint8_t numOfItems;
};

/*************************************************/


/*************************************************
 *			Function Prototypes
 *************************************************/

void ThreadCreate(taskFunc_t funcPtr , TaskTCB_t * TCB , stack_t stackptr , uint8_t priority );

TaskTCB_t * getRunning(void );

TaskTCB_t * getNext(void);

void taskDelete(TaskTCB_t * delete);

void taskAddToReady(TaskTCB_t * TCB);

void taskAddToTimerList(item_t * pItem);

void taskSuspend(TaskTCB_t * TCB);

void refreshTimerList(void );

void taskDelay(TaskTCB_t * TCB ,  uint64_t delay);

void deleteFromTimerList(TaskTCB_t * TCB);

/************************************************/

#endif /* THREADS_H_ */