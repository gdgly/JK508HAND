/**
  ******************************************************************************
  * @file    sysytem.c
  * @author  fire
  * @version V1.0
  * @date    2018-04-29
  * @brief   �ֳֶ�·�¶Ȳ�����ϵͳ���ý���
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
#include "./flash/bsp_spi_flash.h"
#include "jk508.h"
#include "./RTC/bsp_rtc.h"

u8 Data_buf[16][16];
float hisdata[16][500];
u8 histime[10][7];
float YLIMIT[3];
u16 his_config[10];
u8 his_time[10][7];
u8 hispage;

//��ȡ��ID�洢λ��
extern __IO uint32_t DeviceID;
extern __IO uint32_t FlashID;

extern union 
{
   unsigned char FLAG_VAL7;
	
   struct 
   {
       unsigned char  FN:2;    //����
       unsigned char  SP:2;    //�ٶ�
       unsigned char  BD:3;    //����
       unsigned char  LG:1;	   //����
   }BIT_FLAG;
}FLAG7;


void page_his(void)
{
	range = (YHLIMIT - YLLIMIT) / 7;
	enrate = 350/(float)(YHLIMIT - YLLIMIT);
	u8 i;
	u16 j;
	char timetemp[100];
	char buf[10];
	
	
	
	
   /*��ʼ����Ĭ��ʹ��ǰ����*/
	LCD_SetLayer(LCD_FOREGROUND_LAYER);
	/*Ĭ�����ò�͸��	���ú�������Ϊ��͸���ȣ���Χ 0-0xff ��0Ϊȫ͸����0xffΪ��͸��*/
    LCD_SetTransparency(0xFF);
	LCD_Clear(LCD_COLOR_BACK);
	/*����LCD_SetLayer(LCD_FOREGROUND_LAYER)������
	����Һ����������ǰ����ˢ�£��������µ��ù�LCD_SetLayer�������ñ�����*/
	LCD_SetTextColor(LCD_COLOR_HLT);
	LCD_SetBackColor(LCD_COLOR_BACK);
	LCD_DisplayStringLine(0,10, "<      >");
	LCD_DisplayStringLine(5,26, "��ʷ����");
	
	dirflag  =1;
	hispage = 1;
	
	DrawMenu();
	Drawhishmenu();
	Mount_SD();	
	READ_HIS_FOLDER();
	
	
	page_flag = history;
}

void Save_history(u16 rec)
{
//	SPI_FLASH_SectorErase(8192 + 4096 * (rec-1));
	if(rec%16 == 1)
	{
		SPI_FLASH_SectorErase(8192+4096*(rec/16));
	}
	SPI_FLASH_BufferWrite((void*)Data_buf,8192+SPI_FLASH_PageSize*(rec-1), sizeof(Data_buf));
	memset(Data_buf,0,sizeof(time_buf));
}

void Read_history(u16 rec)
{	
	u8 read_buf[16][16];
	u8 i,j,k;
	for(i = 0;i < 62;i++)
	{
		SPI_FLASH_BufferRead((void *)read_buf,8192+15872*(rec-1)+i*256, sizeof(read_buf));
		for(j = 0;j < 16;j ++)
		{
			for(k = 0;k < 8;k++)
			{
				hisdata[j][i*8+k] = (read_buf[j][k%8*2] * 256 +  read_buf[j][k%8*2+1])/10.0;
			}
		}
	}
}


void Save_time(u16 rec)
{
	
	if(rec%16 == 1)
	{
		SPI_FLASH_SectorErase(15880192+4096*(rec/16));
	}
	SPI_FLASH_BufferWrite((void*)time_buf,15880192+SPI_FLASH_PageSize*(rec-1), sizeof(time_buf));
	memset(time_buf,0,sizeof(time_buf));
}

void Read_time(u16 rec)
{
//	memset(histime,0,sizeof(histime));
	SPI_FLASH_BufferRead((void *)histime,15880192+SPI_FLASH_PageSize*(rec-1), sizeof(histime));
}
	
void Save_Sflag(void)
{
	SPI_FLASH_SectorErase(1*4096);
	SPI_FLASH_BufferWrite((void*)his_config,SPI_FLASH_PageSize*16, sizeof(his_config));
}

void Read_Sflag(void)
{
	SPI_FLASH_BufferRead((void *)his_config,SPI_FLASH_PageSize*16, sizeof(his_config));
}

//void hispage(u16 page)
//{
//	Read_history(page);
//	Read_time(page);
//	page_his();
//}
