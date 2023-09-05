/*
 * FFT.h
 *
 *  Created on: Aug 17, 2023
 *      Author: ��
 */

#ifndef FFT_H_
#define FFT_H_
#define fft_pi 3.1415926535 // floatС�����6λ
#define fft_NL 1024  // NLΪ�ϳ��źŵ�������N��ֵ������һ�µģ���NL=fft_N

struct fft_Complex      // ���帴���ṹ��
{
   float real,imag;
};

extern int fft_N;   //FFT����
//extern float fft_Input[fft_NL];//������ź�����

extern struct fft_Complex fft_Wn;//������ת����
extern struct fft_Complex fft_Vn;//ÿһ����һ����ת�����鲿Ϊ0��ʵ��Ϊ1
extern struct fft_Complex fft_T;//�����ת������X(k+B)�ĳ˻�

//float Realin[fft_NL]={0};// ���������ʵ��
extern float fft_output[fft_NL];// �����FFT��ֵ��������ģ��
extern struct fft_Complex fft_Sample[fft_NL];// ���������ʵ��ת��Ϊ����

/*
 * ���帴��
 */
struct fft_Complex MUL(struct fft_Complex a,struct fft_Complex b);

/*
 * ����Ϊ����ָ��*xin����N��FFT
 */
void fft_MYFFT(struct fft_Complex *xin,int fft_N);

/********************************
���ܣ����㸴����ģ
�βΣ�*Sampleָ����Ҫȡģ�ĸ����ṹ��
      NΪȡģ����
      *output���ȡģ����ֵ������
*********************************/
void fft_ModelComplex(struct fft_Complex *fft_Sample,int fft_N,float *fft_output);


void hanning_window(int N, double *window);

#endif /* FFT_H_ */
