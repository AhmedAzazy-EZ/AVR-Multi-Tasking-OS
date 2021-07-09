/*
 * timers.c
 *
 * Created: 23-Jun-21
 *  Author: Ahmed Azazy
 */ 
 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>
#include <stdio.h>
#include "os.h"

void timer0Init(uint8_t ms )
{
	/*
	 *Clock prescaler 1024 ~= 1000
	 *clear timer on comapre match
	 */
	TCCR0 &=~(0xFF);
	TCCR0|= 0xD; 
	
	uint16_t TimerClk = (F_CPU) / 1024;
	
	//
	//*************set wait time********
	//if less than 31 ms , then acceptable 
	//if greater than 31 , then set it to maximum
	//******************************
	// 
	
	uint8_t maxTicks = 255 / (TimerClk / 1000);
	if(ms <= maxTicks )
	OCR0 = ms*(TimerClk / 1000);
	else 
	OCR0 = maxTicks;
	
	//
	//Enable clear timer on capture match interrupt
	//
	TIMSK |=(1<<1);
}


ISR(TIMER0_COMP_vect ,  ISR_NAKED)
{
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
	
	
	asm("call refreshTimerList");
	
	#if INCLUDE_SOFTWARETIMER == 1

	runSoftwareTimers();

	#endif
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


