#ifndef _LED_H_
#define _LED_H_

#include "Tim.h"		

#define LED2_OFF  	GPIO_SetBits(GPIOB, GPIO_Pin_3)	//PB3 LED2 通讯指示
#define LED2_ON 		GPIO_ResetBits(GPIOB, GPIO_Pin_3)

#define LED1_OFF  	GPIO_SetBits(GPIOB, GPIO_Pin_4)	//PB4 LED1 
#define LED1_ON 		GPIO_ResetBits(GPIOB, GPIO_Pin_4)

#define LED3_ON  	GPIO_SetBits(GPIOC, GPIO_Pin_13)//PC13 LED3 夜间指示
#define LED3_OFF 		GPIO_ResetBits(GPIOC, GPIO_Pin_13)


void LED_INIT(void);
void LED_FLASH(void);

void Delay_ms_led(u16 nms);

#endif
