/*
 * mutex.c
 *
 * Created: 01-Jul-21
 *  Author: Ahmed Azazy
 */ 

#include "os.h"
#include <stdlib.h>

void mutexCreate(mutex_t *mutex , uint8_t initialValue)
	{
		for(int i = 0 ; i < PRIORITY_NUM ; i++)
		{
		mutex->waitQueue[i] = malloc(sizeof(eventItem_t * ) * 10 );
		mutex->head[i] = 0;
		mutex->tail[i] = 0;
		mutex->numOfWaitingItems[i] = 0;			
		}
		mutex->value = 	initialValue;
	}
	
status_t mutexTake(mutex_t * mutex , uint64_t delayTime)
	{
		cli();
		if(mutex->value > 0)
			{
				mutex->value--;
				sei();
				return PASS;
			}
			
			else 
			{
				mutexEnqueue(mutex , &pRunning->pTCB->event );
				taskDelay(NULL , delayTime);
			}
			
			cli();
			if(mutex->value > 0)
				{
					mutex->value--;
					sei();
					return PASS;
				}
			sei();
			return FAIL;
	}


void mutexEnqueue(mutex_t * mutex ,eventItem_t * item)
	{
		uint8_t priority = item->pTCB->priority;
		if(mutex->numOfWaitingItems[priority] == 0)
			{
				mutex->waitQueue[priority][0] = item;
				mutex->head[priority] = 0;
				mutex->tail[priority] = 0;
				mutex->numOfWaitingItems[priority]++;
			}
			
			else if(mutex->numOfWaitingItems[priority] < 10)
			{
				mutex->tail[priority]++;
				if(mutex->tail[priority] > 9 )
					mutex->tail[priority] = 0;
				
				mutex->waitQueue[priority][mutex->tail[priority]] = item;
				mutex->numOfWaitingItems[priority]++;
			}
			
			else 
			{
				return ;
			}
			
	}

eventItem_t * mutexDequeue(mutex_t * mutex)
{
	for(int i = 0 ; i < PRIORITY_NUM ; i++)
	{
	if(mutex->numOfWaitingItems[i] > 0)
	{
		uint8_t temp = mutex->head[i];
		mutex->head[i] = mutex->head[i] + 1;
		if(mutex->head[i] > 9)
		mutex->head[i] = 0;
		
		mutex->numOfWaitingItems[i]--;
		eventItem_t * item = mutex->waitQueue[i][temp];
		item->queueIndex = 0;
		return item;
	}		
	}		
		return NULL;
}

void mutexRelease(mutex_t * mutex)
	{
		cli();
		mutex->value ++;
		eventItem_t * item = mutexDequeue(mutex);
		if(item != NULL)
		{
			
		if(item->pTCB->TCB_Item.pList == &timerList)
		{
			taskDelete(item->pTCB);
			taskAddToReady(item->pTCB);
		}
		}
		sei();
	}