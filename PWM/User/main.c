#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "PWM.h"
#include "Servo.h"
#include "GPIO.h"
#include "motor.h"
#include "Timer.h"
#include "led.h"


uint16_t i;

int main(void)
{
	GPIOInit();
	PWM_Init();
	PWM_SetCompara(1, 500);
	GPIO_Set(1);
	//PWM_SetCompara(2, 500);
	//PWM_SetCompara(4, 1500);

	//GPIO_Set(4);
	while (1)
	{
		
//		Delay_ms(1);
	}
}
