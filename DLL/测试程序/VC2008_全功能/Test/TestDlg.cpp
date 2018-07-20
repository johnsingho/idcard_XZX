
// TestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Test.h"
#include "TestDlg.h"
#include "ID_Fpr_Public.H"
#include "ID_FprCap_Public.H"
#include "SynPublic.h"
#include "DIBAPI.H"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
unsigned char cTouchar(unsigned char cCard[2],unsigned char mode)
{
	unsigned char utmp[2];
	unsigned char uRet;
	for(int j=0;j<2;j++)
	{
		utmp[j] = 0;
	}
	for(int i = 0;i<2;i++)
	{
		if(cCard[i]<='F' && cCard[i]>='A')
		{
			utmp[i] = cCard[i] - 'A' + 10;
		}
		if(cCard[i]<='f' && cCard[i]>='a')
		{
			utmp[i] = cCard[i] - 'a' + 10;
		}
		if(cCard[i]<='9' && cCard[i]>='0')
		{
			utmp[i] = cCard[i] - '0';
		}
	}
	if (mode ==2) {
		uRet = utmp[0]*0X10 + utmp[1] ;
	}
	else
	{
		uRet = utmp[1]*0X10 + utmp[0] ;
	}
	return uRet;
}

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


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
	DDX_Control(pDX, IDC_LIST2, m_ListView);
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTFINDREADER, &CTestDlg::OnBnClickedButfindreader)
	ON_BN_CLICKED(IDC_BUTCLEARMES, &CTestDlg::OnBnClickedButclearmes)
	ON_BN_CLICKED(IDC_BUTGETSAMSTATE, &CTestDlg::OnBnClickedButgetsamstate)
	ON_BN_CLICKED(IDC_BUTSETMAX, &CTestDlg::OnBnClickedButsetmax)
	ON_BN_CLICKED(IDC_BUTRESTSAM, &CTestDlg::OnBnClickedButrestsam)
	ON_BN_CLICKED(IDC_BUTGETSAMID, &CTestDlg::OnBnClickedButgetsamid)
	ON_BN_CLICKED(IDC_BUTFINDCARD, &CTestDlg::OnBnClickedButfindcard)
	ON_BN_CLICKED(IDC_BUTSELECTCARD, &CTestDlg::OnBnClickedButselectcard)
	ON_BN_CLICKED(IDC_BUTREADCARD, &CTestDlg::OnBnClickedButreadcard)
	ON_BN_CLICKED(IDC_BUTREADCARD2, &CTestDlg::OnBnClickedButreadcard2)
	ON_BN_CLICKED(IDC_BUTSTARTREAD, &CTestDlg::OnBnClickedButstartread)
	ON_BN_CLICKED(IDC_BUTREADCARDEX, &CTestDlg::OnBnClickedButreadcardex)
	ON_BN_CLICKED(IDC_BUTREADCARDEX2, &CTestDlg::OnBnClickedButreadcardex2)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTSTOPREAD, &CTestDlg::OnBnClickedButstopread)
	ON_BN_CLICKED(IDC_BUTFP_EXT, &CTestDlg::OnBnClickedButfpExt)
	ON_BN_CLICKED(IDC_BUTSOUND, &CTestDlg::OnBnClickedButsound)
	ON_BN_CLICKED(IDC_BUTFINDFP, &CTestDlg::OnBnClickedButfindfp)
	ON_BN_CLICKED(IDC_BUTGETVER, &CTestDlg::OnBnClickedButgetver)
	ON_BN_CLICKED(IDC_BUTGETDESC, &CTestDlg::OnBnClickedButgetdesc)
	ON_BN_CLICKED(IDC_BUTCLOSEFP, &CTestDlg::OnBnClickedButclosefp)
	ON_BN_CLICKED(IDC_BUTBEGINCAP, &CTestDlg::OnBnClickedButbegincap)
	ON_BN_CLICKED(IDC_BUTGETFPRAW, &CTestDlg::OnBnClickedButgetfpraw)
	ON_BN_CLICKED(IDC_BUTREADERUSERINFO, &CTestDlg::OnBnClickedButreaderuserinfo)
	ON_BN_CLICKED(IDC_BUTWRITEUSERINFO, &CTestDlg::OnBnClickedButwriteuserinfo)
	ON_BN_CLICKED(IDC_BUTREADFAC, &CTestDlg::OnBnClickedButreadfac)
	ON_BN_CLICKED(IDC_BUTWRITEFAC, &CTestDlg::OnBnClickedButwritefac)
	ON_BN_CLICKED(IDC_BUTENDCAP, &CTestDlg::OnBnClickedButendcap)
	ON_BN_CLICKED(IDC_BUTGETFPBMP, &CTestDlg::OnBnClickedButgetfpbmp)
	ON_BN_CLICKED(IDC_BUTTON5, &CTestDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON3, &CTestDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTestDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &CTestDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CTestDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON9, &CTestDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CTestDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CTestDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CTestDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_M1RESET, &CTestDlg::OnBnClickedM1reset)
	ON_BN_CLICKED(IDC_M1HALT, &CTestDlg::OnBnClickedM1halt)
	ON_BN_CLICKED(IDC_BUTTON_AUTHENA, &CTestDlg::OnBnClickedButtonAuthena)
	ON_BN_CLICKED(IDC_BUTTON_AUTHENB, &CTestDlg::OnBnClickedButtonAuthenb)
	ON_BN_CLICKED(IDC_BUTTON_READ, &CTestDlg::OnBnClickedButtonRead)
	ON_BN_CLICKED(IDC_BUTTON_WRITE, &CTestDlg::OnBnClickedButtonWrite)
	ON_BN_CLICKED(IDC_BUTTON14, &CTestDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON17, &CTestDlg::OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON16, &CTestDlg::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON18, &CTestDlg::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON13, &CTestDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON15, &CTestDlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON_CHANGA, &CTestDlg::OnBnClickedButtonChanga)
	ON_BN_CLICKED(IDC_BUTTON_CHANGB, &CTestDlg::OnBnClickedButtonChangb)
	ON_BN_CLICKED(IDC_BUTTON19, &CTestDlg::OnBnClickedButton19)
	ON_BN_CLICKED(IDC_BUTTON20, &CTestDlg::OnBnClickedButton20)
	ON_BN_CLICKED(IDC_BUTTON1, &CTestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTFP_BRI, &CTestDlg::OnBnClickedButfpBri)
	ON_BN_CLICKED(IDC_BUTFP_CON, &CTestDlg::OnBnClickedButfpCon)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDCANCEL, &CTestDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON21, &CTestDlg::OnBnClickedButton21)
	ON_BN_CLICKED(IDC_BUTTON23, &CTestDlg::OnBnClickedButton23)
	ON_BN_CLICKED(IDC_BUTTON22, &CTestDlg::OnBnClickedButton22)
	ON_BN_CLICKED(IDC_BUTTON24, &CTestDlg::OnBnClickedButton24)
	ON_BN_CLICKED(IDC_BUTTON8, &CTestDlg::OnBnClickedButton8)
END_MESSAGE_MAP()


// CTestDlg 消息处理程序

BOOL CTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	GetDlgItem(IDC_EDIT1)->SetWindowText("10");
	m_iLoopSum = 10;
	GetDlgItem(IDC_EDIT_BRI)->SetWindowText("128");
	GetDlgItem(IDC_EDIT_CON)->SetWindowText("128");
	GetDlgItem(IDC_EDIT_FAC1)->SetWindowText("SYNJONES");
	GetDlgItem(IDC_EDIT_FAC2)->SetWindowText("V1.0");
	GetDlgItem(IDC_EDIT_FAC3)->SetWindowText("00000001");
	GetDlgItem(IDC_EDIT_FAC4)->SetWindowText("");
	GetDlgItem(IDC_EDIT_USERINFO)->SetWindowText("");

	GetDlgItem(IDC_EDIT_SECNO)->SetWindowText("0");
	GetDlgItem(IDC_EDIT_BLOCKNO)->SetWindowText("1");
	GetDlgItem(IDC_EDIT_OLDPASS0)->SetWindowText("FF");
	GetDlgItem(IDC_EDIT_OLDPASS1)->SetWindowText("FF");
	GetDlgItem(IDC_EDIT_OLDPASS2)->SetWindowText("FF");
	GetDlgItem(IDC_EDIT_OLDPASS3)->SetWindowText("FF");
	GetDlgItem(IDC_EDIT_OLDPASS4)->SetWindowText("FF");
	GetDlgItem(IDC_EDIT_OLDPASS5)->SetWindowText("FF");
	GetDlgItem(IDC_EDIT_NEWPASS0)->SetWindowText("00");
	GetDlgItem(IDC_EDIT_NEWPASS1)->SetWindowText("00");
	GetDlgItem(IDC_EDIT_NEWPASS2)->SetWindowText("00");
	GetDlgItem(IDC_EDIT_NEWPASS3)->SetWindowText("00");
	GetDlgItem(IDC_EDIT_NEWPASS4)->SetWindowText("00");
	GetDlgItem(IDC_EDIT_NEWPASS5)->SetWindowText("00");

	GetDlgItem(IDC_EDIT_DATA0)->SetWindowText("00");
	GetDlgItem(IDC_EDIT_DATA1)->SetWindowText("11");
	GetDlgItem(IDC_EDIT_DATA2)->SetWindowText("22");
	GetDlgItem(IDC_EDIT_DATA3)->SetWindowText("33");
	GetDlgItem(IDC_EDIT_DATA4)->SetWindowText("44");
	GetDlgItem(IDC_EDIT_DATA5)->SetWindowText("55");
	GetDlgItem(IDC_EDIT_DATA6)->SetWindowText("66");
	GetDlgItem(IDC_EDIT_DATA7)->SetWindowText("77");
	GetDlgItem(IDC_EDIT_DATA8)->SetWindowText("88");
	GetDlgItem(IDC_EDIT_DATA9)->SetWindowText("99");
	GetDlgItem(IDC_EDIT_DATA10)->SetWindowText("AA");
	GetDlgItem(IDC_EDIT_DATA11)->SetWindowText("BB");
	GetDlgItem(IDC_EDIT_DATA12)->SetWindowText("CC");
	GetDlgItem(IDC_EDIT_DATA13)->SetWindowText("DD");
	GetDlgItem(IDC_EDIT_DATA14)->SetWindowText("EE");
	GetDlgItem(IDC_EDIT_DATA15)->SetWindowText("FF");


	m_iPort = 0;
	m_iReadType = 0;
	m_iReadSum = 0;
	m_iReadOKSum = 0;
	m_iReadStart = 0;
	m_ListView.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP);

	m_ListView.InsertColumn(0,"发生时间",LVCFMT_LEFT,140);
	m_ListView.InsertColumn(1,"信息",LVCFMT_LEFT,530);

	CComboBox* combo= ( CComboBox*)GetDlgItem(IDC_COMBO1);
	combo->AddString("0BH右手拇指"); 
	combo->AddString("0CH右手食指 ");
	combo->AddString("0DH右手中指");
	combo->AddString("0EH右手环指 ");
	combo->AddString("0FH右手小指 ");
	combo->AddString("10H左手拇指");
	combo->AddString("11H左手食指");
	combo->AddString("12H左手中指");
	combo->AddString("13H左手环指");
	combo->AddString("14H左手小指");

	combo->AddString("20H");
	combo->AddString("21H");
	combo->AddString("22H");
	combo->AddString("23H");
	combo->AddString("24H");
	combo->AddString("25H");
	combo->AddString("26H");
	combo->AddString("27H");
	combo->AddString("28H");
	combo->AddString("29H");
	combo->AddString("2AH");
	combo->AddString("2BH");
	combo->AddString("2CH");
	combo->AddString("2DH");
	combo->AddString("2EH");
	combo->AddString("2FH");

	combo->SetCurSel(0);// 
	BOOL bol;
	bol = OpenLogFile();
	if (!bol)
	{
		AfxMessageBox("打开日志文件错误，不能写入系统日志！");
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
BOOL CTestDlg::OpenLogFile()
{
	CString strFile;
	CTime	tLog = CTime::GetCurrentTime();
	_mkdir(".\\LOG");
	strFile = tLog.Format(".\\Log\\%Y-%m-%d.txt");
	return m_fLog.Open((LPCTSTR) strFile ,CFile::modeNoTruncate | 
		CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite);
}
void CTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
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
	CString strMes;
	timTemp = CTime::GetCurrentTime();
	strTime = timTemp.Format("%Y-%m-%d %H:%M:%S");
	if(m_ListView.GetItemCount()>200)
	{
		m_ListView.DeleteAllItems();	
	}
	m_ListView.InsertItem(LVIF_IMAGE| LVIF_TEXT|LVIF_STATE, 0, strTime,0,0,0,0);
	m_ListView.SetItemText(0, 1,sMsg );
	strMes = strTime+"    "+sMsg+"\r\n";
	m_fLog.SeekToEnd();
	m_fLog.Write(strMes,strMes.GetLength());
/*	CString strTime;
	CTime   timTemp;
	timTemp = CTime::GetCurrentTime();
	strTime = timTemp.Format("%Y-%m-%d %H:%M:%S   ");
	sMsg = strTime + sMsg;
	m_ListMsg.InsertString(m_ListMsg.GetCount(),sMsg );*/
}
void CTestDlg::OnBnClickedButfindreader()
{
	CString sMsg,sMsg2;
	unsigned int uiCurrBaud; 
	int nRet,nRet2;
	unsigned char nARMVol;
	m_iPort = 0;
	CCalcTime tSpan;
	tSpan.Clear();
	tSpan.BegginTime();
	nRet = Syn_FindUSBReader();
	tSpan.EndTime();
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
			sMsg.Format("读卡器连接在USB端口 %d,%d ms",nRet,tSpan.MSecond); 
		}
		else
		{
			Sleep(200);
			nRet2 = Syn_GetCOMBaud( nRet ,&uiCurrBaud);
			sMsg2.Format("%u",uiCurrBaud);
			sMsg.Format("读卡器连接在串口 %d,当前SAM波特率为 %u ,%d ms",nRet,uiCurrBaud,tSpan.MSecond); 
		}
	}
	InsertDebugMes(sMsg);
	if (m_iPort == 9999)
	{
		nRet = Syn_OpenPort(m_iPort);
		nRet = Syn_USBHIDGetMaxByte(m_iPort,&m_iMaxByte,&nARMVol);
		nRet = Syn_ClosePort(m_iPort);
		sMsg.Format("读卡器支持的最大通讯字节数为%d,版本%d",m_iMaxByte,nARMVol);
		sMsg2.Format("%d",m_iMaxByte);
		GetDlgItem(IDC_EDIT_MAX)->SetWindowText(sMsg2);
		InsertDebugMes(sMsg);
	}
}

void CTestDlg::OnBnClickedButclearmes()
{
/*	int Num=m_ListMsg.GetCount();
	for (int i=Num-1; i>=0; i--)
	{
		m_ListMsg.DeleteString( i );
	}*/
	m_ListView.DeleteAllItems();	
	CStatic *pStatic = (CStatic *)GetDlgItem(IDC_STATIC2);
	pStatic->SetBitmap(NULL);					
//	CStatic *pStatic2 = (CStatic *)GetDlgItem(IDC_STATIC3);
//	pStatic2->SetBitmap(NULL);			
	CWnd *wnd=GetDlgItem(IDC_STATIC3);
	CDC  *dc=GetDlgItem(IDC_STATIC3)->GetDC(); 
	CRect rect;
	wnd->GetClientRect(&rect);
	::ClearAll(dc,rect);             //显示位图API函数

}

void CTestDlg::OnBnClickedButgetsamstate()
{
	CString sMsg;
	int nRet;
	if (m_iPort == 9999)
	{
		sMsg = "该读卡器不支持此命令";
		InsertDebugMes(sMsg);
		return ;
	}
	nRet = Syn_OpenPort(m_iPort);
	if (nRet == 0)
	{
		CCalcTime tSpan;
		tSpan.Clear();
		tSpan.BegginTime();
		nRet = Syn_GetSAMStatus(m_iPort,0);
		tSpan.EndTime();
		if (nRet == 0)
		{
			sMsg.Format("获得SAM状态成功，状态正常, %d ms",tSpan.MSecond);
		}
		else
		{
			sMsg.Format("获得SAM状态错误，nRet=%d , %d ms",nRet,tSpan.MSecond);
		}
	}
	else
	{
		sMsg = "打开端口错误";
	}
	if (m_iPort>0)
	{
		Syn_ClosePort(m_iPort);
	}
	InsertDebugMes(sMsg);
}

void CTestDlg::OnBnClickedButsetmax()
{
	int nRet;
	int iMaxByte;
	CString sMsg,sMsg2;
	if (m_iPort == 9999)
	{
		sMsg2.Format("%d",m_iMaxByte);
		GetDlgItem(IDC_EDIT_MAX)->SetWindowText(sMsg2);
	}
	GetDlgItem(IDC_EDIT_MAX)->GetWindowText(sMsg2);
	iMaxByte = atoi(sMsg2);
	nRet = Syn_OpenPort( m_iPort );
	if (nRet == 0)
	{
		CCalcTime tSpan;
		tSpan.Clear();
		tSpan.BegginTime();
		nRet =Syn_SetMaxRFByte( m_iPort ,iMaxByte,0);
		tSpan.EndTime();
		if( nRet == 0)
		{
			sMsg.Format("设置最大通讯字节数成功,最大通讯字节数为 %d , %d ms",iMaxByte,tSpan.MSecond);
		}
		else
		{
			sMsg.Format("设置最大通讯字节数出错, %d ms",tSpan.MSecond);
		}
	}
	else
	{
		sMsg = "打开端口错误！";
	}
	if (m_iPort >0)
	{
		Syn_ClosePort( m_iPort );
	}
	InsertDebugMes(sMsg);
}

void CTestDlg::OnBnClickedButrestsam()
{
	int nRet,iPort;
	CString sMsg;
	iPort = m_iPort;
	if (m_iPort == 9999)
	{
		sMsg = "该读卡器不支持此命令";
		InsertDebugMes(sMsg);
		return ;
	}
	nRet = Syn_OpenPort(iPort);
	if (nRet == 0)
	{
		CCalcTime tSpan;
		tSpan.Clear();
		tSpan.BegginTime();
		nRet = Syn_ResetSAM( iPort , 0 );
		tSpan.EndTime();
		if (nRet == 0)
		{
			sMsg.Format("复位SAM模块成功, %d ms",tSpan.MSecond);
		}
		else
		{
			sMsg.Format("复位SAM模块失败, %d ms",tSpan.MSecond);
		}
	}
	else
	{
		sMsg = "打开端口错误";
	}
	if (iPort >0)
	{
		Syn_ClosePort( iPort );
	}
	InsertDebugMes( sMsg );
}

void CTestDlg::OnBnClickedButgetsamid()
{
	int nRet,iPort;	
	unsigned char cSAMID[16];
	unsigned int uSAMID[4];
	memset(cSAMID,0,16);
	CString sMsg;
	CString sText,strFile;	
	CString strTime;
	CTime   timTemp;
	iPort = m_iPort;
	nRet = Syn_OpenPort( iPort );
	if (nRet == 0)
	{
		CCalcTime tSpan;
		tSpan.Clear();
		tSpan.BegginTime();
		nRet = Syn_GetSAMID( iPort , cSAMID,0 );
		tSpan.EndTime();
		if (nRet == 0)
		{
			memcpy(uSAMID,cSAMID,16);
			sMsg.Format("按16字节获得SAM模块ID成功,SAM模块ID为: %X%X-%X%X-%u-%0.10u-%0.10u, %d ms",cSAMID[1],cSAMID[0],cSAMID[3],cSAMID[2],uSAMID[1],uSAMID[2],uSAMID[3],tSpan.MSecond);
			CFile		m_fLog;
			CTime	tLog = CTime::GetCurrentTime();
			strFile = tLog.Format(".\\%Y-%m-%d.CSV");
			m_fLog.Open((LPCTSTR) strFile ,CFile::modeNoTruncate | 
				CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite);
			timTemp = CTime::GetCurrentTime();
			strTime = timTemp.Format("%Y-%m-%d %H:%M:%S");
			memcpy(uSAMID,cSAMID,16);
			sText.Format("%0X%0X-%0X%0X-%u-%0.10u-%0.10u,\r\n",cSAMID[1],cSAMID[0],cSAMID[3],cSAMID[2],uSAMID[1],uSAMID[2],uSAMID[3]);
			sText = strTime + "," + sText;
			m_fLog.SeekToEnd();
			m_fLog.Write(sText,sText.GetLength());
		}
		else
		{
			sMsg.Format("读取SAM ID号错误, %d ms",tSpan.MSecond);
		}
	}
	else
	{
		sMsg = "打开端口错误";
	}
	if (iPort>0)
	{
		Syn_ClosePort( iPort );
	}
	InsertDebugMes( sMsg );
}

void CTestDlg::OnBnClickedButfindcard()
{
	int nRet;
	CString sMsg;
	unsigned char pucIIN[4];
	nRet = Syn_OpenPort(m_iPort);
	if (nRet == 0)
	{
		CCalcTime tSpan;
		tSpan.Clear();
		tSpan.BegginTime();
		nRet = Syn_StartFindIDCard(m_iPort,pucIIN,0);
		tSpan.EndTime();
		if (nRet == 0)
		{
			sMsg.Format("寻卡成功, %d ms",tSpan.MSecond);
		}
		else
		{
			sMsg.Format("寻卡失败,nRet = %d, %d ms",nRet,tSpan.MSecond);
		}
	}
	else
	{
		sMsg = "打开端口错误";
	}
	if (m_iPort>0)
	{
		Syn_ClosePort(m_iPort);
	}
	InsertDebugMes(sMsg);	
}

void CTestDlg::OnBnClickedButselectcard()
{
	int nRet;
	CString sMsg;
	unsigned char pucSN[8];
	nRet = Syn_OpenPort(m_iPort);
	if (nRet == 0)
	{
		CCalcTime tSpan;
		tSpan.Clear();
		tSpan.BegginTime();
		nRet = Syn_SelectIDCard(m_iPort,pucSN,0);
		tSpan.EndTime();
		if (nRet == 0)
		{
			sMsg.Format("选卡成功, %d ms",tSpan.MSecond);
		}
		else
		{
			sMsg.Format("选卡失败,nRet = %d, %d ms",nRet,tSpan.MSecond);
		}
	}
	else
	{
		sMsg = "打开端口错误";
	}
	if (m_iPort>0)
	{
		Syn_ClosePort(m_iPort);
	}
	InsertDebugMes(sMsg);	
}

void CTestDlg::OnBnClickedButreadcard()
{
	int nRet ;
	CString sMsg;
	IDCardData idcardData;
	char ctmp[256]={0};
	Syn_SetPhotoPath(1,ctmp);
	Syn_SetPhotoName(3);
	nRet = Syn_OpenPort(m_iPort);
	if (nRet == 0)
	{
		CCalcTime tSpan;
		tSpan.Clear();
		tSpan.BegginTime();
		nRet = Syn_ReadMsg(m_iPort,0,&idcardData);
		tSpan.EndTime();
		if (m_iReadStart==1)
		{
			m_iReadSum++;
		}
		if (nRet == 0)
		{
			if (m_iReadStart == 1)
			{
				m_iReadOKSum++;
			}
			sMsg.Format("读取身份证信息成功, %d ms",tSpan.MSecond);
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
//			sMsg.Format("照片:%s",idcardData.PhotoFileName);
//			InsertDebugMes(sMsg);
			HBITMAP hBitmap;
			CStatic *pStatic = (CStatic *)GetDlgItem(IDC_STATIC2);
			sMsg.Format("%s",idcardData.PhotoFileName);
			hBitmap = (HBITMAP) ::LoadImage(NULL,sMsg,IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
			pStatic->ModifyStyle(0XF,SS_BITMAP);
			pStatic->SetBitmap(hBitmap);					

		}
		else
		{
			sMsg.Format("读取身份证信息错误, %d ms",tSpan.MSecond);
			InsertDebugMes(sMsg);
		}
	}
	else
	{
		sMsg = "打开端口错误";
		InsertDebugMes(sMsg);	
	}
	if (m_iPort>0)
	{
		Syn_ClosePort(m_iPort);
	}
}

void CTestDlg::OnBnClickedButreadcard2()
{
	int nRet ;
	CString sMsg;
	IDCardData idcardData;
	char ctmp[256]={0};
	char szPath[_MAX_PATH]={0};
	Syn_SetPhotoPath(1,ctmp);
	Syn_SetPhotoName(3);
	nRet = Syn_OpenPort(m_iPort);
	if (nRet == 0)
	{
		CCalcTime tSpan;
		tSpan.Clear();
		tSpan.BegginTime();
		nRet = Syn_ReadFPMsg(m_iPort,0,&idcardData,szPath);
		tSpan.EndTime();
		if (m_iReadStart == 1)
		{
			m_iReadSum++;
		}
		if (nRet == 0)
		{
			if (m_iReadStart==1)
			{
				m_iReadOKSum++;
			}
			sMsg.Format("读取身份证信息(含指纹)成功, %d ms",tSpan.MSecond);
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
			//			sMsg.Format("照片:%s",idcardData.PhotoFileName);
			//			InsertDebugMes(sMsg);
			HBITMAP hBitmap;
			CStatic *pStatic = (CStatic *)GetDlgItem(IDC_STATIC2);
			sMsg.Format("%s",idcardData.PhotoFileName);
			hBitmap = (HBITMAP) ::LoadImage(NULL,sMsg,IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
			pStatic->ModifyStyle(0XF,SS_BITMAP);
			pStatic->SetBitmap(hBitmap);					
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
			sMsg.Format("读取身份证信息错误, %d ms",tSpan.MSecond);
			InsertDebugMes(sMsg);
		}
	}
	else
	{
		sMsg = "打开端口错误";
		InsertDebugMes(sMsg);	
	}
	if (m_iPort>0)
	{
		Syn_ClosePort(m_iPort);
	}
}

void CTestDlg::OnBnClickedButstartread()
{
	m_iReadType = ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck();
	KillTimer(m_iTime);
	m_iReadStart = 1;
	m_iReadSum = 0;
	m_iReadOKSum = 0;
	m_iTime =	SetTimer(1,1000,0);
}

void CTestDlg::OnBnClickedButreadcardex()
{
	int nRet ;
	unsigned char pucIIN[4];
	unsigned char pucSN[8];
	CString sMsg;
	IDCardData idcardData;
	char ctmp[256]={0};
	try
	{
		Syn_SetPhotoPath(1,ctmp);
		Syn_SetPhotoName(3);
		nRet = Syn_OpenPort(m_iPort);
		if (nRet == 0)
		{
			CCalcTime tSpan;
			tSpan.Clear();
			tSpan.BegginTime();
			nRet = Syn_StartFindIDCard(m_iPort,pucIIN,0);
			nRet = Syn_SelectIDCard(m_iPort,pucSN,0);
			nRet = Syn_ReadMsg(m_iPort,0,&idcardData);
			tSpan.EndTime();
			if (m_iReadStart==1)
			{
				m_iReadSum++;
			}
			if (nRet == 0)
			{
				if (m_iReadStart == 1)
				{
					m_iReadOKSum++;
				}
				sMsg.Format("完整过程读取身份证信息成功, %d ms",tSpan.MSecond);
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
				//			sMsg.Format("照片:%s",idcardData.PhotoFileName);
				//			InsertDebugMes(sMsg);
				HBITMAP hBitmap;
				CStatic *pStatic = (CStatic *)GetDlgItem(IDC_STATIC2);
				sMsg.Format("%s",idcardData.PhotoFileName);
				hBitmap = (HBITMAP) ::LoadImage(NULL,sMsg,IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
				pStatic->ModifyStyle(0XF,SS_BITMAP);
				pStatic->SetBitmap(hBitmap);					

			}
			else
			{
				sMsg.Format("完整过程读取身份证信息错误,nRet = %d, %d ms",nRet,tSpan.MSecond);
				InsertDebugMes(sMsg);
			}
		}
		else
		{
			sMsg = "打开端口错误";
			InsertDebugMes(sMsg);	
		}
		if (m_iPort>0)
		{
			Syn_ClosePort(m_iPort);
		}
	}
	catch (CMemoryException* e)
	{
		e->Delete();
		AfxMessageBox("eRR1");
	}
	catch (CFileException* e)
	{
		e->Delete();
		AfxMessageBox("eRR2");
	}
	catch (CException* e)
	{
		e->Delete();
		AfxMessageBox("eRR3");
	}

}

void CTestDlg::OnBnClickedButreadcardex2()
{
	int nRet ;
	unsigned char pucIIN[4];
	unsigned char pucSN[8];
	CString sMsg;
	IDCardData idcardData;
	char ctmp[256]={0};
	char szPath[_MAX_PATH]={0};
	Syn_SetPhotoPath(1,ctmp);
	Syn_SetPhotoName(3);
	nRet = Syn_OpenPort(m_iPort);
	if (nRet == 0)
	{
		CCalcTime tSpan;
		tSpan.Clear();
		tSpan.BegginTime();
		nRet = Syn_StartFindIDCard(m_iPort,pucIIN,0);
		nRet = Syn_SelectIDCard(m_iPort,pucSN,0);
		nRet = Syn_ReadFPMsg(m_iPort,0,&idcardData,szPath);
		tSpan.EndTime();
		if (m_iReadStart == 1)
		{
			m_iReadSum++;
		}
		if (nRet == 0)
		{
			if (m_iReadStart==1)
			{
				m_iReadOKSum++;
			}
			sMsg.Format("完整过程读取身份证信息(含指纹)成功, %d ms",tSpan.MSecond);
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
			//			sMsg.Format("照片:%s",idcardData.PhotoFileName);
			//			InsertDebugMes(sMsg);
			HBITMAP hBitmap;
			CStatic *pStatic = (CStatic *)GetDlgItem(IDC_STATIC2);
			sMsg.Format("%s",idcardData.PhotoFileName);
			hBitmap = (HBITMAP) ::LoadImage(NULL,sMsg,IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
			pStatic->ModifyStyle(0XF,SS_BITMAP);
			pStatic->SetBitmap(hBitmap);					
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
			sMsg.Format("完整过程读取身份证信息错误, nRet = %d, %d ms",nRet ,tSpan.MSecond);
			InsertDebugMes(sMsg);
		}
	}
	else
	{
		sMsg = "打开端口错误";
		InsertDebugMes(sMsg);	
	}
	if (m_iPort>0)
	{
		Syn_ClosePort(m_iPort);
	}
}

void CTestDlg::OnTimer(UINT_PTR nIDEvent)
{
	if ( nIDEvent == 1 || nIDEvent == 4)
	{
		if (m_iReadType == 0)
		{
			OnBnClickedButreadcardex();
		}
		else
		{
			OnBnClickedButreadcardex2();
		}
	}
	if ( nIDEvent == 2 || nIDEvent == 4)
	{
		OnBnClickedButton13();
	}
	if ( nIDEvent == 3)
	{
		OnBnClickedButton15();
	}
	if ( nIDEvent == 5)
	{
		OnBnClickedButton19();
	}
	if ( nIDEvent == 6)
	{
		OnBnClickedButton20();
	}
	switch (nIDEvent){
		case 1:
			if (m_iReadSum == m_iLoopSum)
			{
				OnBnClickedButstopread();
			}
			break;
		case 2:
			if (m_iM1ReadSum == m_iLoopSum)
			{
				OnBnClickedButton17();
			}
			break;
		case 3:
			if (m_iM1WriteSum == m_iLoopSum)
			{
				OnBnClickedButton18();
			}
			break;
		case 4:
			if (m_iReadSum == m_iLoopSum)
			{
				OnBnClickedButton2();
			}
			break;
		case 5:
			if (m_iM1ReadSum == m_iLoopSum)
			{
				OnBnClickedButton23();
			}
			break;
		case 6:
			if (m_iM1WriteSum == m_iLoopSum)
			{
				OnBnClickedButton24();
			}
			break;
		default :
			break;
	}
	CDialog::OnTimer(nIDEvent);
}

void CTestDlg::OnBnClickedButstopread()
{
	CString sMsg;
	KillTimer(m_iTime);
	m_iReadStart = 0;
	sMsg.Format("读二代证总计 %d 次,成功 %d 次",m_iReadSum,m_iReadOKSum);
	InsertDebugMes(sMsg);
	AfxMessageBox(sMsg);
}

void CTestDlg::OnBnClickedButfpExt()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CTestDlg::OnBnClickedButsound()
{
	unsigned char nSound;
	int nRet;
	CString sMsg,strItem;
	if (m_iPort == 0)
	{
		return ;
	}
	CComboBox* combo= ( CComboBox*)GetDlgItem(IDC_COMBO1);
	int nIndex = combo->GetCurSel();	// 获取当前选中的项目ID。
	if (nIndex>=0 && nIndex <= 9)
	{
		nSound = (unsigned char)(nIndex + 0X0B);
	}
	if (nIndex>9)
	{
		nSound = (unsigned char)(0X20 + nIndex - 10);
	}
	if (m_iPort == 9999)
	{
		nRet = Syn_OpenPort(m_iPort);
		if (nRet == 0)
		{
			CCalcTime tSpan;
			tSpan.Clear();
			tSpan.BegginTime();
			nRet = Syn_USBHIDSendSound(m_iPort ,nSound );
			tSpan.EndTime();
			if (nRet == 0)
			{
				combo->GetLBText( nIndex, strItem); // 就是得到选中的字符串了。
				sMsg.Format("发送语音命令成功, %d ms ,",tSpan.MSecond); sMsg = sMsg + strItem;
			}
			else
			{
				sMsg.Format("发送语音命令不成功,nRet = %d , %d ms",nRet,tSpan.MSecond);
			}
		}
		else
		{
			sMsg = "打开端口错误";
		}
		if (m_iPort>0)
		{
			nRet = Syn_ClosePort(m_iPort);
		}
	}
	else
	{
		sMsg = "该读卡器不支持此命令";
	}
	InsertDebugMes(sMsg);
}

void CTestDlg::OnBnClickedButfindfp()
{
	CString sMsg;
	int nRet ;
	int nBright,nContrast,nWidth,nHeight;
	nRet = LIVESCAN_Init();
	if (nRet == 1)
	{
		nRet = LIVESCAN_GetChannelCount();
		if (nRet > 0)
		{
			sMsg.Format("指纹采集仪通道数量为 %d 个 ",nRet);
		}
		else
		{
			sMsg.Format("获得指纹采集仪通道数量失败,nRet = %d",nRet);
		}
		InsertDebugMes(sMsg);
		nRet = LIVESCAN_GetBright(0,&nBright);	// 通道号必须为0
		if (nRet == 1)
		{
			sMsg.Format("获得指纹采集仪亮度为 %d",nBright);
		}
		else
		{
			sMsg.Format("获得指纹采集仪亮度失败, nRet = %d",nRet);
		}
		InsertDebugMes(sMsg);
		nRet = LIVESCAN_GetContrast(0,&nContrast);	// 通道号必须为0
		if (nRet == 1)
		{
			sMsg.Format("获得指纹采集仪对比度为 %d",nContrast);
		}
		else
		{
			sMsg.Format("获得指纹采集仪对比度失败, nRet = %d",nRet);
		}
		InsertDebugMes(sMsg);
		nRet = LIVESCAN_GetMaxImageSize(0,&nWidth,&nHeight);	// 通道号必须为0
		if (nRet == 1)
		{
			sMsg.Format("获得指纹采集仪可采集图像宽度为 %d,高度为 %d",nWidth,nHeight);
		}
		else
		{
			sMsg.Format("获得指纹采集仪可采集图像宽度、高度失败, nRet = %d",nRet);
		}
		InsertDebugMes(sMsg);
	}
	else
	{
		sMsg.Format("初始化指纹采集器失败,nRet = %d",nRet);
		InsertDebugMes(sMsg);
	}
}

void CTestDlg::OnBnClickedButgetver()
{
	int nRet;
	CString sMsg;
	nRet = LIVESCAN_GetVersion();
	sMsg.Format("采集库接口版本为 %d ",nRet);
	InsertDebugMes(sMsg);
}

void CTestDlg::OnBnClickedButgetdesc()
{
	int nRet;
	CString sMsg;
	char pscDesc[1024]={0};
	nRet = LIVESCAN_GetDesc(pscDesc);
	if ( nRet == 1)
	{
		sMsg.Format("采集库接口采集存储器代码 %d ,描述为 %s ",pscDesc[0],&pscDesc[1]);
	}
	else
	{
		sMsg.Format("获得采集库接口描述失败,nRet = %d ",nRet); 
	}
	InsertDebugMes(sMsg);
}

void CTestDlg::OnBnClickedButclosefp()
{
	int nRet;
	CString sMsg;
	nRet = LIVESCAN_Close();
	if (nRet == 1)
	{
		sMsg = "关闭指纹采集器成功";
	}
	else
	{
		sMsg = "关闭指纹采集器失败";
	}
	InsertDebugMes(sMsg);
}

void CTestDlg::OnBnClickedButbegincap()
{
	int nRet;
	CString sMsg;
	CCalcTime tSpan;
	tSpan.Clear();
	tSpan.BegginTime();
	nRet = LIVESCAN_BeginCapture(0);
	tSpan.EndTime();
	if (nRet == 1)
	{
		sMsg.Format("调用准备采集一帧图像函数成功, %d ms",tSpan.MSecond);
	}
	else
	{
		sMsg.Format("调用准备采集一帧图像函数失败,nRet = %d , %d ms",nRet,tSpan.MSecond);
	}InsertDebugMes(sMsg);
}

void CTestDlg::OnBnClickedButgetfpraw()
{
	int nRet ;
	CString sMsg,sRawFile,sBmpFile;
	CFile filebmp;
	unsigned char ucRaw[256*360]={0};
	CTime   timTemp;
	timTemp = CTime::GetCurrentTime();
	CString sTick;
	DWORD dwTick = GetTickCount();
	sTick.Format("_%d",dwTick);

	unsigned char ucScore=0;
	CCalcTime tSpan;
	tSpan.Clear();
	tSpan.BegginTime();
	nRet = LIVESCAN_GetFPRawData(0,ucRaw);
	tSpan.EndTime();
	if (nRet == 1)
	{
		sRawFile = "C:\\" + timTemp.Format("%Y%m%d%H%M%S") + sTick + "Fp.raw";
		sBmpFile = "C:\\" + timTemp.Format("%Y%m%d%H%M%S") + sTick + "Fp.Bmp";
		filebmp.Open(sRawFile,CFile::modeCreate|CFile::modeWrite|CFile::shareExclusive,NULL);
		filebmp.Write(ucRaw,sizeof(ucRaw));
		filebmp.Close();
		nRet = FP_Begin();
		nRet = FP_GetQualityScore(ucRaw,&ucScore);
		nRet = FP_End();
		RawToBmp(ucRaw,sBmpFile);
		ViewBmp(sBmpFile);
		sMsg.Format("采集一帧图像成功，时间 %d ms ,图像质量为:%d,Raw文件为：",tSpan.MSecond,ucScore);
		sMsg = sMsg + sRawFile;
	}
	else
	{
		sMsg.Format("采集一帧图像失败,nRet = %s , %d ms",nRet,tSpan.MSecond);
	}
	InsertDebugMes(sMsg);
}

void CTestDlg::OnBnClickedButreaderuserinfo()
{
	int nRet;
	unsigned char ucInfo[40] = {0};
	CString sMsg;
	if (  m_iPort == 9999)
	{
		nRet = Syn_OpenPort(m_iPort);
		if (nRet == 0)
		{
			CCalcTime tSpan;
			tSpan.Clear();
			tSpan.BegginTime();
			nRet = Syn_USBHIDReadUserInfo(m_iPort,ucInfo);
			tSpan.EndTime();
			if (nRet == 0)
			{
				sMsg.Format("读用户自定义信息成功, %d ms",tSpan.MSecond);
				InsertDebugMes(sMsg);
				sMsg.Format("用户信息0~9:%0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X",ucInfo[0],ucInfo[1],ucInfo[2],ucInfo[3],ucInfo[4],ucInfo[5],ucInfo[6],ucInfo[7],ucInfo[8],ucInfo[9]);
				InsertDebugMes(sMsg);
				sMsg.Format("用户信息10~19:%0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X",ucInfo[10],ucInfo[11],ucInfo[12],ucInfo[13],ucInfo[14],ucInfo[15],ucInfo[16],ucInfo[17],ucInfo[18],ucInfo[19]);
				InsertDebugMes(sMsg);
				sMsg.Format("用户信息20~29:%0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X",ucInfo[20],ucInfo[21],ucInfo[22],ucInfo[23],ucInfo[24],ucInfo[25],ucInfo[26],ucInfo[27],ucInfo[28],ucInfo[29]);
				InsertDebugMes(sMsg);
				sMsg.Format("用户信息30~39:%0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X",ucInfo[30],ucInfo[31],ucInfo[32],ucInfo[33],ucInfo[34],ucInfo[35],ucInfo[36],ucInfo[37],ucInfo[38],ucInfo[39]);
			}
			else
			{
				sMsg.Format("读取用户自定义信息失败,nRet = %d , %d ms",nRet,tSpan.MSecond);
			}
		}
		else
		{
			sMsg = "打开端口错误";
		}
		if (m_iPort>0)
		{
			Syn_ClosePort(m_iPort);
		}
	}
	else
	{
		sMsg = "该读卡器不支持此命令";
	}
	InsertDebugMes(sMsg);
}

void CTestDlg::OnBnClickedButwriteuserinfo()
{
	int nRet;
	unsigned char ucInfo[40] = {0};
	CString sMsg;
	CString sText;
	int nLen;
	GetDlgItem(IDC_EDIT_USERINFO)->GetWindowText(sText);
	nLen = sText.GetLength();
	if (nLen > 40)
	{
		nLen = 40;
	}
	memcpy(ucInfo,sText.GetBuffer(0),nLen);
	if (  m_iPort == 9999)
	{
		nRet = Syn_OpenPort(m_iPort);
		if (nRet == 0)
		{
			CCalcTime tSpan;
			tSpan.Clear();
			tSpan.BegginTime();
			nRet = Syn_USBHIDWriteUserInfo(m_iPort,ucInfo);
			tSpan.EndTime();
			if (nRet == 0)
			{
				sMsg.Format("写用户自定义信息成功, %d ms",tSpan.MSecond);
			}
			else
			{
				sMsg.Format("写用户自定义信息失败,nRet = %d , %d ms",nRet,tSpan.MSecond);
			}
		}
		else
		{
			sMsg = "打开端口失败";
		}
		if (m_iPort>0)
		{
			Syn_ClosePort(m_iPort);
		}
	}
	else
	{
		sMsg = "该读卡器不支持此命令";
	}
	InsertDebugMes(sMsg);
}

void CTestDlg::OnBnClickedButreadfac()
{
		unsigned char ucFactory[9]={0};
		unsigned char ucVol[9]={0};
		unsigned char ucSerialNo[9]={0};
		unsigned char ucReserved[17]={0};
		int nRet;
		CString  sMsg,sMsg2;
		if (m_iPort == 9999)
		{
			nRet = Syn_OpenPort(m_iPort);
			if (nRet == 0)
			{
				CCalcTime tSpan;
				tSpan.Clear();
				tSpan.BegginTime();
				nRet = Syn_USBHIDReadFactoryInfo(m_iPort,ucFactory,ucVol,ucSerialNo,ucReserved);
				tSpan.EndTime();
				if (nRet == 0)
				{
					sMsg.Format("读生产信息成功, %d ms",tSpan.MSecond);
					InsertDebugMes(sMsg);
					sMsg.Format("生产厂商:%s",ucFactory);sMsg2.Format("%s",ucFactory);
					GetDlgItem(IDC_EDIT_FAC1)->SetWindowText(sMsg2);
					InsertDebugMes(sMsg);
					sMsg.Format("读卡器版本:%s",ucVol);sMsg2.Format("%s",ucVol);
					GetDlgItem(IDC_EDIT_FAC2)->SetWindowText(sMsg2);
					InsertDebugMes(sMsg);
					sMsg.Format("生产序号:%s",ucSerialNo);sMsg2.Format("%s",ucSerialNo);
					GetDlgItem(IDC_EDIT_FAC3)->SetWindowText(sMsg2);
					InsertDebugMes(sMsg);
					sMsg.Format("生产备注:%s",ucReserved);sMsg2.Format("%s",ucReserved);
					GetDlgItem(IDC_EDIT_FAC4)->SetWindowText(sMsg2);
				}
				else
				{
					sMsg.Format("读取生产信息失败, %d ms",tSpan.MSecond);
				}
			}
			else
			{
				sMsg = "打开端口错误";
			}
			if (m_iPort>0)
			{
				Syn_ClosePort(m_iPort);
			}
		}
		else
		{
			sMsg = "该读卡器不支持此命令";
		}
		InsertDebugMes(sMsg);
}

void CTestDlg::OnBnClickedButwritefac()
{
}

void CTestDlg::OnBnClickedButendcap()
{
	int nRet;
	CString sMsg;
	CCalcTime tSpan;
	tSpan.Clear();
	tSpan.BegginTime();
	nRet = LIVESCAN_EndCapture(0);
	tSpan.EndTime();
	if (nRet == 1)
	{
		sMsg.Format("调用结束采集一帧图像函数成功, %d ms",tSpan.MSecond);
	}
	else
	{
		sMsg.Format("调用结束采集一帧图像函数失败,nRet = %d, %d ms",nRet,tSpan.MSecond);
	}
	InsertDebugMes(sMsg);
}

void CTestDlg::OnBnClickedButgetfpbmp()
{
	int nRet ;
	CString sMsg,sBmpFile;
	CFile filebmp;
	unsigned char ucBmp[256*360+1078]={0};
	CTime   timTemp;
	timTemp = CTime::GetCurrentTime();
	CString sTick;
	DWORD dwTick = GetTickCount();
	sTick.Format("_%d",dwTick);

	CCalcTime tSpan;
	tSpan.Clear();
	tSpan.BegginTime();
	nRet = LIVESCAN_GetFPBmpData(0,ucBmp);
	tSpan.EndTime();
	if (nRet == 1)
	{
		sBmpFile = "C:\\" + timTemp.Format("%Y%m%d%H%M%S") + sTick +"Fp.Bmp";
		filebmp.Open(sBmpFile,CFile::modeCreate|CFile::modeWrite|CFile::shareExclusive,NULL);
		filebmp.Write(ucBmp,sizeof(ucBmp));
		filebmp.Close();
		ViewBmp(sBmpFile);
		sMsg.Format("采集一帧BMP图像成功，时间： %d ms,文件为：" ,tSpan.MSecond); sMsg=sMsg+ sBmpFile;
	}
	else
	{
		sMsg.Format("采集一帧BMP图像失败,nRet = %s, %s ms",nRet,tSpan.MSecond);
	}
	InsertDebugMes(sMsg);
}
void CTestDlg::ViewBmp(CString bmpFile)
{
	CFile file;
	HDIB m_hDIB;
	CStatic *pStatic = (CStatic *)GetDlgItem(IDC_STATIC2);
	file.Open(bmpFile, CFile::modeRead);
	m_hDIB = ::ReadDIBFile(file);   //读取位图文件API函数
	file.Close();
	CWnd *wnd=GetDlgItem(IDC_STATIC3);
	CDC  *dc=GetDlgItem(IDC_STATIC3)->GetDC(); 
	CRect rect;
	wnd->GetClientRect(&rect);
	::DisplayDIB(dc, m_hDIB,rect);             //显示位图API函数
}
int CTestDlg::RawToBmp(unsigned char *ucRaw,CString bmpFile)
{
	CFile filebmp;
	unsigned char tmp[256]={0};
	int m_iWidth=256;
	int m_iHeight=360;
	filebmp.Open(bmpFile,CFile::modeCreate|CFile::modeWrite|CFile::shareExclusive,NULL);
	BITMAPFILEHEADER bmfHdr;      //位图头文件
	BITMAPINFOHEADER bmpHdr;      //位图信息头
	RGBQUAD rgb[256];             //调色板


	//位图头文件部分信息初始化
	bmfHdr.bfType='MB';
	bmfHdr.bfReserved1=0;
	bmfHdr.bfReserved2=0;

	//位图信息头部分信息初始化
	bmpHdr.biSize=40;
	bmpHdr.biWidth=m_iWidth;
	bmpHdr.biHeight=m_iHeight;
	bmpHdr.biPlanes=1;
	bmpHdr.biCompression=BI_RGB;
	bmpHdr.biXPelsPerMeter=0;
	bmpHdr.biYPelsPerMeter=0;
	bmpHdr.biClrUsed=0;
	bmpHdr.biClrImportant=0;

	bmpHdr.biBitCount=8;
	bmfHdr.bfOffBits=1078; //bmfHdr.bfOffBits=14+40+256*4;
	bmpHdr.biSizeImage=(((m_iWidth*8)+31)/32*4)*m_iHeight;
	bmfHdr.bfSize=bmfHdr.bfOffBits+bmpHdr.biSizeImage;
	//调色板初始化
	for(int i=0;i<256;i++)
	{
		rgb[i].rgbBlue=i;
		rgb[i].rgbGreen=i;
		rgb[i].rgbRed=i;
		rgb[i].rgbReserved=0;
	}
	filebmp.Write(&bmfHdr,sizeof(bmfHdr));
	filebmp.Write(&bmpHdr,sizeof(bmpHdr));
	filebmp.Write(rgb,sizeof(RGBQUAD)*256); //如果是灰度图像，将调色板写入文件

	int h=m_iHeight;
	int w=m_iWidth;
	int iWidthBytes=bmpHdr.biSizeImage/m_iHeight;  //位图文件的实际每行的存储宽度
	//开始学第四部分
	//注意每一行的字节数必须是死的整数倍，不足的补零
	//像素按照从上到下、从左到右的顺序排列

	int zero=0;
	for(int i=0;i<h;i++)
	{
		filebmp.Write(ucRaw+w*(h-i-1),w);
		memcpy(tmp,ucRaw+w*(h-i-1),w);
		if(w!=iWidthBytes)
			for(int j=0;j<iWidthBytes-w;j++)
				filebmp.Write(&zero,1);
	}
	filebmp.Close();

	return 0;
}
void CTestDlg::OnBnClickedButton5()
{
	GetDlgItem(IDC_EDIT_OLDPASS0)->SetWindowText("FF");
	GetDlgItem(IDC_EDIT_OLDPASS1)->SetWindowText("FF");
	GetDlgItem(IDC_EDIT_OLDPASS2)->SetWindowText("FF");
	GetDlgItem(IDC_EDIT_OLDPASS3)->SetWindowText("FF");
	GetDlgItem(IDC_EDIT_OLDPASS4)->SetWindowText("FF");
	GetDlgItem(IDC_EDIT_OLDPASS5)->SetWindowText("FF");
}

void CTestDlg::OnBnClickedButton3()
{
	GetDlgItem(IDC_EDIT_OLDPASS0)->SetWindowText("00");
	GetDlgItem(IDC_EDIT_OLDPASS1)->SetWindowText("00");
	GetDlgItem(IDC_EDIT_OLDPASS2)->SetWindowText("00");
	GetDlgItem(IDC_EDIT_OLDPASS3)->SetWindowText("00");
	GetDlgItem(IDC_EDIT_OLDPASS4)->SetWindowText("00");
	GetDlgItem(IDC_EDIT_OLDPASS5)->SetWindowText("00");
}

void CTestDlg::OnBnClickedButton4()
{
	GetDlgItem(IDC_EDIT_NEWPASS0)->SetWindowText("00");
	GetDlgItem(IDC_EDIT_NEWPASS1)->SetWindowText("00");
	GetDlgItem(IDC_EDIT_NEWPASS2)->SetWindowText("00");
	GetDlgItem(IDC_EDIT_NEWPASS3)->SetWindowText("00");
	GetDlgItem(IDC_EDIT_NEWPASS4)->SetWindowText("00");
	GetDlgItem(IDC_EDIT_NEWPASS5)->SetWindowText("00");
}

void CTestDlg::OnBnClickedButton6()
{
	GetDlgItem(IDC_EDIT_NEWPASS0)->SetWindowText("FF");
	GetDlgItem(IDC_EDIT_NEWPASS1)->SetWindowText("FF");
	GetDlgItem(IDC_EDIT_NEWPASS2)->SetWindowText("FF");
	GetDlgItem(IDC_EDIT_NEWPASS3)->SetWindowText("FF");
	GetDlgItem(IDC_EDIT_NEWPASS4)->SetWindowText("FF");
	GetDlgItem(IDC_EDIT_NEWPASS5)->SetWindowText("FF");
}

void CTestDlg::OnBnClickedButton7()
{
	CString sMsg,sMsg2;
	GetDlgItem(IDC_EDIT_OLDPASS0)->GetWindowText(sMsg);
	GetDlgItem(IDC_EDIT_NEWPASS0)->GetWindowText(sMsg2);
	GetDlgItem(IDC_EDIT_NEWPASS0)->SetWindowText(sMsg);
	GetDlgItem(IDC_EDIT_OLDPASS0)->SetWindowText(sMsg2);

	GetDlgItem(IDC_EDIT_OLDPASS1)->GetWindowText(sMsg);
	GetDlgItem(IDC_EDIT_NEWPASS1)->GetWindowText(sMsg2);
	GetDlgItem(IDC_EDIT_NEWPASS1)->SetWindowText(sMsg);
	GetDlgItem(IDC_EDIT_OLDPASS1)->SetWindowText(sMsg2);

	GetDlgItem(IDC_EDIT_OLDPASS2)->GetWindowText(sMsg);
	GetDlgItem(IDC_EDIT_NEWPASS2)->GetWindowText(sMsg2);
	GetDlgItem(IDC_EDIT_NEWPASS2)->SetWindowText(sMsg);
	GetDlgItem(IDC_EDIT_OLDPASS2)->SetWindowText(sMsg2);

	GetDlgItem(IDC_EDIT_OLDPASS3)->GetWindowText(sMsg);
	GetDlgItem(IDC_EDIT_NEWPASS3)->GetWindowText(sMsg2);
	GetDlgItem(IDC_EDIT_NEWPASS3)->SetWindowText(sMsg);
	GetDlgItem(IDC_EDIT_OLDPASS3)->SetWindowText(sMsg2);

	GetDlgItem(IDC_EDIT_OLDPASS4)->GetWindowText(sMsg);
	GetDlgItem(IDC_EDIT_NEWPASS4)->GetWindowText(sMsg2);
	GetDlgItem(IDC_EDIT_NEWPASS4)->SetWindowText(sMsg);
	GetDlgItem(IDC_EDIT_OLDPASS4)->SetWindowText(sMsg2);

	GetDlgItem(IDC_EDIT_OLDPASS5)->GetWindowText(sMsg);
	GetDlgItem(IDC_EDIT_NEWPASS5)->GetWindowText(sMsg2);
	GetDlgItem(IDC_EDIT_NEWPASS5)->SetWindowText(sMsg);
	GetDlgItem(IDC_EDIT_OLDPASS5)->SetWindowText(sMsg2);
}

void CTestDlg::OnBnClickedButton9()
{
	GetDlgItem(IDC_EDIT_DATA0)->SetWindowText("00");
	GetDlgItem(IDC_EDIT_DATA1)->SetWindowText("00");
	GetDlgItem(IDC_EDIT_DATA2)->SetWindowText("00");
	GetDlgItem(IDC_EDIT_DATA3)->SetWindowText("00");
	GetDlgItem(IDC_EDIT_DATA4)->SetWindowText("00");
	GetDlgItem(IDC_EDIT_DATA5)->SetWindowText("00");
	GetDlgItem(IDC_EDIT_DATA6)->SetWindowText("00");
	GetDlgItem(IDC_EDIT_DATA7)->SetWindowText("00");
	GetDlgItem(IDC_EDIT_DATA8)->SetWindowText("00");
	GetDlgItem(IDC_EDIT_DATA9)->SetWindowText("00");
	GetDlgItem(IDC_EDIT_DATA10)->SetWindowText("00");
	GetDlgItem(IDC_EDIT_DATA11)->SetWindowText("00");
	GetDlgItem(IDC_EDIT_DATA12)->SetWindowText("00");
	GetDlgItem(IDC_EDIT_DATA13)->SetWindowText("00");
	GetDlgItem(IDC_EDIT_DATA14)->SetWindowText("00");
	GetDlgItem(IDC_EDIT_DATA15)->SetWindowText("00");
}

void CTestDlg::OnBnClickedButton10()
{
	GetDlgItem(IDC_EDIT_DATA0)->SetWindowText("FF");
	GetDlgItem(IDC_EDIT_DATA1)->SetWindowText("FF");
	GetDlgItem(IDC_EDIT_DATA2)->SetWindowText("FF");
	GetDlgItem(IDC_EDIT_DATA3)->SetWindowText("FF");
	GetDlgItem(IDC_EDIT_DATA4)->SetWindowText("FF");
	GetDlgItem(IDC_EDIT_DATA5)->SetWindowText("FF");
	GetDlgItem(IDC_EDIT_DATA6)->SetWindowText("FF");
	GetDlgItem(IDC_EDIT_DATA7)->SetWindowText("FF");
	GetDlgItem(IDC_EDIT_DATA8)->SetWindowText("FF");
	GetDlgItem(IDC_EDIT_DATA9)->SetWindowText("FF");
	GetDlgItem(IDC_EDIT_DATA10)->SetWindowText("FF");
	GetDlgItem(IDC_EDIT_DATA11)->SetWindowText("FF");
	GetDlgItem(IDC_EDIT_DATA12)->SetWindowText("FF");
	GetDlgItem(IDC_EDIT_DATA13)->SetWindowText("FF");
	GetDlgItem(IDC_EDIT_DATA14)->SetWindowText("FF");
	GetDlgItem(IDC_EDIT_DATA15)->SetWindowText("FF");
}

void CTestDlg::OnBnClickedButton11()
{
	GetDlgItem(IDC_EDIT_DATA0)->SetWindowText("00");
	GetDlgItem(IDC_EDIT_DATA1)->SetWindowText("11");
	GetDlgItem(IDC_EDIT_DATA2)->SetWindowText("22");
	GetDlgItem(IDC_EDIT_DATA3)->SetWindowText("33");
	GetDlgItem(IDC_EDIT_DATA4)->SetWindowText("44");
	GetDlgItem(IDC_EDIT_DATA5)->SetWindowText("55");
	GetDlgItem(IDC_EDIT_DATA6)->SetWindowText("66");
	GetDlgItem(IDC_EDIT_DATA7)->SetWindowText("77");
	GetDlgItem(IDC_EDIT_DATA8)->SetWindowText("88");
	GetDlgItem(IDC_EDIT_DATA9)->SetWindowText("99");
	GetDlgItem(IDC_EDIT_DATA10)->SetWindowText("AA");
	GetDlgItem(IDC_EDIT_DATA11)->SetWindowText("BB");
	GetDlgItem(IDC_EDIT_DATA12)->SetWindowText("CC");
	GetDlgItem(IDC_EDIT_DATA13)->SetWindowText("DD");
	GetDlgItem(IDC_EDIT_DATA14)->SetWindowText("EE");
	GetDlgItem(IDC_EDIT_DATA15)->SetWindowText("FF");
}

void CTestDlg::OnBnClickedButton12()
{
	GetDlgItem(IDC_EDIT_DATA0)->SetWindowText("FF");
	GetDlgItem(IDC_EDIT_DATA1)->SetWindowText("EE");
	GetDlgItem(IDC_EDIT_DATA2)->SetWindowText("DD");
	GetDlgItem(IDC_EDIT_DATA3)->SetWindowText("CC");
	GetDlgItem(IDC_EDIT_DATA4)->SetWindowText("BB");
	GetDlgItem(IDC_EDIT_DATA5)->SetWindowText("AA");
	GetDlgItem(IDC_EDIT_DATA6)->SetWindowText("99");
	GetDlgItem(IDC_EDIT_DATA7)->SetWindowText("88");
	GetDlgItem(IDC_EDIT_DATA8)->SetWindowText("77");
	GetDlgItem(IDC_EDIT_DATA9)->SetWindowText("66");
	GetDlgItem(IDC_EDIT_DATA10)->SetWindowText("55");
	GetDlgItem(IDC_EDIT_DATA11)->SetWindowText("44");
	GetDlgItem(IDC_EDIT_DATA12)->SetWindowText("33");
	GetDlgItem(IDC_EDIT_DATA13)->SetWindowText("22");
	GetDlgItem(IDC_EDIT_DATA14)->SetWindowText("11");
	GetDlgItem(IDC_EDIT_DATA15)->SetWindowText("00");
}

void CTestDlg::OnBnClickedM1reset()
{
	int nRet;
	CString sMsg;
	DWORD dwSerialNo;
	unsigned char ucSize;
	if (m_iPort == 9999)
	{
		nRet = Syn_OpenPort(m_iPort);
		if (nRet == 0)
		{
			CCalcTime tSpan;
			tSpan.Clear();
			tSpan.BegginTime();
			nRet = Syn_USBHIDM1Reset(m_iPort,&dwSerialNo,&ucSize);
			tSpan.EndTime();
			if (nRet == 0)
			{
				sMsg.Format("复位M1卡成功,卡号: %0.8X ,卡类型: %0.2X , %d ms",dwSerialNo,ucSize,tSpan.MSecond);
			}
			else
			{
				sMsg.Format("复位M1卡失败,nRet = %d, %d ms",nRet,tSpan.MSecond);
			}
		}
		else
		{
			sMsg = "打开端口错误";
		}
		if (m_iPort >0)
		{
			Syn_ClosePort(m_iPort);
		}
	}
	else
	{
		sMsg = "此读卡器不支持该功能";
	}
	InsertDebugMes(sMsg);
}

void CTestDlg::OnBnClickedM1halt()
{
	int nRet;
	CString sMsg;
	if (m_iPort == 9999)
	{
		nRet = Syn_OpenPort(m_iPort);
		if (nRet == 0)
		{
			CCalcTime tSpan;
			tSpan.Clear();
			tSpan.BegginTime();
			nRet = Syn_USBHIDM1Halt(m_iPort);
			tSpan.EndTime();
			if (nRet == 0)
			{
				sMsg.Format("挂起M1卡成功, %d ms",tSpan.MSecond);
			}
			else
			{
				sMsg.Format("挂起M1卡失败,nRet = %d, %d ms",nRet,tSpan.MSecond);
			}
		}
		else
		{
			sMsg = "打开端口错误";
		}
		if (m_iPort >0)
		{
			Syn_ClosePort(m_iPort);
		}
	}
	else
	{
		sMsg = "此读卡器不支持该功能";
	}
	InsertDebugMes(sMsg);
}

void CTestDlg::OnBnClickedButtonAuthena()
{
	int nRet;
	CString sMsg;
	unsigned char ucKey[6]={0};
	unsigned char uTmp[2];
	unsigned char ucBloCK = 0;
	GetDlgItem(IDC_EDIT_SECNO)->GetWindowText(sMsg);	ucBloCK = atoi(sMsg);
	GetDlgItem(IDC_EDIT_OLDPASS0)->GetWindowText(sMsg);		memcpy(uTmp,sMsg,2);	ucKey[0] = cTouchar(uTmp,sMsg.GetLength());
	GetDlgItem(IDC_EDIT_OLDPASS1)->GetWindowText(sMsg);		memcpy(uTmp,sMsg,2);	ucKey[1] = cTouchar(uTmp,sMsg.GetLength());
	GetDlgItem(IDC_EDIT_OLDPASS2)->GetWindowText(sMsg);		memcpy(uTmp,sMsg,2);	ucKey[2] = cTouchar(uTmp,sMsg.GetLength());
	GetDlgItem(IDC_EDIT_OLDPASS3)->GetWindowText(sMsg);		memcpy(uTmp,sMsg,2);	ucKey[3] = cTouchar(uTmp,sMsg.GetLength());
	GetDlgItem(IDC_EDIT_OLDPASS4)->GetWindowText(sMsg);		memcpy(uTmp,sMsg,2);	ucKey[4] = cTouchar(uTmp,sMsg.GetLength());
	GetDlgItem(IDC_EDIT_OLDPASS5)->GetWindowText(sMsg);		memcpy(uTmp,sMsg,2);	ucKey[5] = cTouchar(uTmp,sMsg.GetLength());

	if (m_iPort == 9999)
	{
		nRet = Syn_OpenPort(m_iPort);
		if (nRet == 0)
		{
			CCalcTime tSpan;
			tSpan.Clear();
			tSpan.BegginTime();
			nRet = Syn_USBHIDM1AuthenKey(m_iPort,0,ucBloCK*4+3,ucKey);
			tSpan.EndTime();
			if (nRet == 0)
			{
				sMsg.Format("密钥A验证M1卡 %d 扇区成功, %d ms",ucBloCK,tSpan.MSecond);
			}
			else
			{
				sMsg.Format("密钥A验证M1卡 %d 扇区失败,nRet = %d, %d ms",ucBloCK,nRet,tSpan.MSecond);
			}
		}
		else
		{
			sMsg = "打开端口错误";
		}
		if (m_iPort >0)
		{
			Syn_ClosePort(m_iPort);
		}
	}
	else
	{
		sMsg = "此读卡器不支持该功能";
	}
	InsertDebugMes(sMsg);
}

void CTestDlg::OnBnClickedButtonAuthenb()
{
	int nRet;
	CString sMsg;
	unsigned char ucKey[6]={0};
	unsigned char uTmp[2];
	unsigned char ucBloCK = 0;
	GetDlgItem(IDC_EDIT_SECNO)->GetWindowText(sMsg);	ucBloCK = atoi(sMsg);
	GetDlgItem(IDC_EDIT_OLDPASS0)->GetWindowText(sMsg);		memcpy(uTmp,sMsg,2);	ucKey[0] = cTouchar(uTmp,sMsg.GetLength());
	GetDlgItem(IDC_EDIT_OLDPASS1)->GetWindowText(sMsg);		memcpy(uTmp,sMsg,2);	ucKey[1] = cTouchar(uTmp,sMsg.GetLength());
	GetDlgItem(IDC_EDIT_OLDPASS2)->GetWindowText(sMsg);		memcpy(uTmp,sMsg,2);	ucKey[2] = cTouchar(uTmp,sMsg.GetLength());
	GetDlgItem(IDC_EDIT_OLDPASS3)->GetWindowText(sMsg);		memcpy(uTmp,sMsg,2);	ucKey[3] = cTouchar(uTmp,sMsg.GetLength());
	GetDlgItem(IDC_EDIT_OLDPASS4)->GetWindowText(sMsg);		memcpy(uTmp,sMsg,2);	ucKey[4] = cTouchar(uTmp,sMsg.GetLength());
	GetDlgItem(IDC_EDIT_OLDPASS5)->GetWindowText(sMsg);		memcpy(uTmp,sMsg,2);	ucKey[5] = cTouchar(uTmp,sMsg.GetLength());

	if (m_iPort == 9999)
	{
		nRet = Syn_OpenPort(m_iPort);
		if (nRet == 0)
		{
			CCalcTime tSpan;
			tSpan.Clear();
			tSpan.BegginTime();
			nRet = Syn_USBHIDM1AuthenKey(m_iPort,1,ucBloCK*4+3,ucKey);
			tSpan.EndTime();
			if (nRet == 0)
			{
				sMsg.Format("密钥B验证M1卡 %d 扇区成功, %d ms",ucBloCK,tSpan.MSecond);
			}
			else
			{
				sMsg.Format("密钥B验证M1卡 %d 扇区失败,nRet = %d, %d ms",ucBloCK,nRet,tSpan.MSecond);
			}
		}
		else
		{
			sMsg = "打开端口错误";
		}
		if (m_iPort >0)
		{
			Syn_ClosePort(m_iPort);
		}
	}
	else
	{
		sMsg = "此读卡器不支持该功能";
	}
	InsertDebugMes(sMsg);
}

void CTestDlg::OnBnClickedButtonRead()
{
	int nRet ;
	CString sMsg;
	unsigned char ucData[16]={0};
	unsigned char ucSec = 0;
	unsigned char ucBloCK = 0;

	GetDlgItem(IDC_EDIT_BLOCKNO)->GetWindowText(sMsg);	ucBloCK = atoi(sMsg);
	GetDlgItem(IDC_EDIT_SECNO)->GetWindowText(sMsg);	ucSec = atoi(sMsg);   

	if (m_iPort == 9999)
	{
		nRet = Syn_OpenPort(m_iPort);
		if (nRet == 0)
		{
			CCalcTime tSpan;
			tSpan.Clear();
			tSpan.BegginTime();
			nRet = Syn_USBHIDM1ReadBlock(m_iPort,ucSec*4 + ucBloCK,ucData);
			tSpan.EndTime();
			if (m_iM1ReadStart == 1)
			{
				m_iM1ReadSum++;
			}
			if (nRet == 0)
			{
				if (m_iM1ReadStart == 1)
				{
					m_iM1ReadOKSum++;
				}
				sMsg.Format("读M1卡 %d 扇区 %d 块成功, %d ms ,数据为:%0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X ",ucSec,ucBloCK,tSpan.MSecond,ucData[0],ucData[1],ucData[2],ucData[3],ucData[4],ucData[5],ucData[6],ucData[7],ucData[8],ucData[9],ucData[10],ucData[11],ucData[12],ucData[13],ucData[14],ucData[15]);
			}
			else
			{
				sMsg.Format("读M1卡 %d 扇区 %d 块失败,nRet = %d, %d ms",ucSec,ucBloCK,nRet,tSpan.MSecond);
			}
		}
		else
		{
			sMsg = "打开端口错误";
		}
		if (m_iPort >0)
		{
			Syn_ClosePort(m_iPort);
		}
	}
	else
	{
		sMsg = "此读卡器不支持该功能";
	}
	InsertDebugMes(sMsg);
}

void CTestDlg::OnBnClickedButtonWrite()
{
	int nRet ;
	CString sMsg;
	unsigned char ucData[16]={0};
	unsigned char uTmp[2];
	unsigned char ucSec = 0;
	unsigned char ucBloCK = 0;

	GetDlgItem(IDC_EDIT_BLOCKNO)->GetWindowText(sMsg);	ucBloCK = atoi(sMsg);
	GetDlgItem(IDC_EDIT_SECNO)->GetWindowText(sMsg);	ucSec = atoi(sMsg);
	GetDlgItem(IDC_EDIT_DATA0)->GetWindowText(sMsg);	memcpy(uTmp,sMsg,2);	ucData[0] = cTouchar(uTmp,sMsg.GetLength());
	GetDlgItem(IDC_EDIT_DATA1)->GetWindowText(sMsg);	memcpy(uTmp,sMsg,2);	ucData[1] = cTouchar(uTmp,sMsg.GetLength());	
	GetDlgItem(IDC_EDIT_DATA2)->GetWindowText(sMsg);	memcpy(uTmp,sMsg,2);	ucData[2] = cTouchar(uTmp,sMsg.GetLength());	
	GetDlgItem(IDC_EDIT_DATA3)->GetWindowText(sMsg);	memcpy(uTmp,sMsg,2);	ucData[3] = cTouchar(uTmp,sMsg.GetLength());	
	GetDlgItem(IDC_EDIT_DATA4)->GetWindowText(sMsg);	memcpy(uTmp,sMsg,2);	ucData[4] = cTouchar(uTmp,sMsg.GetLength());	
	GetDlgItem(IDC_EDIT_DATA5)->GetWindowText(sMsg);	memcpy(uTmp,sMsg,2);	ucData[5] = cTouchar(uTmp,sMsg.GetLength());	
	GetDlgItem(IDC_EDIT_DATA6)->GetWindowText(sMsg);	memcpy(uTmp,sMsg,2);	ucData[6] = cTouchar(uTmp,sMsg.GetLength());	
	GetDlgItem(IDC_EDIT_DATA7)->GetWindowText(sMsg);	memcpy(uTmp,sMsg,2);	ucData[7] = cTouchar(uTmp,sMsg.GetLength());	
	GetDlgItem(IDC_EDIT_DATA8)->GetWindowText(sMsg);	memcpy(uTmp,sMsg,2);	ucData[8] = cTouchar(uTmp,sMsg.GetLength());	
	GetDlgItem(IDC_EDIT_DATA9)->GetWindowText(sMsg);	memcpy(uTmp,sMsg,2);	ucData[9] = cTouchar(uTmp,sMsg.GetLength());	
	GetDlgItem(IDC_EDIT_DATA10)->GetWindowText(sMsg);	memcpy(uTmp,sMsg,2);	ucData[10] = cTouchar(uTmp,sMsg.GetLength());	
	GetDlgItem(IDC_EDIT_DATA11)->GetWindowText(sMsg);	memcpy(uTmp,sMsg,2);	ucData[11] = cTouchar(uTmp,sMsg.GetLength());	
	GetDlgItem(IDC_EDIT_DATA12)->GetWindowText(sMsg);	memcpy(uTmp,sMsg,2);	ucData[12] = cTouchar(uTmp,sMsg.GetLength());	
	GetDlgItem(IDC_EDIT_DATA13)->GetWindowText(sMsg);	memcpy(uTmp,sMsg,2);	ucData[13] = cTouchar(uTmp,sMsg.GetLength());	
	GetDlgItem(IDC_EDIT_DATA14)->GetWindowText(sMsg);	memcpy(uTmp,sMsg,2);	ucData[14] = cTouchar(uTmp,sMsg.GetLength());	
	GetDlgItem(IDC_EDIT_DATA15)->GetWindowText(sMsg);	memcpy(uTmp,sMsg,2);	ucData[15] = cTouchar(uTmp,sMsg.GetLength());
	if (m_iPort == 9999)
	{
		nRet = Syn_OpenPort(m_iPort);
		if (nRet == 0)
		{
			CCalcTime tSpan;
			tSpan.Clear();
			tSpan.BegginTime();
			nRet = Syn_USBHIDM1WriteBlock(m_iPort,ucSec*4 + ucBloCK,ucData);
			tSpan.EndTime();
			if (m_iM1WriteStart == 1)
			{
				m_iM1WriteSum++;
			}
			if (nRet == 0)
			{
				if (m_iM1WriteStart == 1)
				{
					m_iM1WriteOKSum++;
				}
				sMsg.Format("写M1卡 %d 扇区 %d 块成功, %d ms ",ucSec,ucBloCK,tSpan.MSecond);
			}
			else
			{
				sMsg.Format("写M1卡 %d 扇区 %d 块失败,nRet = %d, %d ms",ucSec,ucBloCK,nRet,tSpan.MSecond);
			}
		}
		else
		{
			sMsg = "打开端口错误";
		}
		if (m_iPort >0)
		{
			Syn_ClosePort(m_iPort);
		}
	}
	else
	{
		sMsg = "此读卡器不支持该功能";
	}
	InsertDebugMes(sMsg);

}

void CTestDlg::OnBnClickedButton14()
{
	KillTimer(m_iTime);
	m_iM1ReadStart = 1;
	m_iM1ReadSum = 0;
	m_iM1ReadOKSum = 0;
	m_iTime =	SetTimer(2,1000,0);
}

void CTestDlg::OnBnClickedButton17()
{
	CString sMsg;
	unsigned char ucSec = 0;
	unsigned char ucBloCK = 0;
	m_iM1ReadStart = 0;
	GetDlgItem(IDC_EDIT_BLOCKNO)->GetWindowText(sMsg);	ucBloCK = atoi(sMsg);
	GetDlgItem(IDC_EDIT_SECNO)->GetWindowText(sMsg);	ucSec = atoi(sMsg);   
	KillTimer(m_iTime);
	sMsg.Format("读M1卡 %d 扇区 %d 块 总计 %d 次,成功 %d 次",ucSec,ucBloCK,m_iM1ReadSum,m_iM1ReadOKSum);
	InsertDebugMes(sMsg);
	AfxMessageBox(sMsg);
}

void CTestDlg::OnBnClickedButton16()
{
	KillTimer(m_iTime);
	m_iM1WriteStart = 1;
	m_iM1WriteSum = 0;
	m_iM1WriteOKSum = 0;
	m_iTime =	SetTimer(3,1000,0);
}

void CTestDlg::OnBnClickedButton18()
{
	CString sMsg;
	unsigned char ucSec = 0;
	unsigned char ucBloCK = 0;
	m_iM1WriteStart = 0;
	GetDlgItem(IDC_EDIT_BLOCKNO)->GetWindowText(sMsg);	ucBloCK = atoi(sMsg);
	GetDlgItem(IDC_EDIT_SECNO)->GetWindowText(sMsg);	ucSec = atoi(sMsg);   
	KillTimer(m_iTime);
	sMsg.Format("写M1卡 %d 扇区 %d 块 总计 %d 次,成功 %d 次",ucSec,ucBloCK,m_iM1WriteSum,m_iM1WriteOKSum);
	InsertDebugMes(sMsg);
	AfxMessageBox(sMsg);
}

void CTestDlg::OnBnClickedButton13()
{
	OnBnClickedM1reset();
	OnBnClickedButtonAuthena();
	OnBnClickedButtonRead();
}

void CTestDlg::OnBnClickedButton15()
{
	OnBnClickedM1reset();
	OnBnClickedButtonAuthena();
	OnBnClickedButtonWrite();
}

void CTestDlg::OnBnClickedButtonChanga()
{
	int nRet;
	CString sMsg;
	unsigned char ucKey[6]={0},ucKey2[6]={0};
	unsigned char uTmp[2];
	unsigned char ucBloCK = 0;
	unsigned char ucData[16]={0};
	DWORD dwSerialNo;
	unsigned char ucSize;

	GetDlgItem(IDC_EDIT_SECNO)->GetWindowText(sMsg);	ucBloCK = atoi(sMsg);
	GetDlgItem(IDC_EDIT_OLDPASS0)->GetWindowText(sMsg);		memcpy(uTmp,sMsg,2);	ucKey[0] = cTouchar(uTmp,sMsg.GetLength());
	GetDlgItem(IDC_EDIT_OLDPASS1)->GetWindowText(sMsg);		memcpy(uTmp,sMsg,2);	ucKey[1] = cTouchar(uTmp,sMsg.GetLength());
	GetDlgItem(IDC_EDIT_OLDPASS2)->GetWindowText(sMsg);		memcpy(uTmp,sMsg,2);	ucKey[2] = cTouchar(uTmp,sMsg.GetLength());
	GetDlgItem(IDC_EDIT_OLDPASS3)->GetWindowText(sMsg);		memcpy(uTmp,sMsg,2);	ucKey[3] = cTouchar(uTmp,sMsg.GetLength());
	GetDlgItem(IDC_EDIT_OLDPASS4)->GetWindowText(sMsg);		memcpy(uTmp,sMsg,2);	ucKey[4] = cTouchar(uTmp,sMsg.GetLength());
	GetDlgItem(IDC_EDIT_OLDPASS5)->GetWindowText(sMsg);		memcpy(uTmp,sMsg,2);	ucKey[5] = cTouchar(uTmp,sMsg.GetLength());

	GetDlgItem(IDC_EDIT_NEWPASS0)->GetWindowText(sMsg);		memcpy(uTmp,sMsg,2);	ucKey2[0] = cTouchar(uTmp,sMsg.GetLength());
	GetDlgItem(IDC_EDIT_NEWPASS1)->GetWindowText(sMsg);		memcpy(uTmp,sMsg,2);	ucKey2[1] = cTouchar(uTmp,sMsg.GetLength());
	GetDlgItem(IDC_EDIT_NEWPASS2)->GetWindowText(sMsg);		memcpy(uTmp,sMsg,2);	ucKey2[2] = cTouchar(uTmp,sMsg.GetLength());
	GetDlgItem(IDC_EDIT_NEWPASS3)->GetWindowText(sMsg);		memcpy(uTmp,sMsg,2);	ucKey2[3] = cTouchar(uTmp,sMsg.GetLength());
	GetDlgItem(IDC_EDIT_NEWPASS4)->GetWindowText(sMsg);		memcpy(uTmp,sMsg,2);	ucKey2[4] = cTouchar(uTmp,sMsg.GetLength());
	GetDlgItem(IDC_EDIT_NEWPASS5)->GetWindowText(sMsg);		memcpy(uTmp,sMsg,2);	ucKey2[5] = cTouchar(uTmp,sMsg.GetLength());
	if (m_iPort == 9999)
	{
		nRet = Syn_OpenPort(m_iPort);
		if (nRet == 0)
		{
			CCalcTime tSpan;
			tSpan.Clear();
			tSpan.BegginTime();
			nRet = Syn_USBHIDM1Reset(m_iPort,&dwSerialNo,&ucSize);
			nRet = Syn_USBHIDM1AuthenKey(m_iPort,0,ucBloCK*4+3,ucKey);
			if (nRet == 0)
			{
				nRet = Syn_USBHIDM1ReadBlock(m_iPort,ucBloCK*4+3,ucData);
				if (nRet == 0)
				{
					memcpy(ucData,ucKey2,6);
					nRet = Syn_USBHIDM1WriteBlock(m_iPort,ucBloCK*4+3,ucData);
					tSpan.EndTime();
					if (nRet == 0)
					{
						sMsg.Format("修改M1卡 %d 扇区密钥A成功, %d ms",ucBloCK,tSpan.MSecond);
					}
					else
					{
						sMsg.Format("修改M1卡 %d 扇区密钥A失败,写错误,nRet = %d, %d ms",ucBloCK,nRet,tSpan.MSecond);
					}
				}
				else
				{
					tSpan.EndTime();
					sMsg.Format("修改M1卡 %d 扇区密钥A失败,读错误,nRet = %d, %d ms",ucBloCK,nRet,tSpan.MSecond);
				}
			}
			else
			{
				tSpan.EndTime();
				sMsg.Format("密钥A验证M1卡 %d 扇区失败,无法修改密钥A,nRet = %d, %d ms",ucBloCK,nRet,tSpan.MSecond);
			}
		}
		else
		{
			sMsg = "打开端口错误";
		}
		if (m_iPort >0)
		{
			Syn_ClosePort(m_iPort);
		}
	}
	else
	{
		sMsg = "此读卡器不支持该功能";
	}
	InsertDebugMes(sMsg);

}

void CTestDlg::OnBnClickedButtonChangb()
{
	int nRet;
	CString sMsg;
	unsigned char ucKey[6]={0},ucKey2[6]={0};
	unsigned char uTmp[2];
	unsigned char ucBloCK = 0;
	unsigned char ucData[16]={0};
	DWORD dwSerialNo;
	unsigned char ucSize;

	GetDlgItem(IDC_EDIT_SECNO)->GetWindowText(sMsg);	ucBloCK = atoi(sMsg);
	GetDlgItem(IDC_EDIT_OLDPASS0)->GetWindowText(sMsg);		memcpy(uTmp,sMsg,2);	ucKey[0] = cTouchar(uTmp,sMsg.GetLength());
	GetDlgItem(IDC_EDIT_OLDPASS1)->GetWindowText(sMsg);		memcpy(uTmp,sMsg,2);	ucKey[1] = cTouchar(uTmp,sMsg.GetLength());
	GetDlgItem(IDC_EDIT_OLDPASS2)->GetWindowText(sMsg);		memcpy(uTmp,sMsg,2);	ucKey[2] = cTouchar(uTmp,sMsg.GetLength());
	GetDlgItem(IDC_EDIT_OLDPASS3)->GetWindowText(sMsg);		memcpy(uTmp,sMsg,2);	ucKey[3] = cTouchar(uTmp,sMsg.GetLength());
	GetDlgItem(IDC_EDIT_OLDPASS4)->GetWindowText(sMsg);		memcpy(uTmp,sMsg,2);	ucKey[4] = cTouchar(uTmp,sMsg.GetLength());
	GetDlgItem(IDC_EDIT_OLDPASS5)->GetWindowText(sMsg);		memcpy(uTmp,sMsg,2);	ucKey[5] = cTouchar(uTmp,sMsg.GetLength());

	GetDlgItem(IDC_EDIT_NEWPASS0)->GetWindowText(sMsg);		memcpy(uTmp,sMsg,2);	ucKey2[0] = cTouchar(uTmp,sMsg.GetLength());
	GetDlgItem(IDC_EDIT_NEWPASS1)->GetWindowText(sMsg);		memcpy(uTmp,sMsg,2);	ucKey2[1] = cTouchar(uTmp,sMsg.GetLength());
	GetDlgItem(IDC_EDIT_NEWPASS2)->GetWindowText(sMsg);		memcpy(uTmp,sMsg,2);	ucKey2[2] = cTouchar(uTmp,sMsg.GetLength());
	GetDlgItem(IDC_EDIT_NEWPASS3)->GetWindowText(sMsg);		memcpy(uTmp,sMsg,2);	ucKey2[3] = cTouchar(uTmp,sMsg.GetLength());
	GetDlgItem(IDC_EDIT_NEWPASS4)->GetWindowText(sMsg);		memcpy(uTmp,sMsg,2);	ucKey2[4] = cTouchar(uTmp,sMsg.GetLength());
	GetDlgItem(IDC_EDIT_NEWPASS5)->GetWindowText(sMsg);		memcpy(uTmp,sMsg,2);	ucKey2[5] = cTouchar(uTmp,sMsg.GetLength());
	if (m_iPort == 9999)
	{
		nRet = Syn_OpenPort(m_iPort);
		if (nRet == 0)
		{
			CCalcTime tSpan;
			tSpan.Clear();
			tSpan.BegginTime();
			nRet = Syn_USBHIDM1Reset(m_iPort,&dwSerialNo,&ucSize);
			nRet = Syn_USBHIDM1AuthenKey(m_iPort,0,ucBloCK*4+3,ucKey);
			if (nRet == 0)
			{
				nRet = Syn_USBHIDM1ReadBlock(m_iPort,ucBloCK*4+3,ucData);
				if (nRet == 0)
				{
					memcpy(ucData+10,ucKey2,6);
					nRet = Syn_USBHIDM1WriteBlock(m_iPort,ucBloCK*4+3,ucData);
					tSpan.EndTime();
					if (nRet == 0)
					{
						sMsg.Format("修改M1卡 %d 扇区密钥B成功, %d ms",ucBloCK,tSpan.MSecond);
					}
					else
					{
						sMsg.Format("修改M1卡 %d 扇区密钥B失败,写错误,nRet = %d, %d ms",ucBloCK,nRet,tSpan.MSecond);
					}
				}
				else
				{
					tSpan.EndTime();
					sMsg.Format("修改M1卡 %d 扇区密钥B失败,读错误,nRet = %d, %d ms",ucBloCK,nRet,tSpan.MSecond);
				}
			}
			else
			{
				tSpan.EndTime();
				sMsg.Format("验证M1卡 %d 扇区失败,无法修改密钥B,nRet = %d, %d ms",ucBloCK,nRet,tSpan.MSecond);
			}
		}
		else
		{
			sMsg = "打开端口错误";
		}
		if (m_iPort >0)
		{
			Syn_ClosePort(m_iPort);
		}
	}
	else
	{
		sMsg = "此读卡器不支持该功能";
	}
	InsertDebugMes(sMsg);
}

void CTestDlg::OnBnClickedButton19()
{
	int nRet ;
	int nErr = 0;
	CString sMsg;
	unsigned char ucData[16]={0};
	if (m_iPort == 9999)
	{
		nRet = Syn_OpenPort(m_iPort);
		if (nRet == 0)
		{
			CCalcTime tSpan;
			tSpan.Clear();
			tSpan.BegginTime();
			for (int i = 0;i<64;i++) 
			{
				if ((i%4) == 3)
				{
					continue;
				}
				nRet = Syn_USBHIDM1ReadBlock(m_iPort,i,ucData);
				if (nRet == 0)
				{
					sMsg.Format("读M1卡 %d 扇区 %d 块成功 ,数据为:%0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X ",i/4,i%4,ucData[0],ucData[1],ucData[2],ucData[3],ucData[4],ucData[5],ucData[6],ucData[7],ucData[8],ucData[9],ucData[10],ucData[11],ucData[12],ucData[13],ucData[14],ucData[15]);
					InsertDebugMes(sMsg);
				}
				else
				{
					sMsg.Format("读M1卡 %d 扇区 %d 块失败,nRet = %d",i/4,i%4,nRet);
					if (m_iM1ReadStart == 1)
					{
						nErr++;
					}
					InsertDebugMes(sMsg);
				}
			}
			tSpan.EndTime();
			if (m_iM1ReadStart == 1)
			{
				m_iM1ReadSum++;
				if (nErr==0)
				{
					m_iM1ReadOKSum++;
				}
			}
			sMsg.Format("读卡时间 %d ms",tSpan.MSecond);
		}
		else
		{
			sMsg = "打开端口错误";
		}
		if (m_iPort >0)
		{
			Syn_ClosePort(m_iPort);
		}
	}
	else
	{
		sMsg = "此读卡器不支持该功能";
	}
	InsertDebugMes(sMsg);
}

void CTestDlg::OnBnClickedButton20()
{
	int nRet ;
	int nErr = 0;
	CString sMsg;
	unsigned char ucData[16]={0};
	unsigned char uTmp[2]={0};
	GetDlgItem(IDC_EDIT_DATA0)->GetWindowText(sMsg);	memcpy(uTmp,sMsg,2);	ucData[0] = cTouchar(uTmp,sMsg.GetLength());
	GetDlgItem(IDC_EDIT_DATA1)->GetWindowText(sMsg);	memcpy(uTmp,sMsg,2);	ucData[1] = cTouchar(uTmp,sMsg.GetLength());	
	GetDlgItem(IDC_EDIT_DATA2)->GetWindowText(sMsg);	memcpy(uTmp,sMsg,2);	ucData[2] = cTouchar(uTmp,sMsg.GetLength());	
	GetDlgItem(IDC_EDIT_DATA3)->GetWindowText(sMsg);	memcpy(uTmp,sMsg,2);	ucData[3] = cTouchar(uTmp,sMsg.GetLength());	
	GetDlgItem(IDC_EDIT_DATA4)->GetWindowText(sMsg);	memcpy(uTmp,sMsg,2);	ucData[4] = cTouchar(uTmp,sMsg.GetLength());	
	GetDlgItem(IDC_EDIT_DATA5)->GetWindowText(sMsg);	memcpy(uTmp,sMsg,2);	ucData[5] = cTouchar(uTmp,sMsg.GetLength());	
	GetDlgItem(IDC_EDIT_DATA6)->GetWindowText(sMsg);	memcpy(uTmp,sMsg,2);	ucData[6] = cTouchar(uTmp,sMsg.GetLength());	
	GetDlgItem(IDC_EDIT_DATA7)->GetWindowText(sMsg);	memcpy(uTmp,sMsg,2);	ucData[7] = cTouchar(uTmp,sMsg.GetLength());	
	GetDlgItem(IDC_EDIT_DATA8)->GetWindowText(sMsg);	memcpy(uTmp,sMsg,2);	ucData[8] = cTouchar(uTmp,sMsg.GetLength());	
	GetDlgItem(IDC_EDIT_DATA9)->GetWindowText(sMsg);	memcpy(uTmp,sMsg,2);	ucData[9] = cTouchar(uTmp,sMsg.GetLength());	
	GetDlgItem(IDC_EDIT_DATA10)->GetWindowText(sMsg);	memcpy(uTmp,sMsg,2);	ucData[10] = cTouchar(uTmp,sMsg.GetLength());	
	GetDlgItem(IDC_EDIT_DATA11)->GetWindowText(sMsg);	memcpy(uTmp,sMsg,2);	ucData[11] = cTouchar(uTmp,sMsg.GetLength());	
	GetDlgItem(IDC_EDIT_DATA12)->GetWindowText(sMsg);	memcpy(uTmp,sMsg,2);	ucData[12] = cTouchar(uTmp,sMsg.GetLength());	
	GetDlgItem(IDC_EDIT_DATA13)->GetWindowText(sMsg);	memcpy(uTmp,sMsg,2);	ucData[13] = cTouchar(uTmp,sMsg.GetLength());	
	GetDlgItem(IDC_EDIT_DATA14)->GetWindowText(sMsg);	memcpy(uTmp,sMsg,2);	ucData[14] = cTouchar(uTmp,sMsg.GetLength());	
	GetDlgItem(IDC_EDIT_DATA15)->GetWindowText(sMsg);	memcpy(uTmp,sMsg,2);	ucData[15] = cTouchar(uTmp,sMsg.GetLength());

	if (m_iPort == 9999)
	{
		nRet = Syn_OpenPort(m_iPort);
		if (nRet == 0)
		{
			CCalcTime tSpan;
			tSpan.Clear();
			tSpan.BegginTime();
			for (int i = 1;i<64;i++) 
			{
				if ((i%4) == 3)
				{
					continue;
				}
				nRet = Syn_USBHIDM1WriteBlock(m_iPort,i,ucData);
				if (nRet == 0)
				{
					sMsg.Format("写M1卡 %d 扇区 %d 块成功 ,数据为:%0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X ",i/4,i%4,ucData[0],ucData[1],ucData[2],ucData[3],ucData[4],ucData[5],ucData[6],ucData[7],ucData[8],ucData[9],ucData[10],ucData[11],ucData[12],ucData[13],ucData[14],ucData[15]);
					InsertDebugMes(sMsg);
				}
				else
				{
					sMsg.Format("写M1卡 %d 扇区 %d 块失败,nRet = %d",i/4,i%4,nRet);
					if (m_iM1WriteStart == 1)
					{
						nErr++;
					}
					InsertDebugMes(sMsg);
				}
			}
			tSpan.EndTime();
			if (m_iM1WriteStart == 1)
			{
				m_iM1WriteSum++;
				if (nErr==0)
				{
					m_iM1WriteOKSum++;
				}
			}
			sMsg.Format("读卡时间 %d ms",tSpan.MSecond);
		}
		else
		{
			sMsg = "打开端口错误";
		}
		if (m_iPort >0)
		{
			Syn_ClosePort(m_iPort);
		}
	}
	else
	{
		sMsg = "此读卡器不支持该功能";
	}
	InsertDebugMes(sMsg);
}

void CTestDlg::OnBnClickedButton1()
{
	KillTimer(m_iTime);
	m_iReadStart = 1;
	m_iReadSum = 0;
	m_iReadOKSum = 0;
	m_iM1ReadStart = 1;
	m_iM1ReadSum = 0;
	m_iM1ReadOKSum = 0;
	m_iTime =	SetTimer(4,1000,0);
}

void CTestDlg::OnBnClickedButton2()
{
	CString sMsg;
	unsigned char ucSec = 0;
	unsigned char ucBloCK = 0;
	m_iReadStart = 0;
	m_iM1ReadStart = 0;
	GetDlgItem(IDC_EDIT_BLOCKNO)->GetWindowText(sMsg);	ucBloCK = atoi(sMsg);
	GetDlgItem(IDC_EDIT_SECNO)->GetWindowText(sMsg);	ucSec = atoi(sMsg);   
	KillTimer(m_iTime);
	sMsg.Format("读二代证总计 %d 次,成功 %d 次,读M1卡 %d 扇区 %d 块 总计 %d 次,成功 %d 次",m_iReadSum,m_iReadOKSum,ucSec,ucBloCK,m_iM1ReadSum,m_iM1ReadOKSum);
	InsertDebugMes(sMsg);
	AfxMessageBox(sMsg);
}

void CTestDlg::OnBnClickedButfpBri()
{
	int nRet;
	int nBri=128;
	CString sMsg;
	CCalcTime tSpan;
	GetDlgItem(IDC_EDIT_BRI)->GetWindowText(sMsg);
	nBri = atoi(sMsg);
	tSpan.Clear();
	tSpan.BegginTime();
	nRet = LIVESCAN_SetBright(0,nBri);
	tSpan.EndTime();
	if (nRet == 1)
	{
		sMsg.Format("设置指纹采集仪亮度成功,亮度为%d, %d ms",nBri,tSpan.MSecond);
	}
	else
	{
		sMsg.Format("设置指纹采集仪亮度失败,nRet = %d , %d ms",nRet,tSpan.MSecond);
	}
	InsertDebugMes(sMsg);
}

void CTestDlg::OnBnClickedButfpCon()
{
	int nRet;
	int nCon=128;
	CString sMsg;
	CCalcTime tSpan;
	GetDlgItem(IDC_EDIT_CON)->GetWindowText(sMsg);
	nCon = atoi(sMsg);
	tSpan.Clear();
	tSpan.BegginTime();
	nRet = LIVESCAN_SetBright(0,nCon);
	tSpan.EndTime();
	if (nRet == 1)
	{
		sMsg.Format("设置指纹采集仪对比度成功,亮度为%d, %d ms",nCon,tSpan.MSecond);
	}
	else
	{
		sMsg.Format("设置指纹采集仪对比度失败,nRet = %d , %d ms",nCon,tSpan.MSecond);
	}
	InsertDebugMes(sMsg);
}

void CTestDlg::OnClose()
{
	m_fLog.Close();
	CDialog::OnClose();
}

void CTestDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}

void CTestDlg::OnBnClickedButton21()
{
	KillTimer(m_iTime);
	m_iM1ReadStart = 1;
	m_iM1ReadSum = 0;
	m_iM1ReadOKSum = 0;
	m_iTime =	SetTimer(5,1000,0);
}

void CTestDlg::OnBnClickedButton23()
{
	CString sMsg;
	m_iM1ReadStart = 0;
	KillTimer(m_iTime);
	sMsg.Format("读M1卡所有块 总计 %d 次,成功 %d 次",m_iM1ReadSum,m_iM1ReadOKSum);
	InsertDebugMes(sMsg);
	AfxMessageBox(sMsg);
}

void CTestDlg::OnBnClickedButton22()
{
	KillTimer(m_iTime);
	m_iM1WriteStart = 1;
	m_iM1WriteSum = 0;
	m_iM1WriteOKSum = 0;
	m_iTime =	SetTimer(6,1000,0);
}

void CTestDlg::OnBnClickedButton24()
{
	CString sMsg;
	m_iM1WriteStart = 0;
	KillTimer(m_iTime);
	sMsg.Format("写M1卡所有块 总计 %d 次,成功 %d 次",m_iM1WriteSum,m_iM1WriteOKSum);
	InsertDebugMes(sMsg);
	AfxMessageBox(sMsg);
}

void CTestDlg::OnBnClickedButton8()
{
	CString sMsg;
	CCalcTime tSpan;
	GetDlgItem(IDC_EDIT1)->GetWindowText(sMsg);
	m_iLoopSum = atoi(sMsg);
	sMsg = "连续读写卡次数已经更改，次数为：" + sMsg;
	InsertDebugMes(sMsg);
	AfxMessageBox(sMsg);
}
