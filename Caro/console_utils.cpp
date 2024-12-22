/*
* File: console_utils.cpp
* Author: Nhom 2
* Description: Cai dat cac ham xu ly console
*/

#include "console_utils.h"
#include <iostream>

// An con tro console
void HideConsoleCursor() {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(handle, &cursorInfo);
}

// Hien/an con tro theo tham so truyen vao
void ShowConsoleCursor(bool show) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = show;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

// Thiet lap cua so console co kich thuoc co dinh
void FixConsoleWindow() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    HWND consoleWindow = GetConsoleWindow();

    // Vo hieu hoa nut phong to va thay doi kich thuoc
    LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
    style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
    SetWindowLong(consoleWindow, GWL_STYLE, style);

    // Thiet lap kich thuoc buffer
    COORD bufferSize;
    bufferSize.X = 120;  // Chieu rong buffer
    bufferSize.Y = 30;   // Chieu cao buffer
    SetConsoleScreenBufferSize(hConsole, bufferSize);

    // Thiet lap kich thuoc cua so
    SMALL_RECT windowSize = { 0, 0, 119, 29 };
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

    // Thiet lap mau mac dinh
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE |
        BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);

    system("cls");  // Xoa man hinh
}

// Di chuyen con tro den toa do x, y
void GotoXY(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Thiet lap mau chu va mau nen cho console
void SetConsoleColors(WORD textColor, WORD backgroundColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, textColor | (backgroundColor << 4));

    // Cap nhat toan bo man hinh voi mau moi
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD consoleSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD topLeft = { 0, 0 };
    DWORD charsWritten;

    // To mau nen
    FillConsoleOutputAttribute(hConsole, backgroundColor << 4, consoleSize, topLeft, &charsWritten);
    FillConsoleOutputCharacter(hConsole, ' ', consoleSize, topLeft, &charsWritten);

    // Dua con tro ve vi tri dau
    SetConsoleCursorPosition(hConsole, topLeft);
}
