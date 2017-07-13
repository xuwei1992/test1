

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "stm32f10x.h"
#include "Led.h"
#include "Tim.h"

int x;
void main(void)
{
   while (1)
   {
      LED_INIT();
      for(x=0;x<20;x++)
      {
         LED_FLASH();
      }
   }
}
// ----------------------------------------------------------------------------
