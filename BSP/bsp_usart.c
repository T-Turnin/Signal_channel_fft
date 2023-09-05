/*
 * bsp_usart.c
 *
 *  Created on: Jul 2, 2023
 *      Author: lfp
 */

#include "main.h"

/* ����2�����Դ��� ------------------------------------------------------------*/
/* ���ջ���, */
uint8_t g_usart1_rx_buf[USART1_REC_LEN] = { 0 };
uint8_t cp_g_usart1_rx_buf[USART1_REC_LEN] = { 0 };

uint16_t g_usart1_rx_sta = 0;

uint8_t g_u1_rx_buffer[USART1_RXBUFFERSIZE]; /* HAL��ʹ�õĴ��ڽ��ջ��� */


/*    ���ͻ���    */
#pragma pack(8)
uint8_t USART3_TX_BUF[USART3_MAX_SEND_LEN];     //���ͻ���,���USART2_MAX_SEND_LEN�ֽ�
#pragma pack()
/* ���ջ���, */
uint8_t g_usart3_rx_buf[USART3_REC_LEN] = {0};
uint8_t cp_g_usart3_rx_buf[USART3_REC_LEN]= {0};

uint16_t g_usart3_rx_sta = 0;

uint8_t g_u3_rx_buffer[USART3_RXBUFFERSIZE];/* HAL��ʹ�õĴ��ڽ��ջ��� */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART1) /* ����δ�� */
    {
        if ((g_usart1_rx_sta & 0x8000) == 0) /* ���յ���0x0d */
        {
            if (g_usart1_rx_sta & 0x4000) /* ���յ���0x0d */
            {
                if (g_u1_rx_buffer[0] != 0x0a) {
                    g_usart1_rx_sta = 0; /* ���մ���,���� */
                } else {
                    g_usart1_rx_sta |= 0x8000; /* �������*/
                }
            } else { /* ��û�յ�0X0D */

                if (g_u1_rx_buffer[0] == 0x0d) {
                    g_usart1_rx_sta |= 0x4000;
                } else {
                    cp_g_usart1_rx_buf[g_usart1_rx_sta & 0X3FFF] = g_u1_rx_buffer[0];
                    g_usart1_rx_sta++;
                    if (g_usart1_rx_sta > (USART1_REC_LEN - 1)) {
                        g_usart1_rx_sta = 0; /* �������ݴ���,���� */
                    }
                }
            }
        }

        if (g_usart1_rx_sta & 0x8000) {
            memcpy(g_usart1_rx_buf, cp_g_usart1_rx_buf, USART1_REC_LEN);
            memset(cp_g_usart1_rx_buf, 0, USART1_REC_LEN);
            g_usart1_rx_sta = 0;
        }
    }
    if(huart->Instance == USART3)             /* ����δ�� */
      {
          if((g_usart3_rx_sta & 0x8000) == 0)      /* ���յ���0x0d */
          {
              if(g_usart3_rx_sta & 0x4000)         /* ���յ���0x0d */
              {
                  if(g_u3_rx_buffer[0] != 0x0a)
                  {
                      g_usart3_rx_sta = 0;          /* ���մ���,���� */
                  }else{
                      g_usart3_rx_sta |= 0x8000;   /* �������*/
                  }
              }else{                                /* ��û�յ�0X0D */

                  if(g_u3_rx_buffer[0] == 0x0d)
                  {
                      g_usart3_rx_sta |= 0x4000;
                  }else{
                      cp_g_usart3_rx_buf[g_usart3_rx_sta & 0X3FFF] = g_u3_rx_buffer[0] ;
                      g_usart3_rx_sta++;
                      if(g_usart3_rx_sta > (USART3_REC_LEN - 1))
                      {
                          g_usart3_rx_sta = 0;      /* �������ݴ���,���� */
                      }
                  }
              }
          }

          if (g_usart3_rx_sta & 0x8000) {
                 memcpy(g_usart3_rx_buf, cp_g_usart3_rx_buf, USART3_REC_LEN);
                 memset(cp_g_usart3_rx_buf, 0, USART3_REC_LEN);
                 g_usart3_rx_sta = 0;
          }
      }
}

/*****************  ����1 **********************/
/*****************  �����ַ� **********************/
void Usart1_SendByte(uint8_t str) {
    HAL_UART_Transmit(&huart1, &str, 1, 1000);

}

/*****************  �����ַ��� **********************/
void Usart1_SendString(uint8_t *str) {
    unsigned int k = 0;
    do {
        HAL_UART_Transmit(&huart1, (uint8_t*) (str + k), 1, 1000);
        k++;
    } while (*(str + k) != '\0');
}

#ifdef __GNUC__                                    //�����ض���
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif
PUTCHAR_PROTOTYPE {
    HAL_UART_Transmit(&huart1, (uint8_t*) &ch, 1, 0xFFFF);
    return ch;
}
/*****************  ����3 **********************/
/*****************  �����ַ� **********************/
void Usart3_SendByte(uint8_t str)
{
  HAL_UART_Transmit(&huart3, &str, 1, 1000);

}

/*****************  �����ַ��� **********************/
void Usart3_SendString(uint8_t *str)
{
    unsigned int k=0;
  do
  {
      HAL_UART_Transmit(&huart3,(uint8_t *)(str + k) ,1,1000);
      k++;
  } while(*(str + k)!='\0');
}
//����3,printf ����
//ȷ��һ�η������ݲ�����USART3_MAX_SEND_LEN�ֽ�
void u3_printf(char* fmt,...)
{
    uint16_t i,j;
    va_list ap;
    va_start(ap,fmt);
    vsprintf((char*)USART3_TX_BUF,fmt,ap);
    va_end(ap);
    i=strlen((const char*)USART3_TX_BUF);//�˴η������ݵĳ���
    for(j=0;j<i;j++)//ѭ����������
    {
        while((USART3->SR&0X40)==0);//ѭ������,ֱ���������
        USART3->DR=USART3_TX_BUF[j];
    }
}
