#include "stm32f4xx.h"
#include "ff.h"
#include "jk508.h"
#include "./lcd/bsp_lcd.h"

char filename[20];
char foldername[20];
FILINFO hisinfo;
char dirname[10][13];
DIR dir;
FATFS fs;													/* FatFs�ļ�ϵͳ���� */
FIL fnew;													/* �ļ����� */
FRESULT res_sd;                /* �ļ�������� */
UINT fnum;            					  /* �ļ��ɹ���д���� */
BYTE ReadBuffer[1024]={0};        /* �������� */
//BYTE WriteBuffer[] =              /* д������*/



//��ȡ��ʷ�ļ��б�
void DISP_HIS(void)
{
	static u8 i;
	char buf[5];
	res_sd = f_mount(&fs,"0:",1);
	if(res_sd == FR_NO_FILESYSTEM)
	{
		DrawInstruction("�����ļ�ϵͳʧ�ܣ������¸�ʽ��");
	}else{
		DrawInstruction("�����ļ�ϵͳ�ɹ�");
	}
	
	res_sd = f_opendir(&dir, "");
	if(res_sd == FR_OK)
	{
		res_sd = f_readdir(&dir,&hisinfo);
		if(res_sd==FR_OK)
		{
			for(i=0;i<10;i++)
			{
				res_sd = f_readdir(&dir,&hisinfo);
				if(hisinfo.fname[0] == 0)
				{
					break;
				}
				sprintf(buf,"%d",i+1);
				LCD_DisplayStringLine(40+i*35,10,(uint8_t *)buf);
				LCD_DisplayStringLine(40+i*35,50,(uint8_t *)".");
				LCD_DisplayStringLine(40+i*35,70,(uint8_t *)hisinfo.fname);
			}
		}
		DrawInstruction("��ȡ��ʷ���ݳɹ�");
	}else{
		DrawInstruction("��ȡ��ʷ����ʧ��");
	}
	i = 0;
}
//��ʾ�ļ����б�
void DISP_HIS_FOLDER(void)
{
	static u8 i;
	char buf[5];
	res_sd = f_mount(&fs,"0:",1);
	if(res_sd == FR_NO_FILESYSTEM)
	{
		DrawInstruction("�����ļ�ϵͳʧ�ܣ������¸�ʽ��");
	}
	
	res_sd = f_opendir(&dir, "");
	if(res_sd == FR_OK)
	{
		if(res_sd==FR_OK)
		{
			while(1)
			{
				res_sd = f_readdir(&dir,&hisinfo);
				if(res_sd == FR_OK)
				{
					if(hisinfo.fname[0]==0)break;
					
					if(hisinfo.fattrib & AM_DIR)
					{
						sprintf(buf,"%d",i+1);
						LCD_DisplayStringLine(40+i*35,10,(uint8_t *)buf);
						LCD_DisplayStringLine(40+i*35,50,(uint8_t *)".");
						LCD_DisplayStringLine(40+i*35,70,(uint8_t *)hisinfo.fname);
						strncpy(dirname[i],hisinfo.fname,13);
						i++;
					}
				}
			}
		}
		DrawInstruction("��ȡĿ¼�ɹ�");
	}else{
		DrawInstruction("��ȡĿ¼ʧ��");
	}
	i = 0;
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
}

//�ļ�ϵͳ����ֵ��ʾ
void DISP_FS_RES(FRESULT res)
{
//	switch(res)
//	{
//		 
//	}
}


//�½��ļ���
void Creat_New_Folder(void)
{
	res_sd = f_mount(&fs,"0:",1);
	memset(filename,0,100);
	static u8  testcount;
	if(res_sd == FR_NO_FILESYSTEM)
	{
		DrawInstruction("�����ļ�ϵͳʧ�ܣ������¸�ʽ��");
	}else{
//		DrawInstruction("�����ļ�ϵͳ�ɹ�");
	}
	sprintf(foldername,"0:/%02d%02d%02d%d", 
			usbreadtime[1],
			usbreadtime[2],
			usbreadtime[3],
			testcount);
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

//��ָ���ļ���
void Open_Dir(void)
{
	memset(filename,0,100);
	
	sprintf(foldername,"0:/%02d%02d%02d", 
			usbreadtime[1],
			usbreadtime[2],
			usbreadtime[3]);
	res_sd = f_opendir(&dir,foldername);
}

//ɾ��ָ���ļ���
void Delete_file(char name)
{
	f_unlink(&name);
	
}

