/*
 * FFT.c
 *
 *  Created on: Aug 17, 2023
 *      Author: ��
 */

#include "main.h"
int fft_N=fft_NL;   //FFT����
float fft_Input[fft_NL];//������ź�����


struct fft_Complex fft_Wn;//������ת����
struct fft_Complex fft_Vn;//ÿһ����һ����ת�����鲿Ϊ0��ʵ��Ϊ1
struct fft_Complex fft_T;//�����ת������X(k+B)�ĳ˻�

//float Realin[fft_NL]={0};// ���������ʵ��
float fft_output[fft_NL]={0};// �����FFT��ֵ��������ģ��
struct fft_Complex fft_Sample[fft_NL];// ���������ʵ��ת��Ϊ����

struct fft_Complex MUL(struct fft_Complex a,struct fft_Complex b)//���帴��
{
   struct fft_Complex c;
   c.real=a.real*b.real-a.imag*b.imag;
   c.imag=a.real*b.imag+a.imag*b.real;
   return(c);
}

void fft_MYFFT(struct fft_Complex *xin,int fft_N)//����Ϊ����ָ��*xin����N��FFT
{
   int L=0; // ���������
   int J=0; // ���������
   int K=0,KB=0; // ���������
   int M=1,Nn=0;// fft_N=2^M
   float B=0; // �����������������ݼ��
   /* ������Ϊ�����½��ľֲ�����*/
   int LH=0,J2=0,N1=0,I,K2=0;
   struct fft_Complex fft_T;
   /*�����ǵ���*/
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
   /* ����Ϊ�����M */
   Nn=fft_N;
   while(Nn!=2)// �����N����2Ϊ��������M
   {
     M++;
     Nn=Nn/2;
   }

   /* �������� */
   for(L=1;L<=M;L++)  // ����
    {
      B=pow(2,(L-1));
      fft_Vn.real=1;
      fft_Vn.imag=0;
      fft_Wn.real=cos(fft_pi/B);
      fft_Wn.imag=-sin(fft_pi/B);
      for(J=0;J<B;J++)   // ����
       {
         for(K=J;K<fft_N;K+=2*B)  // ������������
          {
            KB=K+B;
            fft_T=MUL(xin[KB],fft_Vn);
            xin[KB].real=xin[K].real-fft_T.real;//ԭַ���㣬�����������ԭ����������
            xin[KB].imag=xin[K].imag-fft_T.imag;
             xin[K].real=xin[K].real+fft_T.real;
             xin[K].imag=xin[K].imag+fft_T.imag;
          }
          fft_Vn=MUL(fft_Wn,fft_Vn);// ��ת�����������൱��ָ����ӣ��õ��Ľ��
          // ��J*2^��M-L����һ���ģ���Ϊ�ڵ�����������
         // ����M��L���ǲ���ģ�Ψһ��x�����Ǽ��ڵ�J
         // ����J����1Ϊ�����ģ���J*W��Ч��W+W+W...J��W���
        }
     }
}


/********************************
���ܣ����㸴����ģ
�βΣ�*Sampleָ����Ҫȡģ�ĸ����ṹ��
      NΪȡģ����
      *output���ȡģ����ֵ������
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
