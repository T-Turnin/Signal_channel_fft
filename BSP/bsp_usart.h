/*
 * bsp_usart.h
 *
 *  Created on: Jul 2, 2023
 *      Author: lfp
 */

#ifndef BSP_USART_H_
#define BSP_USART_H_

/* 串口1，调试串口 ------------------------------------------------------------*/
#define USART1_REC_LEN   200                     /* 定义最大接收字节数 200 */
#define USART1_RXBUFFERSIZE    1                       /* 缓存大小 */

extern uint8_t  g_usart1_rx_buf[USART1_REC_LEN];  /* 接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 */
extern uint16_t g_usart1_rx_sta;                 /* 接收状态标记 */
extern uint8_t g_u1_rx_buffer[USART1_RXBUFFERSIZE];       /* HAL库USART接收Buffer */

void Usart1_SendByte(uint8_t str);
void Usart1_SendString(uint8_t *str);


/* 串口3 ------------------------------------------------------------*/
#define USART3_MAX_SEND_LEN        400                    //最大发送缓存字节数
extern uint8_t  USART3_TX_BUF[USART3_MAX_SEND_LEN];         //发送缓冲,最大USART3_MAX_SEND_LEN字节

#define USART3_REC_LEN   200                     /* 定义最大接收字节数 200 */
#define USART3_RXBUFFERSIZE    1                       /* 缓存大小 */

extern uint8_t g_usart3_rx_buf[USART3_REC_LEN];
extern uint16_t g_usart3_rx_sta;
extern uint8_t g_u3_rx_buffer[USART3_RXBUFFERSIZE];

void Usart3_SendByte(uint8_t str);
void Usart3_SendString(uint8_t *str);/* HAL库使用的串口接收缓冲 */
void u3_printf(char* fmt,...);

#endif /* BSP_USART_H_ */
