/*
 * FFT.c
 *
 *  Created on: Aug 17, 2023
 *      Author: 黎
 */

#include "main.h"
int fft_N=fft_NL;   //FFT点数
float fft_Input[fft_NL];//输入的信号序列


struct fft_Complex fft_Wn;//定义旋转因子
struct fft_Complex fft_Vn;//每一级第一个旋转因子虚部为0，实部为1
struct fft_Complex fft_T;//存放旋转因子与X(k+B)的乘积

//float Realin[fft_NL]={0};// 采样输入的实数
float fft_output[fft_NL]={0};// 输出的FFT幅值（复数的模）
struct fft_Complex fft_Sample[fft_NL];// 采样输入的实数转化为复数

struct fft_Complex MUL(struct fft_Complex a,struct fft_Complex b)//定义复乘
{
   struct fft_Complex c;
   c.real=a.real*b.real-a.imag*b.imag;
   c.imag=a.real*b.imag+a.imag*b.real;
   return(c);
}

void fft_MYFFT(struct fft_Complex *xin,int fft_N)//输入为复数指针*xin，做N点FFT
{
   int L=0; // 级间运算层
   int J=0; // 级内运算层
   int K=0,KB=0; // 蝶形运算层
   int M=1,Nn=0;// fft_N=2^M
   float B=0; // 蝶形运算两输入数据间隔
   /* 以下是为倒序新建的局部变量*/
   int LH=0,J2=0,N1=0,I,K2=0;
   struct fft_Complex fft_T;
   /*以下是倒序*/
   LH=fft_N/2; // LH=fft_N/2
   J2=LH;
   N1=fft_N-2;
   for(I=1;I<=N1;I++)
    {
     if(I<J2)
     {
       fft_T=xin[I];
       xin[I]=xin[J2];
       xin[J2]=fft_T;
     }
     K2=LH;
     while(J2>=K2)
      {
        J2-=K2;
        K2=K2/2;// K2=K2/2
      }
      J2+=K2;
    }
   /* 以下为计算出M */
   Nn=fft_N;
   while(Nn!=2)// 计算出N的以2为底数的幂M
   {
     M++;
     Nn=Nn/2;
   }

   /* 蝶形运算 */
   for(L=1;L<=M;L++)  // 级间
    {
      B=pow(2,(L-1));
      fft_Vn.real=1;
      fft_Vn.imag=0;
      fft_Wn.real=cos(fft_pi/B);
      fft_Wn.imag=-sin(fft_pi/B);
      for(J=0;J<B;J++)   // 级内
       {
         for(K=J;K<fft_N;K+=2*B)  // 蝶形因子运算
          {
            KB=K+B;
            fft_T=MUL(xin[KB],fft_Vn);
            xin[KB].real=xin[K].real-fft_T.real;//原址运算，计算结果存放在原来的数组中
            xin[KB].imag=xin[K].imag-fft_T.imag;
             xin[K].real=xin[K].real+fft_T.real;
             xin[K].imag=xin[K].imag+fft_T.imag;
          }
          fft_Vn=MUL(fft_Wn,fft_Vn);// 旋转因子做复乘相当于指数相加，得到的结果
          // 和J*2^（M-L）是一样的，因为在蝶形因子运算
         // 层中M与L都是不变的，唯一变x化的是级内的J
         // 而且J是以1为步长的，如J*W等效于W+W+W...J个W相加
        }
     }
}


/********************************
功能：计算复数的模
形参：*Sample指向需要取模的复数结构体
      N为取模点数
      *output存放取模后数值的数组
*********************************/
void fft_ModelComplex(struct fft_Complex *fft_Sample,int fft_N,float *fft_output)
{
   int i;

   for(i=0;i<fft_N;i++)
    {
       fft_output[i]=sqrt(fft_Sample[i].real*fft_Sample[i].real+fft_Sample[i].imag*fft_Sample[i].imag)*2/fft_N;

    }
}
void hanning_window(int N, double *window) {
    int n;
    for ( n = 0; n < N; n++) {
        window[n] = 0.5 * (1 - cos(2 * M_PI * n / (N - 1)));
    }
}
