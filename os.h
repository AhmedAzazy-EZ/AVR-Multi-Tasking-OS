/*
 * os.h
 *
 * Created: 26-Jun-21 
 *  Author: Ahmed Azazy
 */ 


#ifndef OS_H_
#define OS_H_

#include "config.h"
#include "avr/io.h"
#include "threads.h"
#include "lists.h"
#include "timers.h"
#include "softwareTimers.h"

#if INCLUDE_SOFTWARETIMER == 1

extern timer_ControlBlock_t timers;	

#endif


#define LOOP	100000

/**************************************************
 *				Externs
 **************************************************/

extern item_t * pRunning;
extern stack_t idleStack;
extern TaskTCB_t idleTCB;
extern uint64_t ticks;
extern list_t timerList;
extern list_t readyList[PRIORITY_NUM ];

/**************************************************/




/*************************************************
 *			Function Prototypes
 *************************************************/

void osInit(uint8_t  );

TaskTCB_t * getIdle(void );

void startScheduler(void );

/**************************************************/

#endif /* OS_H_ */