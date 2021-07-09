/*
 * os.c
 *
 * Created: 26-Jun-21
 *  Author: Ahmed Azazy
 */

#include "os.h"

#if INCLUDE_SOFTWARETIMER == 1
	timer_ControlBlock_t timers;
#endif


uint64_t idletest;
stack_t idleStack;
TaskTCB_t idleTCB;
extern item_t * pRunning;
void idleTask(void )
{
	while(1)
	{
	}
}

void osInit(uint8_t ms )
{
	OS_listInit();
	ThreadCreate(idleTask , &idleTCB , idleStack , 4);
	readyList[PRIORITY_NUM - 1].numOfItems = 0;
	pRunning = &idleTCB.TCB_Item;
	#if INCLUDE_SOFTWARETIMER == 1
	softwareTimers_Init();
	#endif
	timerListInit();
	timer0Init(ms);
}

TaskTCB_t * getIdle(void )
{
		return &idleTCB;
}
