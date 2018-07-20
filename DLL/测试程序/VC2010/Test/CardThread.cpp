#include "StdAfx.h"
#include ".\cardthread.h"
int CCardThread::m_ComPort = 1;
int CCardThread::m_ComBaud = 115200;
int CCardThread::m_BeepTime = 10;
int CCardThread::m_ReadTime = 1000;
int CCardThread::m_HaveEM = 1;
int CCardThread::m_HaveMefire = 1;
HINSTANCE	CCardThread::m_hNetICon = NULL;	
XZX_INIT	CCardThread::Dev_Init = NULL;
XZX_CLOSE	CCardThread::Dev_Close = NULL;
XZX_BEEP2		CCardThread::Beep2 = NULL;
XZX_LED			CCardThread::Led = NULL;
XZX_LOOKUPCARD	CCardThread::LookupCard = NULL;
XZX_LOADKEY		CCardThread::LoadKey = NULL;
XZX_AUTHENTICATE	CCardThread::Authenticate = NULL;
XZX_READMEFIRE	CCardThread::ReadMefire = NULL;
XZX_WRITEMEFIRE	CCardThread::WriteMefire = NULL;
XZX_GT_HALT		CCardThread::GT_Halt = NULL;
XZX_GT_RESET	CCardThread::GT_Reset = NULL;

CCardThread::CCardThread(void)
{
}

CCardThread::~CCardThread(void)
{
}
int CCardThread::InitDll()
{
	try
	{
		m_hNetICon = ::LoadLibrary("ThirdInOne.dll"); 

		Dev_Init	= (XZX_INIT)	::GetProcAddress(m_hNetICon, "XZX_Init");
		Dev_Close	= (XZX_CLOSE)	::GetProcAddress(m_hNetICon, "XZX_Close");
		Beep2 = (XZX_BEEP2)	::GetProcAddress(m_hNetICon, "XZX_Beep2");
		Led	= (XZX_LED)		::GetProcAddress(m_hNetICon, "XZX_Led");
		LoadKey	= (XZX_LOADKEY)  ::GetProcAddress(m_hNetICon, "XZX_LoadKey");
		LookupCard	= (XZX_LOOKUPCARD)  ::GetProcAddress(m_hNetICon, "XZX_LookupCard");
		Authenticate	= (XZX_AUTHENTICATE)	::GetProcAddress(m_hNetICon, "XZX_Authenticate");
		ReadMefire	= (XZX_READMEFIRE)	::GetProcAddress(m_hNetICon, "XZX_ReadMefire");
		WriteMefire	= (XZX_WRITEMEFIRE)	::GetProcAddress(m_hNetICon, "XZX_WriteMefire");
		GT_Halt	= (XZX_GT_HALT)	::GetProcAddress(m_hNetICon, "XZX_GT_Halt");
		GT_Reset	= (XZX_GT_RESET)	::GetProcAddress(m_hNetICon, "XZX_GT_Reset");

		if(Dev_Init == NULL || Dev_Close == NULL || Beep == NULL || Led == NULL || LoadKey == NULL || Authenticate == NULL
			|| ReadMefire== NULL || WriteMefire == NULL || GT_Halt ==NULL || GT_Reset == NULL || LookupCard == NULL)
		{
			return -1;
		}
	}catch (...) {ASSERT(FALSE); Sleep(0); return 2;}
	return 0;
}
int CCardThread::FreeDLL()
{
	try
	{
		if( m_hNetICon != NULL ) ::FreeLibrary(m_hNetICon);
		Dev_Init			= NULL;
		Dev_Close			= NULL;	
		Beep2	= NULL;
		Led		= NULL;
		LookupCard = NULL;
		LoadKey	= NULL;
		Authenticate	= NULL;
		ReadMefire	= NULL;
		WriteMefire	= NULL;
		GT_Halt		= NULL;
		GT_Reset	= NULL;
	}catch (...) {ASSERT(FALSE); Sleep(0); return -1;}	
	return 0;
}
int CCardThread::LoadConfig()
{
	m_ComPort	= GetPrivateProfileInt("Config","ComPort",1,".\\ConfigCard.ini");
	m_ComBaud	= GetPrivateProfileInt("Config","ComBaud",115200,".\\ConfigCard.ini");
	m_BeepTime	= GetPrivateProfileInt("Config","BeepTime",3,".\\ConfigCard.ini");
	m_ReadTime	= GetPrivateProfileInt("Config","ReadTime",1200,".\\ConfigCard.ini");
	m_HaveEM	= GetPrivateProfileInt("Config","HaveEM",1,".\\ConfigCard.ini");
	m_HaveMefire	= GetPrivateProfileInt("Config","HaveMefire",1,".\\ConfigCard.ini");
	return 0;
}