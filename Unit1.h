//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TShape *playground;
        TShape *player1;
        TShape *player2;
        TImage *ball;
        TTimer *main;
        TTimer *p1_up;
        TTimer *p1_down;
        TTimer *p2_up;
        TTimer *p2_down;
        TLabel *Label1;
        TLabel *winner;
        TLabel *score;
        TButton *Button1;
        TButton *Button2;
        TButton *Button3;
        TLabel *startLabel;
        TTimer *startCounter;
        void __fastcall mainTimer(TObject *Sender);
        void __fastcall p1_upTimer(TObject *Sender);
        void __fastcall p1_downTimer(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall p2_upTimer(TObject *Sender);
        void __fastcall p2_downTimer(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall startCounterTimer(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
