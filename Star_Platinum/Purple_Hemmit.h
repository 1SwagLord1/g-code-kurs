//
// Created by Алексей Михайлов on 19/12/2018.
//

#ifndef STAR_PLATINUM_PURPLE_HEMMIT_H
#define STAR_PLATINUM_PURPLE_HEMMIT_H

#endif //STAR_PLATINUM_PURPLE_HEMMIT_H

//===============================drawmenu.h============================//
#ifndef DRAWMENU_H_INCLUDED
#define DRAWMENU_H_INCLUDED
/* ---- файл drawmenu.h --- */
// описание функций, которые управл€ют работой меню
void DrawMenu(); //создание меню
void gotoxy(int x, int y); // перевод курсора в точку x,y
void itemMenu(int sel, bool activate); // выделить пункт меню
void cls(); // очистка консоли; при it==0 оставл€ем
// строку меню иначе очищаем всю консоль
void getCursorPosition(void); // запомнить положение курсора
//в глобальную переменную curspos
void showCursor(bool visible);// скрыть/показать курсор
#endif // DRAWMENU_H_INCLUDED


//=====================================drawmenu.c==========================//
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <tchar.h>
#include <stdbool.h>
#include "drawmenu.h"
#include "menudemo.h"
#define KEY_ARROW_RIGHT 77
#define KEY_ARROW_LEFT 75
#define KEY_ENTER 13
typedef void(*FUN) (void); //”казатель на функцию void f(void)
//они будут выполн€ть пункты меню
typedef struct { //—труктура дл€ элемента меню
    int x, y; //—толбец и строка консоли
    char *str; //Ќаименование пункта меню
    FUN f; //‘ункци€, прив€занна€ к пункту меню
} ITEM;
// √лобальные переменные, используемые в функци€х меню
HANDLE hStdOut,hNewScreenBuffer; //дескриптор консольного окна
CONSOLE_SCREEN_BUFFER_INFO csbInfo;//информаци€ о консольном окне
SMALL_RECT consolRect; //координату углов консольного окна
COORD curspos={0,1}; //координаты текстового курсора
WORD workWindowAttributes = 158;//атрибуты рабочей области
WORD inactiveItemAttributes = 31; //атрибуты цвета неактивного пункта меню
WORD activeItemAttributes = 158; // атрибуты цвета активного пункта меню
enum menuitems { MNUAUTIMATIC, MNUHAND, MNUIMAGE, MNUEXIT };
#define numMenu 4 //количество пунктов меню
ITEM menu[numMenu] = { //положение (x,y), заголовок,
// указатель на функцию
        { 1,  0, " јвтоматическое управление ", automatic_control },
        { 30, 0, " –учное управление ", hand_control },
        { 50, 0, " ѕосмотреть изображение ", draw_picture},
        { 75, 0, " ¬ыход ", Exit }
};

void DrawMenu() { //”правление меню
    enum menuitems sel;
    sel=MNUAUTIMATIC; // Ќомер текущего пункта меню
    SetConsoleTextAttribute(hStdOut, inactiveItemAttributes);
    draw();
    for (int i = 0; i < numMenu; i++)
    { //Ќапечатать заголовки пунктов меню
        gotoxy(menu[i].x, menu[i].y);
        printf(menu[i].str);
    }
    itemMenu(sel, true); // выделить пункт меню
    fflush(stdin); //очистить буфер клавиатуры
    int iKey = 67;
    while (1)
    {
        draw();
        gotoxy(1,2);
        if (_kbhit())
        {
            draw();
            iKey = _getch();
            switch (iKey)
            {
                case KEY_ARROW_RIGHT:
                    if (sel < numMenu - 1) {
                        itemMenu(sel, false); // сделать неактивным пункт меню
                        sel = (enum menuitems)(sel + 1);
                        itemMenu(sel, true); // выделить активный пункт меню
                    }
                    else {
                        itemMenu(sel, false); // сделать неактивным пункт меню
                        sel = MNUAUTIMATIC; // прокрутка влево
                        itemMenu(sel, true); // выделить активный пункт меню
                    }
                    showCursor(false);
                    break;
                case KEY_ARROW_LEFT:
                    if (sel > 0) {
                        itemMenu(sel, false);
                        sel = (enum menuitems)(sel - 1);
                        itemMenu(sel, true);
                    }
                    else {
                        itemMenu(sel, false);
                        sel = MNUEXIT; // прокрутка влево
                        itemMenu(sel, true);
                    }
                    showCursor(false);
                    break;
                case KEY_ENTER:
                    gotoxy(curspos.X, curspos.Y); //возвращаем курсор из строки
                    // меню в прежнюю позицию
                    SetConsoleTextAttribute(hStdOut,workWindowAttributes); // ”становить цвет
                    showCursor(true);
                    switch (sel)
                    {
                        case MNUAUTIMATIC:
                            draw();
                            automatic_control();
                            getCursorPosition(); // запомнить положение курсора
                            break;
                        case MNUHAND:
                            draw();
                            hand_control();
                            getCursorPosition(); // запомнить положение курсора
                            break;
                        case MNUIMAGE:
                            draw();
                            draw_picture();
                            getCursorPosition(); // запомнить положение курсора,
                            // если отменили выход
                            break;
                        case MNUEXIT:
                            Exit();
                            getCursorPosition(); // запомнить положение курсора,
                            // если отменили выход
                            break;
                    }
                    fflush(stdin); //очистить буфер клавиатуры
                    gotoxy(menu[sel].x, menu[sel].y); // курсор в текущий пункт меню
                    showCursor(false);
                    break;
                case 120: // выход по клавише x
                case 88: // выход по клавише X
                case 27: // выход по клавише ESC
                    gotoxy(0, 0);
                    cls(1);
                    exit(0); //завершение программы
            }
        }
    }
}

// “екстовый курсор в точку x,y
void gotoxy(int x, int y)
{
    COORD cursorPos = { x, y };
    SetConsoleCursorPosition(hStdOut, cursorPos);
}
// запись текущего положени€ текстового курсора в глобальную
// переменную curspos
void getCursorPosition(void)
{
    GetConsoleScreenBufferInfo(hStdOut, &csbInfo);
    curspos = csbInfo.dwCursorPosition;// положение курсора
}

void cls()
{   gotoxy(0,0);
    system("cls");
}
// выделить пункт меню с номером sel
void itemMenu(int sel, bool activate)
{
    WORD itemAttributes;
    if (activate) itemAttributes = activeItemAttributes;
    else itemAttributes = inactiveItemAttributes;
    gotoxy(menu[sel].x, menu[sel].y);
    SetConsoleTextAttribute(hStdOut, itemAttributes);
    printf(menu[sel].str);
}
// скрыть/показать текстовый курсор в консоли
void showCursor(bool visible)
{
    CONSOLE_CURSOR_INFO ccInfo;
    ccInfo.bVisible = visible;
    ccInfo.dwSize = 30;
    SetConsoleCursorInfo(hStdOut, &ccInfo);
}

//=========================menudemo.h===========================//
#ifndef MENUDEMO_H_INCLUDED
#define MENUDEMO_H_INCLUDED
void automatic_control(void );
void hand_control(void);
void Exit(void);
void setconsole();
void draw();
void draw_picture(void);
#endif // MENUDEMO_H_INCLUDED

#include <string.h>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <malloc.h>
#include <locale.h>
#include <stdbool.h>
#include <pthread.h>
#include "drawmenu.h"
#include "menudemo.h"
#include "picture.h"
extern HANDLE hStdOut; //дескриптор консольного окна
extern CONSOLE_SCREEN_BUFFER_INFO csbInfo; //информаци€ о
// консольном окне в структуре csbInfo
extern SMALL_RECT consolRect; //координаты углов консоли
extern WORD workWindowAttributes; //атрибуты рабочей
//области консоли
void disp()
{
    setconsole();
}
// ===================== ‘ункции меню ===================

void automatic_control()
{
    draw();
    gotoxy(1,2);
    printf("¬ы выбрали меню 'јвтоматическое управление'\n");
    double x,y;
    char buff=0, buffs[40];
    int arrx[40],arry[40];
    FILE* file = fopen("Gcod_in.txt", "r");
    if (!file==NULL)
    {
        draw();
        printf("open\n");
        while((buff=fgetc(file))!=EOF)
        {
            if (buff=='X')
            {
                for(int i=0;buff=fgetc(file);i++)
                {
                    buffs[i]=buff;
                    if ((buff==' ')||(buff=='\n'))
                    {
                        buffs[i+1]=EOF;
                        break;
                    }
                    x=atof(buffs);
                    printf(" X%.2f\n ",x);
                }
            }
            if (buff=='Y')
            {
                for(int i=0;buff=fgetc(file);i++)
                {
                    buffs[i]=buff;
                    if ((buff==' ')||(buff=='\n'))
                    {
                        buffs[i+1]=EOF;
                        break;
                    }
                }
                y=atof(buffs);
                printf(" Y%.2f",y);
            }
        }
    }

    else
    {
        printf("ne open\n");
    }
    fclose(file);
    system("pause");
    system("cls");
    setconsole();
}
//‘ункци€ меню <ƒействие>. «аполн€етс€ кодом пользовател€
void hand_control()
{
    draw();
    gotoxy(0,2);
    int pros,num;
    printf("¬ы выбрали меню '–учное управление'\n");
    printf("Enter number\n");
    scanf("%d",&num);
    pros=num*num;
    printf("Pros is %d \n",pros);
    draw();
    system("pause");
    system("cls");
    setconsole();
}

//‘ункци€ меню <¬ыход> - завершение программы
void Exit() {
    gotoxy(1,2);
    draw();
    printf("¬ы уверены, что хотите выйти из программы ? (y / n) ? ");
    int resp = getchar();
    if (resp == 'y' || resp == 'Y')
    {
        gotoxy(0, 0); cls(1); exit(0);
    }
}

void setConsoleSize() // «адание размеров окна консоли
{
    const int colConsole = 120;
    const int rowConsole = 30;
    SMALL_RECT windowSize ={0,0,colConsole,rowConsole};
    SetConsoleWindowInfo(hStdOut,TRUE,&windowSize);
    COORD bufferSize ={colConsole,rowConsole };
    SetConsoleScreenBufferSize(hStdOut,bufferSize);//изменение размеров буфера консольного окна
    system("mode 122,30");//изменение размеров консольного окна
}

void setconsole()
{
    SetConsoleTitle("MENU");
    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hStdOut, &csbInfo);
    consolRect = csbInfo.srWindow; //координаты углов консоли
    SetConsoleTextAttribute(hStdOut, workWindowAttributes);
    system("CLS"); // установка атрибутов цвета рабочей области
    setConsoleSize();//установка размера консоли
    DrawMenu(); // рисуем меню в верхней строке консоли
    draw();
}
void draw()
{
    HWND handle = FindWindow("ConsoleWindowClass", NULL);
    HDC hdc = GetDC(handle);
    SelectObject(hdc,CreatePen(PS_SOLID,5,RGB(224, 255, 255)));
    POINT ptRect[5]={{2,0},{975,0},{975,477},{2,477},{2,0}};
    Polyline(hdc, ptRect, 5); // рисуем пр€моугольник
    MoveToEx(hdc,660,0,NULL);
    LineTo(hdc,660,478);
    MoveToEx(hdc,0,20,NULL);
    LineTo(hdc,660,20);
    MoveToEx(hdc,230,0,NULL);
    LineTo(hdc,230,20);
    MoveToEx(hdc,400,0,NULL);
    LineTo(hdc,400,20);
    MoveToEx(hdc,600,0,NULL);
    LineTo(hdc,600,20);
    LPCTSTR lpString,lpString1;
    COLORREF colorsc = RGB(65, 105, 225);
    COLORREF colortext = RGB(255, 255, 255);
    SetBkColor(hdc,colorsc);
    SetTextColor(hdc,colortext);
    lpString = "»нструкци€ к применению: ";
    TextOut(hdc,726,3,lpString,25);
    TextOut(hdc,664,33,"ƒл€ выбора пункта меню используйте",34);
    TextOut(hdc,664,53,"стрелки вправо/влево на клавиатуре",34);
    TextOut(hdc,664,73,"дл€ выхода нажмите ESC",22);
    TextOut(hdc,664,93,"или выберете дл€ этого пункт меню *¬ыход*",41);
}

void draw_picture()
{
    draw();
    gotoxy(1,2);
    HWND handle = FindWindow("ConsoleWindowClass", NULL);
    HDC hdc = GetDC(handle);
    double x,x1,y,y1;
    COLORREF penColor = RGB(128, 0, 128);
    HPEN Pen;
    Pen = CreatePen(PS_SOLID, 3, RGB(128, 0, 128)); // перо 1
    SelectObject(hdc, Pen); // помещаем перо 1 в контекст
    char buff=0,buffs[40];
    int arrx[40],arry[40];
    FILE* file = fopen("Gcod_in.txt", "r");
    if (!file==NULL)
    {
        while((buff=fgetc(file))!=EOF)
        {
            if (buff=='X')
            {
                for(int i=0;buff=fgetc(file);i++)
                {
                    buffs[i]=buff;
                    if ((buff==' ')||(buff=='\n'))
                    {
                        buffs[i+1]=EOF;
                        break;
                    }
                }
                x=atof(buffs);
            }
            if (buff=='Y')
            {
                for(int i=0;buff=fgetc(file);i++)
                {
                    buffs[i]=buff;
                    if ((buff==' ')||(buff=='\n'))
                    {
                        buffs[i+1]=EOF;
                        break;
                    }
                }
                y=atof(buffs);
                SetPixel(hdc,x*15,y*15,penColor);
                MoveToEx(hdc,x*15,y*15,NULL);
                LineTo(hdc,x*15,y*15);
            }
        }
    }
    else{
        printf("doesnt open open\n");
    }
    DeleteObject(Pen);
    ReleaseDC(NULL, hdc);
    fclose(file);
    //system("pause");
    system("cls");
    setconsole();
}
