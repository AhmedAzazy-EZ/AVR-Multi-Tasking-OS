/*
 * lists.h
 *
 * Created: 26-Jun-21
 *  Author: Ahmed Azazy
 */ 


#ifndef LISTS_H_
#define LISTS_H_

#include "os.h"



/*************************************************
 *			Function Prototypes
 *************************************************/

void listInit(list_t * pList);

void OS_listInit(void );

void addToReady(item_t * pItem);

void timerListInit(void );

/*************************************************/


#endif /* LISTS_H_ */