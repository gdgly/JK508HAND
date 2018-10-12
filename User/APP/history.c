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
	
	DrawMenu();
	Drawhishmenu();
	
	LCD_SetTextColor(LCD_COLOR_RED);
	LCD_SetBackColor(LCD_COLOR_BACK);
	for(i = 0;i < 7;i ++)
	{
		sprintf(buf,"%d",(int)(YHLIMIT - range * i));
		DISP_CNL_S(40 + 50*i,10/*90*/,(uint8_t* )buf);
	}
	
	
	DrawGridLine();
	Read_history(1);
	Read_time(1);
//	for(j = 0; j < 500; j++)
//	{
//		LCD_SetColors(LCD_COLOR_RED,LCD_COLOR_BACK);
//		LCD_DrawUniLine(111 + j,(int)(400-((Data_buf[j] - YLLIMIT)*enrate)),112+j,(400-((Data_buf[j+1] - YLLIMIT)*enrate)));
//	}
	for(j = 0; j < 495; j++)
	{
		if(CH1_SW == ch_on && hisdata[0][j] < YHLIMIT && hisdata[0][j] > YLLIMIT)
		{
			LCD_SetColors(LCD_COLOR_RED,LCD_COLOR_BACK);
			LCD_DrawUniLine(111-80 + j,(int)(400-((hisdata[0][j] - YLLIMIT)*enrate)),112 - 80 + j,(400-((hisdata[0][j+1] - YLLIMIT)*enrate)));
		}
		if(CH2_SW == ch_on && hisdata[1][j] < YHLIMIT && hisdata[1][j] > YLLIMIT)
		{
			LCD_SetColors(LCD_COLOR_GREEN,LCD_COLOR_BACK);
			LCD_DrawUniLine(111-80 + j,(int)(400-((hisdata[1][j] - YLLIMIT)*enrate)),112 - 80 + j,(400-((hisdata[1][j+1] - YLLIMIT)*enrate)));
		}
		if(CH3_SW == ch_on && hisdata[2][j] < YHLIMIT && hisdata[2][j] > YLLIMIT)
		{
			LCD_SetColors(LCD_COLOR_MAGENTA,LCD_COLOR_BACK);
			LCD_DrawUniLine(111-80 + j,(int)(400-((hisdata[2][j] - YLLIMIT)*enrate)),112 - 80 + j,(400-((hisdata[2][j+1] - YLLIMIT)*enrate)));
		}
		if(CH4_SW == ch_on && hisdata[3][j] < YHLIMIT && hisdata[3][j] > YLLIMIT)
		{
			LCD_SetColors(LCD_COLOR_CYAN,LCD_COLOR_BACK);
			LCD_DrawUniLine(111-80 + j,(int)(400-((hisdata[3][j] - YLLIMIT)*enrate)),112 - 80 + j,(400-((hisdata[3][j+1] - YLLIMIT)*enrate)));
		}		
		if(CH5_SW == ch_on && hisdata[4][j] < YHLIMIT && hisdata[4][j] > YLLIMIT)
		{
			LCD_SetColors(LCD_COLOR_YELLOW,LCD_COLOR_BACK);
			LCD_DrawUniLine(111-80 + j,(int)(400-((hisdata[4][j] - YLLIMIT)*enrate)),112 - 80 + j,(400-((hisdata[4][j+1] - YLLIMIT)*enrate)));
		}
		if(CH6_SW == ch_on && hisdata[5][j] < YHLIMIT && hisdata[5][j] > YLLIMIT)
		{
			LCD_SetColors(LCD_COLOR_HLT,LCD_COLOR_BACK);
			LCD_DrawUniLine(111-80 + j,(int)(400-((hisdata[5][j] - YLLIMIT)*enrate)),112 - 80 + j,(400-((hisdata[5][j+1] - YLLIMIT)*enrate)));
		}
		if(CH7_SW == ch_on && hisdata[6][j] < YHLIMIT && hisdata[6][j] > YLLIMIT)
		{
			LCD_SetColors(LCD_COLOR_BT,LCD_COLOR_BACK);
			LCD_DrawUniLine(111-80 + j,(int)(400-((hisdata[6][j] - YLLIMIT)*enrate)),112 - 80 + j,(400-((hisdata[6][j+1] - YLLIMIT)*enrate)));
		}
		if(CH8_SW == ch_on && hisdata[7][j] < YHLIMIT && hisdata[7][j] > YLLIMIT)
		{
			LCD_SetColors(LCD_COLOR_BLUE,LCD_COLOR_BACK);
			LCD_DrawUniLine(111-80 + j,(int)(400-((hisdata[7][j] - YLLIMIT)*enrate)),112 - 80 + j,(400-((hisdata[7][j+1] - YLLIMIT)*enrate)));
		}
		if(CH9_SW == ch_on && hisdata[8][j] < YHLIMIT && hisdata[8][j] > YLLIMIT)
		{
			LCD_SetColors(LCD_COLOR_WHITE,LCD_COLOR_BACK);
			LCD_DrawUniLine(111-80 + j,(int)(400-((hisdata[8][j] - YLLIMIT)*enrate)),112 - 80 + j,(400-((hisdata[8][j+1] - YLLIMIT)*enrate)));
		}
		if(CH10_SW == ch_on && hisdata[1][9] < YHLIMIT && hisdata[1][9] > YLLIMIT)
		{
			LCD_SetColors(LCD_COLOR_GR1,LCD_COLOR_BACK);
			LCD_DrawUniLine(111-80 + j,(int)(400-((hisdata[9][j] - YLLIMIT)*enrate)),112 - 80 + j,(400-((hisdata[9][j+1] - YLLIMIT)*enrate)));
		}
		if(CH11_SW == ch_on && hisdata[10][j] < YHLIMIT && hisdata[10][j] > YLLIMIT)
		{
			LCD_SetColors(LCD_COLOR_GR2,LCD_COLOR_BACK);
			LCD_DrawUniLine(111-80 + j,(int)(400-((hisdata[10][j] - YLLIMIT)*enrate)),112 - 80 + j,(400-((hisdata[10][j+1] - YLLIMIT)*enrate)));
		}
		if(CH12_SW == ch_on && hisdata[11][j] < YHLIMIT && hisdata[11][j] > YLLIMIT)
		{
			LCD_SetColors(LCD_COLOR_GR3,LCD_COLOR_BACK);
			LCD_DrawUniLine(111-80 + j,(int)(400-((hisdata[11][j] - YLLIMIT)*enrate)),112 - 80 + j,(400-((hisdata[11][j+1] - YLLIMIT)*enrate)));
		}
		if(CH13_SW == ch_on && hisdata[12][j] < YHLIMIT && hisdata[12][j] > YLLIMIT)
		{
			LCD_SetColors(LCD_COLOR_GR4,LCD_COLOR_BACK);
			LCD_DrawUniLine(111-80 + j,(int)(400-((hisdata[12][j] - YLLIMIT)*enrate)),112 - 80 + j,(400-((hisdata[12][j+1] - YLLIMIT)*enrate)));
		}
		if(CH14_SW == ch_on && hisdata[13][j] < YHLIMIT && hisdata[13][j] > YLLIMIT)
		{
			LCD_SetColors(LCD_COLOR_GR5,LCD_COLOR_BACK);
			LCD_DrawUniLine(111-80 + j,(int)(400-((hisdata[13][j] - YLLIMIT)*enrate)),112 - 80 + j,(400-((hisdata[13][j+1] - YLLIMIT)*enrate)));
		}
		if(CH15_SW == ch_on && hisdata[14][j] < YHLIMIT && hisdata[14][j] > YLLIMIT)
		{
			LCD_SetColors(LCD_COLOR_GR6,LCD_COLOR_BACK);
			LCD_DrawUniLine(111-80 + j,(int)(400-((hisdata[14][j] - YLLIMIT)*enrate)),112 - 80 + j,(400-((hisdata[14][j+1] - YLLIMIT)*enrate)));
		}
		if(CH16_SW == ch_on && hisdata[15][j] < YHLIMIT && hisdata[15][j] > YLLIMIT)
		{
			LCD_SetColors(LCD_COLOR_GR7,LCD_COLOR_BACK);
			LCD_DrawUniLine(111-80 + j,(int)(400-((hisdata[15][j] - YLLIMIT)*enrate)),112 - 80 + j,(400-((hisdata[15][j+1] - YLLIMIT)*enrate)));
		}
	}
	LCD_SetTextColor(LCD_COLOR_WHITE);
	LCD_SetBackColor(LCD_COLOR_BACK);
	sprintf(timetemp,"%d%0.2d-%0.2d-%0.2d",
			histime[0][0],
			histime[0][1],
			histime[0][2],
			histime[0][3]);		
	LCD_DisplayStringLine(10,200,(uint8_t *)timetemp);
	
	sprintf(timetemp,"%0.2d:%0.2d:%0.2d",
			histime[0][4],
			histime[0][5],
			histime[0][6]);		
	DISP_CNL_S(402,80-80,(uint8_t *)timetemp);
	
	sprintf(timetemp,"%0.2d:%0.2d:%0.2d",
		histime[1][4],
		histime[1][5],
		histime[1][6]);
	DISP_CNL_S(420,130-80,(uint8_t *)timetemp);
	
	sprintf(timetemp,"%0.2d:%0.2d:%0.2d",
		histime[2][4],
		histime[2][5],
		histime[2][6]);
	LCD_SetTextColor(LCD_COLOR_WHITE);
	DISP_CNL_S(402,180-80,(uint8_t *)timetemp);
	
	sprintf(timetemp,"%0.2d:%0.2d:%0.2d",
		histime[3][4],
		histime[3][5],
		histime[3][6]);
	DISP_CNL_S(420,230-80,(uint8_t *)timetemp);
	
	sprintf(timetemp,"%0.2d:%0.2d:%0.2d",
		histime[4][4],
		histime[4][5],
		histime[4][6]);
	DISP_CNL_S(402,280-80,(uint8_t *)timetemp);
	
	sprintf(timetemp,"%0.2d:%0.2d:%0.2d",
		histime[5][4],
		histime[5][5],
		histime[5][6]);
	DISP_CNL_S(420,330-80,(uint8_t *)timetemp);
	
	sprintf(timetemp,"%0.2d:%0.2d:%0.2d",
		histime[6][4],
		histime[6][5],
		histime[6][6]);
	DISP_CNL_S(402,380-80,(uint8_t *)timetemp);
	
	sprintf(timetemp,"%0.2d:%0.2d:%0.2d",
		histime[7][4],
		histime[7][5],
		histime[7][6]);
	DISP_CNL_S(420,430-80,(uint8_t *)timetemp);
	
	sprintf(timetemp,"%0.2d:%0.2d:%0.2d",
		histime[8][4],
		histime[8][5],
		histime[8][6]);
	DISP_CNL_S(402,480-80,(uint8_t *)timetemp);
	
	sprintf(timetemp,"%0.2d:%0.2d:%0.2d",
		histime[9][4],
		histime[9][5],
		histime[9][6]);
	DISP_CNL_S(420,530-80,(uint8_t *)timetemp);
	
	
	LCD_SetColors(LCD_COLOR_RED,LCD_COLOR_RED);
	LCD_DrawLine(540,100-50,10,LCD_DIR_HORIZONTAL);
	LCD_SetBackColor(LCD_COLOR_BACK);
	DISP_CNL_S(90-50,10+540,"001");
	
	LCD_SetColors(LCD_COLOR_GREEN,LCD_COLOR_GREEN);
	LCD_DrawLine(540,120-50,10,LCD_DIR_HORIZONTAL);
	LCD_SetBackColor(LCD_COLOR_BACK);
	DISP_CNL_S(110-50,10+540,"002");
	
	LCD_SetColors(LCD_COLOR_MAGENTA,LCD_COLOR_GREEN);
	LCD_DrawLine(540,140-50,10,LCD_DIR_HORIZONTAL);
	LCD_SetBackColor(LCD_COLOR_BACK);
	DISP_CNL_S(130-50,10+540,"003");
	
	LCD_SetColors(LCD_COLOR_CYAN,LCD_COLOR_GREEN);
	LCD_DrawLine(540,160-50,10,LCD_DIR_HORIZONTAL);
	LCD_SetBackColor(LCD_COLOR_BACK);
	DISP_CNL_S(150-50,10+540,"004");
	
	LCD_SetColors(LCD_COLOR_YELLOW,LCD_COLOR_GREEN);
	LCD_DrawLine(540,180-50,10,LCD_DIR_HORIZONTAL);
	LCD_SetBackColor(LCD_COLOR_BACK);
	DISP_CNL_S(170-50,10+540,"005");
	
	LCD_SetColors(LCD_COLOR_HLT,LCD_COLOR_GREEN);
	LCD_DrawLine(540,200-50,10,LCD_DIR_HORIZONTAL);
	LCD_SetBackColor(LCD_COLOR_BACK);
	DISP_CNL_S(190-50,10+540,"006");
	
	LCD_SetColors(LCD_COLOR_BT,LCD_COLOR_GREEN);
	LCD_DrawLine(540,220-50,10,LCD_DIR_HORIZONTAL);
	LCD_SetBackColor(LCD_COLOR_BACK);
	DISP_CNL_S(210-50,10+540,"007");
	
	LCD_SetColors(LCD_COLOR_BLUE,LCD_COLOR_GREEN);
	LCD_DrawLine(540,240-50,10,LCD_DIR_HORIZONTAL);
	LCD_SetBackColor(LCD_COLOR_BACK);
	DISP_CNL_S(230-50,10+540,"008");
	
	LCD_SetColors(LCD_COLOR_WHITE,LCD_COLOR_GREEN);
	LCD_DrawLine(540,260-50,10,LCD_DIR_HORIZONTAL);
	LCD_SetBackColor(LCD_COLOR_BACK);
	DISP_CNL_S(250-50,10+540,"009");
	
	LCD_SetColors(LCD_COLOR_GR1,LCD_COLOR_GREEN);
	LCD_DrawLine(540,280-50,10,LCD_DIR_HORIZONTAL);
	LCD_SetBackColor(LCD_COLOR_BACK);
	DISP_CNL_S(270-50,10+540,"010");
	
	LCD_SetColors(LCD_COLOR_GR2,LCD_COLOR_GREEN);
	LCD_DrawLine(540,300-50,10,LCD_DIR_HORIZONTAL);
	LCD_SetBackColor(LCD_COLOR_BACK);
	DISP_CNL_S(290-50,10+540,"011");
	
	LCD_SetColors(LCD_COLOR_GR3,LCD_COLOR_GREEN);
	LCD_DrawLine(540,320-50,10,LCD_DIR_HORIZONTAL);
	LCD_SetBackColor(LCD_COLOR_BACK);
	DISP_CNL_S(310-50,10+540,"012");
	
	LCD_SetColors(LCD_COLOR_GR4,LCD_COLOR_GREEN);
	LCD_DrawLine(540,340-50,10,LCD_DIR_HORIZONTAL);
	LCD_SetBackColor(LCD_COLOR_BACK);
	DISP_CNL_S(330-50,10+540,"013");
	
	LCD_SetColors(LCD_COLOR_GR5,LCD_COLOR_GREEN);
	LCD_DrawLine(540,360-50,10,LCD_DIR_HORIZONTAL);
	LCD_SetBackColor(LCD_COLOR_BACK);
	DISP_CNL_S(350-50,10+540,"014");
	
	LCD_SetColors(LCD_COLOR_GR6,LCD_COLOR_GREEN);
	LCD_DrawLine(540,380-50,10,LCD_DIR_HORIZONTAL);
	LCD_SetBackColor(LCD_COLOR_BACK);
	DISP_CNL_S(370-50,10+540,"015");
	
	LCD_SetColors(LCD_COLOR_GR7,LCD_COLOR_GREEN);
	LCD_DrawLine(540,400-50,10,LCD_DIR_HORIZONTAL);
	LCD_SetBackColor(LCD_COLOR_BACK);
	DISP_CNL_S(390-50,10+540,"016");

	page_flag = history;
}

void Save_history(u16 rec)
{
//	SPI_FLASH_SectorErase(rec*4096);
	SPI_FLASH_BufferWrite((void*)Data_buf,8192+SPI_FLASH_PageSize*(rec-1), sizeof(Data_buf));
	
}

void Read_history(u16 rec)
{	u8 read_buf[15872];
	u8 i,j,k;
	SPI_FLASH_BufferRead((void *)read_buf,8192+15872*(rec-1), sizeof(read_buf));
	for(i = 0;i < 496;i ++)
	{
		for(j = 0;j < 16;j++)
		{
//			hisdata[j][i] = read_buff[];
		}
	}
}

void Save_time(u16 rec)
{
	SPI_FLASH_BufferWrite((void*)time_buf,15880192+SPI_FLASH_PageSize*(rec/62-1), sizeof(time_buf));
}

void Read_time(u16 rec)
{
	SPI_FLASH_BufferRead((void *)histime,15880192+SPI_FLASH_PageSize*(rec/62-1), sizeof(histime));
}
	
void Save_Sflag(void)
{`
	SPI_FLASH_SectorErase(1*4096);
	SPI_FLASH_BufferWrite((void*)his_config,SPI_FLASH_PageSize*16, sizeof(his_config));
}

void Read_Sflag(void)
{
	SPI_FLASH_BufferRead((void *)his_config,SPI_FLASH_PageSize*16, sizeof(his_config));
}
