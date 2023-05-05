#include "stm32f10x.h"                  // Device header
#include "OLED.h"

extern int8_t Kp,Ki,Kd,Stop,Leak,Location;
extern uint8_t Target;

void PID_Show_Init(uint8_t Location)
{
	OLED_Init();
	OLED_ShowString(1,1,"PID");
	OLED_ShowString(1,5,"Target:");
	OLED_ShowString(2,Location,"P:");
	OLED_ShowSignedNum(2, Location + 2, 0, 2);
	OLED_ShowString(2,Location + 5,"I:");
	OLED_ShowSignedNum(2, Location + 7, 0, 2);
	OLED_ShowString(2,Location + 10,"D:");
	OLED_ShowSignedNum(2, Location + 12, 0, 2);
}


void PID_Show()
{
	//Prevent parameters out of range

	
	OLED_ShowSignedNum(2, 3, Kp, 2);
	OLED_ShowSignedNum(2, 8, Ki, 2);
	OLED_ShowSignedNum(2, 13, Kd, 2);
	OLED_ShowNum(1, 12, Target, 3);
	
	if(Stop == 1) OLED_ShowString(4,3,"Stop");
	else	OLED_ShowString(4,3,"    ");
	if(Leak == 0)	OLED_ShowString(4,9,"Close ");
	else if(Leak == 1)	OLED_ShowString(4,9,"10ml/s");
	else OLED_ShowString(4,9,"Random");
}
