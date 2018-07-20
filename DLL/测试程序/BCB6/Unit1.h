//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TListBox *ListBox1;
        TButton *Button17;
        TButton *Button19;
        TButton *btn1;
        TButton *btn2;
        TButton *btn3;
        TLabel *lbl1;
        TImage *img1;
        void __fastcall Button19Click(TObject *Sender);
        void __fastcall Button17Click(TObject *Sender);
        void __fastcall btn1Click(TObject *Sender);
        void __fastcall btn3Click(TObject *Sender);
        void __fastcall btn2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        int m_iPort;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
 