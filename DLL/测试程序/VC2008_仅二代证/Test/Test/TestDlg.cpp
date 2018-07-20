
// TestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Test.h"
#include "TestDlg.h"
#include "SynPublic.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestDlg �Ի���




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


// CTestDlg ��Ϣ�������

BOOL CTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��

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
								// 0=���� ��ת��,	1=����ת��Ϊ ��Ч�ڿ�ʼ+50��
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
				sMsg= "��ȡ���֤��Ϣ�ɹ�!";
				InsertDebugMes(sMsg);
				sMsg.Format("����:%s",idcardData.Name);
				InsertDebugMes(sMsg);
				sMsg.Format("�Ա�:%s",idcardData.Sex);
				InsertDebugMes(sMsg);
				sMsg.Format("����:%s",idcardData.Nation);
				InsertDebugMes(sMsg);
				sMsg.Format("����:%s",idcardData.Born);
				InsertDebugMes(sMsg);
				sMsg.Format("סַ:%s",idcardData.Address);
				InsertDebugMes(sMsg);
				sMsg.Format("���֤��:%s",idcardData.IDCardNo);
				InsertDebugMes(sMsg);
				sMsg.Format("��֤����:%s",idcardData.GrantDept);
				InsertDebugMes(sMsg);
				sMsg.Format("��Ч�ڿ�ʼ:%s",idcardData.UserLifeBegin);
				InsertDebugMes(sMsg);
				sMsg.Format("��Ч�ڽ���:%s",idcardData.UserLifeEnd);
				InsertDebugMes(sMsg);
				if (nRet == 1)
				{
					sMsg = "������Ƭʧ��";
				}
				else
				{
					sMsg.Format("��Ƭ:%s",idcardData.PhotoFileName);
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
				sMsg = "��ȡ���֤��Ϣ����!";
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
		sMsg = "�򿪶˿ڴ���";
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
		sMsg = "û���ҵ�������";
	}
	else
	{
		m_iPort = nRet;
		Beep(4000,200);
		if (nRet >1000)
		{
			sMsg.Format("������������USB�˿� %d",nRet); 
		}
		else
		{
			Sleep(200);
			nRet2 = Syn_GetCOMBaud( nRet ,&uiCurrBaud);
			sMsg2.Format("%u",uiCurrBaud);
			sMsg.Format("�����������ڴ��� %d,��ǰSAM������Ϊ %u",nRet,uiCurrBaud); 
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
	// 0=���� ��ת��,	1=����ת��Ϊ ��Ч�ڿ�ʼ+50��
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
				sMsg= "��ȡ���֤��Ϣ�ɹ�!";
				InsertDebugMes(sMsg);
				sMsg.Format("����:%s",idcardData.Name);
				InsertDebugMes(sMsg);
				sMsg.Format("�Ա�:%s",idcardData.Sex);
				InsertDebugMes(sMsg);
				sMsg.Format("����:%s",idcardData.Nation);
				InsertDebugMes(sMsg);
				sMsg.Format("����:%s",idcardData.Born);
				InsertDebugMes(sMsg);
				sMsg.Format("סַ:%s",idcardData.Address);
				InsertDebugMes(sMsg);
				sMsg.Format("���֤��:%s",idcardData.IDCardNo);
				InsertDebugMes(sMsg);
				sMsg.Format("��֤����:%s",idcardData.GrantDept);
				InsertDebugMes(sMsg);
				sMsg.Format("��Ч�ڿ�ʼ:%s",idcardData.UserLifeBegin);
				InsertDebugMes(sMsg);
				sMsg.Format("��Ч�ڽ���:%s",idcardData.UserLifeEnd);
				InsertDebugMes(sMsg);
				if (nRet == 1)
				{
					sMsg = "������Ƭʧ��";
				}
				else
				{
					sMsg.Format("��Ƭ:%s",idcardData.PhotoFileName);
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
					sMsg.Format("ָ���ļ�:%s",szPath);
					InsertDebugMes(sMsg);
				}
				else
				{
					sMsg = "û��ָ����Ϣ";
					InsertDebugMes(sMsg);
				}
			}	
			else
			{
				sMsg = "��ȡ���֤��Ϣ����!";
				InsertDebugMes(sMsg);
			}
		}
	}
	else
	{
		sMsg = "�򿪶˿ڴ���";
		InsertDebugMes(sMsg);
	}
	Syn_ClosePort( m_iPort );
}
