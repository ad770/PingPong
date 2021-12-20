//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

float x=-5;
float y=-3;
int hits=0;
int scorePlayer1=0;
int scorePlayer2=0;
int seconds=4;

void speedIncrement () {
        hits++;
        if (hits%5==0) x*=1.1;
}
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        AnsiString strHelloMessage = "Welcome in PingPong game!";
	AnsiString strSteeringRules = "How to play?";
        AnsiString strSteeringRulesPlayer1 = "Player 1 is using 'A' and 'Z'";
        AnsiString strSteeringRulesPlayer2 = "Player 2 is using UP_ARROW and DOWN_ARROW";
	AnsiString strGameRules1 = "To increase the angle hit the ball with edge of the paddle";
        AnsiString strGameRules2 = "To decrease the angle hit the ball with the center part the paddle";
        AnsiString strGameRules3 = "Every 5 hit speed will increase";
	AnsiString strFinal = "Enjoy!";

	ShowMessage(strHelloMessage + sLineBreak + sLineBreak + strSteeringRules + sLineBreak +
			strSteeringRulesPlayer1 + sLineBreak + strSteeringRulesPlayer2 + sLineBreak + sLineBreak +
                        strGameRules1 + sLineBreak + strGameRules2 +sLineBreak + strGameRules3 + sLineBreak + sLineBreak +
                        strFinal);

        startCounter->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::mainTimer(TObject *Sender)
{
        AnsiString angle;
        AnsiString speed;
        angle=FloatToStrF(abs(y),ffNumber, 7, 2);
        speed=FloatToStrF(abs(x),ffNumber, 7, 2);
        Label1->Caption="Angle="+angle+" Hits="+hits+" Speed="+speed;
        //Label1->Caption="x = "+x;

        ball->Left +=x;
        ball->Top +=y;

        //odbicie od górnej sciany;
        if (ball->Top-5 <= playground->Top) y=-y;
        //odbicie od dolnej sciany;
        if ((ball->Top + ball->Height+5) >= (playground->Top + playground->Height)) y=-y;

        //koniec gry
        if ((ball->Left < player1->Left + player1->Width - 5 && (ball->Top > player1->Top + player1->Height || ball->Top + ball->Height < player1->Top)) ||
                (ball->Left + ball->Width > player2->Left + 5 && (ball->Top > player2->Top + player2->Height || ball->Top + ball->Height < player2->Top))){
                main->Enabled=false;
                ball->Visible=false;
                p1_up->Enabled=false;
                p1_down->Enabled=false;
                p2_up->Enabled=false;
                p2_down->Enabled=false;
                if (ball->Left < 100) {
                        winner->Caption="Player 2 won!";
                        scorePlayer1++;
                }
                else {
                        winner->Caption="Player 1 won!";
                        scorePlayer2++;
                }
                winner->Visible=true;
                score->Caption=IntToStr(scorePlayer1)+":"+IntToStr(scorePlayer2);
                score->Visible=true;
                Button1->Visible=true;
                Button2->Visible=true;
                Button3->Visible=true;
        }
        //odbicie player1
        else if ((ball->Top < player1->Top + player1->Height &&
                ball->Top > player1->Top + player1->Height - 40 ||
                ball->Top + ball->Height > player1->Top &&
                ball->Top + ball->Height < player1->Top + 40) &&
                ball->Left <= player1->Left + player1->Width) {
                        x=-x;
                        if (y>0) y+=2;
                        else y-=0.5;
                        speedIncrement();
                }
        else if (ball->Top <= player1->Top + player1->Height - 40 &&
                ball->Top + ball->Height >= player1->Top + 40 &&
                ball->Left <= player1->Left + player1->Width) {
                        x=-x;
                        if (y>0) y-=0.5;
                        else if (y<0) y+=2;
                        speedIncrement();
                }

        //odbicie player2
        else if ((ball->Top < player2->Top + player2->Height &&
                ball->Top > player2->Top + player2->Height - 40 ||
                ball->Top + ball->Height > player2->Top &&
                ball->Top + ball->Height < player2->Top + 40) &&
                ball->Left + ball->Width >= player2->Left) {
                        x=-x;
                        if (y>=0) y+=2;
                        else y-=0.5;
                        speedIncrement();
                }
        else if (ball->Top <= player2->Top + player2->Height - 40 &&
                ball->Top + ball->Height >= player2->Top + 40 &&
                ball->Left + ball->Width >= player2->Left) {
                        x=-x;
                        if (y>0) y-=0.5;
                        else if (y<0) y+=2;
                        speedIncrement();
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

void __fastcall TForm1::Button1Click(TObject *Sender)
{
        winner->Visible=false;
        score->Visible=false;
        Button1->Visible=false;
        Button2->Visible=false;
        Button3->Visible=false;
        ball->Top = 234; ball->Left = 484;
        ball->Visible=true;
        main->Enabled=true;
        y=-3;
        x=-5;
        hits=0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
        scorePlayer1=0;
        scorePlayer2=0;
        Button1Click(Owner);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
        Application->Terminate();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::startCounterTimer(TObject *Sender)
{
    seconds--;

    startLabel->Caption=IntToStr(seconds);

    if(seconds<1) {
        startLabel->Visible=false;
        startCounter->Enabled=false;
        main->Enabled=true;
    }
}
//---------------------------------------------------------------------------



