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
	Syn_SetPhotoPath(0,szBuffer);	//设置照片路径	iOption 路径选项	0=C:	1=当前路径	2=指定路径
									//cPhotoPath	绝对路径,仅在iOption=2时有效
	iPhototype = 0;
	Syn_SetPhotoType(0); //0 = bmp ,1 = jpg , 2 = base64 , 3 = WLT ,4 = 不生成
	Syn_SetPhotoName(2); // 生成照片文件名 0=tmp 1=姓名 2=身份证号 3=姓名_身份证号 
	
	Syn_SetSexType(1);	// 0=卡中存储的数据	1=解释之后的数据,男、女、未知
	Syn_SetNationType(1);// 0=卡中存储的数据	1=解释之后的数据 2=解释之后加"族"
	Syn_SetBornType(1);			// 0=YYYYMMDD,1=YYYY年MM月DD日,2=YYYY.MM.DD,3=YYYY-MM-DD,4=YYYY/MM/DD
	Syn_SetUserLifeBType(1);	// 0=YYYYMMDD,1=YYYY年MM月DD日,2=YYYY.MM.DD,3=YYYY-MM-DD,4=YYYY/MM/DD
	Syn_SetUserLifeEType(1,1);	// 0=YYYYMMDD(不转换),1=YYYY年MM月DD日,2=YYYY.MM.DD,3=YYYY-MM-DD,4=YYYY/MM/DD,

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
				sprintf(sMsg, "%s  读取身份证信息成功!",Now().DateTimeString());
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  姓名:%s",Now().DateTimeString(),idcardData.Name);
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  性别:%s",Now().DateTimeString(),idcardData.Sex);
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  民族:%s",Now().DateTimeString(),idcardData.Nation);
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  出生:%s",Now().DateTimeString(),idcardData.Born);
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  住址:%s",Now().DateTimeString(),idcardData.Address);
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  身份证号:%s",Now().DateTimeString(),idcardData.IDCardNo);
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  发证机关:%s",Now().DateTimeString(),idcardData.GrantDept);
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  有效期开始:%s",Now().DateTimeString(),idcardData.UserLifeBegin);
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  有效期结束:%s",Now().DateTimeString(),idcardData.UserLifeEnd);
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  照片:%s",Now().DateTimeString(),idcardData.PhotoFileName);
				ListBox1->Items->Add(sMsg);
                                if(iPhototype == 0 )
                                {
                                        img1->Picture->LoadFromFile(idcardData.PhotoFileName);
                                }
			}
			else
			{
				sprintf(sMsg,"%s  读取身份证信息错误!",Now().DateTimeString());
				ListBox1->Items->Add(sMsg);
			}
		}
	}
	else
	{
		sprintf(sMsg , "%s  打开端口错误",Now().DateTimeString());
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
                sprintf(sMsg,"%s  没有找到读卡器",Now().DateTimeString());
        }
        else
        {
                Beep(4000,200);
                if(nPort > 1000)
                {
                        sprintf(sMsg,"%s  读卡器连接在USB %d 上",Now().DateTimeString(),nPort );

                }
                else
                {
                        Syn_GetCOMBaud(nPort,&nCurbaud);
                        sprintf(sMsg,"%s  读卡器连接在串口 %d 上",Now().DateTimeString(),nPort);
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
	Syn_SetPhotoPath(0,szBuffer);	//设置照片路径	iOption 路径选项	0=C:	1=当前路径	2=指定路径
									//cPhotoPath	绝对路径,仅在iOption=2时有效
	iPhototype = 0;
	Syn_SetPhotoType(0); //0 = bmp ,1 = jpg , 2 = base64 , 3 = WLT ,4 = 不生成
	Syn_SetPhotoName(2); // 生成照片文件名 0=tmp 1=姓名 2=身份证号 3=姓名_身份证号 
	
	Syn_SetSexType(1);	// 0=卡中存储的数据	1=解释之后的数据,男、女、未知
	Syn_SetNationType(1);// 0=卡中存储的数据	1=解释之后的数据 2=解释之后加"族"
	Syn_SetBornType(1);			// 0=YYYYMMDD,1=YYYY年MM月DD日,2=YYYY.MM.DD,3=YYYY-MM-DD,4=YYYY/MM/DD
	Syn_SetUserLifeBType(1);	// 0=YYYYMMDD,1=YYYY年MM月DD日,2=YYYY.MM.DD,3=YYYY-MM-DD,4=YYYY/MM/DD
	Syn_SetUserLifeEType(1,1);	// 0=YYYYMMDD(不转换),1=YYYY年MM月DD日,2=YYYY.MM.DD,3=YYYY-MM-DD,4=YYYY/MM/DD,

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
				sprintf(sMsg, "%s  读取身份证信息成功!",Now().DateTimeString());
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  姓名:%s",Now().DateTimeString(),idcardData.Name);
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  性别:%s",Now().DateTimeString(),idcardData.Sex);
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  民族:%s",Now().DateTimeString(),idcardData.Nation);
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  出生:%s",Now().DateTimeString(),idcardData.Born);
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  住址:%s",Now().DateTimeString(),idcardData.Address);
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  身份证号:%s",Now().DateTimeString(),idcardData.IDCardNo);
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  发证机关:%s",Now().DateTimeString(),idcardData.GrantDept);
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  有效期开始:%s",Now().DateTimeString(),idcardData.UserLifeBegin);
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  有效期结束:%s",Now().DateTimeString(),idcardData.UserLifeEnd);
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  照片:%s",Now().DateTimeString(),idcardData.PhotoFileName);
				ListBox1->Items->Add(sMsg);
				sprintf(sMsg,"%s  指纹:%s",Now().DateTimeString(),szPath);
				ListBox1->Items->Add(sMsg);
                                if(iPhototype == 0 )
                                {
                                        img1->Picture->LoadFromFile(idcardData.PhotoFileName);
                                }
			}
			else
			{
				sprintf(sMsg,"%s  读取身份证信息错误!",Now().DateTimeString());
				ListBox1->Items->Add(sMsg);
			}
		}
	}
	else
	{
		sprintf(sMsg , "%s  打开端口错误",Now().DateTimeString());
		ListBox1->Items->Add(sMsg);
	}
	Syn_ClosePort( nPort );
}
//---------------------------------------------------------------------------

