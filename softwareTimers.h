/*
 * softwareTimers.h
 *
 * Created: 03-Jul-21 
 *  Author: Ahmed Azazy
 */ 


#ifndef SOFTWARETIMERS_H_
#define SOFTWARETIMERS_H_
#include "config.h"

typedef uint8_t timerHandle_t;

typedef void (*timerCallBack_t) (void );

typedef enum timer_repetition
{
	ONE_SHOT = 0 ,
	CIRCULAR = 1,
	NOT_SET = 2,
	IDLE = 3
}timer_repetition_t;

typedef struct timers_ControlBlock
{
	timerCallBack_t callback[NUM_OF_CALL_TIMERS];
	uint64_t timerDelay[NUM_OF_CALL_TIMERS];
	uint64_t delayTime[NUM_OF_CALL_TIMERS];
	timer_repetition_t repetition[NUM_OF_CALL_TIMERS];
	uint8_t Num_Of_busyTimers;	
}timer_ControlBlock_t;


void softwareTimers_Init(void );

timerHandle_t CreateSoftwareTimer(timerCallBack_t , uint64_t delay , timer_repetition_t repeat);

void runSoftwareTimers(void );

void TimerDelete(timerHandle_t ID);

void TimerSetOneShot(timerHandle_t ID);

void TimerSetCircular(timerHandle_t ID);

#endif /* SOFTWARETIMERS_H_ */