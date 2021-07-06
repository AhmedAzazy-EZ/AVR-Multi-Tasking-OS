/*
 * threads.c
 *
 * Created: 23-Jun-21
 *  Author: Ahmed Azazy
 */ 

#include <avr/io.h>
#include <string.h>
#include "os.h"

uint8_t loop;

item_t * pRunning;

void ThreadCreate(taskFunc_t funcPtr , TaskTCB_t * TCB , stack_t stackptr , uint8_t priority )
	{
		
		TCB->stackPtr = ((uint16_t) stackptr) + (STACK_SIZE - 1);
		
		TCB->priority = priority;
		
		funcPtr = (taskFunc_t ) (((uint16_t )funcPtr) + 2);
		*((uint8_t *) (TCB->stackPtr - 1)) =(((uint16_t ) funcPtr) >> 8);
		*((uint8_t *) (TCB->stackPtr )) = ((uint16_t) funcPtr);
		//set status register
		*((uint8_t * ) (TCB->stackPtr -3)) = 0x82;
		
		//
		//Next line to make sure the top of stack is pushed properly
		//at the beginning 
		//
		*((uint8_t * ) (TCB->stackPtr - 34)) = 0x33;
		
		
		TCB->stackPtr = TCB->stackPtr - 35;
		TCB->TCB_Item.pTCB = TCB;
		TCB->TCB_Item.pList = &readyList[priority];
		TCB->TCB_Item.pList = &readyList[priority];
		
		TCB->event.pTCB = TCB;
		TCB->event.queueIndex = -1;
		
		addToReady(&TCB->TCB_Item);
		
	}
	
	
TaskTCB_t * getRunning(void )
{
	return pRunning->pTCB;
}

TaskTCB_t * getNext(void)
{

	for( loop = 0 ; loop < PRIORITY_NUM  ; loop++)
		{
			if(readyList[loop].numOfItems > 0)
				{
					readyList[loop].pIndex = readyList[loop].pIndex->pNext;
					
					while(readyList[loop].pIndex == &readyList[loop].End)
						{
							readyList[loop].pIndex = readyList[loop].pIndex->pNext;
						}
					pRunning = 	readyList[loop].pIndex;
					return readyList[loop].pIndex->pTCB;
				}
		}
	
	pRunning = &idleTCB.TCB_Item;
	return &idleTCB;
}

void taskDelete(TaskTCB_t * delete)
{
	cli();
	if(delete == NULL)
		{
			delete = pRunning->pTCB;
		}
	
	item_t *deleteItem = &delete->TCB_Item;
	if(deleteItem == deleteItem->pList->pIndex)
		{
			deleteItem->pList->pIndex = deleteItem->pPrev;
		}
	deleteItem->pPrev->pNext = deleteItem->pNext;
	deleteItem->pNext->pPrev = deleteItem->pPrev; 
	deleteItem->pPrev = NULL;
	deleteItem->pNext = NULL;
	deleteItem->pList->numOfItems --;
	deleteItem->pList = NULL;
}

void taskAddToReady(TaskTCB_t * TCB)
	{
		
	cli();
	/*
	 *First We are gonna check if the task is not in the ready List
	 * if Not then add it , else return
	 */
	
	if(TCB->TCB_Item.pList == &readyList[TCB->priority])
		{
			sei();
			return ;
		}
	item_t *pItem = &TCB->TCB_Item;
	list_t *pList = &readyList[TCB->priority];
	item_t *addTo = pList->End.pPrev;
	addTo->pNext = pItem;
	pItem->pNext = &pList->End;
	pList->End.pPrev = pItem;
	pItem->pPrev = addTo;
	pItem->pList = 	&readyList[TCB->priority];
	pList->numOfItems++;	
	sei();
	}
	
void taskDelay(TaskTCB_t * TCB ,  uint64_t delay)
	{
		cli();
		if(TCB == NULL)
			{
				TCB = pRunning->pTCB;
			}
		TCB->TCB_Item.timerDelay = delay + ticks;
		taskDelete(TCB);
		taskAddToTimerList(&TCB->TCB_Item);
		asm("call scheduler");
	}
	
void taskAddToTimerList(item_t * pItem)
{
	uint64_t targetItemDelay = pItem->timerDelay; 
	item_t *compareItem = timerList.pIndex;
	for(;;)
		{
			if(targetItemDelay <= compareItem->timerDelay)
				{
					pItem->pNext = compareItem->pNext;
					compareItem->pNext->pPrev = pItem;
					pItem->pPrev = compareItem;
					compareItem->pNext = pItem;
					
					if(compareItem == timerList.pIndex)
						timerList.pIndex = pItem;
					timerList.numOfItems++;
					pItem->pList = &timerList;
					break;
				}
				
				else
				{
					compareItem = compareItem->pPrev;
				}
		}
}

void refreshTimerList(void )
	{
		ticks++;
		if(timerList.numOfItems > 0)
			{
				while(timerList.pIndex->timerDelay == ticks)
					{
						item_t * tempHold = timerList.pIndex;
						deleteFromTimerList(tempHold->pTCB);
						taskAddToReady(tempHold->pTCB);			
					}
			}
	}
	
void deleteFromTimerList(TaskTCB_t * TCB)
	{
		item_t * deleteItem = &TCB->TCB_Item;
		timerList.pIndex = deleteItem->pPrev;
		deleteItem->pPrev->pNext = &timerList.End;
		timerList.End.pPrev = deleteItem->pPrev;
		deleteItem->pNext = NULL;
		deleteItem->pPrev = NULL;
		timerList.numOfItems--;
		deleteItem->pList = NULL;
		
	}

void taskSuspend(TaskTCB_t * TCB)
{
	cli();
	if(TCB == NULL)
		TCB = pRunning->pTCB;
	taskDelete(TCB);
	asm("call scheduler");
}
	
__attribute__((naked)) void scheduler(void )
{
	asm("cli");
	asm("push r0");
	asm("in r0 , 0x3f");
	asm("push r0");
	asm("push r1");
	asm("push r2");
	asm("push r3");
	asm("push r4");
	asm("push r5");
	asm("push r6");
	asm("push r7");
	asm("push r8");
	asm("push r9");
	asm("push r10");
	asm("push r11");
	asm("push r12");
	asm("push r13");
	asm("push r14");
	asm("push r15");
	asm("push r16");
	asm("push r17");
	asm("push r18");
	asm("push r19");
	asm("push r20");
	asm("push r21");
	asm("push r22");
	asm("push r23");
	asm("push r24");
	asm("push r25");
	asm("push r26");
	asm("push r27");
	asm("push r28");
	asm("push r29");
	asm("push r30");
	asm("push r31");
	asm("call getRunning");
	asm("mov XL , r24");
	asm("mov XH , r25");
	asm("in r0 , 0x3d");
	asm("in r1 , 0x3e");
	asm("st X+ , r0");
	asm("st X , r1");
	
	//asm("call refreshTimerList");
	//;;current Context has been stored;;
	//;
	//;
	//;
	//;
	//;;Now , load Next context;;
	
	asm("ldi r16 , 0");
	asm("mov r1 , r16");
	asm("call getNext");
	asm("mov XL , r24");
	asm("mov XH , r25");
	asm("ld r0 , X+");
	asm("ld r1 , X");
	asm("out 0x3d, r0");
	asm("out	0x3e , r1");
	asm("nop");
	asm("pop r31");
	asm("pop r30");
	asm("pop r29");
	asm("pop r28");
	asm("pop r27");
	asm("pop r26");
	asm("pop r25");
	asm("pop r24");
	asm("pop r23");
	asm("pop r22");
	asm("pop r21");
	asm("pop r20");
	asm("pop r19");
	asm("pop r18");
	asm("pop r17");
	asm("pop r16");
	asm("pop r15");
	asm("pop r14");
	asm("pop r13");
	asm("pop r12");
	asm("pop r11");
	asm("pop r10");
	asm("pop r9");
	asm("pop r8");
	asm("pop r7");
	asm("pop r6");
	asm("pop r5");
	asm("pop r4");
	asm("pop r3");
	asm("pop r2");
	asm("pop r1");
	asm("pop r0");
	asm("out 0x3f , r0");
	asm("pop r0");
	asm("reti");
}