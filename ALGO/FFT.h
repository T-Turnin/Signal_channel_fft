/*
 * FFT.h
 *
 *  Created on: Aug 17, 2023
 *      Author: 黎
 */

#ifndef FFT_H_
#define FFT_H_
#define fft_pi 3.1415926535 // float小数点后6位
#define fft_NL 1024  // NL为合成信号点数，与N的值必须是一致的，即NL=fft_N

struct fft_Complex      // 定义复数结构体
{
   float real,imag;
};

extern int fft_N;   //FFT点数
//extern float fft_Input[fft_NL];//输入的信号序列

extern struct fft_Complex fft_Wn;//定义旋转因子
extern struct fft_Complex fft_Vn;//每一级第一个旋转因子虚部为0，实部为1
extern struct fft_Complex fft_T;//存放旋转因子与X(k+B)的乘积

//float Realin[fft_NL]={0};// 采样输入的实数
extern float fft_output[fft_NL];// 输出的FFT幅值（复数的模）
extern struct fft_Complex fft_Sample[fft_NL];// 采样输入的实数转化为复数

/*
 * 定义复乘
 */
struct fft_Complex MUL(struct fft_Complex a,struct fft_Complex b);

/*
 * 输入为复数指针*xin，做N点FFT
 */
void fft_MYFFT(struct fft_Complex *xin,int fft_N);

/********************************
功能：计算复数的模
形参：*Sample指向需要取模的复数结构体
      N为取模点数
      *output存放取模后数值的数组
*********************************/
void fft_ModelComplex(struct fft_Complex *fft_Sample,int fft_N,float *fft_output);


void hanning_window(int N, double *window);

#endif /* FFT_H_ */
