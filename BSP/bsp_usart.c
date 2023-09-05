/*
 * bsp_usart.c
 *
 *  Created on: Jul 2, 2023
 *      Author: lfp
 */

#include "main.h"

/* 串口2，调试串口 ------------------------------------------------------------*/
/* 接收缓冲, */
uint8_t g_usart1_rx_buf[USART1_REC_LEN] = { 0 };
uint8_t cp_g_usart1_rx_buf[USART1_REC_LEN] = { 0 };

uint16_t g_usart1_rx_sta = 0;

uint8_t g_u1_rx_buffer[USART1_RXBUFFERSIZE]; /* HAL库使用的串口接收缓冲 */


/*    发送缓冲    */
#pragma pack(8)
uint8_t USART3_TX_BUF[USART3_MAX_SEND_LEN];     //发送缓冲,最大USART2_MAX_SEND_LEN字节
#pragma pack()
/* 接收缓冲, */
uint8_t g_usart3_rx_buf[USART3_REC_LEN] = {0};
uint8_t cp_g_usart3_rx_buf[USART3_REC_LEN]= {0};

uint16_t g_usart3_rx_sta = 0;

uint8_t g_u3_rx_buffer[USART3_RXBUFFERSIZE];/* HAL库使用的串口接收缓冲 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART1) /* 接收未完 */
    {
        if ((g_usart1_rx_sta & 0x8000) == 0) /* 接收到了0x0d */
        {
            if (g_usart1_rx_sta & 0x4000) /* 接收到了0x0d */
            {
                if (g_u1_rx_buffer[0] != 0x0a) {
                    g_usart1_rx_sta = 0; /* 接收错误,重新 */
                } else {
                    g_usart1_rx_sta |= 0x8000; /* 接收完成*/
                }
            } else { /* 还没收到0X0D */

                if (g_u1_rx_buffer[0] == 0x0d) {
                    g_usart1_rx_sta |= 0x4000;
                } else {
                    cp_g_usart1_rx_buf[g_usart1_rx_sta & 0X3FFF] = g_u1_rx_buffer[0];
                    g_usart1_rx_sta++;
                    if (g_usart1_rx_sta > (USART1_REC_LEN - 1)) {
                        g_usart1_rx_sta = 0; /* 接收数据错误,重新 */
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
    if(huart->Instance == USART3)             /* 接收未完 */
      {
          if((g_usart3_rx_sta & 0x8000) == 0)      /* 接收到了0x0d */
          {
              if(g_usart3_rx_sta & 0x4000)         /* 接收到了0x0d */
              {
                  if(g_u3_rx_buffer[0] != 0x0a)
                  {
                      g_usart3_rx_sta = 0;          /* 接收错误,重新 */
                  }else{
                      g_usart3_rx_sta |= 0x8000;   /* 接收完成*/
                  }
              }else{                                /* 还没收到0X0D */

                  if(g_u3_rx_buffer[0] == 0x0d)
                  {
                      g_usart3_rx_sta |= 0x4000;
                  }else{
                      cp_g_usart3_rx_buf[g_usart3_rx_sta & 0X3FFF] = g_u3_rx_buffer[0] ;
                      g_usart3_rx_sta++;
                      if(g_usart3_rx_sta > (USART3_REC_LEN - 1))
                      {
                          g_usart3_rx_sta = 0;      /* 接收数据错误,重新 */
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

/*****************  串口1 **********************/
/*****************  发送字符 **********************/
void Usart1_SendByte(uint8_t str) {
    HAL_UART_Transmit(&huart1, &str, 1, 1000);

}

/*****************  发送字符串 **********************/
void Usart1_SendString(uint8_t *str) {
    unsigned int k = 0;
    do {
        HAL_UART_Transmit(&huart1, (uint8_t*) (str + k), 1, 1000);
        k++;
    } while (*(str + k) != '\0');
}

#ifdef __GNUC__                                    //串口重定向
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif
PUTCHAR_PROTOTYPE {
    HAL_UART_Transmit(&huart1, (uint8_t*) &ch, 1, 0xFFFF);
    return ch;
}
/*****************  串口3 **********************/
/*****************  发送字符 **********************/
void Usart3_SendByte(uint8_t str)
{
  HAL_UART_Transmit(&huart3, &str, 1, 1000);

}

/*****************  发送字符串 **********************/
void Usart3_SendString(uint8_t *str)
{
    unsigned int k=0;
  do
  {
      HAL_UART_Transmit(&huart3,(uint8_t *)(str + k) ,1,1000);
      k++;
  } while(*(str + k)!='\0');
}
//串口3,printf 函数
//确保一次发送数据不超过USART3_MAX_SEND_LEN字节
void u3_printf(char* fmt,...)
{
    uint16_t i,j;
    va_list ap;
    va_start(ap,fmt);
    vsprintf((char*)USART3_TX_BUF,fmt,ap);
    va_end(ap);
    i=strlen((const char*)USART3_TX_BUF);//此次发送数据的长度
    for(j=0;j<i;j++)//循环发送数据
    {
        while((USART3->SR&0X40)==0);//循环发送,直到发送完毕
        USART3->DR=USART3_TX_BUF[j];
    }
}
