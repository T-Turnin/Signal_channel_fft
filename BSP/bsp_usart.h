/*
 * bsp_usart.h
 *
 *  Created on: Jul 2, 2023
 *      Author: lfp
 */

#ifndef BSP_USART_H_
#define BSP_USART_H_

/* ����1�����Դ��� ------------------------------------------------------------*/
#define USART1_REC_LEN   200                     /* �����������ֽ��� 200 */
#define USART1_RXBUFFERSIZE    1                       /* �����С */

extern uint8_t  g_usart1_rx_buf[USART1_REC_LEN];  /* ���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� */
extern uint16_t g_usart1_rx_sta;                 /* ����״̬��� */
extern uint8_t g_u1_rx_buffer[USART1_RXBUFFERSIZE];       /* HAL��USART����Buffer */

void Usart1_SendByte(uint8_t str);
void Usart1_SendString(uint8_t *str);


/* ����3 ------------------------------------------------------------*/
#define USART3_MAX_SEND_LEN        400                    //����ͻ����ֽ���
extern uint8_t  USART3_TX_BUF[USART3_MAX_SEND_LEN];         //���ͻ���,���USART3_MAX_SEND_LEN�ֽ�

#define USART3_REC_LEN   200                     /* �����������ֽ��� 200 */
#define USART3_RXBUFFERSIZE    1                       /* �����С */

extern uint8_t g_usart3_rx_buf[USART3_REC_LEN];
extern uint16_t g_usart3_rx_sta;
extern uint8_t g_u3_rx_buffer[USART3_RXBUFFERSIZE];

void Usart3_SendByte(uint8_t str);
void Usart3_SendString(uint8_t *str);/* HAL��ʹ�õĴ��ڽ��ջ��� */
void u3_printf(char* fmt,...);

#endif /* BSP_USART_H_ */
