//
// Created by Алексей Михайлов on 21/12/2018.
//

#ifndef STAR_PLATINUM_MENU_H
#define STAR_PLATINUM_MENU_H

#endif //STAR_PLATINUM_MENU_H

void automatic_control(void );
void hand_control(void);
void Exit(void);
void setconsole();
void draw();
void draw_picture(void);
void DrawMenu(); //�������� ����
void gotoxy(int x, int y); // ������� ������� � ����� x,y
void itemMenu(int sel, bool activate); // �������� ����� ����
void cls(); // ������� �������; ��� it==0 ���������
// ������ ���� ����� ������� ��� �������
void getCursorPosition(void); // ��������� ��������� �������
//� ���������� ���������� curspos
void showCursor(bool visible);// ������/�������� ������
#endif // MENU_H_INCLUDED

#include <string.h>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <tchar.h>
#include <stdbool.h>
#define KEY_ARROW_RIGHT 77
#define KEY_ARROW_LEFT 75
#define KEY_ENTER 13
#define numMenu 4 //���������� ������� ����

typedef void(*FUN) (void); //��������� �� ������� void f(void)
typedef struct { //��������� ��� �������� ����
    int x, y; //������� � ������ �������
    char *str; //������������ ������ ����
    FUN f; //�������, ����������� � ������ ����
}ITEM;

// ���������� ����������, ������������ � �������� ����
HANDLE hStdOut, hNewScreenBuffer; //���������� ����������� ����
CONSOLE_SCREEN_BUFFER_INFO csbInfo;//���������� � ���������� ����
SMALL_RECT consolRect; //���������� ����� ����������� ����
COORD curspos={0,1}; //���������� ���������� �������
WORD workWindowAttributes = 158;//�������� ������� �������
WORD inactiveItemAttributes = 31; //�������� ����� ����������� ������ ����
WORD activeItemAttributes = 158; // �������� ����� ��������� ������ ����
enum menuitems { MNUAUTIMATIC, MNUHAND, MNUIMAGE, MNUEXIT };

ITEM menu[numMenu] = { //��������� (x,y), ���������,
// ��������� �� �������
        { 1,  0, " �������������� ���������� ", automatic_control },
        { 30, 0, " ������ ���������� ", hand_control },
        { 50, 0, " ���������� ����������� ", draw_picture},
        { 75, 0, " ����� ", Exit }
};

void DrawMenu() { //���������� ����
    enum menuitems sel;
    sel=MNUAUTIMATIC; // ����� �������� ������ ����
    SetConsoleTextAttribute(hStdOut, inactiveItemAttributes);
    draw();
    for (int i = 0; i < numMenu; i++) { //���������� ��������� ������� ����
        gotoxy(menu[i].x, menu[i].y);
        printf(menu[i].str);
    }
    itemMenu(sel, true); // �������� ����� ����
    fflush(stdin); //�������� ����� ����������
    int iKey = 67;
    while (1) {
        draw();
        gotoxy(1,2);
        if (_kbhit()) {
            draw();
            iKey = _getch();
            switch (iKey) {
                case KEY_ARROW_RIGHT:
                    if (sel < numMenu - 1) {
                        itemMenu(sel, false); // ������� ���������� ����� ����
                        sel = (enum menuitems)(sel + 1);
                        itemMenu(sel, true); // �������� �������� ����� ����
                    } else {
                        itemMenu(sel, false); // ������� ���������� ����� ����
                        sel = MNUAUTIMATIC; // ��������� �����
                        itemMenu(sel, true); // �������� �������� ����� ����
                    }
                    showCursor(false);
                    break;
                case KEY_ARROW_LEFT:
                    if (sel > 0) {
                        itemMenu(sel, false);
                        sel = (enum menuitems)(sel - 1);
                        itemMenu(sel, true);
                    } else {
                        itemMenu(sel, false);
                        sel = MNUEXIT;
                        itemMenu(sel, true);
                    }
                    showCursor(false);
                    break;
                case KEY_ENTER:
                    gotoxy(curspos.X, curspos.Y); //���������� ������ �� ������
                    SetConsoleTextAttribute(hStdOut,workWindowAttributes); // ���������� ����
                    showCursor(true);
                    switch (sel) {
                        case MNUAUTIMATIC:
                            automatic_control();
                            getCursorPosition();
                            break;
                        case MNUHAND:
                            hand_control();
                            getCursorPosition();
                            break;
                        case MNUIMAGE:
                            draw_picture();
                            getCursorPosition();
                            break;
                        case MNUEXIT:
                            Exit();
                            getCursorPosition();
                            break;
                    }
                    fflush(stdin); //�������� ����� ����������
                    gotoxy(menu[sel].x, menu[sel].y); // ������ � ������� ����� ����
                    showCursor(false);
                    break;
                case 27: // ����� �� ������� ESC
                    gotoxy(0, 0);
                    cls(1);
                    exit(0); //���������� ���������
            }
        }
    }
}

// ��������� ������ � ����� x,y

void gotoxy(int x, int y) {
    COORD cursorPos = { x, y };
    SetConsoleCursorPosition(hStdOut, cursorPos);
}

// ������ �������� ��������� ���������� ������� � ����������
// ���������� curspos

void getCursorPosition(void) {
    GetConsoleScreenBufferInfo(hStdOut, &csbInfo);
    curspos = csbInfo.dwCursorPosition;// ��������� �������
}

void cls() {
    gotoxy(0,0);
    system("cls");
}

// �������� ����� ���� � ������� sel

void itemMenu(int sel, bool activate) {
    WORD itemAttributes;
    if (activate)
        itemAttributes = activeItemAttributes;
    else itemAttributes = inactiveItemAttributes;
    gotoxy(menu[sel].x, menu[sel].y);
    SetConsoleTextAttribute(hStdOut, itemAttributes);
    printf(menu[sel].str);
}

//������/�������� ��������� ������ � �������

void showCursor(bool visible) {
    CONSOLE_CURSOR_INFO ccInfo;
    ccInfo.bVisible = visible;
    ccInfo.dwSize = 30;
    SetConsoleCursorInfo(hStdOut, &ccInfo);
}

//�������������� ����������

void automatic_control() {
    gotoxy(1,2);
    printf("�� ������� ���� '�������������� ����������'\n");
    system("pause");
    system("cls");
    setconsole();
}

//������ ����������

void hand_control() {
    gotoxy(1,2);
    printf("�� ������� ���� '������ ����������'\n");
    system("pause");
    system("cls");
    setconsole();
}

void Exit() {
    gotoxy(1,2);
//draw();
    printf("�� �������, ��� ������ ����� �� ��������� ? (y / n) ? ");
    int resp = getchar();
    if (resp == 'y' || resp == 'Y')
        gotoxy(0, 0); cls(1); exit(0);
}

//������� ������ ������� ����

void setConsoleSize() {
    const int colConsole = 122;
    const int rowConsole = 30;
    SMALL_RECT windowSize = {0, 0, colConsole, rowConsole};
    SetConsoleWindowInfo(hStdOut, TRUE, &windowSize);
    COORD bufferSize = {colConsole, rowConsole};
    SetConsoleScreenBufferSize(hStdOut, bufferSize);//��������� �������� ������ ����������� ����
    system("mode 122,30");//��������� �������� ����������� ����
}

void setconsole(){
    SetConsoleTitle("MENU");
    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hStdOut, &csbInfo);
    consolRect = csbInfo.srWindow; //���������� ����� �������
    SetConsoleTextAttribute(hStdOut, workWindowAttributes);
    system("CLS"); // ��������� ��������� ����� ������� �������
    setConsoleSize();// ��������� ������� �������
    DrawMenu(); // ������ ���� � ������� ������ �������
    draw();// ��������� �������
}

void draw(){
    HWND handle = FindWindow("ConsoleWindowClass", NULL);
    HDC hdc = GetDC(handle);
    COLORREF colorsc = RGB(65, 105, 225);
    COLORREF colortext = RGB(255, 255, 255);
    SelectObject(hdc, CreatePen(PS_SOLID,5,RGB(224, 255, 255)));
    POINT ptRect[5] = {{2,0},{975,0},{975,477},{2,477},{2,0}};
    Polyline(hdc, ptRect, 5);
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
    SetBkColor(hdc,colorsc);
    SetTextColor(hdc,colortext);
//����� ���������� ��� ������������
    TextOut(hdc, 726, 3,"���������� � ����������: ", 25);
    TextOut(hdc, 664, 33, "��� ������ ������ ���� �����������", 34);
    TextOut(hdc, 664, 53, "������� ������/����� �� ����������", 34);
    TextOut(hdc, 664, 73, "��� ������ ������� ESC", 22);
    TextOut(hdc, 664, 93, "��� �������� ��� ����� ����� ���� *�����*", 41);
}

void draw_picture() {
    gotoxy(1,2);
    double x;
    double x1;
    double y;
    double y1;
    HWND handle = FindWindow("ConsoleWindowClass", NULL);
    HPEN Pen;
    HDC hdc = GetDC(handle);
    COLORREF penColor = RGB(224, 255, 255);
    Pen = CreatePen(PS_SOLID, 3, RGB(224, 255, 255)); // ���� 1
    SelectObject(hdc, Pen); // �������� ���� 1 � ��������
//���������� ��� ��������� ������� �� ����� gcode
    system("pause");
    system("cls");
    setconsole();
}


