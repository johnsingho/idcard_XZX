
// TestDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


class CCalcTime
{
public:	
	LARGE_INTEGER t1;
	LARGE_INTEGER t2;
	__int64 CountTick ;
	__int64 Count ;
	__int64 PerSec;
	__int64 ThisTick;
	int ThisMSecond;


	int MSecond;
	int ms[10000];
	int Index ;



	CCalcTime()
	{ 
		Clear();
	} 
	~CCalcTime(){};

	void BegginTime(){ QueryPerformanceCounter( &t1 ); };
	void EndTime() { 
		QueryPerformanceCounter( &t2 ) ;
		ThisTick   = (t2.QuadPart-t1.QuadPart);
		CountTick += ThisTick;
		Count++;
		ThisMSecond = (int)( ThisTick*1000 / PerSec);
		MSecond = (int) (((double)CountTick )/ PerSec * 1000 );
		ms[Index++] =    (int)((double)(t2.QuadPart-t1.QuadPart) / PerSec * 1000 );
		if( Index == 10000 ) Index = 0;
	};
	void Clear()
	{
		Count = 0 ;
		CountTick = 0 ; 
		QueryPerformanceFrequency ( &t1 );
		PerSec = t1.QuadPart;
		MSecond =0;
		Index = 0;
		memset( ms , 0 , sizeof(ms) );
		ThisMSecond = 0;
		ThisTick = 0;
	};

};

// CTestDlg 对话框
class CTestDlg : public CDialog
{
// 构造
public:
	CTestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_ListMsg;
	int m_iPort;
	unsigned int m_CurrBaud; 
	int IsEncryptMode;

	unsigned char m_iMaxByte;
	int m_iReadType;
	int m_iLogType;
	int m_iReadSum;
	int m_iReadOKSum;
	int m_iReadStart;

	int m_iM1ReadSum;
	int m_iM1ReadOKSum;
	int m_iM1ReadStart;

	int m_iM1WriteSum;
	int m_iM1WriteOKSum;
	int m_iM1WriteStart;
	
	int m_iLoopSum;
	int m_iTime;
	CFile m_fLog;
	void InsertDebugMes(CString sMsg);
	//int progressCallback(int progress);
	BOOL OpenLogFile();
	void SetUserCode();
	afx_msg void OnBnClickedButfindreader();
	afx_msg void OnBnClickedButclearmes();
	afx_msg void OnBnClickedButgetsamstate();
	afx_msg void OnBnClickedButsetmax();
	afx_msg void OnBnClickedButrestsam();
	afx_msg void OnBnClickedButgetsamid();
	CListCtrl m_ListView;
	afx_msg void OnBnClickedButfindcard();
	afx_msg void OnBnClickedButselectcard();
	afx_msg void OnBnClickedButreadcard();
	afx_msg void OnBnClickedButreadcard2();
	afx_msg void OnBnClickedButstartread();
	afx_msg void OnBnClickedButreadcardex();
	afx_msg void OnBnClickedButreadcardex2();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButstopread();
	afx_msg void OnBnClickedButfpExt();
	afx_msg void OnBnClickedButsound();
	afx_msg void OnBnClickedButfindfp();
	afx_msg void OnBnClickedButgetver();
	afx_msg void OnBnClickedButgetdesc();
	afx_msg void OnBnClickedButclosefp();
	afx_msg void OnBnClickedButbegincap();
	afx_msg void OnBnClickedButgetfpraw();
	afx_msg void OnBnClickedButreaderuserinfo();
	afx_msg void OnBnClickedButwriteuserinfo();
	afx_msg void OnBnClickedButreadfac();
	afx_msg void OnBnClickedButwritefac();
	afx_msg void OnBnClickedButendcap();
	afx_msg void OnBnClickedButgetfpbmp();
	afx_msg void ViewBmp(CString bmpFile);
	int RawToBmp(unsigned char *ucRaw,CString bmpFile);
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedM1reset();
	afx_msg void OnBnClickedM1halt();
	afx_msg void OnBnClickedButtonAuthena();
	afx_msg void OnBnClickedButtonAuthenb();
	afx_msg void OnBnClickedButtonRead();
	afx_msg void OnBnClickedButtonWrite();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton17();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton18();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButtonChanga();
	afx_msg void OnBnClickedButtonChangb();
	afx_msg void OnBnClickedButton19();
	afx_msg void OnBnClickedButton20();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButfpBri();
	afx_msg void OnBnClickedButfpCon();
	afx_msg void OnClose();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton21();
	afx_msg void OnBnClickedButton23();
	afx_msg void OnBnClickedButton22();
	afx_msg void OnBnClickedButton24();
	afx_msg void OnBnClickedButton8();

	afx_msg void OnBnClickedButton25();
	afx_msg void OnBnClickedButton26();
	afx_msg void OnBnClickedButton27();
	afx_msg void OnBnClickedButsimon();
	afx_msg void OnBnClickedButsimoff();
	afx_msg void OnBnClickedButsimapdu();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedButton28();
	afx_msg void OnBnClickedButton29();
	afx_msg void OnBnClickedButfpGetqua();
};
