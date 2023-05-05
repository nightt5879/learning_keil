#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"

extern uint8_t Location;
int8_t Kp = 0,Ki = 0,Kd = 0,Stop = 0,Leak = 0;	//Stop:motor switch; Leak:Leak Select
int16_t Target = 253;

/**
  * @brief  Used to Init Input 
  * @param None
  * @retval None
  */
void Input_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 |GPIO_Pin_10 |GPIO_Pin_11 |GPIO_Pin_12 |GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
  * @brief  Get_Input
  * @param None
  * @retval Input Value
  */
uint8_t Get_Input(void)
{
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8) == 0) //cursor left
	{
		Delay_ms(10);
		while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8) == 0);	
		Delay_ms(10);
		//move the cursor
		OLED_ShowString(3,Location + 2,"  "); //Empty
		if(Location == 2) Location = 22;  //To cycle cursor
		Location -= 5;
//		OLED_ShowNum(4,1,Location,2);
	}
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9) == 0)	//cursor right
	{
		Delay_ms(10);
		while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9) == 0);
		Delay_ms(10);
		//move the cursor
		OLED_ShowString(3,Location + 2,"  ");  //Empty
		if(Location == 17) Location = 2;  //To cycle cursor
		else Location += 5;
	}
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_10) == 0)	//Argument +
	{
		Delay_ms(10);
		while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_10) == 0);
		Delay_ms(10);
		if (Location == 2)	Kp += 1;
		else if(Location == 7)	Ki +=1;
		else if(Location == 12)	Kd += 1;
		else Target += 1;
		//prevent out of range
		if(Kp >99) Kp = 99;
		if(Ki >99) Ki = 99;
		if(Kd >99) Ki = 99;
		if(Target >255) Target = 255;
	}
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11) == 0)	//Argument -
	{
		Delay_ms(10);
		while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11) == 0);
		Delay_ms(10);
		if (Location == 2)	Kp -= 1;
		else if(Location == 7)	Ki -=1;
		else if(Location == 12)	Kd -= 1;
		else Target -= 1;
		//prevent out of range
		if(Kp < -99) Kp = -99;
		if(Ki < -99) Ki = -99;
		if(Kd < -99) Kd = -99;
		if(Target < 0) Target = 0;
	}
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12) == 0)	//Run & Stop
	{
		Delay_ms(10);
		while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12) == 0);
		Delay_ms(10);
		Stop += 1;
		if (Stop > 1)	Stop = 0;
	}
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15) == 0)	//Leak select
	{
		Delay_ms(10);
		while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15) == 0);
		Delay_ms(10);
		Leak += 1;
		if (Leak > 2) Leak = 0;
	}

}
