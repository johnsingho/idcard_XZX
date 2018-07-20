// HFSDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Test.h"
#include "HFSDlg.h"
#include "TestDlg.h"
#include "CardThread.h"

// CHFSDlg 对话框
unsigned char cToucharex(unsigned char cCard[2],unsigned char mode)
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

IMPLEMENT_DYNAMIC(CHFSDlg, CDialog)

CHFSDlg::CHFSDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHFSDlg::IDD, pParent)
{

}

CHFSDlg::~CHFSDlg()
{
}

void CHFSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTMSG, m_MsgList);
}


BEGIN_MESSAGE_MAP(CHFSDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTONOPEN, &CHFSDlg::OnBnClickedButtonopen)
	ON_BN_CLICKED(IDC_BUTTONCLOSE, &CHFSDlg::OnBnClickedButtonclose)
	ON_BN_CLICKED(IDC_BEEP, &CHFSDlg::OnBnClickedBeep)
	ON_BN_CLICKED(IDC_LEDON, &CHFSDlg::OnBnClickedLedon)
	ON_BN_CLICKED(IDC_LEDOFF, &CHFSDlg::OnBnClickedLedoff)
	ON_BN_CLICKED(IDC_LOADKEYA, &CHFSDlg::OnBnClickedLoadkeya)
	ON_BN_CLICKED(IDC_LOADKEYB, &CHFSDlg::OnBnClickedLoadkeyb)
	ON_BN_CLICKED(IDC_HALT, &CHFSDlg::OnBnClickedHalt)
	ON_BN_CLICKED(IDC_RESET, &CHFSDlg::OnBnClickedReset)
	ON_BN_CLICKED(IDC_AUTHA, &CHFSDlg::OnBnClickedAutha)
	ON_BN_CLICKED(IDC_AUTHB, &CHFSDlg::OnBnClickedAuthb)
	ON_BN_CLICKED(IDC_FINDIC, &CHFSDlg::OnBnClickedFindic)
	ON_BN_CLICKED(IDC_FINDEM, &CHFSDlg::OnBnClickedFindem)
	ON_BN_CLICKED(IDC_BUTTON1, &CHFSDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_READIC, &CHFSDlg::OnBnClickedReadic)
	ON_BN_CLICKED(IDC_WRITEIC, &CHFSDlg::OnBnClickedWriteic)
	ON_BN_CLICKED(IDC_BUTTON2, &CHFSDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CHFSDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON9, &CHFSDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON4, &CHFSDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CHFSDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CHFSDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CHFSDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CHFSDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_WRITEIC2, &CHFSDlg::OnBnClickedWriteic2)
	ON_BN_CLICKED(IDC_WRITEIC4, &CHFSDlg::OnBnClickedWriteic4)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CHFSDlg 消息处理程序

BOOL CHFSDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CCardThread::LoadConfig();
	InitData();
	GetDlgItem(IDC_EDIT1)->SetWindowText("10");
	m_iLoopSum = 10;

	if (CCardThread::InitDll() != 0) {
		AfxMessageBox("调用ThirdInOneDll失败！",MB_OK|MB_ICONINFORMATION);
	}
	BOOL bol;
	bol = OpenLogFile();
	if (!bol)
	{
		AfxMessageBox("打开日志文件错误，不能写入系统日志！");
	}
	InsertDebugMes("系统初始化成功!");

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
BOOL CHFSDlg::OpenLogFile()
{
	CString strFile;
	CTime	tLog = CTime::GetCurrentTime();
	_mkdir(".\\LOG");
	strFile = tLog.Format(".\\Log\\%Y-%m-%d-hfs.txt");
	return m_fLog.Open((LPCTSTR) strFile ,CFile::modeNoTruncate | 
		CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite);
}
void CHFSDlg::InsertDebugMes(CString sMsg)
{
	CString strTime;
	CTime   timTemp;
	CString strMes;
	timTemp = CTime::GetCurrentTime();
	strTime = timTemp.Format("%Y-%m-%d %H:%M:%S");
	if(m_MsgList.GetCount() >200)
	{
		DeleteAllMsg();
	}
	strMes = strTime+"    "+sMsg+"\r\n";
	m_MsgList.InsertString(0,strMes);
	m_fLog.SeekToEnd();
	m_fLog.Write(strMes,strMes.GetLength());
}
void CHFSDlg::DeleteAllMsg()
{
	int Num=m_MsgList.GetCount();
	for (int i=Num-1; i>=0; i--)
	{
		m_MsgList.DeleteString( i );
	}
}
void CHFSDlg::InitData()
{
	GetDlgItem(IDC_EDITSECTION)->SetWindowText("8");
	GetDlgItem(IDC_EDITBLOCK)->SetWindowText("32");
	GetDlgItem(IDC_EDITBLOCKNUM)->SetWindowText("3");
	GetDlgItem(IDC_EDITKEY)->SetWindowText("FF");
	GetDlgItem(IDC_EDITKEY2)->SetWindowText("FF");
	GetDlgItem(IDC_EDITKEY3)->SetWindowText("FF");
	GetDlgItem(IDC_EDITKEY4)->SetWindowText("FF");
	GetDlgItem(IDC_EDITKEY5)->SetWindowText("FF");
	GetDlgItem(IDC_EDITKEY6)->SetWindowText("FF");
	GetDlgItem(IDC_EDITDATA)->SetWindowText("00");
	GetDlgItem(IDC_EDITDATA2)->SetWindowText("01");
	GetDlgItem(IDC_EDITDATA3)->SetWindowText("02");
	GetDlgItem(IDC_EDITDATA4)->SetWindowText("03");
	GetDlgItem(IDC_EDITDATA5)->SetWindowText("04");
	GetDlgItem(IDC_EDITDATA6)->SetWindowText("05");
	GetDlgItem(IDC_EDITDATA7)->SetWindowText("06");
	GetDlgItem(IDC_EDITDATA8)->SetWindowText("07");
	GetDlgItem(IDC_EDITDATA9)->SetWindowText("08");
	GetDlgItem(IDC_EDITDATA10)->SetWindowText("09");
	GetDlgItem(IDC_EDITDATA11)->SetWindowText("0A");
	GetDlgItem(IDC_EDITDATA12)->SetWindowText("0B");
	GetDlgItem(IDC_EDITDATA13)->SetWindowText("0C");
	GetDlgItem(IDC_EDITDATA14)->SetWindowText("0D");
	GetDlgItem(IDC_EDITDATA15)->SetWindowText("0E");
	GetDlgItem(IDC_EDITDATA16)->SetWindowText("0F");
}

void CHFSDlg::ReadSecondCard()
{
	bool bRet = false;int nLen;
	unsigned char uTmp[2048];
	unsigned char uSerialNo[16];
	unsigned char uSerialLen = 0;
	memset(uSerialNo,0,16);
	CString sText;
	CCalcTime tSpan;
	tSpan.Clear();
	bRet = true;
	if (bRet) {
		tSpan.Clear();
		tSpan.BegginTime();
		nLen = CCardThread::ReadMefire(255,uTmp);
		tSpan.EndTime();
		if (m_iReadStart == 1)
		{
			m_iReadSum++;
		}
		if (nLen > 0) {
			if (m_iReadStart == 1)
			{
				m_iReadOKSum++;
			}
			sText.Format("读二代证卡成功,操作时间 %d ms",tSpan.MSecond);	InsertDebugMes(sText);//m_MsgList.InsertString(0,sText);
			tagIDCardData2 tIdCard;
			memcpy(&tIdCard,uTmp,sizeof(tagIDCardData2));
			sText.Format("姓名: %s",tIdCard.Name);			InsertDebugMes(sText);//m_MsgList.InsertString(0,sText);
			memset(uSerialNo,0,16),memcpy(uSerialNo,tIdCard.Sex,2);
			sText.Format("性别: %s",uSerialNo);		InsertDebugMes(sText);//m_MsgList.InsertString(0,sText);
			memset(uSerialNo,0,16),memcpy(uSerialNo,tIdCard.Nation,4);
			sText.Format("民族: %s",uSerialNo);		InsertDebugMes(sText);//m_MsgList.InsertString(0,sText);
			sText.Format("出生日期: %s",tIdCard.Born);		InsertDebugMes(sText);//m_MsgList.InsertString(0,sText);
			sText.Format("地址: %s",tIdCard.Address);		InsertDebugMes(sText);//m_MsgList.InsertString(0,sText);
			sText.Format("身份证号: %s",tIdCard.IDCardNo);		InsertDebugMes(sText);//m_MsgList.InsertString(0,sText);
			sText.Format("发证机关: %s",tIdCard.GrantDept);		InsertDebugMes(sText);//m_MsgList.InsertString(0,sText);
			sText.Format("有效期: %s",tIdCard.UserLife);		InsertDebugMes(sText);//m_MsgList.InsertString(0,sText);
			sText.Format("照片路径: %s",tIdCard.PhotoFileName);		InsertDebugMes(sText);//m_MsgList.InsertString(0,sText);
		}
		else
		{
			sText.Format("读二代证卡失败,操作时间 %d ms",tSpan.MSecond);	InsertDebugMes(sText);//m_MsgList.InsertString(0,sText);
		}
	}
}
void CHFSDlg::OnBnClickedButtonopen()
{
	bool bRet;
	CString sText;
	CCalcTime tSpan;
	tSpan.Clear();
	tSpan.BegginTime();
	bRet = CCardThread::Dev_Init(CCardThread::m_ComPort,CCardThread::m_ComBaud );
	tSpan.EndTime();
	if (bRet) {
		sText.Format("初始化读卡器成功,操作时间 %d ms!",tSpan.MSecond);
	}
	else
	{
		sText.Format("初始化读卡器失败,操作时间 %d ms!",tSpan.MSecond);
	}
	InsertDebugMes(sText);
}

void CHFSDlg::OnBnClickedButtonclose()
{
	CCardThread::Dev_Close(CCardThread::m_ComPort);
	InsertDebugMes("关闭读卡器成功");
}

void CHFSDlg::OnBnClickedBeep()
{
	unsigned char BeepTime;
	BeepTime = (unsigned char) CCardThread::m_BeepTime;
	CString sText;
	CCalcTime tSpan;
	tSpan.Clear();
	tSpan.BegginTime();
	CCardThread::Beep2(BeepTime);
	tSpan.EndTime();
	sText.Format("发送Beep命令，操作时间 %d ms!",tSpan.MSecond);
	InsertDebugMes(sText);
}

void CHFSDlg::OnBnClickedLedon()
{
	bool bOn=true ;
	CString sText;
	CCalcTime tSpan;
	tSpan.Clear();
	tSpan.BegginTime();
	CCardThread::Led(bOn);
	tSpan.EndTime();
	sText.Format("发送LED亮命令，操作时间 %d ms!",tSpan.MSecond);
	InsertDebugMes(sText);
}

void CHFSDlg::OnBnClickedLedoff()
{
	bool bOn=false ;
	CString sText;
	CCalcTime tSpan;
	tSpan.Clear();
	tSpan.BegginTime();
	CCardThread::Led(bOn);
	tSpan.EndTime();
	sText.Format("发送LED灭命令，操作时间 %d ms!",tSpan.MSecond);
	InsertDebugMes(sText);
}

void CHFSDlg::OnBnClickedLoadkeya()
{
	bool bRet= false;
	unsigned char uMode = 0;
	unsigned char uSectionNum;
	unsigned char uKey[6];
	unsigned char uTmp[2];
	CString sText;
	GetDlgItem(IDC_EDITSECTION)->GetWindowText(sText);	uSectionNum = atoi(sText);
	GetDlgItem(IDC_EDITKEY)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uKey[0] = cToucharex(uTmp,sText.GetLength());
	GetDlgItem(IDC_EDITKEY2)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uKey[1] = cToucharex(uTmp,sText.GetLength());
	GetDlgItem(IDC_EDITKEY3)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uKey[2] = cToucharex(uTmp,sText.GetLength());
	GetDlgItem(IDC_EDITKEY4)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uKey[3] = cToucharex(uTmp,sText.GetLength());
	GetDlgItem(IDC_EDITKEY5)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uKey[4] = cToucharex(uTmp,sText.GetLength());
	GetDlgItem(IDC_EDITKEY6)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uKey[5] = cToucharex(uTmp,sText.GetLength());
	CCalcTime tSpan;
	tSpan.Clear();
	tSpan.BegginTime();
	bRet = CCardThread::LoadKey(uMode,uSectionNum,uKey);
	tSpan.EndTime();
	if(bRet)
	{
		sText.Format("下载A密钥 %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X 成功,操作时间 %d ms!",uKey[0],uKey[1],uKey[2],uKey[3],uKey[4],uKey[5],tSpan.MSecond);
	}
	else
	{
		sText.Format("下载A密钥 %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X 失败,操作时间 %d ms!",uKey[0],uKey[1],uKey[2],uKey[3],uKey[4],uKey[5],tSpan.MSecond);
	}
	InsertDebugMes(sText);
}

void CHFSDlg::OnBnClickedLoadkeyb()
{
	bool bRet= false;
	unsigned char uMode = 1;
	unsigned char uSectionNum;
	unsigned char uKey[6];
	unsigned char uTmp[2];
	CString sText;
	GetDlgItem(IDC_EDITSECTION)->GetWindowText(sText);	uSectionNum = atoi(sText);
	GetDlgItem(IDC_EDITKEY)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uKey[0] = cToucharex(uTmp,sText.GetLength());
	GetDlgItem(IDC_EDITKEY2)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uKey[1] = cToucharex(uTmp,sText.GetLength());
	GetDlgItem(IDC_EDITKEY3)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uKey[2] = cToucharex(uTmp,sText.GetLength());
	GetDlgItem(IDC_EDITKEY4)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uKey[3] = cToucharex(uTmp,sText.GetLength());
	GetDlgItem(IDC_EDITKEY5)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uKey[4] = cToucharex(uTmp,sText.GetLength());
	GetDlgItem(IDC_EDITKEY6)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uKey[5] = cToucharex(uTmp,sText.GetLength());
	CCalcTime tSpan;
	tSpan.Clear();
	tSpan.BegginTime();
	bRet = CCardThread::LoadKey(uMode,uSectionNum,uKey);
	tSpan.EndTime();
	if(bRet)
	{
		sText.Format("下载B密钥 %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X 成功,操作时间 %d ms!",uKey[0],uKey[1],uKey[2],uKey[3],uKey[4],uKey[5],tSpan.MSecond);
	}
	else
	{
		sText.Format("下载B密钥 %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X 失败,操作时间 %d ms!",uKey[0],uKey[1],uKey[2],uKey[3],uKey[4],uKey[5],tSpan.MSecond);
	}
	InsertDebugMes(sText);
}

void CHFSDlg::OnBnClickedHalt()
{
	bool bRet=false ;
	CString sText;
	CCalcTime tSpan;
	tSpan.Clear();
	tSpan.BegginTime();
	bRet = CCardThread::GT_Halt();
	tSpan.EndTime();
	if (bRet) {
		sText.Format("挂起卡片成功,操作时间 %d ms!",tSpan.MSecond);
	}
	else
	{
		sText.Format("挂起卡片失败,操作时间 %d ms!",tSpan.MSecond);
	}
	InsertDebugMes(sText);
}

void CHFSDlg::OnBnClickedReset()
{
	bool bRet=false ;
	CString sText;
	CCalcTime tSpan;
	tSpan.Clear();
	tSpan.BegginTime();
	bRet = CCardThread::GT_Reset();
	tSpan.EndTime();
	if (bRet) {
		sText.Format("复位卡片成功,操作时间 %d ms!",tSpan.MSecond);
	}
	else
	{
		sText.Format("复位卡片失败,操作时间 %d ms!",tSpan.MSecond);
	}
	InsertDebugMes(sText);
}

void CHFSDlg::OnBnClickedAutha()
{
	bool bRet= false;
	unsigned char uMode = 0;
	unsigned char uSectionNum;
	CString sText;
	GetDlgItem(IDC_EDITSECTION)->GetWindowText(sText);	uSectionNum = atoi(sText);
	CCalcTime tSpan;
	tSpan.Clear();
	tSpan.BegginTime();
	bRet = CCardThread::Authenticate(uMode,uSectionNum);
	tSpan.EndTime();
	if(bRet)
	{
		sText.Format("密钥A验证 %d 扇区成功,操作时间 %d ms!",uSectionNum,tSpan.MSecond);
	}
	else
	{
		sText.Format("密钥A验证 %d 扇区失败,操作时间 %d ms!",uSectionNum,tSpan.MSecond);
	}
	InsertDebugMes(sText);
}

void CHFSDlg::OnBnClickedAuthb()
{
	bool bRet= false;
	unsigned char uMode = 1;
	unsigned char uSectionNum;
	CString sText;
	GetDlgItem(IDC_EDITSECTION)->GetWindowText(sText);	uSectionNum = atoi(sText);
	CCalcTime tSpan;
	tSpan.Clear();
	tSpan.BegginTime();
	bRet = CCardThread::Authenticate(uMode,uSectionNum);
	tSpan.EndTime();
	if(bRet)
	{
		sText.Format("密钥B验证 %d 扇区成功,操作时间 %d ms!",uSectionNum,tSpan.MSecond);
	}
	else
	{
		sText.Format("密钥B验证 %d 扇区失败,操作时间 %d ms!",uSectionNum,tSpan.MSecond);
	}
	InsertDebugMes(sText);
}

void CHFSDlg::OnBnClickedFindic()
{
	unsigned char BeepTime;
	BeepTime = (unsigned char) CCardThread::m_BeepTime;
	bool bRet = false;
	unsigned char uSerialNo[16];
	unsigned char uSerialLen = 0;
	memset(uSerialNo,0,16);
	CString sText;
	CCalcTime tSpan;
	tSpan.Clear();
	tSpan.BegginTime();
	bRet = CCardThread::LookupCard(1,uSerialNo,&uSerialLen);
	tSpan.EndTime();
	if (m_iM1ReadStart == 1)
	{
		m_iM1ReadSum++;
	}
	if (bRet) 
	{
		sText.Format("寻找IC卡成功,序列号为 %0.2X %0.2X %0.2X %0.2X,长度为 %d ,操作时间 %d ms",uSerialNo[0],uSerialNo[1],uSerialNo[2],uSerialNo[3],uSerialLen,tSpan.MSecond);
		if (BeepTime!=0)
		{
			CCardThread::Beep2(BeepTime);
		}
		if (m_iM1ReadStart == 1)
		{
			m_iM1ReadOKSum ++;
		}
	}
	else
	{
		sText.Format("寻找IC卡失败,操作时间 %d ms",tSpan.MSecond);
	}
	InsertDebugMes(sText);
}

void CHFSDlg::OnBnClickedFindem()
{
	unsigned char BeepTime;
	BeepTime = (unsigned char) CCardThread::m_BeepTime;
	bool bRet = false;
	unsigned char uSerialNo[16];
	unsigned char uSerialLen = 0;
	memset(uSerialNo,0,16);
	CString sText;
	CCalcTime tSpan;
	tSpan.Clear();
	tSpan.BegginTime();
	bRet = CCardThread::LookupCard(2,uSerialNo,&uSerialLen);
	tSpan.EndTime();
	if (bRet) 
	{
		sText.Format("寻找EM卡成功,序列号为 %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X,长度为 %d ,操作时间 %d ms",uSerialNo[0],uSerialNo[1],uSerialNo[2],uSerialNo[3],uSerialNo[4],uSerialNo[5],uSerialNo[6],uSerialNo[7],uSerialLen,tSpan.MSecond);
		CCardThread::Beep2(BeepTime);
	}
	else
	{
		sText.Format("寻找EM卡失败,操作时间 %d ms",tSpan.MSecond);
	}
	InsertDebugMes(sText);
}

void CHFSDlg::OnBnClickedButton1()
{
	ReadSecondCard();
}

void CHFSDlg::OnBnClickedReadic()
{
	int nRet = 0;
	unsigned char uBlock; unsigned char uBlockNum;
	unsigned char uData[16]; 
	CString sText;
	CCalcTime tSpan;
	memset(uData,0,16);
	GetDlgItem(IDC_EDITBLOCK)->GetWindowText(sText);	uBlock = atoi(sText);
	GetDlgItem(IDC_EDITBLOCKNUM)->GetWindowText(sText);	uBlockNum = atoi(sText);
	if (uBlock==0) { uBlockNum = 1;	}
	for (int i = 0;i<uBlockNum;i++) {
		tSpan.Clear();
		tSpan.BegginTime();
		nRet = CCardThread::ReadMefire(uBlock+i,uData);
		tSpan.EndTime();
		if (nRet>0) {
			sText.Format("读%d块数据成功,数据 %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X,操作时间 %d ms",uBlock+i,uData[0],uData[1],uData[2],uData[3],uData[4],uData[5],uData[6],uData[7],uData[8],uData[9],uData[10],uData[11],uData[12],uData[13],uData[14],uData[15],tSpan.MSecond);
		}
		else
		{
			sText.Format("读%d块数据失败,操作时间 %d ms",uBlock+i,tSpan.MSecond);
		}
		InsertDebugMes(sText);//m_MsgList.InsertString(0,sText);
	}
}

void CHFSDlg::OnBnClickedWriteic()
{
	bool bRet = false;
	unsigned char uBlock;
	unsigned char uData[16]; unsigned char uTmp[2];
	CString sText;
	CCalcTime tSpan;
	GetDlgItem(IDC_EDITBLOCK)->GetWindowText(sText);	uBlock = atoi(sText);
	GetDlgItem(IDC_EDITDATA)->GetWindowText(sText);		memcpy(uTmp,sText,2);	uData[0] = cToucharex(uTmp,sText.GetLength());
	GetDlgItem(IDC_EDITDATA2)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uData[1] = cToucharex(uTmp,sText.GetLength());
	GetDlgItem(IDC_EDITDATA3)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uData[2] = cToucharex(uTmp,sText.GetLength());
	GetDlgItem(IDC_EDITDATA4)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uData[3] = cToucharex(uTmp,sText.GetLength());
	GetDlgItem(IDC_EDITDATA5)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uData[4] = cToucharex(uTmp,sText.GetLength());
	GetDlgItem(IDC_EDITDATA6)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uData[5] = cToucharex(uTmp,sText.GetLength());
	GetDlgItem(IDC_EDITDATA7)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uData[6] = cToucharex(uTmp,sText.GetLength());
	GetDlgItem(IDC_EDITDATA8)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uData[7] = cToucharex(uTmp,sText.GetLength());
	GetDlgItem(IDC_EDITDATA9)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uData[8] = cToucharex(uTmp,sText.GetLength());
	GetDlgItem(IDC_EDITDATA10)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uData[9] = cToucharex(uTmp,sText.GetLength());
	GetDlgItem(IDC_EDITDATA11)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uData[10] = cToucharex(uTmp,sText.GetLength());
	GetDlgItem(IDC_EDITDATA12)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uData[11] = cToucharex(uTmp,sText.GetLength());
	GetDlgItem(IDC_EDITDATA13)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uData[12] = cToucharex(uTmp,sText.GetLength());
	GetDlgItem(IDC_EDITDATA14)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uData[13] = cToucharex(uTmp,sText.GetLength());
	GetDlgItem(IDC_EDITDATA15)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uData[14] = cToucharex(uTmp,sText.GetLength());
	GetDlgItem(IDC_EDITDATA16)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uData[15] = cToucharex(uTmp,sText.GetLength());
	tSpan.Clear();
	tSpan.BegginTime();
	bRet = CCardThread::WriteMefire(uBlock,uData);
	tSpan.EndTime();
	if (bRet) {
		sText.Format("写%d块数据 %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X 成功,操作时间 %d ms!",uBlock,uData[0],uData[1],uData[2],uData[3],uData[4],uData[5],uData[6],uData[7],uData[8],uData[9],uData[10],uData[11],uData[12],uData[13],uData[14],uData[15],tSpan.MSecond);
		//		sText.Format("写%d块数据 %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X  成功,操作时间 %d ms!",uBlock,uData[0],uData[1],uData[2],uData[3],uData[4],uData[5],uData[6],uData[7],uData[8],uData[9],tSpan.MSecond);
	}
	else
	{
		sText.Format("写%d块数据 %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X 失败,操作时间 %d ms!",uBlock,uData[0],uData[1],uData[2],uData[3],uData[4],uData[5],uData[6],uData[7],uData[8],uData[9],uData[10],uData[11],uData[12],uData[13],uData[14],uData[15],tSpan.MSecond);
		//		sText.Format("写%d块数据 %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X 失败,操作时间 %d ms!",uBlock,uData[0],uData[1],uData[2],uData[3],uData[4],uData[5],uData[6],uData[7],uData[8],uData[9],tSpan.MSecond);
	}
	InsertDebugMes(sText);//	m_MsgList.InsertString(0,sText);
}

void CHFSDlg::OnBnClickedButton2()
{
	int nRet = 0;
	int nErr = 0;
	unsigned char uData[16]; 
	CString sText;
	CCalcTime tSpan;
	tSpan.Clear();
	tSpan.BegginTime();
	for (int i = 0;i<64;i++) 
	{
		if ((i%4) == 3)
		{
			continue;
		}
		memset(uData,0,16);
		nRet = CCardThread::ReadMefire(i,uData);
		if (nRet>0) {
			sText.Format("读%d块数据成功,数据 %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X,操作时间 %d ms",i,uData[0],uData[1],uData[2],uData[3],uData[4],uData[5],uData[6],uData[7],uData[8],uData[9],uData[10],uData[11],uData[12],uData[13],uData[14],uData[15],tSpan.MSecond);
		}
		else
		{
			if (m_iM1ReadStart == 1)
			{
				nErr++;
			}
			sText.Format("读%d块数据失败",i);
		}
		InsertDebugMes(sText);
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

	sText.Format("读卡时间 %d ms",tSpan.MSecond );
	InsertDebugMes(sText);
}

void CHFSDlg::OnBnClickedButton3()
{
	bool bRet = false;
	int nErr = 0;
	unsigned char uBlock;
	unsigned char uData[16]; unsigned char uTmp[2];
	CString sText;
	CCalcTime tSpan;
	GetDlgItem(IDC_EDITBLOCK)->GetWindowText(sText);	uBlock = atoi(sText);
	GetDlgItem(IDC_EDITDATA)->GetWindowText(sText);		memcpy(uTmp,sText,2);	uData[0] = cToucharex(uTmp,sText.GetLength());
	GetDlgItem(IDC_EDITDATA2)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uData[1] = cToucharex(uTmp,sText.GetLength());
	GetDlgItem(IDC_EDITDATA3)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uData[2] = cToucharex(uTmp,sText.GetLength());
	GetDlgItem(IDC_EDITDATA4)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uData[3] = cToucharex(uTmp,sText.GetLength());
	GetDlgItem(IDC_EDITDATA5)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uData[4] = cToucharex(uTmp,sText.GetLength());
	GetDlgItem(IDC_EDITDATA6)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uData[5] = cToucharex(uTmp,sText.GetLength());
	GetDlgItem(IDC_EDITDATA7)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uData[6] = cToucharex(uTmp,sText.GetLength());
	GetDlgItem(IDC_EDITDATA8)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uData[7] = cToucharex(uTmp,sText.GetLength());
	GetDlgItem(IDC_EDITDATA9)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uData[8] = cToucharex(uTmp,sText.GetLength());
	GetDlgItem(IDC_EDITDATA10)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uData[9] = cToucharex(uTmp,sText.GetLength());
	GetDlgItem(IDC_EDITDATA11)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uData[10] = cToucharex(uTmp,sText.GetLength());
	GetDlgItem(IDC_EDITDATA12)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uData[11] = cToucharex(uTmp,sText.GetLength());
	GetDlgItem(IDC_EDITDATA13)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uData[12] = cToucharex(uTmp,sText.GetLength());
	GetDlgItem(IDC_EDITDATA14)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uData[13] = cToucharex(uTmp,sText.GetLength());
	GetDlgItem(IDC_EDITDATA15)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uData[14] = cToucharex(uTmp,sText.GetLength());
	GetDlgItem(IDC_EDITDATA16)->GetWindowText(sText);	memcpy(uTmp,sText,2);	uData[15] = cToucharex(uTmp,sText.GetLength());
	tSpan.Clear();
	tSpan.BegginTime();
	for(int i = 4;i<64;i++)
	{
		if ((i%4) == 3)
		{
			continue;
		}
		bRet = CCardThread::WriteMefire(i,uData);
		if (bRet) {
			sText.Format("写%d块数据 %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X 成功,操作时间 %d ms!",i,uData[0],uData[1],uData[2],uData[3],uData[4],uData[5],uData[6],uData[7],uData[8],uData[9],uData[10],uData[11],uData[12],uData[13],uData[14],uData[15],tSpan.MSecond);
		}
		else
		{
			if (m_iM1WriteStart == 1)
			{
				nErr++;
			}
			sText.Format("写%d块数据 %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X 失败",i,uData[0],uData[1],uData[2],uData[3],uData[4],uData[5],uData[6],uData[7],uData[8],uData[9],uData[10],uData[11],uData[12],uData[13],uData[14],uData[15]);
		}
		InsertDebugMes(sText);
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
	sText.Format("写卡时间 %d ms",tSpan.MSecond );
	InsertDebugMes(sText);
}

void CHFSDlg::OnBnClickedButton9()
{
	unsigned char BeepTime;
	BeepTime = (unsigned char) CCardThread::m_BeepTime;
	bool bRet = false;
	unsigned char uSerialNo[16];
	unsigned char uSerialLen = 0;
	memset(uSerialNo,0,16);
	CString sText;
	CCalcTime tSpan;
	tSpan.Clear();
	tSpan.BegginTime();
	bRet = CCardThread::LookupCard(4,uSerialNo,&uSerialLen);
	tSpan.EndTime();
	if (bRet) 
	{
		sText.Format("读身份证物理ID号成功,序列号为 %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X %0.2X,长度为 %d ,操作时间 %d ms",uSerialNo[0],uSerialNo[1],uSerialNo[2],uSerialNo[3],uSerialNo[4],uSerialNo[5],uSerialNo[6],uSerialNo[7],uSerialLen,tSpan.MSecond);
		CCardThread::Beep2(BeepTime);
	}
	else
	{
		sText.Format("读身份证物理ID号失败,操作时间 %d ms",tSpan.MSecond);
	}
	InsertDebugMes(sText);
}

void CHFSDlg::OnBnClickedButton4()
{
	CString sMsg;
	CCalcTime tSpan;
	GetDlgItem(IDC_EDIT1)->GetWindowText(sMsg);
	m_iLoopSum = atoi(sMsg);
	sMsg = "连续读写卡次数已经更改，次数为：" + sMsg;
	InsertDebugMes(sMsg);
	AfxMessageBox(sMsg);
}

void CHFSDlg::OnBnClickedButton5()
{
	GetDlgItem(IDC_BEEP)->EnableWindow(false);
	GetDlgItem(IDC_LEDON)->EnableWindow(false);
	GetDlgItem(IDC_LEDOFF)->EnableWindow(false);
	GetDlgItem(IDC_LOADKEYA)->EnableWindow(false);
	GetDlgItem(IDC_LOADKEYB)->EnableWindow(false);
	GetDlgItem(IDC_HALT)->EnableWindow(false);
	GetDlgItem(IDC_RESET)->EnableWindow(false);
	GetDlgItem(IDC_AUTHA)->EnableWindow(false);
	GetDlgItem(IDC_AUTHB)->EnableWindow(false);
	GetDlgItem(IDC_FINDIC)->EnableWindow(false);
	GetDlgItem(IDC_FINDEM)->EnableWindow(false);
	GetDlgItem(IDC_WRITEIC)->EnableWindow(false);
	GetDlgItem(IDC_READIC)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(false);
	KillTimer(m_nTime);
	m_iM1ReadStart = 1;
	m_iM1ReadSum = 0;
	m_iM1ReadOKSum = 0;
	m_nTime =	SetTimer(2,1000,0);
}

void CHFSDlg::OnBnClickedButton6()
{
	CString sMsg;
	m_iM1ReadStart = 0;
	KillTimer(m_nTime);
	GetDlgItem(IDC_BEEP)->EnableWindow(true);
	GetDlgItem(IDC_LEDON)->EnableWindow(true);
	GetDlgItem(IDC_LEDOFF)->EnableWindow(true);
	GetDlgItem(IDC_LOADKEYA)->EnableWindow(true);
	GetDlgItem(IDC_LOADKEYB)->EnableWindow(true);
	GetDlgItem(IDC_HALT)->EnableWindow(true);
	GetDlgItem(IDC_RESET)->EnableWindow(true);
	GetDlgItem(IDC_AUTHA)->EnableWindow(true);
	GetDlgItem(IDC_AUTHB)->EnableWindow(true);
	GetDlgItem(IDC_FINDIC)->EnableWindow(true);
	GetDlgItem(IDC_FINDEM)->EnableWindow(true);
	GetDlgItem(IDC_WRITEIC)->EnableWindow(true);
	GetDlgItem(IDC_READIC)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(true);
	sMsg.Format("读M1卡所有块 总计 %d 次,成功 %d 次",m_iM1ReadSum,m_iM1ReadOKSum);
	InsertDebugMes(sMsg);
	AfxMessageBox(sMsg);
}

void CHFSDlg::OnBnClickedButton7()
{
	GetDlgItem(IDC_BEEP)->EnableWindow(false);
	GetDlgItem(IDC_LEDON)->EnableWindow(false);
	GetDlgItem(IDC_LEDOFF)->EnableWindow(false);
	GetDlgItem(IDC_LOADKEYA)->EnableWindow(false);
	GetDlgItem(IDC_LOADKEYB)->EnableWindow(false);
	GetDlgItem(IDC_HALT)->EnableWindow(false);
	GetDlgItem(IDC_RESET)->EnableWindow(false);
	GetDlgItem(IDC_AUTHA)->EnableWindow(false);
	GetDlgItem(IDC_AUTHB)->EnableWindow(false);
	GetDlgItem(IDC_FINDIC)->EnableWindow(false);
	GetDlgItem(IDC_FINDEM)->EnableWindow(false);
	GetDlgItem(IDC_WRITEIC)->EnableWindow(false);
	GetDlgItem(IDC_READIC)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(false);
	KillTimer(m_nTime);
	m_iM1WriteStart = 1;
	m_iM1WriteSum = 0;
	m_iM1WriteOKSum = 0;
	m_nTime =	SetTimer(3,1000,0);
}

void CHFSDlg::OnBnClickedButton8()
{
	CString sMsg;
	m_iM1WriteStart = 0;
	KillTimer(m_nTime);
	GetDlgItem(IDC_BEEP)->EnableWindow(true);
	GetDlgItem(IDC_LEDON)->EnableWindow(true);
	GetDlgItem(IDC_LEDOFF)->EnableWindow(true);
	GetDlgItem(IDC_LOADKEYA)->EnableWindow(true);
	GetDlgItem(IDC_LOADKEYB)->EnableWindow(true);
	GetDlgItem(IDC_HALT)->EnableWindow(true);
	GetDlgItem(IDC_RESET)->EnableWindow(true);
	GetDlgItem(IDC_AUTHA)->EnableWindow(true);
	GetDlgItem(IDC_AUTHB)->EnableWindow(true);
	GetDlgItem(IDC_FINDIC)->EnableWindow(true);
	GetDlgItem(IDC_FINDEM)->EnableWindow(true);
	GetDlgItem(IDC_WRITEIC)->EnableWindow(true);
	GetDlgItem(IDC_READIC)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(true);
	sMsg.Format("写M1卡所有块 总计 %d 次,成功 %d 次",m_iM1WriteSum,m_iM1WriteOKSum);
	InsertDebugMes(sMsg);
	AfxMessageBox(sMsg);
}

void CHFSDlg::OnBnClickedWriteic2()
{
	GetDlgItem(IDC_BEEP)->EnableWindow(false);
	GetDlgItem(IDC_LEDON)->EnableWindow(false);
	GetDlgItem(IDC_LEDOFF)->EnableWindow(false);
	GetDlgItem(IDC_LOADKEYA)->EnableWindow(false);
	GetDlgItem(IDC_LOADKEYB)->EnableWindow(false);
	GetDlgItem(IDC_HALT)->EnableWindow(false);
	GetDlgItem(IDC_RESET)->EnableWindow(false);
	GetDlgItem(IDC_AUTHA)->EnableWindow(false);
	GetDlgItem(IDC_AUTHB)->EnableWindow(false);
	GetDlgItem(IDC_FINDIC)->EnableWindow(false);
	GetDlgItem(IDC_FINDEM)->EnableWindow(false);
	GetDlgItem(IDC_WRITEIC)->EnableWindow(false);
	GetDlgItem(IDC_READIC)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(false);
	m_iReadStart = 1;
	m_iReadSum = 0;
	m_iReadOKSum = 0;
	m_iM1ReadStart = 1;
	m_iM1ReadSum = 0;
	m_iM1ReadOKSum = 0;
	KillTimer(m_nTime);
	m_nTime =	SetTimer(1,CCardThread::m_ReadTime,0);
}

void CHFSDlg::OnBnClickedWriteic4()
{
	CString sMsg;
	KillTimer(m_nTime);
	GetDlgItem(IDC_BEEP)->EnableWindow(true);
	GetDlgItem(IDC_LEDON)->EnableWindow(true);
	GetDlgItem(IDC_LEDOFF)->EnableWindow(true);
	GetDlgItem(IDC_LOADKEYA)->EnableWindow(true);
	GetDlgItem(IDC_LOADKEYB)->EnableWindow(true);
	GetDlgItem(IDC_HALT)->EnableWindow(true);
	GetDlgItem(IDC_RESET)->EnableWindow(true);
	GetDlgItem(IDC_AUTHA)->EnableWindow(true);
	GetDlgItem(IDC_AUTHB)->EnableWindow(true);
	GetDlgItem(IDC_FINDIC)->EnableWindow(true);
	GetDlgItem(IDC_FINDEM)->EnableWindow(true);
	GetDlgItem(IDC_WRITEIC)->EnableWindow(true);
	GetDlgItem(IDC_READIC)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(true);
	m_iReadStart = 0;
	sMsg.Format("读二代证总计 %d 次,成功 %d 次,读M1卡总计 %d 次,成功 %d 次",m_iReadSum,m_iReadOKSum,m_iM1ReadSum,m_iM1ReadOKSum);
	InsertDebugMes(sMsg);
	AfxMessageBox(sMsg);
}

void CHFSDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		Sleep(600);
		if (CCardThread::m_HaveEM == 1)
		{
			OnBnClickedFindem();
			Sleep(100);
		}
		if (CCardThread::m_HaveMefire == 1)
		{
			OnBnClickedFindic();
			Sleep(100);
		}
		ReadSecondCard();
	}
	if (nIDEvent == 2)
	{
		OnBnClickedButton2();
	}
	if (nIDEvent == 3)
	{
		OnBnClickedButton3();
	}
	switch (nIDEvent){
		case 1:
			if (m_iReadSum == m_iLoopSum)
			{
				OnBnClickedWriteic4();
			}
			break;
		case 2:
			if (m_iM1ReadSum == m_iLoopSum)
			{
				OnBnClickedButton6();
			}
			break;
		case 3:
			if (m_iM1WriteSum == m_iLoopSum)
			{
				OnBnClickedButton8();
			}
			break;
		default :
			break;
	}
	CDialog::OnTimer(nIDEvent);
}
