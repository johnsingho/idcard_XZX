unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls,FileCtrl, ExtCtrls;
type
  Pint=^integer; //定义指针类型
  pbyte=^byte;
  Puint=^DWORD;
  TIDCardData=record
    name:array[0..31] of char;
    sex:array[0..5] of char;
    nation:array[0..19] of char;
    born:array[0..17] of char;
    address:array[0..71] of char;
    IDcardno:array[0..37] of char;
    grantdept:array[0..31] of char;
    UserLifeBegin:array[0..17] of char;
    UserLifeEnd:array[0..17] of char;
    reserved:array[0..37] of char;
    PhotoFileName:array[0..254] of char;
  end;


type
  TForm1 = class(TForm)
    ListBox1: TListBox;
    Button17: TButton;
    Button18: TButton;
    Button19: TButton;
    Button1: TButton;
    Button2: TButton;
    lbl1: TLabel;
    img1: TImage;
    procedure Button1Click(Sender: TObject);
    procedure Button19Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure Button17Click(Sender: TObject);
    procedure Button18Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
  private
    { Private declarations }
    PROCEDURE LOADDLL();
  public
    { Public declarations }
  end;

var
  Form1: TForm1;
  m_iPort: Integer;
implementation

{$R *.dfm}
VAR
  Moudlegm:longint;
Syn_SetMaxRFByte:function (iPort:integer;ucByte:Byte;bIfOpen:integer):integer;stdcall;
Syn_GetCOMBaud:function (iPort:integer;puiBaudRate:Puint):integer;stdcall;
Syn_SetCOMBaud:function (iPort:integer;uiCurrBaud:DWORD;uiSetBaud:DWORD):integer;stdcall;
Syn_OpenPort: function (iPort:integer):integer;stdcall;
Syn_ClosePort: function (iPort:integer):integer;stdcall;

Syn_ResetSAM:function (iPort:integer;iIfOpen:integer):integer;stdcall;
Syn_GetSAMStatus:function (iPort:integer;iIfOpen:integer):integer;stdcall;
Syn_GetSAMID:function (iPort:integer;pucSAMID:pbyte;iIfOpen:integer):integer;stdcall;
Syn_GetSAMIDToStr:function (iPort:integer;pcSAMID:PCHAR;iIfOpen:integer):integer;stdcall;

Syn_StartFindIDCard: function (iPort:integer;pucManaInfo:PCHAR;iIfOpen:integer):integer;stdcall;
Syn_SelectIDCard: function (iPort:integer;pucManaMsg:pbyte;iIfOpen:integer):integer;stdcall;
Syn_ReadBaseMsg: function (iPort:integer;pucCHMsg:pbyte;puiCHMsgLen:Puint;pucPHMsg:pbyte;puiPHMsgLen:Puint;pucFPMsg:pbyte;puiFPMsgLen:Puint;iIfOpen:integer):integer;stdcall;
Syn_ReadBaseMsgToFile: function (iPort:integer;pcCHMsgFileName:PCHAR;puiCHMsgFileLen:Puint;pcPHMsgFileName:PCHAR;puiPHMsgFileLen:Puint;pcFPMsgFileName:PCHAR;puiFPMsgFileLen:Puint;iIfOpen:integer):integer;stdcall;
Syn_ReadBaseFPMsg: function (iPort:integer;pucCHMsg:pbyte;puiCHMsgLen:Puint;pucPHMsg:pbyte;puiPHMsgLen:Puint;iIfOpen:integer):integer;stdcall;
Syn_ReadBaseFPMsgToFile: function (iPort:integer;pcCHMsgFileName:PCHAR;puiCHMsgFileLen:Puint;pcPHMsgFileName:PCHAR;puiPHMsgFileLen:Puint;iIfOpen:integer):integer;stdcall;
Syn_ReadNewAppMsg: function (iPort:integer;pucAppMsg:pbyte;puiAppMsgLen:Puint;iIfOpen:integer):integer;stdcall;
Syn_GetBmp: function (iPort:integer;Wlt_File:PCHAR):integer;stdcall;
Syn_ReadMsg: function (iPort:integer;iIfOpen:integer;var pIDCardData:TIDCardData):integer;stdcall;
Syn_ReadFPMsg: function (iPort:integer;iIfOpen:integer;var pIDCardData:TIDCardData;pName:pbyte):integer;stdcall;
Syn_FindReader:function ():integer;stdcall;
Syn_FindUSBReader:function ():integer;stdcall;

Syn_SetPhotoPath: function (iOption:integer;cPhotoPath:PCHAR):integer;stdcall;
Syn_SetPhotoType: function (iType:integer):integer;stdcall;
Syn_SetPhotoName: function (iType:integer):integer;stdcall;
Syn_SetSexType: function (iType:integer):integer;stdcall;
Syn_SetNationType: function (iType:integer):integer;stdcall;
Syn_SetBornType: function (iType:integer):integer;stdcall;
Syn_SetUserLifeBType: function (iType:integer):integer;stdcall;
Syn_SetUserLifeEType: function (iType:integer;iOption:integer):integer;stdcall;
procedure TForm1.LOADDLL();
begin
    Moudlegm := Loadlibrary('SynIDCardAPI.dll');
    if (Moudlegm>32) then
      begin
        @Syn_SetMaxRFByte:=GetProcAddress(Moudlegm,'Syn_SetMaxRFByte');
        @Syn_GetCOMBaud:=GetProcAddress(Moudlegm,'Syn_GetCOMBaud');
        @Syn_SetCOMBaud:=GetProcAddress(Moudlegm,'Syn_SetCOMBaud');
        @Syn_OpenPort:=GetProcAddress(Moudlegm,'Syn_OpenPort');
        @Syn_ClosePort:=GetProcAddress(Moudlegm,'Syn_ClosePort');

        @Syn_ResetSAM:=GetProcAddress(Moudlegm,'Syn_ResetSAM');
        @Syn_GetSAMStatus:=GetProcAddress(Moudlegm,'Syn_GetSAMStatus');
        @Syn_GetSAMID:=GetProcAddress(Moudlegm,'Syn_GetSAMID');
        @Syn_GetSAMIDToStr:=GetProcAddress(Moudlegm,'Syn_GetSAMIDToStr');

        @Syn_StartFindIDCard:=GetProcAddress(Moudlegm,'Syn_StartFindIDCard');
        @Syn_SelectIDCard:=GetProcAddress(Moudlegm,'Syn_SelectIDCard');
        @Syn_ReadBaseMsg:=GetProcAddress(Moudlegm,'Syn_ReadBaseMsg');
        @Syn_ReadBaseMsgToFile:=GetProcAddress(Moudlegm,'Syn_ReadBaseMsgToFile');
        @Syn_ReadBaseFPMsg:=GetProcAddress(Moudlegm,'Syn_ReadBaseFPMsg');
        @Syn_ReadBaseFPMsgToFile:=GetProcAddress(Moudlegm,'Syn_ReadBaseFPMsgToFile');

        @Syn_ReadNewAppMsg:=GetProcAddress(Moudlegm,'Syn_ReadNewAppMsg');
        @Syn_GetBmp:=GetProcAddress(Moudlegm,'Syn_GetBmp');
        @Syn_ReadMsg:=GetProcAddress(Moudlegm,'Syn_ReadMsg');
        @Syn_ReadFPMsg:=GetProcAddress(Moudlegm,'Syn_ReadFPMsg');
        @Syn_FindReader:=GetProcAddress(Moudlegm,'Syn_FindReader');

        @Syn_SetPhotoPath:=GetProcAddress(Moudlegm,'Syn_SetPhotoPath');
        @Syn_SetPhotoType:=GetProcAddress(Moudlegm,'Syn_SetPhotoType');
        @Syn_SetPhotoName:=GetProcAddress(Moudlegm,'Syn_SetPhotoName');
        @Syn_SetSexType:=GetProcAddress(Moudlegm,'Syn_SetSexType');
        @Syn_SetNationType:=GetProcAddress(Moudlegm,'Syn_SetNationType');
        @Syn_SetBornType:=GetProcAddress(Moudlegm,'Syn_SetBornType');
        @Syn_SetUserLifeBType:=GetProcAddress(Moudlegm,'Syn_SetUserLifeBType');
        @Syn_SetUserLifeEType:=GetProcAddress(Moudlegm,'Syn_SetUserLifeEType');
      end
end;


procedure TForm1.Button1Click(Sender: TObject);
  var
  nPort:integer;
  nCurBaud:DWORD;
begin
  nPort := Syn_FindReader();
  m_iPort:= nPort;
  if nPort = 0 then begin
    ListBox1.Items.Add( DateTimeToStr(now())+ '  没有找到读卡器' );
  end else begin
    Windows.Beep(4000,200);
    if nPort>1000 then begin
      ListBox1.Items.Add( DateTimeToStr(Now())+'  读卡器连接在USB ' + IntToStr(nPort) + ' 上');
    end else begin
      Syn_GetCOMBaud(nPort,@nCurBaud);
      ListBox1.Items.Add( DateTimeToStr(Now())+'  读卡器连接在COM ' + IntToStr(nPort) + ' 上');
     end;
  end;
end;

procedure TForm1.Button19Click(Sender: TObject);
begin
  Application.Terminate();
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
  LOADDLL();
end;

procedure TForm1.Button17Click(Sender: TObject);
var
  nRet:Integer;
  nPort:Integer;
  nPhotoType:Integer;
  pucIIN:array[0..3] of byte;
  pucSN:array[0..7] of byte;
  CardMsg:TIDCardData;
begin
  nPort:=m_iPort;
  nPhotoType :=0;
  img1.Picture :=nil;
  nRet := Syn_OpenPort(nPort);
  if nRet = 0 then begin
	  Syn_SetMaxRFByte( nPort ,80 , 0);
	  Syn_StartFindIDCard( nPort , @pucIIN , 0 );
	  Syn_SelectIDCard( nPort , @pucSN , 0 );
    if Syn_ReadMsg( nPort , 0 , CardMsg)=0 then begin
    ListBox1.Items.Add(DateTimeToStr(Now())+'  读取身份证信息成功');
    ListBox1.Items.Add(DateTimeToStr(Now())+'  姓名：'+trim(CardMsg.Name));
    ListBox1.Items.Add(DateTimeToStr(Now())+'  性别：'+trim(CardMsg.sex));
    ListBox1.Items.Add(DateTimeToStr(Now())+'  民族：'+trim(CardMsg.Nation));
    ListBox1.Items.Add(DateTimeToStr(Now())+'  出生日期：'+trim(CardMsg.Born));
    ListBox1.Items.Add(DateTimeToStr(Now())+'  地址：'+trim(CardMsg.address));
    ListBox1.Items.Add(DateTimeToStr(Now())+'  身份证号：'+trim(CardMsg.Idcardno));
    ListBox1.Items.Add(DateTimeToStr(Now())+'  有效期开始：'+trim(CardMsg.UserLifeBegin));
    ListBox1.Items.Add(DateTimeToStr(Now())+'  有效期结束：'+trim(CardMsg.UserLifeEnd));
    ListBox1.Items.Add(DateTimeToStr(Now())+'  发证机关：'+trim(CardMsg.grantdept));
    ListBox1.Items.Add(DateTimeToStr(Now())+'  照片文件名：'+trim(CardMsg.photofilename));
    if nPhotoType = 0 then begin
      img1.Picture.LoadFromFile(CardMsg.photofilename);
    end;
    end else begin
    ListBox1.Items.Add(DateTimeToStr(Now())+'  读取身份证信息错误');
    end;
  end else begin
    ListBox1.Items.Add(DateTimeToStr(Now())+'  打开端口失败');
  end;
  Syn_ClosePort(nPort);
end;

procedure TForm1.Button18Click(Sender: TObject);
begin
  ListBox1.Clear();
  img1.Picture :=nil;
end;

procedure TForm1.Button2Click(Sender: TObject);
var
  nRet:Integer;
  nPort:Integer;
  nPhotoType:Integer;
  pucIIN:array[0..3] of byte;
  pucSN:array[0..7] of byte;
  pcName:array[0..255] of char;
  CardMsg:TIDCardData;
begin
  nPort:=m_iPort;
  nPhotoType :=0;
  img1.Picture :=nil;
  nRet := Syn_OpenPort(nPort);
  if nRet = 0 then begin
	  Syn_SetMaxRFByte( nPort ,80 , 0);
	  Syn_StartFindIDCard( nPort , @pucIIN , 0 );
	  Syn_SelectIDCard( nPort , @pucSN , 0 );
    if Syn_ReadFPMsg( nPort , 0 , CardMsg,@pcName)=0 then begin
    ListBox1.Items.Add(DateTimeToStr(Now())+'  读取身份证信息成功');
    ListBox1.Items.Add(DateTimeToStr(Now())+'  姓名：'+trim(CardMsg.Name));
    ListBox1.Items.Add(DateTimeToStr(Now())+'  性别：'+trim(CardMsg.sex));
    ListBox1.Items.Add(DateTimeToStr(Now())+'  民族：'+trim(CardMsg.Nation));
    ListBox1.Items.Add(DateTimeToStr(Now())+'  出生日期：'+trim(CardMsg.Born));
    ListBox1.Items.Add(DateTimeToStr(Now())+'  地址：'+trim(CardMsg.address));
    ListBox1.Items.Add(DateTimeToStr(Now())+'  身份证号：'+trim(CardMsg.Idcardno));
    ListBox1.Items.Add(DateTimeToStr(Now())+'  有效期开始：'+trim(CardMsg.UserLifeBegin));
    ListBox1.Items.Add(DateTimeToStr(Now())+'  有效期结束：'+trim(CardMsg.UserLifeEnd));
    ListBox1.Items.Add(DateTimeToStr(Now())+'  发证机关：'+trim(CardMsg.grantdept));
    ListBox1.Items.Add(DateTimeToStr(Now())+'  照片文件名：'+trim(CardMsg.photofilename));
    ListBox1.Items.Add(DateTimeToStr(Now())+'  指纹文件名：'+trim(pcName));
    if nPhotoType = 0 then begin
      img1.Picture.LoadFromFile(CardMsg.photofilename);
    end;
    end else begin
    ListBox1.Items.Add(DateTimeToStr(Now())+'  读取身份证信息错误');
    end;
  end else begin
    ListBox1.Items.Add(DateTimeToStr(Now())+'  打开端口失败');
  end;
  Syn_ClosePort(nPort);
end;

end.
