/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ����������
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:����  STM32 F429 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f4xx.h"
#include "./RTC/bsp_rtc.h"
#include "./usart/bsp_debug_usart.h"
#include "./lcd/bsp_lcd.h"
#include "jk508.h"
#include "touchscreen.h"



void Touch_GPIO_Config(void) 
{
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*������ص�GPIO����ʱ��*/
	RCC_AHB1PeriphClockCmd (TOUCH_XPLUS_GPIO_CLK|TOUCH_XMINUS_GPIO_CLK|TOUCH_YPLUS_GPIO_CLK|
	TOUCH_YMINUS_GPIO_CLK,ENABLE); 
	
	GPIO_InitStructure.GPIO_Pin = TOUCH_YPLUS_GPIO_PIN;/*ѡ������*/     
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;/*��������Ϊ����ģʽ*/   
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; /*��������Ϊ����ģʽ*/	  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;/*������������Ϊ2MHz */    
	GPIO_Init(TOUCH_YPLUS_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = TOUCH_XMINUS_GPIO_PIN;/*ѡ������*/     
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;/*��������Ϊ���ģʽ*/   
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;/*�������ŵ��������Ϊ�������*/    
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; /*��������Ϊ����ģʽ*/	  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;/*������������Ϊ2MHz */    
	GPIO_Init(TOUCH_XMINUS_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_ResetBits(TOUCH_XMINUS_GPIO_PORT,TOUCH_XMINUS_GPIO_PIN);
	
}

