//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "SynPublic.h"
#include <stdio.h>
#include <FileCtrl.hpp>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button19Click(TObject *Sender)
{
        Application->Terminate();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button17Click(TObject *Sender)
{
	int nRet,nPort;
	char sMsg[1024];
	unsigned char pucIIN[4];
	unsigned char pucSN[8];
	IDCardData idcardData;
 	int iPhototype;
	char   szBuffer[_MAX_PATH]={0};
	Syn_SetPhotoPath(0,szBuffer);	//������Ƭ·��	iOption ·��ѡ��	0=C:	1=��ǰ·��	2=ָ��·��
									//cPhotoPath	����·��,����iOption=2ʱ��Ч
	iPhototype = 0;
	Syn_SetPhotoType(0); //0 = bmp ,1 = jpg , 2 = base64 , 3 = WLT ,4 = ������
	Syn_SetPhotoName(2); // ������Ƭ�ļ��� 0=tmp 1=���� 2=���֤�� 3=����_���֤�� 
	
	Syn_SetSexType(1);	// 0=���д洢������	1=����֮�������,�С�Ů��δ֪
	Syn_SetNationType(1);// 0=���д洢������	1=����֮������� 2=����֮���"��"
	Syn_SetBornType(1);			// 0=YYYYMMDD,1=YYYY��MM��DD��,2=YYYY.MM.DD,3=YYYY-MM-DD,4=YYYY/MM/DD
	Syn_SetUserLifeBType(1);	// 0=YYYYMMDD,1=YYYY��MM��DD��,2=YYYY.MM.DD,3=YYYY-MM-DD,4=YYYY/MM/DD
	Syn_SetUserLifeEType(1,1);	// 0=YYYYMMDD(��ת��),1=YYYY��MM��DD��,2=YYYY.MM.DD,3=YYYY-MM-DD,4=YYYY/MM/DD,

	nPort = m_iPort;
	nRet = Syn_OpenPort(nPort);
	if (nRet == 0)
	{
		if ( Syn_SetMaxRFByte( nPort ,80 , 0) == 0)
		{
			Syn_StartFindIDCard( nPort , pucIIN , 0 );
			Syn_SelectIDCard( nPort , pucSN , 0 );
			if (Syn_ReadMsg( nPort , 0 , &idcardData) == 0)
			{
				sprintf(sMsg, "%s  ��ȡ���֤��Ϣ�ɹ�!",Now().DateTimeString());
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  ����:%s",Now().DateTimeString(),idcardData.Name);
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  �Ա�:%s",Now().DateTimeString(),idcardData.Sex);
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  ����:%s",Now().DateTimeString(),idcardData.Nation);
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  ����:%s",Now().DateTimeString(),idcardData.Born);
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  סַ:%s",Now().DateTimeString(),idcardData.Address);
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  ���֤��:%s",Now().DateTimeString(),idcardData.IDCardNo);
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  ��֤����:%s",Now().DateTimeString(),idcardData.GrantDept);
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  ��Ч�ڿ�ʼ:%s",Now().DateTimeString(),idcardData.UserLifeBegin);
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  ��Ч�ڽ���:%s",Now().DateTimeString(),idcardData.UserLifeEnd);
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  ��Ƭ:%s",Now().DateTimeString(),idcardData.PhotoFileName);
				ListBox1->Items->Add(sMsg);
                                if(iPhototype == 0 )
                                {
                                        img1->Picture->LoadFromFile(idcardData.PhotoFileName);
                                }
			}
			else
			{
				sprintf(sMsg,"%s  ��ȡ���֤��Ϣ����!",Now().DateTimeString());
				ListBox1->Items->Add(sMsg);
			}
		}
	}
	else
	{
		sprintf(sMsg , "%s  �򿪶˿ڴ���",Now().DateTimeString());
		ListBox1->Items->Add(sMsg);
	}
	Syn_ClosePort( nPort );
}
//---------------------------------------------------------------------------


void __fastcall TForm1::btn1Click(TObject *Sender)
{
        char sMsg[1024];
        int nPort=0;
        unsigned int nCurbaud;
        nPort = Syn_FindReader();
        m_iPort = nPort;
        if(nPort ==0)
        {
                sprintf(sMsg,"%s  û���ҵ�������",Now().DateTimeString());
        }
        else
        {
                Beep(4000,200);
                if(nPort > 1000)
                {
                        sprintf(sMsg,"%s  ������������USB %d ��",Now().DateTimeString(),nPort );

                }
                else
                {
                        Syn_GetCOMBaud(nPort,&nCurbaud);
                        sprintf(sMsg,"%s  �����������ڴ��� %d ��",Now().DateTimeString(),nPort);
                }
        }
        ListBox1->Items->Add(sMsg);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btn3Click(TObject *Sender)
{
        ListBox1->Items->Clear();
        img1->Picture = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btn2Click(TObject *Sender)
{
	int nRet,nPort;
	char sMsg[1024];
	unsigned char pucIIN[4];
	unsigned char pucSN[8];
	IDCardData idcardData;
 	int iPhototype;
	char   szBuffer[_MAX_PATH]={0};
        char szPath[256]={0};
	Syn_SetPhotoPath(0,szBuffer);	//������Ƭ·��	iOption ·��ѡ��	0=C:	1=��ǰ·��	2=ָ��·��
									//cPhotoPath	����·��,����iOption=2ʱ��Ч
	iPhototype = 0;
	Syn_SetPhotoType(0); //0 = bmp ,1 = jpg , 2 = base64 , 3 = WLT ,4 = ������
	Syn_SetPhotoName(2); // ������Ƭ�ļ��� 0=tmp 1=���� 2=���֤�� 3=����_���֤�� 
	
	Syn_SetSexType(1);	// 0=���д洢������	1=����֮�������,�С�Ů��δ֪
	Syn_SetNationType(1);// 0=���д洢������	1=����֮������� 2=����֮���"��"
	Syn_SetBornType(1);			// 0=YYYYMMDD,1=YYYY��MM��DD��,2=YYYY.MM.DD,3=YYYY-MM-DD,4=YYYY/MM/DD
	Syn_SetUserLifeBType(1);	// 0=YYYYMMDD,1=YYYY��MM��DD��,2=YYYY.MM.DD,3=YYYY-MM-DD,4=YYYY/MM/DD
	Syn_SetUserLifeEType(1,1);	// 0=YYYYMMDD(��ת��),1=YYYY��MM��DD��,2=YYYY.MM.DD,3=YYYY-MM-DD,4=YYYY/MM/DD,

	nPort = m_iPort;
	nRet = Syn_OpenPort(nPort);
	if (nRet == 0)
	{
		if ( Syn_SetMaxRFByte( nPort ,80 , 0) == 0)
		{
			Syn_StartFindIDCard( nPort , pucIIN , 0 );
			Syn_SelectIDCard( nPort , pucSN , 0 );
                        nRet = Syn_ReadFPMsg( m_iPort , 0 , &idcardData , szPath);
                        if ( nRet == 0 || nRet == 1)
			{
				sprintf(sMsg, "%s  ��ȡ���֤��Ϣ�ɹ�!",Now().DateTimeString());
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  ����:%s",Now().DateTimeString(),idcardData.Name);
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  �Ա�:%s",Now().DateTimeString(),idcardData.Sex);
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  ����:%s",Now().DateTimeString(),idcardData.Nation);
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  ����:%s",Now().DateTimeString(),idcardData.Born);
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  סַ:%s",Now().DateTimeString(),idcardData.Address);
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  ���֤��:%s",Now().DateTimeString(),idcardData.IDCardNo);
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  ��֤����:%s",Now().DateTimeString(),idcardData.GrantDept);
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  ��Ч�ڿ�ʼ:%s",Now().DateTimeString(),idcardData.UserLifeBegin);
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  ��Ч�ڽ���:%s",Now().DateTimeString(),idcardData.UserLifeEnd);
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  ��Ƭ:%s",Now().DateTimeString(),idcardData.PhotoFileName);
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  ָ��:%s",Now().DateTimeString(),szPath);
				ListBox1->Items->Add(sMsg);
                                if(iPhototype == 0 )
                                {
                                        img1->Picture->LoadFromFile(idcardData.PhotoFileName);
                                }
			}
			else
			{
				sprintf(sMsg,"%s  ��ȡ���֤��Ϣ����!",Now().DateTimeString());
				ListBox1->Items->Add(sMsg);
			}
		}
	}
	else
	{
		sprintf(sMsg , "%s  �򿪶˿ڴ���",Now().DateTimeString());
		ListBox1->Items->Add(sMsg);
	}
	Syn_ClosePort( nPort );
}
//---------------------------------------------------------------------------

