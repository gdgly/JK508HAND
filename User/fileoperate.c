#include "stm32f4xx.h"
#include "ff.h"
#include "jk508.h"
#include "./lcd/bsp_lcd.h"



char filename[20];
char foldername[20];
FILINFO hisinfo;
DIR dir;
FATFS fs;													/* FatFs�ļ�ϵͳ���� */
FIL fnew;													/* �ļ����� */
FRESULT res_sd;                /* �ļ�������� */
UINT fnum;            					/* �ļ��ɹ���д���� */
BYTE ReadBuffer[1024]={0};        /* �������� */
char Dirname[MAXDIR][13];
char Filelist[MAXFILE][13];
u8 maxhispage,dirflag;
//BYTE WriteBuffer[] =              /* д������*/

//����SD��
void Mount_SD(void)
{
	res_sd = f_mount(&fs,"0:",1);
	if(res_sd == FR_NO_FILESYSTEM)
	{
		DrawInstruction("�����ļ�ϵͳʧ�ܣ������¸�ʽ��");
	}else{
		DrawInstruction("�����ļ�ϵͳ�ɹ�");
	}
}

//��ȡ��ʷ�ļ��б�
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
		DrawInstruction("��ȡ��ʷ���ݳɹ�");
	}else{
		DrawInstruction("��ȡ��ʷ����ʧ��");
	}
	i = 0;
}

//��ȡ�ļ����б�
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
		DrawInstruction("��ȡĿ¼�ɹ�");
	}else{
		DrawInstruction("��ȡĿ¼ʧ��");
	}
	i = 0;	
}

//��ʾ��ʷ�ļ�
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

//��ʾ��ʷ�����ļ���
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


//��ʷ������һҳ
void His_Npage(void)
{
	if(hispage < maxhispage)
	{
		hispage ++;
	}
	dirflag = 1;
	DISP_HIS_FOLDER();	
}

//��ʷ������һҳ
void His_Ppage(void)
{
	if(hispage > 1)
	{
		hispage --;
	}
	dirflag = 1;
	DISP_HIS_FOLDER();
}
//�����ļ��洢����
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
		DrawInstruction("�����ļ��ɹ�");
	}
	else
	{	
		DrawInstruction("����ʧ��");
	}
	READ_HIS_FOLDER();
}

//��ʽ��SD��
void Format_SD(void)
{
	f_mkfs("0:",0,0);
}


//�½��ļ���
void Creat_New_Folder(void)
{
//	res_sd = f_mount(&fs,"0:",1);
	memset(filename,0,100);
	static u8  testcount;
	if(res_sd == FR_NO_FILESYSTEM)
	{
		DrawInstruction("�����ļ�ϵͳʧ�ܣ������¸�ʽ��");
	}else{
//		DrawInstruction("�����ļ�ϵͳ�ɹ�");
	}
	sprintf(foldername,"0:/%02d%02d%02d", 
			usbreadtime[1],
			usbreadtime[2],
			usbreadtime[3]);
	res_sd = f_mkdir((char *)foldername);
	if(res_sd == FR_OK)
	{
		DrawInstruction("�ɹ�");
	}else if(res_sd == FR_EXIST){
		DrawInstruction("Ŀ¼�Ѵ���");
	}else{
		DrawInstruction("ʧ��");
	}
	testcount++;
}

//�Զ��洢����
void SD_Save_His(void)
{
	
}
////��ָ���ļ���
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

//ɾ��ָ���ļ���
void Delete_file(char name)
{
	f_unlink(&name);
	
}
