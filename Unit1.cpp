//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int x=-5;
int y=-5;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::mainTimer(TObject *Sender)
{
        ball->Left +=x;
        ball->Top +=y;

        //odbicie od górnej sciany;
        if (ball->Top-5 <= playground->Top) y=-y;
        //odbicie od dolnej sciany;
        if ((ball->Top + ball->Height+5) >= (playground->Top + playground->Height)) y=-y;

        //koniec gry
        if (ball->Left < player1->Left + player1->Width - 25 || ball->Left + ball->Width > player2->Left + 15){
                main->Enabled=false;
                ball->Visible=false;
                if (Application->MessageBoxA("Chcesz rozpoczac nowa gre?","Koniec gry", MB_YESNO | MB_ICONQUESTION) == IDYES) {
                        ball->Top = 280; ball->Left = 496;
                        ball->Visible=true;
                        main->Enabled=true;
                };
        }
        //odbicie player1
        else if (ball->Top < player1->Top + player1->Height &&
                ball->Top + ball->Height > player1->Top &&
                ball->Left < player1->Left + player1->Width) {
                        x=-x;
                }

        //odbicie player2
        else if (ball->Top < player2->Top + player2->Height &&
                ball->Top + ball->Height > player2->Top &&
                ball->Left + ball->Width > player2->Left) {
                        x=-x;
                }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::p1_upTimer(TObject *Sender)
{
        if (player1->Top > 10) player1->Top -= 10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::p1_downTimer(TObject *Sender)
{
        if (player1->Top + player1->Height < playground->Top + playground->Height - 10) player1->Top += 10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::p2_upTimer(TObject *Sender)
{
        if (player2->Top > 10) player2->Top -= 10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::p2_downTimer(TObject *Sender)
{
        if (player2->Top + player2->Height < playground->Top + playground->Height - 10) player2->Top += 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if (Key == 0x41) p1_up->Enabled=true;
        if (Key == 0x5A) p1_down->Enabled=true;
        if (Key == VK_UP) p2_up->Enabled=true;
        if (Key == VK_DOWN) p2_down->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if (Key == 0x41) p1_up->Enabled=false;
        if (Key == 0x5A) p1_down->Enabled=false;
        if (Key == VK_UP) p2_up->Enabled=false;
        if (Key == VK_DOWN) p2_down->Enabled=false;
}
//---------------------------------------------------------------------------

