#include <graphics.h>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <stack>
#include <cstring>
#include <vector>
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 780
#define MATRIX_TOP 66
#define MATRIX_WIDTH 10
#define MATRIX_HEIGHT 6
#define ON_SPAWN_BLOCK 1
#define IN_SCHEM 2
#define ON_CONNECT 3
#define ON_DELETE 4
#define ON_GENERATE 5
#define ON_SAVE 6
#define ON_LOAD 7
#define ON_CLEAR 8
#define ON_EVAL 9
#define NO_START 10
#define NO_STOP 11
#define CORECT 20
#define ON_SCR_D 12
#define ON_SCR_UP 13
#define ON_EDIT 14

using namespace std;

ifstream fin;
ofstream fout;

int lgG,del=0,cntloop,nrline,uz[100];

char txt[1000];

enum BlockType
{
	bstart,bcalc,bstop,binput,boutput,bdec,empty
};

struct SecMenu
{
	int x,y;
	bool stat;
};

struct Matrix
{
	BlockType type;
	char exp[150];
	int poz;
};

struct Point
{
	int x,y;
};

struct Graf
{
	Point poz;
	BlockType type;
};

struct chenbut
{
	int s,d,t,b;
} start,about,closeab,startsch,calculus,stop,input,output,decision;

Matrix M[MATRIX_WIDTH][MATRIX_HEIGHT];
Graf G[100];
SecMenu RClkMenu,Conn;
int dside,C[50][50],auxC[50][50];
bool infoBoxOpen;
int liniiMaxEval, lincur;
int scrollable;


void AnimatedTitle();
void Draw_SchemeMenu();
void ShowData(Matrix block);
void OpenBox(char *type,char *str,int text1, int text2);
bool IsValidCalculus(char *exp);
bool IsValidInput(char *exp);
bool IsValidOutput(char *exp);
bool IsValidDecision(char *exp);
bool IsValidExpresion(char *type, char *exp);
void HandleButtonClick(int x1, int y1, int x2, int y2, char* text);
void menu();
void DrawRectangleStart();
void DrawRectangleStop();
void DrawRectangleCalculus();
void DrawTrapezoidInput();
void DrawTrapezoidOutput();
void DrawTriangle();
void DrawStartButton(bool hov);
void DrawAboutButton(bool hov);
void DrawCloseButton();
void DrawGenerateCodeButton();
void DrawSaveSchemeButton();
void DrawLoadButtonSchemeButton();
void DrawEvaluateSchemeButton();
void DrawClearSchemeButton();
void DrawBackToMenuButton();
void DrawScrollButtons(int color);
void AboutPage();
void Undo();
void Redo();
void InterPage();
void HandleKeyboardInput();
void HandleMenuHover(int x,int y);
void HandleSchemHover(int x,int y);
void HandleLeftClick (int mx,int my);
int WhereMouse (int mx, int my);
void SpawnBlock (int x, int y);
void DrawBlock (BlockType type, Point center,int color);
void MoveBlock (int x,int y);
void HandleRightClick(int x,int y);
void RightClickMenu (int x,int y);
void DeleteRightClickMenu ();
void MakeConnection (int x, int y);
void DrawConnection (int a, int b, int color);
void ReDrawConnections();
void DeleteBlock(int x,int y);
void Generate();
void PrintCode();
int CheckSchem();
int DetectLoop (int start, int &loopend);
void Code(int curb,int h,int side,int loop);
void DrawScrollButtons(int color);
void HandleSave();
void HandleLoad();
void ClearSchem();
void Evaluate();
bool InputSchem(char nume[]);
bool OnIntBlock (int x, int y);
bool InsideSchem (int x,int y);
bool OnConnect (int x, int y);
bool OnDelete (int x,int y);
bool OnEdit(int x, int y);
bool OnGenerate(int x,int y);
bool OnSave(int x,int y);
bool OnLoad(int x, int y);
bool OnClear(int x, int y);
bool OnEval(int x,int y);
void PrintEval();
void ScrollDown();
void ScrollUp();
bool OnScrD(int x,int y);
bool OnScrUp(int x,int y);
void ClearScreen (int x,int y);
bool Capat(int i);
bool PDelay(int x,int y);
bool MDelay(int x,int y);
void Delayop(int n);
void DrawDelay();

long long int exp(int &, char[]);
void transformare(long long int, char[]);
int evalExp(char[]);
long long int valori[1000];
long long int termen(int &poz, char s[]);
long long int factor(int &poz, char s[]);

int main ()
{
	int screen_width = GetSystemMetrics(SM_CXSCREEN);
	int screen_height = GetSystemMetrics(SM_CYSCREEN);
	int start_x = (screen_width - WINDOW_WIDTH) / 2;
	int start_y = (screen_height - WINDOW_HEIGHT) / 2;
	initwindow(WINDOW_WIDTH,WINDOW_HEIGHT,"INTERSCHEM",start_x,start_y-50);
	setbkcolor(WHITE);
	cleardevice();
	AnimatedTitle();
	menu();
}
void Draw_SchemeMenu()
{
	setbkcolor(BLACK);
	setcolor(14);
	cleardevice();
	rectangle(0,0,WINDOW_WIDTH-275,WINDOW_HEIGHT-68);

	//DrawScrollButtons();

	setcolor(12);
	rectangle(1010,4,1270,610);
	settextstyle(8, 0, 5);
	setfillstyle(SOLID_FILL, BLUE);
	setcolor(WHITE);
	setbkcolor(BLUE);
	//outtextxy(1077,20, "CODE");
	DrawGenerateCodeButton();
	DrawSaveSchemeButton();
	DrawLoadButtonSchemeButton();
	DrawEvaluateSchemeButton();
	DrawClearSchemeButton();
	DrawRectangleStart();
	DrawRectangleCalculus();
	DrawRectangleStop();
	DrawTrapezoidInput();
	DrawTrapezoidOutput();
	DrawTriangle();
	/*while (true) {
    	if (ismouseclick(WM_LBUTTONDOWN)) {
        	int x = mousex();
        	int y = mousey();
        	clearmouseclick(WM_LBUTTONDOWN);
        	cout << "Coordonate: X=" << x << " Y=" << y<<"\n";
    	}
	}*/
	setcolor(LIGHTGRAY);
	line(0,65,WINDOW_WIDTH-275-1,65);
	DrawDelay();
}

void DrawScrollButtons(int color)
{
	setcolor(color);
	rectangle(WINDOW_WIDTH-276-5-30,5,WINDOW_WIDTH-276-5,30);
	rectangle(WINDOW_WIDTH-276-5-30,35,WINDOW_WIDTH-276-5,60);

	line(WINDOW_WIDTH-276-30,25,WINDOW_WIDTH-276-5-5,25);
	line (WINDOW_WIDTH-276-30,25,WINDOW_WIDTH-276-20,10);
	line (WINDOW_WIDTH-276-5-5,25,WINDOW_WIDTH-276-20,10);

	line(WINDOW_WIDTH-276-30,40,WINDOW_WIDTH-276-5-5,40);
	line (WINDOW_WIDTH-276-30,40,WINDOW_WIDTH-276-20,55);
	line (WINDOW_WIDTH-276-5-5,40,WINDOW_WIDTH-276-20,55);

}

void AnimatedTitle()
{
	int title_width = textwidth("INTERSCHEM");
	setbkcolor(WHITE);
	cleardevice();
	for (int i = 1; i <= 9; i++)
	{
    	settextstyle(8, 0, i);
    	cleardevice();
    	setcolor(BLUE);
    	outtextxy(WINDOW_WIDTH / 2 - textwidth("INTERSCHEM") / 2, 100, "INTERSCHEM");
    	delay(100);
	}
}

void menu()
{
	setbkcolor(WHITE);
	cleardevice();
	settextstyle(8, 0, 9);
	int title_width=textwidth("INTERSCHEM");
	int title_height=textheight("INTERSCHEM");
	setcolor(BLUE);
	outtextxy(WINDOW_WIDTH / 2 - title_width / 2, 100, "INTERSCHEM");
	DrawStartButton(0);
	DrawAboutButton(0);
	while (true)
	{
    	int mx = mousex();
    	int my = mousey();
    	HandleMenuHover(mx,my);
    	if (ismouseclick(WM_LBUTTONDOWN))
    	{
        	if (mx >= start.s && mx <= start.d && my >= start.t && my <= start.b)
        	{
            	clearmouseclick(WM_LBUTTONDOWN);
            	InterPage();
            	break;
        	}
        	else if (mx >= about.s && mx <= about.d && my >= about.t && my <= about.b)
        	{
            	clearmouseclick(WM_LBUTTONDOWN);
            	AboutPage();
            	break;
        	}
        	clearmouseclick(WM_LBUTTONDOWN);
    	}
    	delay(50);
	}
}

void DrawStartButton(bool hov)
{
	settextstyle(8,0,5);
	if (hov==1)
    	setcolor(LIGHTBLUE);
	else
    	setcolor(BLUE);
	int width=textwidth("START");
	int height=textheight("START");
	start.s=WINDOW_WIDTH/2-width/2-50;
	start.d=WINDOW_WIDTH/2+width/2+50;
	start.t=400;
	start.b=400+height+5;
	outtextxy(WINDOW_WIDTH/2-width/2,405,"START");
	rectangle(start.s,start.t,start.d,start.b);
}

void DrawGenerateCodeButton()
{
	settextstyle(8, 0, 2);
	setfillstyle(SOLID_FILL, BLUE);
	setcolor(WHITE);
	setbkcolor(BLUE);
	int x1 = 20;
	int y1 = 720;
	int x2 = x1 + 110;
	int y2 = y1 + 50;
	bar(x1, y1, x2, y2);
	rectangle(x1, y1, x2, y2);
	int width = textwidth("GENERATE");
	int height = textheight("GENERATE");
	int textX = x1 + (x2 - x1) / 2 - width / 2;
	int textY = y1 + (y2 - y1) / 2 - height / 2;
	outtextxy(textX, textY, "GENERATE");
}

void DrawSaveSchemeButton()
{
	settextstyle(8, 0, 2);
	setfillstyle(SOLID_FILL, BLUE);
	setcolor(WHITE);
	setbkcolor(BLUE);
	int spacing = 65;
	int x1 = 20 + 110 + spacing;
	int y1 = 720;
	int x2 = x1 + 110;
	int y2 = y1 + 50;
	bar(x1, y1, x2, y2);
	rectangle(x1, y1, x2, y2);
	int width = textwidth("SAVE");
	int height = textheight("SAVE");
	int textX = x1 + (x2 - x1) / 2 - width / 2;
	int textY = y1 + (y2 - y1) / 2 - height / 2;
	outtextxy(textX, textY, "SAVE");
}

void DrawLoadButtonSchemeButton()
{
	settextstyle(8, 0, 2);
	setfillstyle(SOLID_FILL, BLUE);
	setcolor(WHITE);
	setbkcolor(BLUE);
	int spacing = 65;
	int x1 = 20 + 2 * (110 + spacing);
	int y1 = 720;
	int x2 = x1 + 110;
	int y2 = y1 + 50;
	bar(x1, y1, x2, y2);
	rectangle(x1, y1, x2, y2);
	int width = textwidth("LOAD");
	int height = textheight("LOAD");
	int textX = x1 + (x2 - x1) / 2 - width / 2;
	int textY = y1 + (y2 - y1) / 2 - height / 2;
	outtextxy(textX, textY, "LOAD");
}

void DrawEvaluateSchemeButton()
{
	settextstyle(8, 0, 2);
	setfillstyle(SOLID_FILL, BLUE);
	setcolor(WHITE);
	setbkcolor(BLUE);
	int spacing = 65;
	int x1 = 20 + 3 * (110 + spacing);
	int y1 = 720;
	int x2 = x1 + 110;
	int y2 = y1 + 50;
	bar(x1, y1, x2, y2);
	rectangle(x1, y1, x2, y2);
	int width = textwidth("EVALUATE");
	int height = textheight("EVALUATE");
	int textX = x1 + (x2 - x1) / 2 - width / 2;
	int textY = y1 + (y2 - y1) / 2 - height / 2;
	outtextxy(textX, textY, "EVALUATE");
}

void DrawClearSchemeButton()
{
	settextstyle(8, 0, 2);
	setfillstyle(SOLID_FILL, BLUE);
	setcolor(WHITE);
	setbkcolor(BLUE);
	int spacing = 65;
	int x1 = 20 + 4 * (110 + spacing);
	int y1 = 720;
	int x2 = x1 + 110;
	int y2 = y1 + 50;
	bar(x1, y1, x2, y2);
	rectangle(x1, y1, x2, y2);
	int width = textwidth("CLEAR");
	int height = textheight("CLEAR");
	int textX = x1 + (x2 - x1) / 2 - width / 2;
	int textY = y1 + (y2 - y1) / 2 - height / 2;
	outtextxy(textX, textY, "CLEAR");
}

void DrawAboutButton(bool hov)
{
	settextstyle(8,0,5);
	if (hov==1)
    	setcolor(LIGHTBLUE);
	else
    	setcolor(BLUE);
	int width=textwidth("ABOUT");
	int height=textheight("ABOUT");
	about.s=WINDOW_WIDTH/2-width/2-50;
	about.d=WINDOW_WIDTH/2+width/2+50;
	about.t=start.b+10;
	about.b=about.t+height+5;
	outtextxy(about.s+50,about.t+5,"ABOUT");
	rectangle(about.s,about.t,about.d,about.b);
}

void DrawRectangleStart()
{
	setcolor(13);
	int x1 = 14, y1 = 13;
	int x2 = 125, y2 = 57;
	startsch.s=x1-5,startsch.t=y1-5,startsch.d=x2+5,startsch.b=y2+5;
	rectangle(x1,y1,x2,y2);
	settextstyle(8, 0, 2);
	setbkcolor(BLACK);
	setcolor(WHITE);
	int textWidth = textwidth("START");
	int textHeight = textheight("START");
	int textX = x1 + (x2 - x1) / 2 - textWidth / 2;
	int textY = y1 + (y2 - y1) / 2 - textHeight / 2;
	outtextxy(textX, textY, "START");
}

void DrawRectangleCalculus()
{
	setcolor(10);
	int prevX2 = 125;
	int spacing = 20;
	int x1 = prevX2 + spacing;
	int y1 = 13;
	int x2 = x1 + (125 - 14);
	int y2 = 57;
	calculus.s=x1-5,calculus.t=y1-5,calculus.d=x2+5,calculus.b=y2+5;
	rectangle(x1,y1,x2,y2);
	settextstyle(8, 0, 2);
	setbkcolor(BLACK);
	setcolor(WHITE);
	int textWidth = textwidth("CALCULUS");
	int textHeight = textheight("CALCULUS");
	int textX = x1 + (x2 - x1) / 2 - textWidth / 2;
	int textY = y1 + (y2 - y1) / 2 - textHeight / 2;
	outtextxy(textX, textY, "CALCULUS");
}

void DrawRectangleStop()
{
	setcolor(13);
	int prevX2 = 125 + 20 + (125 - 14);
	int spacing = 20;
	int x1 = prevX2 + spacing;
	int y1 = 13;
	int x2 = x1 + (125 - 14);
	int y2 = 57;
	stop.s=x1-5,stop.t=y1-5,stop.d=x2+5,stop.b=y2+5;
	rectangle (x1,y1,x2,y2);
	settextstyle(8, 0, 2);
	setbkcolor(BLACK);
	setcolor(WHITE);
	int textWidth = textwidth("STOP");
	int textHeight = textheight("STOP");
	int textX = x1 + (x2 - x1) / 2 - textWidth / 2;
	int textY = y1 + (y2 - y1) / 2 - textHeight / 2;
	outtextxy(textX, textY, "STOP");
}

void DrawTrapezoidOutput()
{
	setcolor(9);
	int prevX2 = 125 + 20 + (125 - 14) + 20 + (125 - 14) + 20 + (125 - 14);
	int spacing = 20;
	int bottomBaseX1 = prevX2 + spacing;
	int bottomBaseX2 = bottomBaseX1 + (125 - 14);
	int topBaseX1 = bottomBaseX1 + 15;
	int topBaseX2 = bottomBaseX2 - 15;
	int topY = 13;
	int bottomY = 57;
	output.s=bottomBaseX1-5,output.d=bottomBaseX2+5,output.t=topY-5,output.b=bottomY+5;
	line(bottomBaseX1, bottomY, bottomBaseX2, bottomY);
	line(bottomBaseX2, bottomY, topBaseX2, topY);
	line(topBaseX2, topY, topBaseX1, topY);
	line(topBaseX1, topY, bottomBaseX1, bottomY);
	settextstyle(8, 0, 2);
	setbkcolor(BLACK);
	setcolor(WHITE);
	int textWidth = textwidth("OUTPUT");
	int textHeight = textheight("OUTPUT");
	int textX = bottomBaseX1 + (bottomBaseX2 - bottomBaseX1) / 2 - textWidth / 2;
	int textY = topY + (bottomY - topY) / 2 - textHeight / 2;
	outtextxy(textX, textY, "OUTPUT");
}

void DrawTrapezoidInput()
{
	setcolor(11);
	int prevX2 = 125 + 20 + (125 - 14) + 20 + (125 - 14);
	int spacing = 20;
	int topBaseX1 = prevX2 + spacing;
	int topBaseX2 = topBaseX1 + (125 - 14);
	int bottomBaseX1 = topBaseX1 + 15;
	int bottomBaseX2 = topBaseX2 - 15;
	int topY = 13;
	int bottomY = 57;
	input.s=topBaseX1-5,input.d=topBaseX2+5,input.t=topY-5,input.b=bottomY+5;
	line(topBaseX1, topY, topBaseX2, topY);
	line(topBaseX2, topY, bottomBaseX2, bottomY);
	line(bottomBaseX2, bottomY, bottomBaseX1, bottomY);
	line(bottomBaseX1, bottomY, topBaseX1, topY);
	settextstyle(8, 0, 2);
	setbkcolor(BLACK);
	setcolor(WHITE);
	int textWidth = textwidth("INPUT");
	int textHeight = textheight("INPUT");
	int textX = topBaseX1 + (topBaseX2 - topBaseX1) / 2 - textWidth / 2;
	int textY = topY + (bottomY - topY) / 2 - textHeight / 2;
	outtextxy(textX, textY, "INPUT");
}

void DrawTriangle()
{
	setcolor(14);
	int prevX2 = 125 + 20 + (125 - 14) + 20 + (125 - 14) + 20 + (125 - 14) + 20 + (125 - 14);
	int spacing = 20;
	int baseX1 = prevX2 + spacing;
	int baseX2 = baseX1 + (125 - 14);
	int apexX = baseX1 + (baseX2 - baseX1) / 2;
	int baseY = 57;
	int apexY = 13;
	decision.s=baseX1-5,decision.d=baseX2+5,decision.t=apexY-5,decision.b=baseY+5;
	line(baseX1, baseY, baseX2, baseY);
	line(baseX2, baseY, apexX, apexY);
	line(apexX, apexY, baseX1, baseY);
	settextstyle(8, 0, 2);
	setbkcolor(BLACK);
	setcolor(WHITE);
	int textWidth = textwidth("DECISION");
	int textHeight = textheight("DECISION");
	int textX = baseX1 + (baseX2 - baseX1) / 2 - textWidth / 2;
	int textY = apexY + (baseY - apexY) / 2 - textHeight / 2;
	outtextxy(textX, textY, "DECISION");
}

void AboutPage() {
	setbkcolor(WHITE);
	cleardevice();
	DrawBackToMenuButton();

	settextstyle(8, 0, 4);
	outtextxy(20, 20, "About InterSchem App");

	settextstyle(8, 0, 2);
	setcolor(BLACK);
	int text_y = 100;
	outtextxy(20, text_y, "InterSchem este un instrument educational pentru");
	text_y += 30;
	outtextxy(20, text_y, "crearea si vizualizarea algoritmilor sub forma de");
	text_y += 30;
	outtextxy(20, text_y, "schema logica.");
	text_y += 50;
	outtextxy(20, text_y, "Functionalitati principale:");
	text_y += 30;
	outtextxy(40, text_y, "- Inserarea blockurilor si realizarea conexiunilor intre ele: Start, Stop, Input, Output,");
	text_y += 30;
	outtextxy(40, text_y, "  Calcul si Decizie.");
	text_y += 30;
	outtextxy(40, text_y, "- Generarea automata a codului dupa apasarea butonului GENERATE.");
	text_y += 30;
	outtextxy(40, text_y, "- Salvarea si incarcarea diagramelor in/din fisiere .sch .");
	text_y += 30;
	outtextxy(40, text_y, "- Evaluarea logicii schemei.");
	text_y += 50;
	outtextxy(20,text_y,"Sintaxa corespunzatoare fiecarui block: ");
	text_y+=30;
	outtextxy(40,text_y, "- Blockurile START si STOP nu vor fi modificate,");
	text_y+=30;
	outtextxy(42,text_y,"sunt implicit declarate pentru inceputul si sfarsitul algoritmului.");
	text_y+=30;
	outtextxy(40,text_y,"- Blockul CALCULUS trebuie sa aiba un input simplu , de forma OPERAND = OPERAND _ OPERATOR _ OPERAND.");
	text_y+=30;
	outtextxy(40,text_y,"- Blockurile INPUT si OUTPUT trebuie sa fie de forma OPERAND , fara alti operatori/operanzi.");
	text_y+=30;
	outtextxy(40,text_y,"- Blockul DECISION trebuie sa fie de forma OPERAND urmat de o CONDITIE simpla");
	text_y+=50;
	outtextxy(20, text_y, "Proiect dezvoltat de Panainte Tudor-Emanuel si Filibiu Matei pentru a ajuta studentii sa inteleaga");
	text_y += 30;
	outtextxy(20, text_y, "structura si logica algoritmilor.");

	while (true) {
    	int mx = mousex();
    	int my = mousey();
    	if (ismouseclick(WM_LBUTTONDOWN)) {
        	if (mx >= closeab.s && mx <= closeab.d && my >= closeab.t && my <= closeab.b) {
            	clearmouseclick(WM_LBUTTONDOWN);
            	cleardevice();
            	break;
        	}
        	clearmouseclick(WM_LBUTTONDOWN);
    	}
    	delay(50);
	}
	menu();
}

void DrawBackToMenuButton()
{
	settextstyle(8, 0, 3);
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	setbkcolor(LIGHTGRAY);
	setcolor(RED);
	int width = textwidth("BACK");
	int height = textheight("BACK");
	closeab.s = 1160;
	closeab.t = 720;
	closeab.d = closeab.s + width + 20;
	closeab.b = closeab.t + height + 10;
	bar(closeab.s, closeab.t, closeab.d, closeab.b);
	setcolor(WHITE);
	rectangle(closeab.s, closeab.t, closeab.d, closeab.b);
	setcolor(RED);
	outtextxy(closeab.s + (closeab.d - closeab.s) / 2 - width / 2,closeab.t + (closeab.b - closeab.t) / 2 - height / 2,"BACK");
	setbkcolor(WHITE);
}

void InterPage()
{
	cleardevice();
	settextstyle(8,0,5);
	Draw_SchemeMenu();
	DrawBackToMenuButton();
	for(int i=0; i<MATRIX_WIDTH; i++)
    	for(int j=0; j<MATRIX_HEIGHT; j++)
    	{
        	M[i][j].type = empty;
        	M[i][j].poz=-1;
    	}
	for (int i=0; i<=20; i++)
	{
    	G[i].poz= {-1,-1};
    	G[i].type=empty;
	}
	lgG=0;
	while (true)
	{
    	int mx=mousex();
    	int my=mousey();
    	HandleSchemHover(mx,my);
    	if (ismouseclick(WM_LBUTTONDOWN))
    	{

        	if (mx>=closeab.s && mx<=closeab.d && my>=closeab.t && my<=closeab.b)
        	{
            	clearmouseclick(WM_LBUTTONDOWN);
            	cleardevice();
            	break;
        	}
        	else
            	HandleLeftClick(mx,my);
        	clearmouseclick(WM_LBUTTONDOWN);
        	ReDrawConnections();
    	}
    	if (ismouseclick(WM_RBUTTONDOWN))
    	{
        	HandleRightClick(mx,my);
        	clearmouseclick(WM_RBUTTONDOWN);
        	ReDrawConnections();
    	}
    	delay(50);
	}
	menu();
}

void HandleMenuHover (int x,int y)
{
	if (x>=start.s && x<=start.d && y>=start.t && y<=start.b)
    	DrawStartButton (1);
	else
    	DrawStartButton(0);

	if (x>=about.s && x<=about.d && y>=about.t && y<=about.b)
    	DrawAboutButton(1);
	else
    	DrawAboutButton(0);
}

void HandleSchemHover (int x, int y)
{
	if (x>=startsch.s && x<=startsch.d && y>=startsch.t && y<=startsch.b)
    	setcolor(WHITE);
	else
    	setcolor(BLACK);
	rectangle(startsch.s,startsch.t,startsch.d,startsch.b);

	if (x>=calculus.s && x<=calculus.d && y>=calculus.t && y<=calculus.b)
    	setcolor(WHITE);
	else
    	setcolor(BLACK);
	rectangle(calculus.s,calculus.t,calculus.d,calculus.b);

	if (x>=stop.s && x<=stop.d && y>=stop.t && y<=stop.b)
    	setcolor(WHITE);
	else
    	setcolor(BLACK);
	rectangle(stop.s,stop.t,stop.d,stop.b);

	if (x>=output.s && x<=output.d && y>=output.t && y<=output.b)
    	setcolor(WHITE);
	else
    	setcolor(BLACK);
	rectangle(output.s,output.t,output.d,output.b);

	if (x>=input.s && x<=input.d && y>=input.t && y<=input.b)
    	setcolor(WHITE);
	else
    	setcolor(BLACK);
	rectangle(input.s,input.t,input.d,input.b);

	if (x>=decision.s && x<=decision.d && y>=decision.t && y<=decision.b)
    	setcolor(WHITE);
	else
    	setcolor(BLACK);
	rectangle(decision.s,decision.t,decision.d,decision.b);
}

void ShowData(Matrix block)
{
	int x1 = 1014, y1 = 515;
	int x2 = 1265, y2 = 607;
	int maxWidth = x2 - x1 - 20;
	int lineHeight = textheight("A");
	setfillstyle(SOLID_FILL, BLACK);
	setbkcolor(BLACK);
	bar(x1, y1, x2, y2);
	setcolor(WHITE);
	rectangle(x1, y1, x2, y2);
	char *blockType;
	switch(block.type)
	{
	case bstart:
    	blockType = "Type: START";
    	break;
	case bcalc:
    	blockType = "Type: CALCULUS";
    	break;
	case binput:
    	blockType = "Type: INPUT";
    	break;
	case bstop:
    	blockType = "Type : STOP";
    	break;
	case boutput:
    	blockType = "Type: OUTPUT";
    	break;
	case bdec:
    	blockType = "Type: DECISION";
    	break;
	}
	outtextxy(x1+10,y1+10,blockType);
	if(strlen(block.exp) > 0)
	{
    	outtextxy(x1+10,y1+30,"Data: ");
    	char expText[205];
    	int diferenta = textwidth("Data: ");
    	strcpy(expText,block.exp);
    	int currentX = x1 + 10 + diferenta + 5;
    	int currentY = y1 + 30;
    	char line[205]="";
    	for (int i = 0; i < strlen(expText); ++i)
    	{
        	char tmp[3] = {expText[i], '\0', '\0'};
        	if ((expText[i] == '&' || expText[i] == '|') && i + 1 < strlen(expText) && expText[i] == expText[i + 1])
        	{
            	tmp[1] = expText[i + 1];
            	i++;
        	}
        	if (textwidth(line) + textwidth(tmp) < maxWidth - diferenta)
            	strcat(line, tmp);
        	else
        	{
            	outtextxy(currentX, currentY, line);
            	currentY += lineHeight;
            	if (currentY + lineHeight > y2 - 10)
                	break;
            	strcpy(line, tmp);
            	currentX = x1 + 10;
            	diferenta = 0;
        	}
    	}
    	if(strlen(line) > 0 && currentY + lineHeight <= y2 - 10)
        	outtextxy(currentX,currentY, line);
	}
}
void EditBlock(int x, int y)
{
	HWND main_window = FindWindow(NULL, "INTERSCHEM");
	if (M[x][y].type == bstart || M[x][y].type == bstop)
	{
    	MessageBox(main_window, "START si STOP nu pot fi editate!", "Error", MB_OK | MB_ICONERROR);
    	return;
	}
	char newText[150] = "";
	OpenBox("Edit Block", newText, x, y);
	bool valid = true;
	switch(M[x][y].type)
	{
	case bcalc:
    	valid = IsValidCalculus(newText);
    	break;
	case binput:
    	valid = IsValidInput(newText);
    	break;
	case boutput:
    	valid = IsValidOutput(newText);
    	break;
	case bdec:
    	valid = IsValidDecision(newText);
    	break;
	}
	if(valid){
    	MessageBox(main_window, "Edit cu succes!", "DONE", MB_OK | MB_ICONINFORMATION);
    	strcpy(M[x][y].exp, newText);
    	DrawBlock(M[x][y].type, Point{x * 100 + 50, y * 100 + 50}, BLACK);
	}
	else{
    	MessageBox(main_window, "Expresia nu este valida, scrieti corect datele!", "Error", MB_OK | MB_ICONERROR);
    	EditBlock(x,y);
	}
}
void HandleLeftClick (int mx,int my)
{
	if(scrollable)
    	ClearScreen(mx,my);

	int poz=WhereMouse(mx,my);
	if (infoBoxOpen)
	{
    	setfillstyle(SOLID_FILL, BLACK);
    	bar(1014, 515, 1265, 607);
    	setcolor(BLACK);
    	rectangle(1014, 515, 1265, 607);
    	infoBoxOpen = false;
    	return;
	}
	DeleteRightClickMenu();

	if (PDelay(mx,my))
            Delayop(1);
        else
            if (MDelay(mx,my))
                Delayop(2);

	switch(poz)
	{
	case ON_SPAWN_BLOCK:
	{
    	SpawnBlock(mx,my);
    	break;
	}
	case ON_CONNECT:
	{
    	Conn.stat=1;
    	Conn.x=RClkMenu.x;
    	Conn.y=RClkMenu.y;
    	break;
	}
	case ON_EDIT:
	{
    	int blockX = (RClkMenu.x - 50) / 100;
    	int blockY = (RClkMenu.y - 66 - 50) / 100;
    	EditBlock(blockX,blockY);
    	break;
	}
	case ON_DELETE:
	{
    	DeleteBlock(mx/100,(my-66)/100);
    	break;
	}
	case IN_SCHEM:
	{
    	if(M[mx/100][(my-66)/100].type  != empty)
    	{
        	if(!ismouseclick(WM_LBUTTONUP))
        	{
            	ShowData(M[mx/100][(my-66)/100]);
            	infoBoxOpen = true;
        	}
    	}
    	if (Conn.stat)
    	{
        	MakeConnection(mx/100,(my-66)/100);
        	Conn.stat=0;
    	}
    	else
    	{
        	MoveBlock(mx/100,(my-66)/100);
    	}
    	break;
	}
	case ON_GENERATE:
	{
    	for (int i=1; i<=lgG; i++)
        	for (int j=1; j<=lgG; j++)
            	auxC[i][j]=C[i][j];
    	Generate();
    	for (int i=1; i<=lgG; i++)
        	for (int j=1; j<=lgG; j++)
            	C[i][j]=auxC[i][j];
    	ReDrawConnections();
    	break;
	}
	case ON_LOAD:
	{
    	HandleLoad();
    	break;
	}
	case ON_CLEAR:
	{
    	ClearSchem();
    	break;
	}
	case ON_SAVE:
	{
    	HandleSave();
    	break;
	}
	case ON_EVAL:
	{
    	Evaluate();
    	break;
	}
	case ON_SCR_D:
	{
    	ScrollDown();
    	break;
	}
	case ON_SCR_UP:
	{
    	ScrollUp();
    	break;
	}
	default:
    	break;

	}
}
int WhereMouse (int mx, int my)
{
	if (RClkMenu.stat)
	{
    	if (OnConnect(mx,my))
        	return ON_CONNECT;
    	if (OnDelete(mx,my))
        	return ON_DELETE;
    	if(OnEdit(mx,my))
    	{
        	return ON_EDIT;
    	}
	}
	if (OnIntBlock(mx,my))
    	return ON_SPAWN_BLOCK;
	if (InsideSchem(mx,my))
    	return IN_SCHEM;
	if (OnGenerate(mx,my))
    	return ON_GENERATE;
	if (OnSave(mx,my))
    	return ON_SAVE;
	if (OnLoad(mx,my))
    	return ON_LOAD;
	if (OnClear(mx,my))
    	return ON_CLEAR;
	if (OnEval(mx,my))
    	return ON_EVAL;
	if (OnScrD(mx,my))
    	return ON_SCR_D;
	if (OnScrUp(mx,my))
    	return ON_SCR_UP;
}
bool IsAreaFree(int startX, int startY, int width, int height)
{
	for (int i = startX; i < startX + width; i++)
	{
    	for (int j = startY; j < startY + height; j++)
    	{
        	if (i >= MATRIX_WIDTH || j >= MATRIX_HEIGHT || M[i][j].type != empty)
            	return false;
    	}
	}
	return true;
}
void SpawnBlock(int x, int y)
{
	int newx = -1, newy = -1;
	int textw = 0, texth = 0;
	char str[256] = "";
	for (int i = 0; i < MATRIX_WIDTH && newx < 0 && newy < 0; i++)
	{
    	for (int j = 0; j < MATRIX_HEIGHT && newx < 0 && newy < 0; j++)
    	{
        	if (M[i][j].type == empty)
        	{
            	newx = i;
            	newy = j;
        	}
    	}
	}
	if (newx < 0 || newy < 0)
    	return;
	if (x >= startsch.s && x <= startsch.d)
	{
    	for (int i = 0; i <= lgG; i++)
    	{
        	if (G[i].type == bstart)
            	return;
    	}
    	M[newx][newy].type = bstart;
	}
	else if (x >= stop.s && x <= stop.d)
    	M[newx][newy].type = bstop;
	else if (x >= calculus.s && x <= calculus.d)
	{
    	bool ok = false;
    	M[newx][newy].type = bcalc;
    	HWND main_window = FindWindow(NULL, "INTERSCHEM");
    	while (!ok)
    	{
        	OpenBox("CALCULUS", str, textw, texth);
        	if (IsValidExpresion("CALCULUS", str))
        	{
            	cout << str << " " << "Este valid" << "\n";
            	MessageBox(main_window, "Expresia este valida si inserata!", "DONE", MB_OK | MB_ICONINFORMATION);
            	strcpy(M[newx][newy].exp, str);
            	ok = true;
        	}
        	else
        	{
            	cout << "Invalid" << "\n";
            	MessageBox(main_window, "Expresia nu este valida,scrieti corect datele!", "Error", MB_OK | MB_ICONERROR);
        	}
    	}
	}
	else if (x >= input.s && x <= input.d)
	{
    	bool ok = false;
    	M[newx][newy].type = binput;
    	HWND main_window = FindWindow(NULL, "INTERSCHEM");
    	while (!ok)
    	{
        	OpenBox("INPUT", str, textw, texth);
        	if (IsValidExpresion("INPUT", str))
        	{
            	cout << str << " " << "Este valid" << "\n";
            	MessageBox(main_window, "Expresia este valida si inserata!", "DONE", MB_OK | MB_ICONINFORMATION);
            	strcpy(M[newx][newy].exp, str);
            	ok = true;
        	}
        	else
        	{
            	cout << "Invalid" << "\n";
            	MessageBox(main_window, "Expresia nu este valida, scrieti corect datele!", "Error", MB_OK | MB_ICONERROR);
        	}
    	}
	}
	else if (x >= decision.s && x <= decision.d)
	{
    	bool ok = false;
    	M[newx][newy].type = bdec;
    	HWND main_window = FindWindow(NULL, "INTERSCHEM");
    	while (!ok)
    	{
        	OpenBox("DECISION", str, textw, texth);
        	if (IsValidExpresion("DECISION", str))
        	{
            	cout << str << " " << "Este valid" << "\n";
            	MessageBox(main_window, "Expresia este valida si inserata!", "DONE", MB_OK | MB_ICONINFORMATION);
            	strcpy(M[newx][newy].exp, str);
            	ok = true;
        	}
        	else
        	{
            	cout << "Invalid" << "\n";
            	MessageBox(main_window, "Expresia nu este valida, scrieti corect datele!", "Error", MB_OK | MB_ICONERROR);
        	}
    	}
	}
	else if(x>=output.s && x<=output.d)
	{
    	bool ok = false;
    	M[newx][newy].type = boutput;
    	HWND main_window = FindWindow(NULL, "INTERSCHEM");
    	while (!ok)
    	{
        	OpenBox("OUTPUT", str, textw, texth);
        	if (IsValidExpresion("OUTPUT", str))
        	{
            	cout << str << " " << "Este valid" << "\n";
            	MessageBox(main_window, "Expresia este valida si inserata!", "DONE", MB_OK | MB_ICONINFORMATION);
            	strcpy(M[newx][newy].exp, str);
            	ok = true;
        	}
        	else
        	{
            	cout << "Invalid" << "\n";
            	MessageBox(main_window, "Expresia nu este valida, scrieti corect datele!", "Error", MB_OK | MB_ICONERROR);
        	}
    	}
	}
	lgG++;
	M[newx][newy].poz = lgG;
	G[lgG].poz = Point{newx, newy};
	G[lgG].type = M[newx][newy].type;
	DrawBlock(M[newx][newy].type, Point{newx * 100 + 50, newy * 100 + 50},BLACK);
}

void DrawBlock(BlockType type, Point center,int color)
{
	switch (type)
	{
	case bstart:
	{
    	settextstyle(8, 0, 1);
    	setbkcolor(BLACK);
    	setcolor(WHITE);
    	outtextxy(center.x - 30, center.y - 10 + 66, "START");
    	if (color==BLACK)
        	setcolor(13);
    	else
        	setcolor(color);
    	rectangle(center.x - 45, center.y - 15 + 66, center.x + 45, center.y + 15 + 66);
    	int circleX = center.x;
    	int circleY = center.y + 15 + 66;
    	setcolor(YELLOW);
    	circle(circleX, circleY, 6);
    	setfillstyle(SOLID_FILL,BLACK);
    	floodfill(circleX,circleY,YELLOW);
    	break;
	}
	case bcalc:
	{
    	settextstyle(8, 0, 1);
    	int tw = textwidth("CALCULUS");
    	int th = textheight("CALCULUS");
    	setbkcolor(BLACK);
    	if (color==BLACK)
        	setcolor(10);
    	else
        	setcolor(color);
    	rectangle(center.x-tw/2-5,center.y-th/2-5+66,center.x+tw/2+5,center.y+th/2+5+66);
    	setcolor(WHITE);
    	char displayText[4] = "";
    	if (strlen(M[center.x / 100][center.y / 100].exp) > 3)
    	{
        	displayText[0] = M[center.x / 100][center.y / 100].exp[0];
        	displayText[1] = '.';
        	displayText[2] = '.';
        	displayText[3] = '\0';
    	}
    	else
        	strcpy(displayText, M[center.x / 100][center.y / 100].exp);
    	int textX = center.x - textwidth(displayText) / 2;
    	int textY = center.y - textheight(displayText) / 2 + 66;
    	outtextxy(textX, textY, displayText);
    	setcolor(YELLOW);
    	circle(center.x, center.y + th / 2 + 71, 6);
    	circle(center.x, center.y - th / 2 + 61, 6);
    	setfillstyle(SOLID_FILL,BLACK);
    	floodfill(center.x, center.y + th / 2 + 71,YELLOW);
    	floodfill(center.x, center.y - th / 2 + 61,YELLOW);
    	break;
	}
	case bstop:
	{
    	settextstyle(8, 0, 1);
    	int tw = textwidth("STOP");
    	int th = textheight("STOP");
    	setbkcolor(BLACK);
    	if (color==BLACK)
        	setcolor(13);
    	else
        	setcolor(color);
    	rectangle(center.x - tw / 2 - 5, center.y - th / 2 - 5 + 66, center.x + tw / 2 + 5, center.y + th / 2 + 5 + 66);
    	setcolor(WHITE);
    	outtextxy(center.x - tw / 2, center.y - th / 2 + 66, "STOP");
    	int circleX = center.x;
    	int circleY = center.y - th / 2 - 5 + 66;
    	setcolor(YELLOW);
    	circle(circleX, circleY, 6);
    	setfillstyle(SOLID_FILL,BLACK);
    	floodfill(circleX, circleY,YELLOW);
    	break;
	}
	case boutput:
	{
    	settextstyle(8, 0, 1);
    	int tw = textwidth("OUTPUT");
    	int th = textheight("OUTPUT");
    	setbkcolor(BLACK);
    	if (color==BLACK)
        	setcolor(9);
    	else
        	setcolor(color);
    	line(center.x - tw / 2 - 5, center.y - th / 2 - 5 + 66, center.x + tw / 2 + 5, center.y - th / 2 - 5 + 66);
    	line(center.x + tw / 2 + 5, center.y - th / 2 - 5 + 66, center.x + tw / 2 + 10, center.y + th / 2 + 5 + 66);
    	line(center.x + tw / 2 + 10, center.y + th / 2 + 5 + 66, center.x - tw / 2 - 10, center.y + th / 2 + 5 + 66);
    	line(center.x - tw / 2 - 5, center.y - th / 2 - 5 + 66, center.x - tw / 2 - 10, center.y + th / 2 + 5 + 66);
    	char displayedText[5] = "";
    	if (strlen(M[center.x / 100][center.y / 100].exp) > 3)
    	{
        	displayedText[0] = M[center.x / 100][center.y / 100].exp[0];
        	displayedText[1] = '.';
        	displayedText[2] = '.';
        	displayedText[3] = '\0';
    	}
    	else
        	strcpy(displayedText, M[center.x / 100][center.y / 100].exp);
    	setcolor(WHITE);
    	outtextxy(center.x - textwidth(displayedText) / 2, center.y - textheight(displayedText) / 2 + 66, displayedText);
    	setcolor(YELLOW);
    	circle(center.x, center.y - th / 2 - 5 + 66, 6);
    	circle(center.x, center.y + th / 2 + 5 + 66, 6);
    	setfillstyle(SOLID_FILL,BLACK);
    	floodfill(center.x, center.y - th / 2 - 5 + 66,YELLOW);
    	floodfill(center.x, center.y + th / 2 + 5 + 66,YELLOW);
    	break;
	}
	case binput:
	{
    	settextstyle(8, 0, 1);
    	setbkcolor(BLACK);
    	if (color==BLACK)
        	setcolor(11);
    	else
        	setcolor(color);

    	int tw = textwidth("INPUT");
    	int th = textheight("INPUT");

    	line(center.x-tw/2-10,center.y-th/2-5+66,center.x+tw/2+10,center.y-th/2-5+66);
    	line(center.x+tw/2+10,center.y-th/2-5+66,center.x+tw/2+5,center.y+th/2+5+66);
    	line(center.x+tw/2+5,center.y+th/2+5+66,center.x-tw/2-5,center.y+th/2+5+66);
    	line(center.x-tw/2-10,center.y-th/2-5+66,center.x-tw/2-5,center.y+th/2+5+66);
    	char displayedText[5] = "";
    	if (strlen(M[center.x / 100][center.y / 100].exp) > 3)
    	{
        	displayedText[0] = M[center.x / 100][center.y / 100].exp[0];
        	displayedText[1] = '.';
        	displayedText[2] = '.';
        	displayedText[3] = '\0';
    	}
    	else
        	strcpy(displayedText, M[center.x / 100][center.y / 100].exp);
    	setcolor(WHITE);
    	outtextxy(center.x - textwidth(displayedText) / 2, center.y - textheight(displayedText) / 2 + 66, displayedText);
    	setcolor(YELLOW);
    	circle(center.x, center.y + th / 2 + 71, 6);
    	circle(center.x, center.y - th / 2 + 61, 6);
    	setfillstyle(SOLID_FILL,BLACK);
    	floodfill(center.x, center.y + th / 2 + 71,YELLOW);
    	floodfill(center.x, center.y - th / 2 + 61,YELLOW);
    	break;
	}
	case bdec:
	{
    	settextstyle(8, 0, 1);
    	setbkcolor(BLACK);
    	if (color==BLACK)
        	setcolor(14);
    	else
        	setcolor(color);

    	line(center.x, center.y - textheight("DEC") / 2 - 5 + 66, center.x - textwidth("DEC"), center.y + textheight("DEC") + 5 + 66);
    	line(center.x, center.y - textheight("DEC") / 2 - 5 + 66, center.x + textwidth("DEC"), center.y + textheight("DEC") + 5 + 66);
    	line(center.x - textwidth("DEC") - 5, center.y + textheight("DEC") + 5 + 66, center.x + textwidth("DEC") + 5, center.y + textheight("DEC") + 5 + 66);
    	char displayedText[5] = "";
    	if (strlen(M[center.x / 100][center.y / 100].exp) > 2)
    	{
        	displayedText[0] = M[center.x / 100][center.y / 100].exp[0];
        	displayedText[1] = '.';
        	displayedText[2] = '.';
        	displayedText[3] = '\0';
    	}
    	else
        	strcpy(displayedText, M[center.x / 100][center.y / 100].exp);
    	setcolor(WHITE);
    	outtextxy(center.x - textwidth(displayedText) / 2, center.y + 75 - textheight(displayedText) / 2, displayedText);
    	settextstyle(8, 0, 1);
    	outtextxy(center.x - textwidth("DEC") - textwidth("T") - 4, center.y + textheight("DEC") + 66 - 20, "T");
    	outtextxy(center.x + textwidth("DEC") + 5, center.y + textheight("DEC") + 66 - 20, "F");
    	setcolor(YELLOW);
    	circle(center.x, center.y - textheight("DEC") / 2 + 59, 6);
    	circle(center.x - textwidth("DEC") - 5, center.y + textheight("DEC") + 70, 6);
    	circle(center.x + textwidth("DEC") + 5, center.y + textheight("DEC") + 70, 6);
    	setfillstyle(SOLID_FILL,BLACK);
    	floodfill(center.x, center.y - textheight("DEC") / 2 + 59,YELLOW);
    	floodfill(center.x - textwidth("DEC") - 5, center.y + textheight("DEC") + 70,YELLOW);
    	floodfill(center.x + textwidth("DEC") + 5, center.y + textheight("DEC") + 70,YELLOW);
    	break;
	}
	case empty:
	{
    	setcolor(BLACK);
    	setbkcolor(BLACK);
    	setfillstyle(8,BLACK);
    	if (center.x-50==0 && center.y-50==0)
        	bar(center.x-50+1,center.y-50+66+1,center.x+50,center.y+50+66);
    	else if (center.x-50==0 && center.y+50+66>=WINDOW_HEIGHT-75)
        	bar(center.x-50+1,center.y-50+66,center.x+50,center.y+50+66-22);
    	else if (center.y+50+66>=WINDOW_HEIGHT-75)
        	bar(center.x-50,center.y-50+66,center.x+50,center.y+50+66-22);
    	else if (center.x-50==0)
        	bar(center.x-50+1,center.y-50+66,center.x+50,center.y+50+66);
    	else if (center.y-50==0)
        	bar(center.x-50,center.y-50+66+1,center.x+50,center.y+50+66);
    	else
        	bar(center.x-50,center.y-50+66,center.x+50,center.y+50+66);
	}
	}
}
bool OnIntBlock (int x, int y)
{
	if (x>=startsch.s && x<=startsch.d && y>=startsch.t && y<=startsch.b)
    	return 1;
	if (x>=calculus.s && x<=calculus.d && y>=calculus.t && y<=calculus.b)
    	return 1;
	if (x>=stop.s && x<=stop.d && y>=stop.t && y<=stop.b)
    	return 1;
	if (x>=output.s && x<=output.d && y>=output.t && y<=output.b)
    	return 1;
	if (x>=input.s && x<=input.d && y>=input.t && y<=input.b)
    	return 1;
	if (x>=decision.s && x<=decision.d && y>=decision.t && y<=decision.b)
    	return 1;
	return 0;
}

bool InsideSchem (int x,int y)
{
	if (x>=1 && x<=WINDOW_WIDTH-275 && y>=66 && y<=WINDOW_HEIGHT-120)
    	return 1;
	return 0;
}

void MoveBlock(int x,int y)
{
	clearmouseclick(WM_LBUTTONUP);
	if (M[x][y].type==empty)
    	return;

	Point aux {x,y};
	int n=M[aux.x][aux.y].poz;
	for (int i=1; i<=lgG; i++)
	{
    	if (C[n][i])
        	DrawConnection(n,i,BLACK);
    	if (C[i][n])
        	DrawConnection(i,n,BLACK);
	}
	while (true)
	{
    	Point next=Point {mousex()/100,(mousey()-66)/100};
    	if (M[next.x][next.y].type==empty && InsideSchem(mousex(),mousey()))
    	{
        	if (next.x!=aux.x || next.y!=aux.y)
        	{
            	DrawBlock(M[x][y].type,Point{next.x*100+50,next.y*100+50},BLACK);
            	DrawBlock(empty,Point{aux.x*100+50,aux.y*100+50},BLACK);
            	aux=next;
        	}
    	}
    	if(ismouseclick(WM_LBUTTONUP))
    	{
        	if (!InsideSchem(mousex(),mousey()))
        	{
            	DrawBlock(empty,Point {aux.x*100+50,aux.y*100+50},BLACK);
            	DrawBlock(M[x][y].type,Point{x*100+50,y*100+50},BLACK);
        	}
        	else if (M[next.x][next.y].type==empty && InsideSchem(mousex(),mousey()))
        	{
            	cout<<x<<' '<<y<<'\n';
            	cout<<"a fost miscat blocul "<<M[x][y].poz<<" de la "<<x<<' '<<y<<" la "<<next.x<<' '<<next.y<<'\n';
            	G[M[x][y].poz].poz=Point {next.x,next.y};
            	swap(M[next.x][next.y],M[x][y]);
            	DrawBlock(M[next.x][next.y].type,Point{next.x*100+50,next.y*100+50},BLACK);
            	DrawBlock(empty,Point{x*100+50,y*100+50},BLACK);
        	}
        	clearmouseclick(WM_LBUTTONUP);
        	break;
    	}
	}
}
void OpenBox(char *type,char *str,int text1,int text2)
{
	int x1 = 1014, y1 = 515;
	int x2 = 1265, y2 = 607;

	setfillstyle(SOLID_FILL, BLACK);
	setbkcolor(BLACK);
	bar(x1, y1, x2, y2);
	setcolor(WHITE);
	rectangle(x1, y1, x2, y2);
	outtextxy(x1 + 5, y1 + 5, "Enter data: ");
	char input[105] = "";
	int lineHeight = textheight("A");
	int cursorX = x1 + textwidth("Enter data: ") + 10;
	int cursorY = y1 + 5;
	while (true)
	{
    	char c = getch();
    	if (c == 13)	/// Enter
    	{
        	strcpy(str,input);
        	break;
    	}
    	else if (c == 8)   /// Backspace
    	{
        	if (strlen(input) > 0)
        	{
            	input[strlen(input) - 1] = '\0';
            	setfillstyle(SOLID_FILL, BLACK);
            	bar(x1 + 1, y1 + 1, x2 - 1, y2 - 1);
            	rectangle(x1, y1, x2, y2);
            	outtextxy(x1 + 5, y1 + 5, "Enter data:");
            	cursorX = x1 + textwidth("Enter data: ") + 10;
            	cursorY = y1 + 5;
            	for (int i = 0; i < strlen(input); i++)
            	{
                	char temp[2] = {input[i], '\0'};
                	outtextxy(cursorX, cursorY, temp);
                	cursorX += textwidth(temp);
                	if (cursorX + textwidth("A") >= x2)
                	{
                    	cursorX = x1 + 5;
                    	cursorY += lineHeight;
                    	if (cursorY + lineHeight > y2)
                        	break;
                	}
            	}
        	}
    	}
    	else if (strlen(input) < 100 && isprint(c))   /// Caracter normal
    	{
        	strncat(input, &c, 1);
        	char temp[2] = {c, '\0'};
        	outtextxy(cursorX, cursorY, temp);
        	cursorX += textwidth(temp);
        	if (cursorX + textwidth("A") >= x2)
        	{
            	cursorX = x1 + 5;
            	cursorY += lineHeight;
            	if (cursorY + lineHeight > y2)
                	break;
        	}
    	}
	}
	setfillstyle(SOLID_FILL, BLACK);
	bar(x1, y1, x2, y2);
	setcolor(BLACK);
	rectangle(x1, y1, x2, y2);
	setbkcolor(BLACK);
}

void HandleRightClick(int x, int y)
{
	int poz=WhereMouse(x,y);
	DeleteRightClickMenu();
	switch (poz)
	{
	case IN_SCHEM:
	{
    	if (M[x/100][(y-66)/100].type!=empty)
    	{
        	RClkMenu.stat=true;
        	if (M[x/100][(y-66)/100].type==bdec)
        	{
            	if (x%100>=50)
                	dside=2;
            	else
                	dside=1;
        	}
        	else
            	dside=0;
        	RightClickMenu(x/100,(y-66)/100);
    	}
	}
	}

}

void RightClickMenu (int x, int y)
{
	if (M[x][y].type==empty)
    	return;
	RClkMenu.x=x*100+50;
	RClkMenu.y=y*100+50+66;
	RClkMenu.stat=true;
	setcolor (WHITE);
	setfillstyle(SOLID_FILL,BLACK);
	rectangle (RClkMenu.x,RClkMenu.y,RClkMenu.x+100,RClkMenu.y+75);
	bar (RClkMenu.x+1,RClkMenu.y+1,RClkMenu.x+100-1,RClkMenu.y+75-1);
	settextstyle(8,0,1);
	outtextxy(RClkMenu.x+(100-textwidth("CONNECT"))/2,RClkMenu.y+5,"CONNECT");
	outtextxy(RClkMenu.x+(100-textwidth("DELETE"))/2,RClkMenu.y+28,"DELETE");
	outtextxy(RClkMenu.x+(100-textwidth("EDIT"))/2,RClkMenu.y+53,"EDIT");
	line (RClkMenu.x,RClkMenu.y+25,RClkMenu.x+100,RClkMenu.y+25);
	line(RClkMenu.x, RClkMenu.y + 50, RClkMenu.x + 100, RClkMenu.y + 50);
}

void DeleteRightClickMenu ()
{
	if (!RClkMenu.stat)
    	return;
	int x=(RClkMenu.x-50)/100;
	int y=(RClkMenu.y-66-50)/100;
	setfillstyle(SOLID_FILL,BLACK);
	bar (RClkMenu.x,RClkMenu.y,RClkMenu.x+100+1,RClkMenu.y+75+1); /// curatarea meniului
	DrawBlock(M[x][y].type,Point{x*100+50,y*100+50},BLACK);
	if (x<9)
    	DrawBlock(M[x+1][y].type,Point{x*100+150,y*100+50},BLACK);
	/*if (y==5)
	{
    	DrawGenerateCodeButton();
    	DrawSaveSchemeButton();
    	DrawLoadButtonSchemeButton();
    	DrawEvaluateSchemeButton();
    	DrawClearSchemeButton();
    	setcolor(YELLOW);
    	rectangle (0,0,WINDOW_WIDTH-280,WINDOW_HEIGHT-75);
	}*/
	if (x==9)
	{
    	setcolor(YELLOW);
    	rectangle(0,0,WINDOW_WIDTH-275,WINDOW_HEIGHT-68);
    	setcolor(12);
    	rectangle(1010,4,1270,610);
	}
	RClkMenu.stat=false;
}


bool OnConnect(int x, int y)
{
	if (RClkMenu.stat)
	{
    	if (x>=RClkMenu.x && x<=RClkMenu.x+100 && RClkMenu.y<=y && y<=RClkMenu.y+25)
        	return 1;
	}
	return 0;
}

bool OnDelete(int x, int y)
{
	if (RClkMenu.stat)
	{
    	if (x>=RClkMenu.x && x<=RClkMenu.x+100 && y>RClkMenu.y+25 && y<=RClkMenu.y+50)
    	{
        	return 1;
    	}
	}
	return 0;
}

bool OnEdit(int x,int y)
{
	if(RClkMenu.stat)
	{
    	if(x>=RClkMenu.x && x<=RClkMenu.x+100 && y>=RClkMenu.y + 50 && y<=RClkMenu.y + 75)
        	return true;
	}
	return false;
}

void MakeConnection(int x,int y)
{
	int a=M[Conn.x/100][(Conn.y-66)/100].poz;
	int b=M[x][y].poz;
	if (a==b || G[a].type==bstop || G[b].type==bstart)
    	return;
	if (G[a].type==bdec)
	{
    	if (C[a][b])
        	return;
    	for (int i=1; i<=lgG; i++)
        	if (C[a][i]==dside)
            	return;
    	C[a][b]=dside;
	}
	else
	{
    	for (int i=1; i<=lgG; i++)
        	if (C[a][i]==1)
            	return;
    	C[a][b]=1;
	}
	DrawConnection(a,b,WHITE);
}

void DrawConnection(int a, int b, int color)
{
	setcolor(color);
	Point apoz = Point{G[a].poz.x * 100 + 50, G[a].poz.y * 100 + 50+66}, bpoz = {G[b].poz.x * 100 + 50, G[b].poz.y * 100 + 50+66};
	if (G[a].type==bdec)
	{
    	if(C[a][b]==1)
    	{
        	if (apoz.x==bpoz.x && (bpoz.y-66-50)/100-(apoz.y-66-50)/100==1)
        	{
            	line(apoz.x- textwidth("DEC") - 5,apoz.y+50,apoz.x,apoz.y+50);
        	}
        	else
            	if ((bpoz.y-66-50)/100-(apoz.y-66-50)/100==1 && bpoz.x>apoz.x)
            	{
                	line(apoz.x- textwidth("DEC") - 5,apoz.y+50,bpoz.x,apoz.y+50);
            	}
        	else
        	{
            	line (apoz.x- textwidth("DEC") - 5,apoz.y+50,apoz.x-50,apoz.y+50);
            	line (apoz.x-50,apoz.y+50,apoz.x-50,bpoz.y-50);
            	line (apoz.x-50,bpoz.y-50,bpoz.x,bpoz.y-50);

        	}
    	}
    	else
    	{
        	if (apoz.x==bpoz.x && (bpoz.y-66-50)/100-(apoz.y-66-50)/100==1)
        	{
            	line(apoz.x + textwidth("DEC") + 5,apoz.y+50,apoz.x,apoz.y+50);
        	}
        	else
        	if ((bpoz.y-66-50)/100-(apoz.y-66-50)/100==1 && apoz.x>bpoz.x)
            	{
                	line(apoz.x+ textwidth("DEC") + 5,apoz.y+50,bpoz.x,apoz.y+50);
            	}
        	else
        	{
            	line (apoz.x+ textwidth("DEC") +5,apoz.y+50,bpoz.x-50,apoz.y+50);
            	line (bpoz.x-50,apoz.y+50,bpoz.x-50,bpoz.y-50);
            	line (bpoz.x-50,bpoz.y-50,bpoz.x,bpoz.y-50);
        	}
    	}

	}
	else
	{
    	if (apoz.x==bpoz.x && (bpoz.y-66-50)/100-(apoz.y-66-50)/100==1)
    	{
        	line(apoz.x,apoz.y+50,apoz.x,apoz.y+50);
    	}
    	else
    	{
        	if (apoz.x<bpoz.x)
        	{
            	line (apoz.x,apoz.y+50,bpoz.x-50,apoz.y+50);
            	line (bpoz.x-50,apoz.y+50,bpoz.x-50,bpoz.y-50);
            	line (bpoz.x-50,bpoz.y-50,bpoz.x,bpoz.y-50);
        	}
        	else
        	{
            	line(apoz.x,apoz.y+50,bpoz.x+50,apoz.y+50);
            	line(bpoz.x+50,apoz.y+50,bpoz.x+50,bpoz.y-50);
            	line(bpoz.x+50,bpoz.y-50,bpoz.x,bpoz.y-50);
        	}
    	}
	}
	settextstyle(8,0,2);
	switch (G[a].type)
	{
	case bstart:
	{
    	line (apoz.x,apoz.y + 15,apoz.x,apoz.y+50);
    	break;
	}
	case bcalc:
	{
    	line (apoz.x,apoz.y+textheight("CALCULUS")/2+5,apoz.x,apoz.y+50);
    	break;
	}
	case binput:
	{
    	line (apoz.x,apoz.y+textheight("INPUT")/2+5,apoz.x,apoz.y+50);
    	break;
	}
	case boutput:
	{
    	line (apoz.x,apoz.y+textheight("OUTPUT")/2+5,apoz.x,apoz.y+50);
    	break;
	}
	case bdec:
	{
    	settextstyle(8,0,1);
    	if (C[a][b]==1)
        	line(apoz.x- textwidth("DEC") - 5, apoz.y + textheight("DEC") + 5,apoz.x- textwidth("DEC") - 5,apoz.y+50);
    	else
        	line(apoz.x + textwidth("DEC") + 5, apoz.y + textheight("DEC") + 5,apoz.x + textwidth("DEC") + 5,apoz.y+50);
    	break;
	}
	default:
    	break;
	}
	switch (G[b].type)
	{
	case bstop:
	{
    	line(bpoz.x,bpoz.y - textheight("STOP") / 2 - 5,bpoz.x,bpoz.y-50);
    	break;
	}
	case bcalc:
	{
    	line(bpoz.x,bpoz.y-textheight("CALCULUS")/2-5,bpoz.x,bpoz.y-50);
    	break;
	}
	case boutput:
	{
    	line(bpoz.x,bpoz.y-textheight("OUTPUT")/2-5,bpoz.x,bpoz.y-50);
    	break;
	}
	case binput:
	{
    	line(bpoz.x,bpoz.y-textheight("INPUT")/2-5,bpoz.x,bpoz.y-50);
    	break;
	}
	case bdec:
	{
    	settextstyle(8,0,1);
    	line (bpoz.x,bpoz.y-textheight("DEC")/2-5,bpoz.x,bpoz.y-50);
    	break;
	}
	default:
    	break;
	}

}
bool IsValidExpresion(char *type, char *exp)
{
	if(!strcmp("CALCULUS",type))
    	return IsValidCalculus(exp);
	if(!strcmp("INPUT",type))
    	return IsValidInput(exp);
	if(!strcmp("OUTPUT",type))
    	return IsValidOutput(exp);
	if(!strcmp("DECISION",type))
    	return IsValidDecision(exp);
	return false;
}
bool IsValidCalculus(char *exp)
{
	if (strlen(exp) == 0)
    	return false;
	bool lastWasOperator = true;
	bool lastWasOperand = false;
	bool hasOperand = false;
	int x = strlen(exp);
	int i;
	for (i = 0; i < x; ++i)
	{
    	char c = exp[i];

    	if (isalpha(c))
        	continue;
    	else if (c == '=')
    	{
        	if (i != 1)
            	return false;
        	++i;
        	break;
    	}
    	else
        	return false;
	}

	if (i >= x)
    	return false;

	for (int j = i; j < x; ++j)
	{
    	char c = exp[j];

    	if (isdigit(c) || isalpha(c))
    	{
        	hasOperand = true;
        	lastWasOperator = false;
        	lastWasOperand = true;
    	}
    	else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%')
    	{
        	if (lastWasOperator)
            	return false;
        	lastWasOperator = true;
        	lastWasOperand = false;
    	}
    	else
        	return false;
	}

	if (lastWasOperator)
    	return false;

	return hasOperand;
}

bool IsValidInput(char *exp)
{
	if (strlen(exp) != 1)
    	return false;
	char c = exp[0];
	if (isalpha(c))
    	return true;
	return false;
}
bool IsValidOutput(char *exp)
{
	if (strlen(exp) != 1)
    	return false;
	char c = exp[0];
	if (isalpha(c))
    	return true;
	return false;
}
bool IsValidDecision(char *exp)
{
	if (strlen(exp) == 0)
    	return false;
	bool lastWasOperator = true;
	bool hasOperand = false;
	int x = strlen(exp);
	for (int i = 0; i < x; ++i)
	{
    	char c = exp[i];
    	if (isspace(c))
        	return false;
    	if (isalpha(c))
    	{
        	if (i + 1 < x && isalnum(exp[i + 1]))
            	return false;
        	hasOperand = true;
        	lastWasOperator = false;
    	}
    	else if (isdigit(c))
    	{
        	hasOperand = true;
        	lastWasOperator = false;
        	while (i + 1 < x && isdigit(exp[i + 1]))
            	i++;
    	}
    	else if (c == '<' || c == '>' || c == '=' || c == '!')
    	{
        	if (i + 1 < x && exp[i + 1] == '=')
            	i++;
        	if (lastWasOperator)
            	return false;
        	lastWasOperator = true;
    	}
    	else
        	return false;
	}
	if (lastWasOperator)
    	return false;

	return hasOperand;
}
void ReDrawConnections()
{
	int aux=dside;
	for (int i=1; i<=lgG; i++)
	{
    	for (int j=1; j<=lgG; j++)
    	{
        	if (C[i][j])
        	{
            	if (G[i].type==bdec)
                	dside=C[i][j];
            	else
                	dside=0;
            	DrawConnection(i,j,WHITE);
        	}
    	}
	}
	dside=aux;
}
void DeleteBlock(int x,int y)
{
	cout<<"Matricea conexiunilor inainte:\n";
	for (int i=1; i<=lgG; i++,cout<<'\n')
    	for(int j=1; j<=lgG; j++)
        	cout<<C[i][j]<<' ';
	cout<<'\n';
	int n=M[x][y].poz;
	cout<<"Blockul sters este:"<<n<<'\n';
	for (int i=1; i<=lgG; i++)
	{
    	if (C[n][i]){
        	DrawConnection(n,i,BLACK);	/// conexiunea iesire
    	}
    	if (C[i][n]){
        	DrawConnection(i,n,BLACK); 	/// conexiunea intrare
    	}
    	C[n][i]=C[i][n]=0;
	}
	for (int i=1; i<=lgG; i++)
	{
    	for (int j=n; j<lgG; j++)
    	{
        	swap(C[i][j],C[i][j+1]);
    	}
	}
	for (int j=1; j<=lgG; j++)
	{
    	for (int i=n; i<lgG; i++)
    	{
        	swap(C[i][j],C[i+1][j]);
    	}
	}

	for (int i=n; i<lgG; i++)
    	swap(G[i],G[i+1]);
	G[lgG].type=empty;
	G[lgG].poz= {-1,-1};
	lgG--;
	M[x][y].type=empty;
	M[x][y].poz=-1;

	for (int i=1; i<=lgG; i++)
	{
    	M[G[i].poz.x][G[i].poz.y].type=G[i].type;
    	M[G[i].poz.x][G[i].poz.y].poz=i;
	}

	cout<<"Numar elemente:"<<lgG<<'\n';

	DrawBlock(empty,Point{x*100+50,y*100+50},BLACK);

	cout<<"Matricea conexiunilor dupa:\n";
	for (int i=1; i<=lgG; i++,cout<<'\n')
    	for(int j=1; j<=lgG; j++)
        	cout<<C[i][j]<<' ';
	cout<<'\n';
}

bool OnGenerate(int x,int y)
{
	if (20<=x && x<=130 && y>=720 && y<=770)
    	return 1;
	return 0;
}

void Generate()
{
	int curb=1;

	setbkcolor(BLACK);

	fout.open("code.txt", std::ofstream::trunc);

	int x=CheckSchem();
	switch(x)
	{
	case NO_START:
	{
    	fout<<"Schema nu are block de start\n";
    	break;
	}
	case NO_STOP:
	{
    	fout<<"Schema nu are destule blockuri\nde tip stop";
    	break;
	}
	default:
    	break;
	}
	if (x!=CORECT)
	{
    	fout.close();
    	PrintCode();
	}
	else
	{
    	fout<<"#include <iostream>\n";
    	fout<<"\n";
    	fout<<"using namespace std;\n";
    	fout<<"\n";
    	fout<<"int main()\n";
    	fout<<"{\n";
    	for(; curb<=lgG && G[curb].type!=bstart; curb++);
    	Code(curb,1,1,-1);
    	for(int i=0; i<4; i++)
        	fout<<" ";
    	fout<<"return 0;\n";
    	fout<<"}";
    	fout.close();
    	PrintCode();
	}
}

int CheckSchem()
{
	bool kstart=0,kstop=0,ok=0;
	for (int i=1; i<=lgG; i++)
	{
    	if (G[i].type==bstart)
        	kstart=1;
    	else if (G[i].type==bstop)
        	kstop=1;
	}
	if (kstart==0)
    	return NO_START;
	if (kstop==0)
    	return NO_STOP;
	for (int i=1;i<=lgG;i++)
	{
    	if (G[i].type!=bstop && uz[i]==0)
    	{
    	    uz[i]=1;
        	if (Capat(i)==0)
            	return NO_STOP;
    	}
	}
	return CORECT;
}

void Code (int curb,int h,int side,int loop)
{
	int nextb,auxb;
	setbkcolor(BLACK);


	for (nextb=1; C[curb][nextb]!=side && nextb<=lgG; nextb++);
	if (nextb>lgG)
    	return;
	if (loop>-1)
	{
    	auxb=curb;
    	C[loop][curb]=0;
	}
	curb=nextb;

	if (G[curb].type==bstop)
    	return;
	for (int i=0; i<h; i++)
    	for (int j=0; j<4; j++)
        	fout<<" ";


	switch (G[curb].type)
	{
	case binput:
	{
    	fout<<"cin>>"<<M[G[curb].poz.x][G[curb].poz.y].exp<<";\n";
    	break;
	}
	case boutput:
	{
    	fout<<"cout<<"<<M[G[curb].poz.x][G[curb].poz.y].exp<<";\n";
    	break;
	}
	case bcalc:
	{
    	fout<<M[G[curb].poz.x][G[curb].poz.y].exp<<";\n";
    	break;
	}
	case bdec:
	{
    	int loopend;
    	int loopside=DetectLoop(curb,loopend);

    	if (loopside>-1)
    	{
        	if (loopside==1)
        	{
            	fout << "while(" << M[G[curb].poz.x][G[curb].poz.y].exp << ")\n";
            	for (int i=0; i<h; i++)
                	for (int j=0; j<4; j++)
                    	fout<<" ";
            	fout<<"{\n";
            	Code(curb,h+1,loopside,loopend);
            	for (int i = 0; i < h; i++)
                	for (int j = 0; j < 4; j++)
                    	fout << " ";
            	fout << "}\n";
            	Code(curb,h,3-loopside,-1);
        	}
        	else
        	{
            	fout << "while(!(" << M[G[curb].poz.x][G[curb].poz.y].exp << "))\n";
            	for (int i=0; i<h; i++)
                	for (int j=0; j<4; j++)
                    	fout<<" ";
            	fout<<"{\n";
            	Code(curb,h+1,loopside,loopend);
            	for (int i = 0; i < h; i++)
                	for (int j = 0; j < 4; j++)
                    	fout << " ";
            	fout << "}\n";
            	Code(curb,h,3-loopside,-1);
        	}
    	}
    	else
    	{
        	int i;
        	for(i=1; i<=lgG && C[curb][i]!=1; i++);
        	if(i>lgG)
            	fout << "if(" << M[G[curb].poz.x][G[curb].poz.y].exp << "){}\n";
        	else
        	{
            	fout << "if(" << M[G[curb].poz.x][G[curb].poz.y].exp << ")\n";
            	for (int i=0; i<h; i++)
                	for (int j=0; j<4; j++)
                    	fout<<" ";
            	fout<<"{\n";
            	Code(curb,h+1,1,-1);
            	for(i = 0; i < h; i ++)
                	for(int j = 0; j < 4; j ++)
                    	fout<<" ";
            	fout<<"}\n";
        	}
        	for (int i=0; i<h; i++)
            	for (int j=0; j<4; j++)
                	fout<<" ";
        	for (i=1; i<=lgG && C[curb][i]!=2; i++);
        	if (i>lgG)
            	fout<<"else{}\n";
        	else
        	{
            	fout<<"else\n";
            	for (int i=0; i<h; i++)
                	for (int j=0; j<4; j++)
                    	fout<<" ";
            	fout<<"{\n";
            	Code(curb,h+1,2,-1);
            	for(i = 0; i < h; i ++)
                	for(int j = 0; j < 4; j ++)
                    	fout<<" ";
            	fout<<"}\n";
        	}
    	}
	}
	default:
    	break;
	}
	if (G[curb].type!=bdec)
    	Code(curb,h,1,-1);
	if (loop>-1)
	{
    	C[loop][auxb]=side;
	}
}

int DetectLoop (int start, int &loopend)
{
	int v[1050],side[1050];
	int st=0,dr=-1;
	for(int i = 1; i <=lgG; i ++)
    	if(C[start][i])
    	{
        	dr++;
        	v[dr] = i;
        	side[i] = C[start][i];
    	}
	while(st <= dr)
	{
    	int aux = v[st];
    	st++;
    	for(int i = 1; i <=lgG; i ++)
        	if(C[aux][i])
        	{
            	side[i] = side[aux];
            	if(i == start)
            	{
                	loopend = aux;
                	cntloop++;
                	return side[aux];
            	}
            	dr++;
            	v[dr] = i;
        	}
	}
	return -1;
}

void PrintCode()
{
	setbkcolor(BLACK);
	setcolor(BLACK);
	setfillstyle(SOLID_FILL,BLACK);
	bar(1011,5,1269,609);
	fin.open("code.txt");
	int line=0,curline=0;
	char sir[256];

	setcolor(WHITE);
	settextstyle(SANS_SERIF_FONT, 0, 1);

	while(fin.getline(sir, 256))
	{
    	if(line == 28)
    	{
        	curline ++;
    	}
    	else
    	{
        	outtextxy(1020, 24 + line * 20, sir);
        	line ++;
    	}
	}
	if(curline)
	{
    	lincur = 0,liniiMaxEval = line - 28 + curline;
    	DrawScrollButtons(WHITE);
    	scrollable=1;
	}
	else
	{

    	lincur = liniiMaxEval = 0;
    	DrawScrollButtons(BLACK);
	}
	fin.close();

}

void HandleSave()
{
	setbkcolor(BLACK);

	setcolor(BLACK);
	setfillstyle(SOLID_FILL,BLACK);
	bar(1011,5,1269,609);

	char nume[100];
	int i;
	bool result = InputSchem(nume);
	if(!result)
	{
    	setcolor(BLACK);
    	setfillstyle(SOLID_FILL, BLACK);
    	bar(1011,5,1269,609);
    	return;
	}
	strcat(nume, ".sch");
	fout.open(nume, std::ofstream::trunc);
	fout<<lgG<<'\n';
	for(i = 1; i <=lgG; i ++)
	{
    	fout << G[i].poz.x << ' ' << G[i].poz.y << ' ' << G[i].type << '\n';
    	switch(G[i].type)
    	{
    	case bstart:
    	case bstop:
    	case empty:
    	{
        	break;
    	}
    	case binput:
    	case boutput:
    	case bdec:
    	case bcalc:
    	{
        	fout << M[G[i].poz.x][G[i].poz.y].exp << '\n';
        	break;
    	}
    	default:
        	break;
    	}
    	fout << '\n';
	}

	for(i=1; i<=lgG; i++)
	{
    	for (int j=1; j<=lgG; j++)
        	fout<<C[i][j]<<' ';
    	fout<<'\n';
	}
	fout.close();

	/*setcolor(WHITE);
	setfillstyle(SOLID_FILL, WHITE);
	rectangle(1060, 380, 1240, 400);
	for(i = 0; i < 10; i ++)
	{
    	bar(1060, 380, 1060 + i * 20, 400);
    	delay(300);
	}*/
	bar(1011,5,1269,609);
	outtextxy(1015, 530,"Schema salvata cu succes");
}

void HandleLoad()
{
	setbkcolor(BLACK);
	setcolor(BLACK);
	setfillstyle(SOLID_FILL,BLACK);
	bar(1011,5,1269,609);

	char nume[100];
	int i;
	bool result = InputSchem(nume);
	if(!result)
	{
    	setcolor(BLACK);
    	setfillstyle(SOLID_FILL, BLACK);
    	bar(1011,5,1269,609);
    	return;
	}
	strcat(nume, ".sch");

	fin.open(nume);
	if(!fin.good())
	{
    	ClearSchem();
    	setcolor(WHITE);
    	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    	outtextxy(1015, 530, (char*)"Schema nu a putut fi gasita");
    	fin.close();
    	return;
	}

	/*setcolor(WHITE);
	setfillstyle(SOLID_FILL, WHITE);
	rectangle(1060, 380, 1240, 400);
	for(i = 0; i < 10; i ++)
	{
    	bar(1060, 380, 1060 + i * 20, 400);
    	delay(300);
	}*/

	ClearSchem();

	fin>>lgG;
	for(i =1; i<=lgG; i++)
	{
    	fin>>G[i].poz.x>>G[i].poz.y;
    	int bt;
    	fin>>bt;
    	G[i].type = (BlockType)bt;
    	switch(G[i].type)
    	{
    	case bstart:
    	case bstop:
    	case empty:
    	{
        	break;
    	}
    	case binput:
    	case boutput:
    	case bdec:
    	case bcalc:
    	{
        	fin >> M[G[i].poz.x][G[i].poz.y].exp;
        	break;
    	}
    	}
    	M[G[i].poz.x][G[i].poz.y].poz = i;
    	M[G[i].poz.x][G[i].poz.y].type = G[i].type;
    	DrawBlock(G[i].type, Point{G[i].poz.x * 100 + 50, G[i].poz.y * 100 + 50},BLACK);
	}

	for(i=1; i<=lgG; i++)
    	for(int j = 1; j <=lgG; j++)
        	fin >> C[i][j];
	ReDrawConnections();
	fin.close();

	setcolor(WHITE);
	settextstyle(SANS_SERIF_FONT,0, 1);
	outtextxy(1015, 530, (char*)"Schema incarcata cu succes");
}

bool InputSchem(char nume[])
{
	setcolor(BLACK);
	setfillstyle(SOLID_FILL,BLACK);
	bar(1011,5,1269,609);

	setcolor(WHITE);
	settextstyle(SANS_SERIF_FONT, 0, 1);
	outtextxy(1015, 530, (char*)"Introduceti numele schemei");
	outtextxy(1015, 560, (char*)"(maxim 20 caractere)");

	for (; kbhit(); getch());
	strcpy(nume,"\0");
	int i;
	for(i=0;; i++)
	{
    	nume[i] = 0;

    	setcolor(WHITE);
    	outtextxy(1015, 590, nume);

    	char c = getch();
    	if(c == (char)13)
        	break;
    	if(c == (char)27)
        	return false;
    	if(c == (char)8)
    	{
        	if (i)
        	{
            	setcolor(BLACK);
            	setfillstyle(SOLID_FILL, BLACK);
            	bar(1015 + (i - 1) * 5, 590, 1110 + i * 10, 610);
            	nume[--i] = 0;
        	}
        	i--;
    	}
    	else
    	{
        	if (i<20)
        	{
            	if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')))
            	{
                	i--;
                	continue;
            	}
            	else
                	nume[i] = c;
        	}
        	else
            	i--;
    	}
	}
	return true;

}

void ClearSchem()
{
	setcolor(BLACK);
	setfillstyle(SOLID_FILL,BLACK);
	bar(1011,5,1269,610);
	bar(1,66,WINDOW_WIDTH-276,WINDOW_HEIGHT-69);

	for(int i=1; i<=lgG; i++)
    	for (int j=1; j<=lgG; j++)
        	C[i][j]=0;

	for (int i=0; i<=8; i++)
    	for (int j=0; j<=5; j++)
    	{
        	M[i][j].poz=-1;
        	M[i][j].type=empty;
        	strcpy(M[i][j].exp,"\0");
    	}

	for (int i=1; i<=lgG; i++)
	{
    	G[i].poz= {-1,-1};
    	G[i].type=empty;
	}

	for (int i=1;i<=98;i++)
        uz[i]=0;

	lgG=0;
	DrawScrollButtons(BLACK);
	scrollable=0;
}

void DrawDelay()
{
    settextstyle(8, 0, 1);
    setcolor(WHITE);
    int x=textwidth("DELAY");
    outtextxy(897,720,"DELAY");
    int h=textheight("DELAY");
    rectangle(830+65,720+h+5,830+65+27,720+h+5+27);
    rectangle(830+65+27+5,720+h+5,830+65+27+27+5,720+h+5+27);

    setfillstyle(SOLID_FILL,WHITE);
    bar(830+1+65+5,720+h+5+13,830+65+27-5,720+h+5+15);
    bar(830+1+65+27+5+5,720+h+5+13,830+65+27+5+27-5,720+h+5+15);
    bar(830+65+27+5+13,720+h+5+5,830+65+27+5+15,720+h+5+27-5);

    for (int i=0;i<5;i++)
    {
        rectangle(830+65+27+27+10,721+10*i,830+65+27+27+50,721+10*i+8);
    }

    setfillstyle(SOLID_FILL,BLUE);
    bar(830+65+27+27+10+1,721+10*4+1,830+65+27+27+50-1,721+10*4+8-1);
}

bool OnClear (int x,int y)
{
	if (x>=720 && x<=830 && y>=720 && y<=770)
    	return 1;
	return 0;
}

bool OnSave (int x, int y)
{
	if (x>=195 && x<=305 && y>=720 && y<=770)
    	return 1;
	return 0;
}

bool OnLoad (int x,int y)
{
	if (x>=370 && x<=480 && y>=720 && y<=770)
    	return 1;
	return 0;
}

void Evaluate()
{
	setcolor(BLACK);
	setfillstyle(SOLID_FILL,BLACK);
	bar(1011,5,1269,609);

    int mx=mousex();
    int my=mousey();


	setcolor(WHITE);
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
	fout.open("schem.txt", std::ofstream::trunc);

	int x=CheckSchem();
	switch(x)
	{
	case NO_START:
	{
    	fout<<"Schema nu are block de start\n";
    	break;
	}
	case NO_STOP:
	{
    	fout<<"Schema nu are block de stop\n";
    	break;
	}
	default:
    	break;
	}
	if (x!=CORECT)
	{
    	fout.close();
    	PrintEval();
    	return;
	}

	int curb=0,curl=0;

	for (curb=1; curb<=lgG && G[curb].type!=bstart; curb++);


	while(true)
	{

	    if (ismouseclick(WM_LBUTTONDOWN))
        {
            int mx=mousex();
            int my=mousey();

            if (PDelay(mx,my))
                Delayop(1);
            else
                if (MDelay(mx,my))
                    Delayop(2);
            clearmouseclick(WM_LBUTTONDOWN);
        }

    	DrawBlock(G[curb].type, {G[curb].poz.x*100+50,G[curb].poz.y*100+50},RED);
    	delay(del);

    	bool isdec=0;

    	if(G[curb].type == bstop)
    	{
        	DrawBlock(G[curb].type, Point{G[curb].poz.x * 100 + 50, G[curb].poz.y * 100 + 50},BLACK);
        	break;
    	}

    	switch (G[curb].type)
    	{
    	case bstart:
    	case bstop:
    	case empty:
    	{
        	break;
    	}
    	case binput:
    	{
        	int i=0;
        	char text[64], val[30], valc;
        	strcpy(text, "Introduceti variabila:");
        	strcat(text, M[G[curb].poz.x][G[curb].poz.y].exp);

        	setcolor(WHITE);
        	settextstyle(SANS_SERIF_FONT,0, 1);
        	outtextxy(1015, 530, text);

        	for(; kbhit(); getch());
        	while(true)
        	{
            	valc = getch();
            	if(valc == (char)8)
            	{
                	setcolor(BLACK);
                	setfillstyle(SOLID_FILL, BLACK);
                	bar(1015, 550, 1300, 570);
                	if(i)
                    	val[--i] = 0;
            	}
            	else
            	{
                	if (valc == (char) 13)
                    	break;
                	if ((valc < '0' || valc > '9' || val[0] == '0') && valc != '-')
                    	continue;
                	val[i++] = valc;
                	val[i] = 0;
            	}
            	setcolor(WHITE);
            	outtextxy(1015, 550, val);
        	}
        	valori[M[G[curb].poz.x][G[curb].poz.y].exp[0] - 'a'] = atoll(val);
        	fout<<"Variabila "<<M[G[curb].poz.x][G[curb].poz.y].exp<<" ia valoarea "<<val<<'\n';
        	break;
    	}
    	case bdec:
    	{
        	bool valoare = evalExp(M[G[curb].poz.x][G[curb].poz.y].exp);
        	isdec = true;
        	setcolor(WHITE);
        	settextstyle(SANS_SERIF_FONT,0, 1);
        	if(valoare)
        	{
            	outtextxy(1015, 530, "Expresia este adevarata");
                fout<<"Expresia este adevarata\n";
            	for(int i=1; i<=lgG; i++)
                	if(C[curb][i] == 1)
                	{
                    	dside=1;
                    	DrawBlock(G[curb].type, Point{G[curb].poz.x * 100 + 50, G[curb].poz.y * 100 + 50},BLACK);
                    	delay(del);
                    	DrawConnection(curb, i, RED);
                    	delay(del);
                    	DrawConnection(curb, i, WHITE);
                    	curb = i;
                    	break;
                	}
        	}
        	else
        	{
            	outtextxy(1015, 530, "Expresia este falsa");
                fout<<"Expresia este falsa\n";
            	for(int i=1; i<=lgG; i++)
                	if(C[curb][i] == 2)
                	{
                    	dside=2;
                    	DrawBlock(G[curb].type, Point{G[curb].poz.x * 100 + 50, G[curb].poz.y * 100 + 50},BLACK);
                    	delay(del);
                    	DrawConnection(curb, i, RED);
                    	delay(del);
                    	DrawConnection(curb, i, WHITE);
                    	curb = i;
                    	break;
                	}
        	}
        	break;
    	}
    	case bcalc:
    	{
        	int poz = 0;
        	long long int valoare = exp(poz, M[G[curb].poz.x][G[curb].poz.y].exp + 2);
        	char expCur[200], text[64], aux[64];
        	valori[M[G[curb].poz.x][G[curb].poz.y].exp[0]-'a']=valoare;
        	poz = 0;

        	strcpy(text, "Variabila ");
        	text[10] = M[G[curb].poz.x][G[curb].poz.y].exp[0];
        	text[11] = 0;
        	strcat(text, " ia valoarea ");
        	setcolor(WHITE);
        	settextstyle(SANS_SERIF_FONT,0, 1);
        	transformare(valoare, aux);
        	strcat(text, aux);
        	outtextxy(1015,530, text);
        	fout<<"Variabila "<<M[G[curb].poz.x][G[curb].poz.y].exp[0]<<" ia valoarea "<<aux<<'\n';
        	break;
    	}
    	case boutput:
    	{
        	char text[64], aux[64];
        	int poz = 0;
        	text[0] = M[G[curb].poz.x][G[curb].poz.y].exp[0];
        	text[1] = 0;
        	strcat(text, " = ");
        	setcolor(WHITE);
        	settextstyle(SANS_SERIF_FONT,0, 1);
        	transformare(valori[M[G[curb].poz.x][G[curb].poz.y].exp[0]-'a'],aux);
        	strcat(text, aux);
        	outtextxy(1015,530, text);
        	fout<<text;
        	break;
    	}
    	default:
        	break;
    	}

    	if(!isdec)
        for(int i=1; i<=lgG; i++)
            if(C[curb][i])
            {
                DrawBlock(G[curb].type, Point{G[curb].poz.x * 100 + 50, G[curb].poz.y * 100 + 50},BLACK);
                delay(del);

                if (ismouseclick(WM_LBUTTONDOWN))
                {
                    int mx=mousex();
                    int my=mousey();

                    if (PDelay(mx,my))
                        Delayop(1);
                    else if (MDelay(mx,my))
                        Delayop(2);
                    clearmouseclick(WM_LBUTTONDOWN);
                }

                DrawConnection(curb,i,RED);
                delay(del);

                if (ismouseclick(WM_LBUTTONDOWN))
                {
                    int mx=mousex();
                    int my=mousey();

                    if (PDelay(mx,my))
                        Delayop(1);
                    else if (MDelay(mx,my))
                        Delayop(2);
                    clearmouseclick(WM_LBUTTONDOWN);
                }
                DrawConnection(curb,i,WHITE);
                delay(del);
                curb=i;
                break;
            }
    	setfillstyle(SOLID_FILL,BLACK);
    	bar(1011,5,1269,610);
	}
	fout.close();
    PrintEval();
}

//transforma numarul x in sir de caractere
void transformare(long long int x, char text[])
{
	if(x==0)
	{
    	text[0]='0';
    	text[1]=NULL;
    	return;
	}
	long long int aux, pow = 1, lgt = 0;
	if(x < 0)
	{
    	text[lgt++] = '-';
    	x *= -1;
	}
	aux = x;
	while(aux)
	{
    	aux /= 10;
    	pow *= 10;
	}
	pow /= 10;
	while(pow)
	{
    	text[lgt ++] = ((x / pow) % 10)  + '0';
    	pow /= 10;
	}
	text[lgt] = 0;
}

//evalueaza rezultatul unei comparatii intre expresii
int evalExp(char s[])
{
	int poz1 = 0, poz2 = 0, lgsS = strlen(s);
	char *p, aux[200];
	strcpy(aux, s);
	p = strtok(aux, "!");
	if (strlen(p) != lgsS)
    	return (exp(poz1, p) != exp(poz2, p + strlen(p) + 2));
	p = strtok(aux, ">");
	if (strlen(p) != lgsS)
	{
    	if (*(p + strlen(p) + 1) == '=')
        	return (exp(poz1, p) >= exp(poz2, p + strlen(p) + 2));
    	else
        	return (exp(poz1, p) > exp(poz2, p + strlen(p) + 1));
	}
	p = strtok(aux, "<");
	if (strlen(p) != lgsS)
	{
    	if (*(p + strlen(p) + 1) == '=')
        	return (exp(poz1, p) <= exp(poz2, p + strlen(p) + 2));
    	else
        	return (exp(poz1, p) < exp(poz2, p + strlen(p) + 1));
	}
	p = strtok(aux, "=");
	if (strlen(p) != lgsS)
    	return (exp(poz1, p) == exp(poz2, p + strlen(p) + 2));
	return 0;
}

//calculeaza valoarea unei expresii
long long int exp(int &poz, char s[])
{
	long long int t1 = 1, t2;
	if(poz == 0 && s[0] == '-')
    	poz++, t1 *= -1;
	t1 *= termen(poz, s);
	char op;
	while (s[poz] == '+' || s[poz] == '-')
    	op = s[poz++], t2 = termen(poz, s), op == '+' ? t1 += t2 : t1 -= t2;
	return t1;
}

//calculeaza un termen (variabile si constante ce contin intre ele doar simbolurile * / %
long long int termen(int &poz, char s[])
{
	long long int t1 = factor(poz, s), t2;
	char op;
	while (s[poz] == '*' || s[poz] == '/' || s[poz] == '%')
    	op = s[poz++], t2 = factor(poz, s), op == '*' ? t1 *= t2 : op == '/' ? t1 /= t2 : t1 %= t2;
	return t1;
}

//returneaza rezultatul unei subexpresii (in cazul in care aceasta incepe cu "(" ), o constanta sau valoarea unei variabile
long long int factor(int &poz, char s[])
{
	long long int t;
	if (s[poz] == '(')
	{
    	poz++, t = exp(poz, s), poz++;
    	return t;
	}
	if (s[poz] >= '0'&&s[poz] <= '9')
	{
    	t=(s[poz]-'0');
    	poz++;
    	while(s[poz] >= '0' && s[poz] <= '9')
        	t=t*10+(s[poz]-'0'), poz++;
    	return t;
	}
	t = valori[s[poz] - 'a'];
	poz++;
	return t;
}

bool OnEval(int x, int y)
{
	if (x>=545 && x<=655 && y>=720 && y<=770)
    	return 1;
	return 0;
}


void PrintEval()
{
	setbkcolor(BLACK);
	setcolor(WHITE);
	setfillstyle(SOLID_FILL,BLACK);
	bar(1011,5,1269,609);
	fin.open("schem.txt");
	int line=0,curline=0;
	char sir[256];

	setcolor(WHITE);
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);

	while(fin.getline(sir, 256))
	{
    	if(line == 28)
    	{
        	curline ++;
        	line --;
    	}
    	else
        	outtextxy(1020, 24 + line * 20, sir);
    	line ++;
	}
	if(curline)
    {
    	lincur = 0;
    	liniiMaxEval = line - 28 + curline;
        DrawScrollButtons(WHITE);
        scrollable=2;
    }
	else
	{

    	lincur = liniiMaxEval = 0;
    	DrawScrollButtons(BLACK);
	}
	fin.close();
}

bool OnScrUp (int x,int y)
{
	if (scrollable)
	{
    	if (x>=WINDOW_WIDTH-276-5-30 && y>=5 && x<=WINDOW_WIDTH-276-5 && y<=30)
        	return 1;
    	else
        	return 0;
	}
	return 0;
}

bool OnScrD (int x, int y)
{
	if (scrollable)
	{
    	if (x>=WINDOW_WIDTH-276-5-30 && y>=35 && x<=WINDOW_WIDTH-276-5 && y<=60)
        	return 1;
    	else
        	return 0;
	}
	return 0;
}


void ScrollDown ()
{
	if(!scrollable)
    	return;
	int linenr=0;
	char text[1000];
	setcolor(WHITE);
	if (scrollable==1)
        fin.open("code.txt", fstream::in);
    else
        fin.open("schem.txt", fstream::in);
	settextstyle(SANS_SERIF_FONT, 0, 1);

	if(lincur<liniiMaxEval)
	{
    	setfillstyle(SOLID_FILL,BLACK);
    	bar(1011,5,1269,610);
    	lincur++;
    	for(int i=0; i<lincur; fin.getline(text,1000),i++);

    	for(int i=0; i<28; i++)
    	{
        	fin.getline(text,1000);
        	outtextxy(1020,24+20 * (linenr ++), text);
    	}
	}
	fin.close();
}

void ScrollUp()
{
	if(!scrollable)
    	return;
	int linenr=0;
	char text[1000];
	setcolor(WHITE);
	if (scrollable==1)
        fin.open("code.txt", fstream::in);
    else
        fin.open("schem.txt", fstream::in);
	settextstyle(SANS_SERIF_FONT, 0, 1);

	if(lincur>0)
	{
    	setfillstyle(SOLID_FILL,BLACK);
    	bar(1011,5,1269,610);
    	lincur--;
    	for(int i=0; i<lincur; fin.getline(text,1000),i++);

    	for(int i=0; i<28; i++)
    	{
        	fin.getline(text,1000);
        	outtextxy(1020,24+20 * (linenr ++), text);
    	}
	}
	fin.close();
}

void ClearScreen(int x,int y)
{
	if (!(OnScrD(x,y) || OnScrUp(x,y)))
	{
    	setfillstyle(SOLID_FILL,BLACK);
    	bar(1011,5,1269,609);
    	DrawScrollButtons(BLACK);
    	scrollable=0;
	}
}

bool Capat(int i)
{
	int j=1;
	for (j=1;j<=lgG;j++)
    	if (C[i][j]!=0)
        	break;
	if (j>lgG)
    	return 0;
	if (uz[j]==1 || G[j].type==bstop)
    	return 1;
    uz[j]=1;
	return Capat(j);
	uz[j]=0;
}

bool PDelay(int x,int y)
{
    settextstyle(8,0,1);
    int h=textheight("DELAY");

    if(x>=(830+65+27+5) && y>=(720+h+5) && x<=(830+65+27+27+5) && y<=(720+h+5+27))
        return 1;
    return 0;
}

bool MDelay (int x,int y)
{
    settextstyle(8,0,1);
    int h=textheight("DELAY");
    if (x>=(830+65) && y>=(720+h+5) && x<=(830+65+27) && y<=(720+h+5+27))
        return 1;
    return 0;
}

void Delayop(int n)
{
    int i;
    if (n==1 && del<1000)
    {
        del=del+200;
        i=5-(del/200);

        setfillstyle(SOLID_FILL,BLUE);
        bar(830+65+27+27+10+1,721+10*i+1,830+65+27+27+50-1,721+10*i+8-1);
    }
    else
        if (n==2 && del>200)
        {
            i=5-(del/200);
            del=del-200;

            setfillstyle(SOLID_FILL,BLACK);
            bar(830+65+27+27+10+1,721+10*i+1,830+65+27+27+50-1,721+10*i+8-1);
        }
}




