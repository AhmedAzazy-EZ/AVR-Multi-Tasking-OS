/*
 * softwareTimers.c
 *
 * Created: 03-Jul-21
 *  Author: Ahmed Azazy
 */ 

#include "os.h"
#include <stdlib.h>

#if INCLUDE_SOFTWARETIMER == 1

void softwareTimers_Init(void )
{
	for(int i = 0 ; i < NUM_OF_CALL_TIMERS ; i ++)
		{
			timers.callback[i] = NULL;
			timers.repetition[i] = NOT_SET;
			timers.delayTime[i] = 0;
			timers.timerDelay[i] = 0xFFFFFFFFFFFFFFFF;
		}
		timers.Num_Of_busyTimers = 0;
}


timerHandle_t CreateSoftwareTimer(timerCallBack_t callback , uint64_t delay , timer_repetition_t repeat)
{
	//
	//Note that : the user has to check if the timer is successfully Created or Not
	//
	if(timers.Num_Of_busyTimers == NUM_OF_CALL_TIMERS)
		return 0;
		
	else 
		{
			timers.Num_Of_busyTimers ++;
			for(uint8_t i = 0 ; i < NUM_OF_CALL_TIMERS ; i++)
				{
					if(timers.repetition[i] == NOT_SET)
						{
							timers.callback[i] = callback;
							timers.repetition[i] = repeat;
							timers.timerDelay[i] = ticks + delay;
							timers.delayTime[i] = delay;
							return i+1;
						}
				}
		}
		
	return 0;
}


 void runSoftwareTimers(void )
	{
		asm("mov r1 , 0");
		for(volatile uint8_t  i = 0x0; i < NUM_OF_CALL_TIMERS ; i++)
			{
				if((timers.repetition[i] == IDLE) ||(timers.repetition[i] == NOT_SET))
					continue ;
					
				else 
				{
					if(timers.timerDelay[i] == ticks)
						{
							timers.callback[i]();							
							if(timers.repetition[i] == ONE_SHOT)
								timers.repetition[i] = IDLE;
								
							else
								timers.timerDelay[i] = ticks + timers.delayTime[i];
						}
				}
			}
	}
	
	
void TimerDelete(timerHandle_t ID)
	{
		if(ID == 0 || ID > NUM_OF_CALL_TIMERS) 
			return ;
			
		else 
			{
				ID--;
				timers.callback[ID] = NULL;
				timers.delayTime[ID] = 0;
				timers.timerDelay[ID] = 0xFFFFFFFFFFFFFFFF;
				timers.repetition[ID] = NOT_SET;
				timers.Num_Of_busyTimers--;
			}
	}
	
void TimerSetOneShot(timerHandle_t ID)
{
		if(ID == 0 || ID > NUM_OF_CALL_TIMERS)
		return ;
		
		else
		{
			ID--;
			timers.repetition[ID] = ONE_SHOT;
		}
}

void TimerSetCircular(timerHandle_t ID)
{
	if(ID == 0 || ID > NUM_OF_CALL_TIMERS)
	return ;
	
	else
	{
		ID--;
		timers.repetition[ID] = CIRCULAR;
	}
}

void TimerSetDelayTime(timerHandle_t ID , uint64_t delay)
	{
	if(ID == 0 || ID > NUM_OF_CALL_TIMERS)
	return ;
	
	else
	{
		ID--;
		timers.delayTime[ID] = delay;
	}
	}

#endif