#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "GPIO.h"
#include "Input.h"
// the rand need those library
#include <stdio.h>
#include <stdlib.h>

extern int8_t Stop,Leak;
int a;  //for random
	
void Motor_Init(void)
{
	PWM_Init();
	GPIOInit();  //it seems like GPIO_Init already exist
	
}

void Motor_Control_1(void)
{
	if(Stop) GPIO_Set(3);   //stop the #1 motor
	else
	{
		
	}
	
}

void Motor_Control_2(void)
{
	
	if(Stop) GPIO_Set(6);   //stop the #2 motor
	else
	{
		if(Leak == 1)	//it mean 10ml/s pumping
		{
			GPIO_Set(4);
			PWM_SetCompara(2, 16);  
		}

		else if (Leak == 2)	   //it mean random pumping
		{
			GPIO_Set(4);
			a = rand() % 200 + 20;
			PWM_SetCompara(2, a);  
		}
	}
}
void Motor_Control_2_Test(void)
{
	PWM_SetCompara(2, 500); 
	GPIO_Set(4);
}
