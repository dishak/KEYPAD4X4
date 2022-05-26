
#include "lcd.h"
#include "delay.h"
#include <stdint.h>
#include <stdio.h>
#include "keypad_init.h"
GPIO_Handle_t Keypad_Config;


 void KEYPAD_PINS_CONFIG()
{
	Keypad_Config.pGPIOx=KEYPAD_GPIO_PORT;
	Keypad_Config.GPIO_PinConfig.GPIO_PinOPType=GPIO_OP_TYPE_PP;
	Keypad_Config.GPIO_PinConfig.GPIO_PinPuPdControl=GPIO_PIN_PD;
	for(int i=0;i<=7;i++)
	{
		if(i<=3)			//making PB0-PB3 as input connected to C1-C4
		{
		Keypad_Config.GPIO_PinConfig.GPIO_PinMode=GPIO_MODE_IN;
		Keypad_Config.GPIO_PinConfig.GPIO_PinNumber=i;
		GPIO_Init(&Keypad_Config);
		}
		else			//making PB4-PB7 as output connected to R1-R4
		{
		Keypad_Config.GPIO_PinConfig.GPIO_PinMode=GPIO_MODE_OUT;
		Keypad_Config.GPIO_PinConfig.GPIO_PinNumber=i;
		GPIO_Init(&Keypad_Config);
		}
	}
	for(int x=4;x<=7;x++)		//Initially RESET all o/p pins
	GPIO_WriteToOutputPin(GPIOB, x, RESET);
}

uint8_t DETECT_KEY_PRESS()
{
	uint32_t Value=0,KeyPress=0,ele=0;
	// Values to send to detect keypad press
	uint32_t in[][4]={{0x11,0x12,0x14,0x18},{0x21,0x22,0x24,0x28},{0x41,0x42,0x44,0x48},{0x81,0x82,0x84,0x88}};
	// All character in an array
	char act[]={'1','2','3','A','4','5','6','B','7','8','9','C','*','0','#','D'};
	for(int i=0;i<=3;i++)		//Makes R1-R4 high one at a time to detect key press if any
	{
		Value=0;
		Value|=(1<<(4+i));
		GPIO_WriteToOutputPort(GPIOB, Value); delay_ms(10);
		KeyPress=GPIO_ReadFromInputPort(GPIOB); delay_ms(10);
		if(KeyPress!=Value)		//only if key press detected goes inside loop
		{
			for(uint32_t *p=&in[i][0];p<=&in[4][4];p++)
			{
				if(KeyPress==*p)
				{
					ele=(uint32_t)(p-&in[0][0]);
					return(act[ele]);
				}
			}
		}
	}
	return('x');
}





