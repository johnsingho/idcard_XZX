#pragma once
#include "afxwin.h"


// CHFSDlg 对话框

class CHFSDlg : public CDialog
{
	DECLARE_DYNAMIC(CHFSDlg)

public:
	CHFSDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHFSDlg();

// 对话框数据
	enum { IDD = IDD_HFS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	void InitData();
	void ReadSecondCard();
	int m_nTime;

	CListBox m_MsgList;
	CFile m_fLog;
	void InsertDebugMes(CString sMsg);
	void DeleteAllMsg();
	BOOL OpenLogFile();

	int m_iLoopSum;

	int m_iReadSum;
	int m_iReadOKSum;
	int m_iReadStart;

	int m_iM1ReadSum;
	int m_iM1ReadOKSum;
	int m_iM1ReadStart;

	int m_iM1WriteSum;
	int m_iM1WriteOKSum;
	int m_iM1WriteStart;
	afx_msg void OnBnClickedButtonopen();
	afx_msg void OnBnClickedButtonclose();
	afx_msg void OnBnClickedBeep();
	afx_msg void OnBnClickedLedon();
	afx_msg void OnBnClickedLedoff();
	afx_msg void OnBnClickedLoadkeya();
	afx_msg void OnBnClickedLoadkeyb();
	afx_msg void OnBnClickedHalt();
	afx_msg void OnBnClickedReset();
	afx_msg void OnBnClickedAutha();
	afx_msg void OnBnClickedAuthb();
	afx_msg void OnBnClickedFindic();
	afx_msg void OnBnClickedFindem();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedReadic();
	afx_msg void OnBnClickedWriteic();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedWriteic2();
	afx_msg void OnBnClickedWriteic4();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
