#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f4xx.h"

//�ڵδ�ʱ���жϷ������е���
void TimingDelay_Decrement(void);

// ��ʼ��ϵͳ�δ�ʱ��
void SysTick_Init(void);
void delay_1us(u32 nus);
#define delay_ms(x) delay_us(100*x)	 //��λms
//�ṩ��Ӧ�ó������
void Delay_ms(__IO u32 nTime);

#endif /* __SYSTICK_H */
