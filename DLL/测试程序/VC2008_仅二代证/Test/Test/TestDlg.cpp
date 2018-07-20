
// TestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Test.h"
#include "TestDlg.h"
#include "SynPublic.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestDlg 对话框




CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListMsg);
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CTestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CTestDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CTestDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CTestDlg 消息处理程序

BOOL CTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。

HCURSOR CTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CTestDlg::InsertDebugMes(CString sMsg)
{
	CString strTime;
	CTime   timTemp;
	timTemp = CTime::GetCurrentTime();
	strTime = timTemp.Format("%Y-%m-%d %H:%M:%S   ");
	sMsg = strTime + sMsg;
	m_ListMsg.InsertString(m_ListMsg.GetCount(),sMsg );
}

void CTestDlg::OnBnClickedButton1()
{
	int nRet;
	CString sMsg;
	CString sText;
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
								// 0=长期 不转换,	1=长期转换为 有效期开始+50年
	nRet = Syn_OpenPort(m_iPort);
	if (nRet == 0)
	{
		int nMaxRfByte = 0;
		nMaxRfByte = Syn_SetMaxRFByte(m_iPort, 80, 0);
		if (nMaxRfByte == 0)
		{
			nRet = Syn_StartFindIDCard( m_iPort , pucIIN , 0 );
			nRet = Syn_SelectIDCard( m_iPort , pucSN , 0 );
			nRet = Syn_ReadMsg( m_iPort , 0 , &idcardData);
			if ( nRet == 0 || nRet == 1)
			{
				sMsg= "读取身份证信息成功!";
				InsertDebugMes(sMsg);
				sMsg.Format("姓名:%s",idcardData.Name);
				InsertDebugMes(sMsg);
				sMsg.Format("性别:%s",idcardData.Sex);
				InsertDebugMes(sMsg);
				sMsg.Format("民族:%s",idcardData.Nation);
				InsertDebugMes(sMsg);
				sMsg.Format("出生:%s",idcardData.Born);
				InsertDebugMes(sMsg);
				sMsg.Format("住址:%s",idcardData.Address);
				InsertDebugMes(sMsg);
				sMsg.Format("身份证号:%s",idcardData.IDCardNo);
				InsertDebugMes(sMsg);
				sMsg.Format("发证机关:%s",idcardData.GrantDept);
				InsertDebugMes(sMsg);
				sMsg.Format("有效期开始:%s",idcardData.UserLifeBegin);
				InsertDebugMes(sMsg);
				sMsg.Format("有效期结束:%s",idcardData.UserLifeEnd);
				InsertDebugMes(sMsg);
				if (nRet == 1)
				{
					sMsg = "解码照片失败";
				}
				else
				{
					sMsg.Format("照片:%s",idcardData.PhotoFileName);
				}
				InsertDebugMes(sMsg);
				if (iPhototype == 0 && nRet == 0 )
				{
					HBITMAP hBitmap;
					CStatic *pStatic = (CStatic *)GetDlgItem(IDC_STATIC2);
					sText.Format("%s",idcardData.PhotoFileName);
					hBitmap = (HBITMAP) ::LoadImage(NULL,sText,IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
					pStatic->ModifyStyle(0XF,SS_BITMAP);
					pStatic->SetBitmap(hBitmap);					
				}
			}	
			else
			{
				sMsg = "读取身份证信息错误!";
				InsertDebugMes(sMsg);
			}
		}
		else {
			sMsg.Format("Syn_SetMaxRFByte, ret=%d", nMaxRfByte);
			InsertDebugMes(sMsg);
		}
	}
	else
	{
		sMsg = "打开端口错误";
		InsertDebugMes(sMsg);
	}
	Syn_ClosePort( m_iPort );
}

void CTestDlg::OnBnClickedButton2()
{
	CString sMsg,sMsg2;
	unsigned int uiCurrBaud; 
	int nRet,nRet2;
	m_iPort = 0;
	nRet = Syn_FindUSBReader();
	if ( nRet == 0)
	{
		sMsg = "没有找到读卡器";
	}
	else
	{
		m_iPort = nRet;
		Beep(4000,200);
		if (nRet >1000)
		{
			sMsg.Format("读卡器连接在USB端口 %d",nRet); 
		}
		else
		{
			Sleep(200);
			nRet2 = Syn_GetCOMBaud( nRet ,&uiCurrBaud);
			sMsg2.Format("%u",uiCurrBaud);
			sMsg.Format("读卡器连接在串口 %d,当前SAM波特率为 %u",nRet,uiCurrBaud); 
		}
	}
	InsertDebugMes(sMsg);
}

void CTestDlg::OnBnClickedButton4()
{
	int Num=m_ListMsg.GetCount();
	for (int i=Num-1; i>=0; i--)
	{
		m_ListMsg.DeleteString( i );
	}
	CStatic *pStatic = (CStatic *)GetDlgItem(IDC_STATIC2);
	pStatic->SetBitmap(NULL);					
}

void CTestDlg::OnBnClickedButton3()
{
	int nRet;
	CString sMsg;
	CString sText;
	unsigned char pucIIN[4];
	unsigned char pucSN[8];
	IDCardData idcardData;
	int iPhototype;
	char szBuffer[_MAX_PATH]={0};  
	char szPath[_MAX_PATH]={0};
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
	// 0=长期 不转换,	1=长期转换为 有效期开始+50年
	nRet = Syn_OpenPort(m_iPort);
	if (nRet == 0 )
	{
		if ( Syn_SetMaxRFByte( m_iPort ,80 , 0) == 0)
		{
			nRet = Syn_StartFindIDCard( m_iPort , pucIIN , 0 );
			nRet = Syn_SelectIDCard( m_iPort , pucSN , 0 );
			nRet = Syn_ReadFPMsg( m_iPort , 0 , &idcardData , szPath);
			if ( nRet == 0 || nRet == 1)
			{
				sMsg= "读取身份证信息成功!";
				InsertDebugMes(sMsg);
				sMsg.Format("姓名:%s",idcardData.Name);
				InsertDebugMes(sMsg);
				sMsg.Format("性别:%s",idcardData.Sex);
				InsertDebugMes(sMsg);
				sMsg.Format("民族:%s",idcardData.Nation);
				InsertDebugMes(sMsg);
				sMsg.Format("出生:%s",idcardData.Born);
				InsertDebugMes(sMsg);
				sMsg.Format("住址:%s",idcardData.Address);
				InsertDebugMes(sMsg);
				sMsg.Format("身份证号:%s",idcardData.IDCardNo);
				InsertDebugMes(sMsg);
				sMsg.Format("发证机关:%s",idcardData.GrantDept);
				InsertDebugMes(sMsg);
				sMsg.Format("有效期开始:%s",idcardData.UserLifeBegin);
				InsertDebugMes(sMsg);
				sMsg.Format("有效期结束:%s",idcardData.UserLifeEnd);
				InsertDebugMes(sMsg);
				if (nRet == 1)
				{
					sMsg = "解码照片失败";
				}
				else
				{
					sMsg.Format("照片:%s",idcardData.PhotoFileName);
				}
				InsertDebugMes(sMsg);
				if (iPhototype == 0 && nRet == 0)
				{
					HBITMAP hBitmap;
					CStatic *pStatic = (CStatic *)GetDlgItem(IDC_STATIC2);
					sText.Format("%s",idcardData.PhotoFileName);
					hBitmap = (HBITMAP) ::LoadImage(NULL,sText,IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
					pStatic->ModifyStyle(0XF,SS_BITMAP);
					pStatic->SetBitmap(hBitmap);					
				}
				if (nRet == 0 || nRet == 1)
				{
					sMsg.Format("指纹文件:%s",szPath);
					InsertDebugMes(sMsg);
				}
				else
				{
					sMsg = "没有指纹信息";
					InsertDebugMes(sMsg);
				}
			}	
			else
			{
				sMsg = "读取身份证信息错误!";
				InsertDebugMes(sMsg);
			}
		}
	}
	else
	{
		sMsg = "打开端口错误";
		InsertDebugMes(sMsg);
	}
	Syn_ClosePort( m_iPort );
}
