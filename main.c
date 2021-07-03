/*
 * main.c
 *
 * Created: 23-Jun-21 
 * Author : Ahmed Azazy
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "os.h"
#include "application.h"

void task1func(void );
void task2func(void );
void task3func(void );
void task4func(void );
void task5func(void );
void task6func(void );
void task7func(void );
void task8func(void );
void task9func(void );
void task10func(void );
uint32_t i;
uint32_t j ;
uint32_t k;

stack_t task1Stack;
TaskTCB_t task1TCB;

stack_t task2Stack;
TaskTCB_t task2TCB;

stack_t task3Stack;
TaskTCB_t task3TCB;

stack_t task4Stack;
TaskTCB_t task4TCB;

stack_t task5Stack;
TaskTCB_t task5TCB;

stack_t task6Stack;
TaskTCB_t task6TCB;

stack_t task7Stack;
TaskTCB_t task7TCB;

stack_t task8Stack;
TaskTCB_t task8TCB;

stack_t task9Stack;
TaskTCB_t task9TCB;

stack_t task10Stack;
TaskTCB_t task10TCB;

mutex_t mutex1;

uint8_t wait = 0;


void ledToggle(void )
	{
		PORTA^=(1<<4);
	}
	
void ledToggle2(void )
{
	PORTA^=(1<<5);
}

void ledToggle3(void )
{
	PORTA^=(1<<6);
}

void ledToggle4(void )
{
	PORTA^=(1<<7);
}

int main(void)
{
   DDRA = 0xFF; 
   LCD_Init();
   //
   //osInit() take an unsigned integer the number of miliseconds 
   //to call the OS scheduler , In this example 1ms 
   //
   osInit(1);
   //
   //create a mutex that allows only one task can access the shared Resource (LCD)
   //
   mutexCreate(&mutex1 , 1); 
   ThreadCreate(task1func , &task1TCB , task1Stack , 1 );
   ThreadCreate(task2func , &task2TCB , task2Stack , 1);
   ThreadCreate(task3func , &task3TCB , task3Stack , 1);
   ThreadCreate(task4func , &task4TCB , task4Stack , 1 );
   ThreadCreate(task5func , &task5TCB , task5Stack , 1);
   ThreadCreate(task6func , &task6TCB , task6Stack , 1);
   ThreadCreate(task7func , &task7TCB , task7Stack , 1);
   ThreadCreate(task8func , &task8TCB , task8Stack , 1 );
   ThreadCreate(task9func , &task9TCB , task9Stack , 1);
   ThreadCreate(task10func , &task10TCB , task10Stack , 1);
   
   CreateSoftwareTimer(ledToggle , 500 , CIRCULAR );
   CreateSoftwareTimer(ledToggle2, 500, CIRCULAR );
   CreateSoftwareTimer(ledToggle3 , 500 , CIRCULAR);
   CreateSoftwareTimer(ledToggle4 , 500 , CIRCULAR );
   
   startScheduler();
    while (1) 
    {
    }
}

void task1func(void )
{
	uint8_t flag = 0;
	while(1)
	{
		for(i = 0 ; i < LOOP; i++);
		flag++;
		if(flag%10 == 0)
		{
				if(mutexTake(&mutex1 , 5000) == PASS)
				{
					LCD_String("****Thread1*****");
					mutexRelease(&mutex1);
				}
		}
		//taskAddToReady(&task2TCB);			
		}

	}


void task2func(void )
{
	uint8_t flag = 0;
	while(1)
	{
		for(j = 0 ; j < LOOP ; j++);
		flag++;
		/*
		 *Task2 delete itself every 10 Toggels
		 */
		if(flag%10 == 0)
		{
				if(mutexTake(&mutex1 , 5000) == PASS)
				{
					LCD_String("****Thread2*****");
					mutexRelease(&mutex1);
				}
			}

			//taskAddToReady(&task2TCB);
		}

	}

void task3func(void )
{
	uint8_t flag = 0;
	while(1)
	{
		for(k = 0 ; k < LOOP; k++);
		flag++;
		
		if(flag%10 == 0)
			{
				if(mutexTake(&mutex1 , 5000) == PASS)
				{
				LCD_String("****Thread3*****");
				mutexRelease(&mutex1);
				}
			}
			//taskAddToReady(&task2TCB);
		}
	}
	
void task4func(void )
{
	uint8_t flag = 0;
	while(1)
	{
		for(k = 0 ; k < LOOP; k++);
		flag++;
		
		if(flag%10 == 0)
		{
			if(mutexTake(&mutex1 , 5000) == PASS)
			{
				LCD_String("****Thread4*****");
				mutexRelease(&mutex1);
			}
		}
		//taskAddToReady(&task2TCB);
	}
}

void task5func(void )
{
	uint8_t flag = 0;
	while(1)
	{
		for(k = 0 ; k < LOOP; k++);
		flag++;
		
		if(flag%10 == 0)
		{
			if(mutexTake(&mutex1 , 5000) == PASS)
			{
				LCD_String("****Thread5*****");
				mutexRelease(&mutex1);
			}
		}
		//taskAddToReady(&task2TCB);
	}
}

void task6func(void )
{
	uint8_t flag = 0;
	while(1)
	{
		for(k = 0 ; k < LOOP; k++);
		flag++;
		
		if(flag%10 == 0)
		{
			if(mutexTake(&mutex1 , 5000) == PASS)
			{
				LCD_String("****Thread6*****");
				mutexRelease(&mutex1);
			}
		}
		//taskAddToReady(&task2TCB);
	}
}

void task7func(void )
{
	uint8_t flag = 0;
	while(1)
	{
		for(k = 0 ; k < LOOP; k++);
		flag++;
		
		if(flag%10 == 0)
		{
			if(mutexTake(&mutex1 , 5000) == PASS)
			{
				LCD_String("****Thread7*****");
				mutexRelease(&mutex1);
			}
		}
		//taskAddToReady(&task2TCB);
	}
}

void task8func(void )
{
	uint8_t flag = 0;
	while(1)
	{
		for(k = 0 ; k < LOOP; k++);
		flag++;
		
		if(flag%10 == 0)
		{
			if(mutexTake(&mutex1 , 5000) == PASS)
			{
				LCD_String("****Thread8*****");
				mutexRelease(&mutex1);
			}
		}
		//taskAddToReady(&task2TCB);
	}
}

void task9func(void )
{
	uint8_t flag = 0;
	while(1)
	{
		for(k = 0 ; k < LOOP; k++);
		flag++;
		
		if(flag%10 == 0)
		{
			if(mutexTake(&mutex1 , 5000) == PASS)
			{
				LCD_String("****Thread9*****");
				mutexRelease(&mutex1);
			}
		}
		//taskAddToReady(&task2TCB);
	}
}

void task10func(void )
{
	uint8_t flag = 0;
	while(1)
	{
		for(k = 0 ; k < LOOP; k++);
		flag++;
		
		if(flag%10 == 0)
		{
			if(mutexTake(&mutex1 , 5000) == PASS)
			{
				LCD_String("****Thread10****");
				mutexRelease(&mutex1);
			}
		}
		//taskAddToReady(&task2TCB);
	}
}