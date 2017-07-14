/*
 * USART_Config.c
 *
 *  Created on: 2017年7月14日
 *      Author: xuwei
 */
// 串口 1-USART1



#include "stm32f10x_usart.h"
#include "USART_Config.h"

static void NVIC_Configuration(void)
{
   NVIC_InitTypeDef NVIC_InitStructure;

/* 嵌套向量中断控制器组选择 */
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

/* 配置 USART 为中断源 */
NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
/* 抢断优先级为 1 */
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
/* 子优先级为 1 */
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
/* 使能中断 */
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
/* 初始化配置 NVIC */
NVIC_Init(&NVIC_InitStructure);
}


void USART_Config(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
   USART_InitTypeDef USART_InitStructure;

   DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);

   DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);

   GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);


   GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
   GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);

   USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;

   USART_InitStructure.USART_WordLength = USART_WordLength_8b;

   USART_InitStructure.USART_StopBits = USART_StopBits_1;

   // 配置校验位
   USART_InitStructure.USART_Parity = USART_Parity_No ;
   // 配置硬件流控制
   USART_InitStructure.USART_HardwareFlowControl =
   USART_HardwareFlowControl_None;
   // 配置工作模式，收发一起
   USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
   // 完成串口的初始化配置
   USART_Init(DEBUG_USARTx, &USART_InitStructure);

   // 串口中断优先级配置
   NVIC_Configuration();

   // 使能串口接收中断
   USART_ITConfig(DEBUG_USARTx, USART_IT_RXNE, ENABLE);

   // 使能串口
   USART_Cmd(DEBUG_USARTx, ENABLE);

}


void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
   /* 发送一个字节数据到 USART */
   USART_SendData(pUSARTx,ch);

   /*等待发送数据寄存器为空 */
   while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}


void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
   unsigned int k=0;
   do {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
   } while (*(str + k)!='\0');

      /* 等待发送完成 */
   while (USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET) {
   }
}


