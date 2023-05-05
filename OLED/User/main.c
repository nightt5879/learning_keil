#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Input.h"
#include "OLED.h"
#include "PID_Show.h"
#include "Timer.h"

uint16_t Num = 0;
uint8_t Flashing = 0,Location = 2; //Flashing: on&off  Location: where to on&off
uint8_t Loc = 0;  //Using for Flashing


int main(void)
{
	PID_Show_Init(1);
	Timer_Init();
	Input_Init();
	while (1)
	{
		Get_Input();  //Get the button input 
	}
}


//Timer3 using for flashing button
void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
	{
		PID_Show();
		if (Flashing == 0)  //on
		{
			Flashing = 1;
			if(Location == 17) OLED_ShowString(1,15,"<");  //select the target
			else 
			OLED_ShowString(3,Location + 2,"^^");
		}
		else	//off
		{
			Flashing = 0;
			OLED_ShowString(1,15," ");
			OLED_ShowString(3,Location + 2,"  ");
		}
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}

