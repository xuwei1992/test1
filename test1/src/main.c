

#include <Inc/Led.h>
#include <Inc/Tim.h>
#include <Inc/USART_Config.h>
#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "stm32f10x.h"


int x;
void main(void)
{
   USART_Config();

   LED_INIT();
   for(x=0;x<2;x++)
   {
      LED_FLASH();
   }
   while(1)
   {
      Usart_SendString(DEBUG_USARTx, "这是一个串口中断显示实验！");
      Delay_ms_led(2000);
   }
}
// ----------------------------------------------------------------------------
