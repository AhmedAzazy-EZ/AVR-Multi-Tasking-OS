/*
 * lists.c
 *
 * Created: 26-Jun-21
 *  Author: Ahmed Azazy
 */ 
#include <avr/io.h>
#include <stdio.h>
#include "os.h"

list_t readyList[PRIORITY_NUM];
uint64_t ticks=0;
list_t timerList;

void listInit(list_t * pList)
	{
		pList->pIndex = &pList->End;
		pList->End.pList = pList;
		pList->End.pNext = &pList->End;
		pList->End.pPrev = &pList->End;
		pList->End.pTCB = NULL;
		pList->pIndex = &pList->End;
		pList->numOfItems = 0;
	}
	
void OS_listInit(void )
	{
		for(uint8_t i = 0 ; i < PRIORITY_NUM  ; i++)
			{
				listInit(&readyList[i]);
			}
	}
	
void addToReady(item_t * pItem )
{
	list_t *pList = pItem->pList;
	item_t *addTo = pList->End.pPrev;
	addTo->pNext = pItem;
	pItem->pNext = &pList->End;
	pList->End.pPrev = pItem;
	pItem->pPrev = addTo;
	
	pList->numOfItems++;
}

void timerListInit(void )
{
	timerList.pIndex = &timerList.End;
	timerList.End.pList = &timerList;
	timerList.End.pNext = &timerList.End;
	timerList.End.pPrev = &timerList.End;
	timerList.End.pTCB = NULL;
	timerList.End.timerDelay = 0xFFFFFFFFFFFFFFFF;
	timerList.numOfItems = 0;
}