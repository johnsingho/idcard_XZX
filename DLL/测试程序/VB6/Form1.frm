VERSION 5.00
Begin VB.Form Form1 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Form1"
   ClientHeight    =   5145
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   10290
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5145
   ScaleWidth      =   10290
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command3 
      Caption         =   "读二代征信息部包含指纹"
      Height          =   375
      Left            =   7680
      TabIndex        =   5
      Top             =   3720
      Width           =   2415
   End
   Begin VB.CommandButton Command2 
      Caption         =   "寻找读卡器"
      Height          =   375
      Left            =   7680
      TabIndex        =   4
      Top             =   2760
      Width           =   2415
   End
   Begin VB.CommandButton Command20 
      Caption         =   "清除所有信息"
      Height          =   375
      Left            =   7680
      TabIndex        =   3
      Top             =   4200
      Width           =   2415
   End
   Begin VB.CommandButton Command18 
      Caption         =   "读二代征信息部包含指纹"
      Height          =   375
      Left            =   7680
      TabIndex        =   2
      Top             =   3240
      Width           =   2415
   End
   Begin VB.ListBox List1 
      Height          =   4935
      Left            =   120
      TabIndex        =   1
      Top             =   0
      Width           =   7335
   End
   Begin VB.CommandButton Command1 
      Caption         =   "退    出"
      Height          =   375
      Left            =   7680
      TabIndex        =   0
      Top             =   4680
      Width           =   2415
   End
   Begin VB.Image Image1 
      Appearance      =   0  'Flat
      BorderStyle     =   1  'Fixed Single
      Height          =   1935
      Left            =   8040
      Top             =   480
      Width           =   1575
   End
   Begin VB.Label Label1 
      Caption         =   "照    片"
      Height          =   255
      Left            =   8520
      TabIndex        =   6
      Top             =   120
      Width           =   615
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Declare Function Syn_SetMaxRFByte Lib "SynIDCardAPI.dll" (ByVal iPort As Long, ByVal ucByte As Byte, ByVal bIfOpen As Long) As Long
Private Declare Function Syn_GetCOMBaud Lib "SynIDCardAPI.dll" (ByVal iPort As Long, ByRef puiBaudRate As Long) As Long
Private Declare Function Syn_SetCOMBaud Lib "SynIDCardAPI.dll" (ByVal iPort As Long, ByVal uiCurrBaud As Long, ByVal uiSetBaud As Long) As Long
Private Declare Function Syn_OpenPort Lib "SynIDCardAPI.dll" (ByVal iPort As Long) As Long
Private Declare Function Syn_ClosePort Lib "SynIDCardAPI.dll" (ByVal iPort As Long) As Long

Private Declare Function Syn_ResetSAM Lib "SynIDCardAPI.dll" (ByVal iPort As Long, ByVal iIfOpen As Long) As Long
Private Declare Function Syn_GetSAMStatus Lib "SynIDCardAPI.dll" (ByVal iPort As Long, ByVal iIfOpen As Long) As Long
Private Declare Function Syn_GetSAMID Lib "SynIDCardAPI.dll" (ByVal iPort As Long, ByRef pucSAMID As Byte, ByVal iIfOpen As Long) As Long
Private Declare Function Syn_GetSAMIDToStr Lib "SynIDCardAPI.dll" (ByVal iPort As Long, ByRef pcSAMID As Byte, ByVal iIfOpen As Long) As Long

Private Declare Function Syn_StartFindIDCard Lib "SynIDCardAPI.dll" (ByVal iPort As Long, ByRef pucIIN As Byte, ByVal iIfOpen As Long) As Long
Private Declare Function Syn_SelectIDCard Lib "SynIDCardAPI.dll" (ByVal iPort As Long, ByRef pucSN As Byte, ByVal iIfOpen As Long) As Long
Private Declare Function Syn_ReadBaseMsg Lib "SynIDCardAPI.dll" (ByVal iPort As Long, ByRef pucCHMsg As Byte, ByRef puiCHMsgLen As Long, ByRef pucPHMsg As Byte, ByRef puiPHMsgLen As Long, ByVal iIfOpen As Long) As Long
Private Declare Function Syn_ReadBaseMsgToFile Lib "SynIDCardAPI.dll" (ByVal iPort As Long, ByRef pcCHMsgFileName As Byte, ByRef puiCHMsgFileLen As Long, ByRef pcPHMsgFileName As Byte, ByRef puiPHMsgFileLen As Long, ByVal iIfOpen As Long) As Long
Private Declare Function Syn_ReadBaseFPMsg Lib "SynIDCardAPI.dll" (ByVal iPort As Long, ByRef pucCHMsg As Byte, ByRef puiCHMsgLen As Long, ByRef pucPHMsg As Byte, ByRef puiPHMsgLen As Long, ByRef pucFPMsg As Byte, ByRef puiFPMsgLen As Long, ByVal iIfOpen As Long) As Long
Private Declare Function Syn_ReadBaseFPMsgToFile Lib "SynIDCardAPI.dll" (ByVal iPort As Long, ByRef pcCHMsgFileName As Byte, ByRef puiCHMsgFileLen As Long, ByRef pcPHMsgFileName As Byte, ByRef puiPHMsgFileLen As Long, ByRef pcFPMsgFileName As Byte, ByRef puiFPMsgFileLen As Long, ByVal iIfOpen As Long) As Long
Private Declare Function Syn_ReadNewAppMsg Lib "SynIDCardAPI.dll" (ByVal iPort As Long, ByRef pucAppMsg As Byte, ByRef puiAppMsgLen As Long, ByVal iIfOpen As Long) As Long
Private Declare Function Syn_GetBmp Lib "SynIDCardAPI.dll" (ByVal iPort As Long, ByRef Wlt_File As Byte) As Long
    
Private Declare Function Syn_ReadMsg Lib "SynIDCardAPI.dll" (ByVal iPort As Long, ByVal IfOpen As Long, ByRef pIDCardData As Byte) As Long
Private Declare Function Syn_ReadFPMsg Lib "SynIDCardAPI.dll" (ByVal iPort As Long, ByVal IfOpen As Long, ByRef pIDCardData As Byte, ByRef cPhotoName As Byte) As Long
Private Declare Function Syn_FindReader Lib "SynIDCardAPI.dll" () As Long
Private Declare Function Syn_FindUSBReader Lib "SynIDCardAPI.dll" () As Long
    
Private Declare Function Syn_SetPhotoPath Lib "SynIDCardAPI.dll" (ByVal iOption As Long, ByRef cPhotoPath As Byte) As Long
Private Declare Function Syn_SetPhotoType Lib "SynIDCardAPI.dll" (ByVal iType As Long) As Long
Private Declare Function Syn_SetPhotoName Lib "SynIDCardAPI.dll" (ByVal iType As Long) As Long
Private Declare Function Syn_SetSexType Lib "SynIDCardAPI.dll" (ByVal iType As Long) As Long
Private Declare Function Syn_SetNationType Lib "SynIDCardAPI.dll" (ByVal iType As Long) As Long
Private Declare Function Syn_SetBornType Lib "SynIDCardAPI.dll" (ByVal iType As Long) As Long
Private Declare Function Syn_SetUserLifeBType Lib "SynIDCardAPI.dll" (ByVal iType As Long) As Long
Private Declare Function Syn_SetUserLifeEType Lib "SynIDCardAPI.dll" (ByVal iType As Long, ByVal iOption As Long) As Long

Private Declare Sub Sleep Lib "kernel32" (ByVal dwMilliseconds As Long)
Private Declare Function APIBeep Lib "kernel32" Alias "Beep" (ByVal dwFreq As Long, ByVal dwDuration As Long) As Long
Private Const BIF_RETURNONLYFSDIRS = 1                                        '从这里开始为API声明
Private Const BIF_DONTGOBELOWDOMAIN = 2
Private Const MAX_PATH = 260
Dim m_iPort As Long

Private Declare Function SHBrowseForFolder Lib "Shell32" _
      (lpbi As BrowseInfo) As Long

Private Declare Function SHGetPathFromIDList Lib "Shell32" _
      (ByVal pidList As Long, _
      ByVal lpBuffer As String) As Long

Private Declare Function lstrcat Lib "kernel32" Alias "lstrcatA" _
      (ByVal lpString1 As String, ByVal _
      lpString2 As String) As Long

Private Type BrowseInfo
     hWndOwner As Long
     pIDLRoot As Long
     pszDisplayName As Long
     lpszTitle As Long
     ulFlags    As Long
     lpfnCallback     As Long
     lParam     As Long
     iImage     As Long
End Type

Private Sub Command1_Click()
    Unload Me
End Sub


Private Sub Command18_Click()
    Dim nLen As Long
    Dim nRet As Long
    Dim utmp(1280) As Byte
    Dim uName(32) As Byte
    Dim uSex(6) As Byte
    Dim uNation(20) As Byte
    Dim uBorn(18) As Byte
    Dim uAddress(72) As Byte
    Dim uIDCardNo(38) As Byte
    Dim uGrantDept(32) As Byte
    Dim uUserLife(18) As Byte
    Dim uUserLifeEnd(18) As Byte
    Dim uPhotoFileName(255) As Byte
    Dim i, j, k, l, m, n, o, p, q, r As Integer
    Dim strMsg, tmpstr, tmpstr2, sMsg As String
    Dim pucIIN(4) As Byte
    Dim pucSN(8) As Byte
    iPort = m_iPort
    nRet = Syn_OpenPort(iPort)
    If nRet = 0 Then
        nRet = Syn_SetMaxRFByte(iPort, 80, 0)
        If nRet = 0 Then
            nRet = Syn_StartFindIDCard(iPort, pucIIN(0), 0)
            nRet = Syn_SelectIDCard(iPort, pucSN(0), 0)
            nLen = Syn_ReadMsg(iPort, 0, utmp(0))
            If nLen = 0 Then
                For i = 0 To 32
                    uName(i) = utmp(i)
                Next i
                For j = 0 To 6
                    uSex(j) = utmp(32 + j)
                Next j
                For k = 0 To 20
                    uNation(k) = utmp(38 + k)
                Next k
                For l = 0 To 18
                    uBorn(l) = utmp(58 + l)
                Next l
                For m = 0 To 72
                    uAddress(m) = utmp(76 + m)
                Next m
                For n = 0 To 38
                    uIDCardNo(n) = utmp(148 + n)
                Next n
                For o = 0 To 32
                    uGrantDept(o) = utmp(186 + o)
                Next o
                For p = 0 To 18
                    uUserLife(p) = utmp(218 + p)
                Next p
                For r = 0 To 18
                    uUserLifeEnd(r) = utmp(236 + r)
                Next r
                For q = 0 To 255
                    uPhotoFileName(q) = utmp(292 + q)
                Next q
                strMsg = Str(Now()) + " 姓名：" + StrConv(uName, vbUnicode)
                List1.AddItem strMsg
                strMsg = Str(Now()) + " 性别：" + StrConv(uSex, vbUnicode)
                List1.AddItem strMsg
                strMsg = Str(Now()) + " 民族：" + StrConv(uNation, vbUnicode)
                List1.AddItem strMsg
                strMsg = Str(Now()) + " 出生日期：" + StrConv(uBorn, vbUnicode)
                List1.AddItem strMsg
                strMsg = Str(Now()) + " 地址：" + StrConv(uAddress, vbUnicode)
                List1.AddItem strMsg
                strMsg = Str(Now()) + " 身份证号：" + StrConv(uIDCardNo, vbUnicode)
                List1.AddItem strMsg
                strMsg = Str(Now()) + " 发证机关：" + StrConv(uGrantDept, vbUnicode)
                List1.AddItem strMsg
                tmpstr = StrConv(uUserLife, vbUnicode)
                
                tmpstr2 = StrConv(uUserLifeEnd, vbUnicode)
                strMsg = Str(Now()) + " 有效期开始：" + tmpstr
                List1.AddItem strMsg
                strMsg = Str(Now()) + " 有效期结束：" + tmpstr2
                List1.AddItem strMsg
                strMsg = Str(Now()) + " 照片路径：" + StrConv(uPhotoFileName, vbUnicode)
                List1.AddItem strMsg
                Image1.Picture = LoadPicture(StrConv(uPhotoFileName, vbUnicode))
            Else
                smsm = Str(Now()) + " 读二代证失败"
                List1.AddItem sMsg
            End If
        Else
            sMsg = Str(Now()) + " 连接读卡器失败"
            List1.AddItem sMsg
        End If
    Else
        sMsg = Str(Now()) + " 打开端口失败"
        List1.AddItem sMsg
    End If
    Syn_ClosePort (iPort)
End Sub


Private Sub Command2_Click()
    Dim nPort As Long
    Dim nBaud As Long
    Dim nRet As Long
    nPort = Syn_FindReader()
    m_iPort = nPort
    If nPort = 0 Then
        sMsg = Str(Now()) + " 没有找到读卡器"
    Else
        APIBeep 4000, 500
        If nPort > 100 Then
            sMsg = Str(Now()) + " 读卡器连接在USB端口 " + Str(nPort) + " 上"
        Else
            sMsg = Str(Now()) + " 读卡器连接在串口 " + Str(nPort) + " 上"
        End If
    End If
    List1.AddItem sMsg, 0
End Sub

Private Sub Command20_Click()
    List1.Clear

End Sub

Private Sub Command3_Click()
    Dim nLen As Long
    Dim nRet As Long
    Dim utmp(1280) As Byte
    Dim uName(32) As Byte
    Dim uSex(6) As Byte
    Dim uNation(20) As Byte
    Dim uBorn(18) As Byte
    Dim uAddress(72) As Byte
    Dim uIDCardNo(38) As Byte
    Dim uGrantDept(32) As Byte
    Dim uUserLife(18) As Byte
    Dim uUserLifeEnd(18) As Byte
    Dim uPhotoFileName(255) As Byte
    Dim uFPName(255) As Byte
    Dim i, j, k, l, m, n, o, p, q, r As Integer
    Dim strMsg, tmpstr, tmpstr2, sMsg As String
    Dim pucIIN(4) As Byte
    Dim pucSN(8) As Byte
    iPort = m_iPort
    nRet = Syn_OpenPort(iPort)
    If nRet = 0 Then
        nRet = Syn_SetMaxRFByte(iPort, 80, 0)
        If nRet = 0 Then
            nRet = Syn_StartFindIDCard(iPort, pucIIN(0), 0)
            nRet = Syn_SelectIDCard(iPort, pucSN(0), 0)
            nLen = Syn_ReadFPMsg(iPort, 0, utmp(0), uFPName(0))
            If nLen = 0 Then
                For i = 0 To 32
                    uName(i) = utmp(i)
                Next i
                For j = 0 To 6
                    uSex(j) = utmp(32 + j)
                Next j
                For k = 0 To 20
                    uNation(k) = utmp(38 + k)
                Next k
                For l = 0 To 18
                    uBorn(l) = utmp(58 + l)
                Next l
                For m = 0 To 72
                    uAddress(m) = utmp(76 + m)
                Next m
                For n = 0 To 38
                    uIDCardNo(n) = utmp(148 + n)
                Next n
                For o = 0 To 32
                    uGrantDept(o) = utmp(186 + o)
                Next o
                For p = 0 To 18
                    uUserLife(p) = utmp(218 + p)
                Next p
                For r = 0 To 18
                    uUserLifeEnd(r) = utmp(236 + r)
                Next r
                For q = 0 To 255
                    uPhotoFileName(q) = utmp(292 + q)
                Next q
                strMsg = Str(Now()) + " 姓名：" + StrConv(uName, vbUnicode)
                List1.AddItem strMsg
                strMsg = Str(Now()) + " 性别：" + StrConv(uSex, vbUnicode)
                List1.AddItem strMsg
                strMsg = Str(Now()) + " 民族：" + StrConv(uNation, vbUnicode)
                List1.AddItem strMsg
                strMsg = Str(Now()) + " 出生日期：" + StrConv(uBorn, vbUnicode)
                List1.AddItem strMsg
                strMsg = Str(Now()) + " 地址：" + StrConv(uAddress, vbUnicode)
                List1.AddItem strMsg
                strMsg = Str(Now()) + " 身份证号：" + StrConv(uIDCardNo, vbUnicode)
                List1.AddItem strMsg
                strMsg = Str(Now()) + " 发证机关：" + StrConv(uGrantDept, vbUnicode)
                List1.AddItem strMsg
                tmpstr = StrConv(uUserLife, vbUnicode)
                
                tmpstr2 = StrConv(uUserLifeEnd, vbUnicode)
                strMsg = Str(Now()) + " 有效期开始：" + tmpstr
                List1.AddItem strMsg
                strMsg = Str(Now()) + " 有效期结束：" + tmpstr2
                List1.AddItem strMsg
                strMsg = Str(Now()) + " 照片文件：" + StrConv(uPhotoFileName, vbUnicode)
                List1.AddItem strMsg
                strMsg = Str(Now()) + " 指纹文件：" + StrConv(uFPName, vbUnicode)
                List1.AddItem strMsg
                Image1.Picture = LoadPicture(StrConv(uPhotoFileName, vbUnicode))
            Else
                smsm = Str(Now()) + " 读二代证失败"
                List1.AddItem sMsg
            End If
        Else
            sMsg = Str(Now()) + " 连接读卡器失败"
            List1.AddItem sMsg
        End If
    Else
        sMsg = Str(Now()) + " 打开端口失败"
        List1.AddItem sMsg
    End If
    Syn_ClosePort (iPort)

End Sub
