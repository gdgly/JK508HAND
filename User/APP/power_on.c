/**
  ******************************************************************************
  * @file    sysytem.c
  * @author  k
  * @version V1.0
  * @date    2018-04-29
  * @brief   �ֳֶ�·�¶Ȳ����ǿ�������
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:����  STM32 F429 ������
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "./led/bsp_led.h"
#include "./lcd/bsp_lcd.h"
#include "./key/bsp_key.h"
#include "./beep/bsp_beep.h"
#include "./tim/bsp_basic_tim.h"
#include "jk508.h"


void power_on(void)
{
//	u8 i;
//	char buf[10];
	
	
  /*��ʼ����Ĭ��ʹ��ǰ����*/
	LCD_SetLayer(LCD_FOREGROUND_LAYER); 
	/*Ĭ�����ò�͸��	���ú�������Ϊ��͸���ȣ���Χ 0-0xff ��0Ϊȫ͸����0xffΪ��͸��*/
    LCD_SetTransparency(0xFF);
	LCD_Clear(LCD_COLOR_BLACK);
	/*����LCD_SetLayer(LCD_FOREGROUND_LAYER)������
	����Һ����������ǰ����ˢ�£��������µ��ù�LCD_SetLayer�������ñ�����*/
//	for(i=0;i<16;i++)
//	{
//		LCD_SetColors(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
//		DISP_INS(5+i*20,5,"Initializing Channel");
//		sprintf(buf,"%03d",i+1);
//		DISP_INS(5+i*20,336,(uint8_t*)buf);
//		Delay(500);
//	}
	
	LCD_SetColors(LCD_COLOR_GR7,LCD_COLOR_BLACK);
	DISP_SYS(0,0,"JKOS");
	LCD_SetColors(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
	DISP_INS(50,0,"REV 1.0");
	DISP_INS(200,0,"JK508 Multi-channel Temp.Meter");
	DISP_INS(230,0,"REV 1.0");
	
	
	
	page_flag = poweron;
	
	
}

void DrawLogo(u16 x,u16 y)
{
	page_flag = 0xff;
	LCD_Clear(LCD_COLOR_BLACK);	
	LCD_SetColors(LCD_COLOR_GR7,LCD_COLOR_BLACK);
	/*J*/
	LCD_DrawLine(x,y,41,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x-1,y-1,44,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x-1,y-2,46,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x,y-3,46,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+2,y-4,46,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+35,y-5,14,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+35,y-6,15,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+35,y-7,15,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+36,y-8,14,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+36,y-9,15,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+37,y-10,14,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+37,y-11,14,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+37,y-12,14,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+38,y-13,14,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+37,y-14,15,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+38,y-15,14,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+38,y-16,14,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+38,y-17,15,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+39,y-18,14,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+39,y-19,14,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+39,y-20,15,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+40,y-21,14,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+40,y-22,14,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+40,y-23,14,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+40,y-24,14,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+41,y-25,13,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+41,y-26,14,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+41,y-27,14,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+42,y-28,14,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+42,y-29,14,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+42,y-30,14,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+42,y-31,15,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+42,y-32,15,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+43,y-33,13,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+43,y-34,14,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+44,y-35,13,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+44,y-36,14,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+44,y-37,14,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+44,y-38,15,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+44,y-39,15,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+45,y-40,14,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+45,y-41,14,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+45,y-42,15,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+45,y-43,15,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+46,y-44,14,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+46,y-45,14,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+46,y-46,15,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+47,y-47,14,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+47,y-48,14,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+47,y-49,15,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+47,y-50,15,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+48,y-51,14,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+48,y-52,14,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+48,y-53,14,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+49,y-54,13,LCD_DIR_HORIZONTAL);
	LCD_DrawLine(x+49,y-55,14,LCD_DIR_HORIZONTAL);
}