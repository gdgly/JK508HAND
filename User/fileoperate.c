#include "stm32f4xx.h"
#include "ff.h"
#include "jk508.h"
#include "./lcd/bsp_lcd.h"



char filename[20];
char foldername[20];
FILINFO hisinfo;
DIR dir;
FATFS fs;													/* FatFs文件系统对象 */
FIL fnew;													/* 文件对象 */
FRESULT res_sd;                /* 文件操作结果 */
UINT fnum;            					/* 文件成功读写数量 */
BYTE ReadBuffer[1024]={0};        /* 读缓冲区 */
char Dirname[MAXDIR][13];
char Filelist[MAXFILE][13];
u8 maxhispage,dirflag;
//BYTE WriteBuffer[] =              /* 写缓冲区*/

//加载SD卡
void Mount_SD(void)
{
	res_sd = f_mount(&fs,"0:",1);
	if(res_sd == FR_NO_FILESYSTEM)
	{
		DrawInstruction("加载文件系统失败，请重新格式化");
	}else{
		DrawInstruction("加载文件系统成功");
	}
}

//读取历史文件列表
void READ_HIS(void)
{
	static u8 i;
	char buf[5];
	
	res_sd = f_opendir(&dir,Dirname[(hispage-1)*10+(dirflag-1)]);
//	res_sd = f_opendir(&dir, "");
	if(res_sd == FR_OK)
	{
		for(i=0;i<100;i++)
		{
			res_sd = f_readdir(&dir,&hisinfo);
			if(hisinfo.fname[0] == 0)
			{		
				DISP_HIS_FILE();
				break;
			}
			strncpy(Filelist[i],hisinfo.fname,13);
		}
		DrawInstruction("读取历史数据成功");
	}else{
		DrawInstruction("读取历史数据失败");
	}
	i = 0;
}

//读取文件夹列表
void READ_HIS_FOLDER(void)
{
	static u16 i;
	char buf[5];

	
	res_sd = f_opendir(&dir, "");
	if(res_sd == FR_OK)
	{					
		for(i=0;i<300;i++)
		{
			res_sd = f_readdir(&dir,&hisinfo);
			if(hisinfo.fname[0] == 0)
			{
				maxhispage = i/10;
				DISP_HIS_FOLDER();
				break;
			}
			if(hisinfo.fattrib&AM_DIR)
			{
				strncpy(Dirname[i],hisinfo.fname,13);
			}
		}
		DrawInstruction("读取目录成功");
	}else{
		DrawInstruction("读取目录失败");
	}
	i = 0;	
}

//显示历史文件
void DISP_HIS_FILE(void)
{
	char buf[10],num[5];
	u8 i;
	
	LCD_SetColors(LCD_COLOR_BACK,LCD_COLOR_BACK);
	LCD_DrawFullRect(10,40,100,400);
	
	for(i=0;i<10;i++)
	{
		LCD_SetColors(LCD_COLOR_LIGHTBLUE,LCD_COLOR_BACK);
		sprintf(num,"%d",i+1);
		LCD_DisplayStringLine(40+i*35,10,(uint8_t *)num);
		LCD_DisplayStringLine(40+i*35,50,(uint8_t *)".");
		if(i+1 == dirflag)
		{
			LCD_SetColors(LCD_COLOR_BLACK,LCD_COLOR_YELLOW);			
		}else{
			LCD_SetColors(LCD_COLOR_YELLOW,LCD_COLOR_BACK);
		}
		LCD_DisplayStringLine(40+i*35,70,(uint8_t *)Filelist[i+10*(hispage-1)]);
	}
	LCD_SetColors(LCD_COLOR_YELLOW,LCD_COLOR_BACK);
	sprintf(buf,"%d/%d",hispage,maxhispage);
	LCD_DisplayStringLine(400,500,(uint8_t *)buf);
	page_flag = hisfile;
}

//显示历史数据文件夹
void DISP_HIS_FOLDER(void)
{
	char buf[10],num[5];
	u8 i;
	
	
	for(i=0;i<10;i++)
	{
		LCD_SetColors(LCD_COLOR_YELLOW,LCD_COLOR_BACK);
		sprintf(num,"%d",i+1);
		LCD_DisplayStringLine(40+i*35,10,(uint8_t *)num);
		LCD_DisplayStringLine(40+i*35,50,(uint8_t *)".");
		if(i+1 == dirflag)
		{
			LCD_SetColors(LCD_COLOR_BLACK,LCD_COLOR_YELLOW);			
		}else{
			LCD_SetColors(LCD_COLOR_YELLOW,LCD_COLOR_BACK);
		}
		LCD_DisplayStringLine(40+i*35,70,(uint8_t *)Dirname[i+10*(hispage-1)]);
	}
	LCD_SetColors(LCD_COLOR_YELLOW,LCD_COLOR_BACK);
	sprintf(buf,"%d/%d",hispage,maxhispage);
	LCD_DisplayStringLine(400,500,(uint8_t *)buf);
}


//历史数据下一页
void His_Npage(void)
{
	if(hispage < maxhispage)
	{
		hispage ++;
	}
	dirflag = 1;
	DISP_HIS_FOLDER();	
}

//历史数据下一页
void His_Ppage(void)
{
	if(hispage > 1)
	{
		hispage --;
	}
	dirflag = 1;
	DISP_HIS_FOLDER();
}
//建立文件存储数据
void Create_His_File(void)
{
	static char namebuf[10];
	static u8 i;
	
	memcpy ((void *)filename,"0:",2);
	sprintf(namebuf,"%02d%02d%02d%d", 
			usbreadtime[4],
			usbreadtime[5],
			usbreadtime[6],
			i);
	strcat((char *)filename,(char *)namebuf);
	strcat((char *)filename,(char *)".xls");	
	res_sd = f_open(&fnew, (char *)filename,FA_CREATE_ALWAYS | FA_WRITE );
	if ( res_sd == FR_OK )
	{
		DrawInstruction("创建文件成功");
	}
	else
	{	
		DrawInstruction("创建失败");
	}
	READ_HIS_FOLDER();
}

//格式化SD卡
void Format_SD(void)
{
	f_mkfs("0:",0,0);
}


//新建文件夹
void Creat_New_Folder(void)
{
//	res_sd = f_mount(&fs,"0:",1);
	memset(filename,0,100);
	static u8  testcount;
	if(res_sd == FR_NO_FILESYSTEM)
	{
		DrawInstruction("加载文件系统失败，请重新格式化");
	}else{
//		DrawInstruction("加载文件系统成功");
	}
	sprintf(foldername,"0:/%02d%02d%02d", 
			usbreadtime[1],
			usbreadtime[2],
			usbreadtime[3]);
	res_sd = f_mkdir((char *)foldername);
	if(res_sd == FR_OK)
	{
		DrawInstruction("成功");
	}else if(res_sd == FR_EXIST){
		DrawInstruction("目录已存在");
	}else{
		DrawInstruction("失败");
	}
	testcount++;
}

//自动存储数据
void SD_Save_His(void)
{
	
}
////打开指定文件夹
//void Open_Dir(void)
//{
//	memset(filename,0,100);
//	
//	sprintf(foldername,"0:/%02d%02d%02d", 
//			usbreadtime[1],
//			usbreadtime[2],
//			usbreadtime[3]);
//	res_sd = f_opendir(&dir,foldername);
//}

//删除指定文件夹
void Delete_file(char name)
{
	f_unlink(&name);
	
}

