#pragma once
typedef bool (__stdcall *XZX_INIT)(int port,long baud);
typedef bool (__stdcall *XZX_CLOSE)(int port);
typedef void (__stdcall *XZX_BEEP2)(unsigned char ON_100ms);
typedef void (__stdcall *XZX_LED)(bool bOn);
typedef bool (__stdcall *XZX_LOOKUPCARD)(unsigned char nType ,unsigned char * SerialNum,unsigned char *nSerialLen);
typedef bool (__stdcall *XZX_LOADKEY)(unsigned char mode,unsigned char sectionNum,unsigned char *key);
typedef bool (__stdcall *XZX_AUTHENTICATE)(unsigned char mode,unsigned char sectionNum);
typedef int  (__stdcall *XZX_READMEFIRE)(unsigned char Block_Adr,unsigned char * _Data);
typedef bool (__stdcall *XZX_WRITEMEFIRE)(unsigned char Start_Block,unsigned char *data);
typedef bool (__stdcall *XZX_GT_HALT)();
typedef bool (__stdcall *XZX_GT_RESET)();
#pragma pack(1)
typedef struct tagIDCardData2{
	unsigned char Name[30];
	unsigned char Sex[6];
	unsigned char Nation[20];
	unsigned char Born[16];
	unsigned char Address[70];
	unsigned char IDCardNo[36];
	unsigned char GrantDept[30];
	unsigned char UserLife[32];
	unsigned char PhotoFileName[1024];
}tagIDCARDDATA2;
#pragma pack()
class CCardThread
{
public:
	CCardThread(void);
	~CCardThread(void);
public:
	static int m_ComPort;
	static int m_ComBaud;
	static int m_BeepTime;
	static int m_ReadTime;
	static int m_HaveEM;
	static int m_HaveMefire;
	static int InitDll();
	static int FreeDLL();
	static int LoadConfig();
	static HINSTANCE	m_hNetICon;	
	static XZX_INIT	Dev_Init;
	static XZX_CLOSE	Dev_Close;
	static XZX_BEEP2		Beep2;
	static XZX_LED			Led;
	static XZX_LOOKUPCARD	LookupCard;
	static XZX_LOADKEY		LoadKey;
	static XZX_AUTHENTICATE	Authenticate;
	static XZX_READMEFIRE	ReadMefire;
	static XZX_WRITEMEFIRE	WriteMefire;
	static XZX_GT_HALT		GT_Halt;
	static XZX_GT_RESET	GT_Reset;
};
