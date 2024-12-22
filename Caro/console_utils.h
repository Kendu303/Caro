/*
* File: console_utils.h
* Author: Nhom 2
* Description: Chua cac ham xu ly console nhu di chuyen con tro, thay doi mau sac
*/

#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H

#include <windows.h>

// An con tro nhap nhay tren man hinh console
void HideConsoleCursor();

// Hien/an con tro nhap nhay
// @param show: true de hien, false de an
void ShowConsoleCursor(bool show);

// Co dinh kich thuoc cua so console va vo hieu hoa nut phong to
void FixConsoleWindow();

// Di chuyen con tro den vi tri x, y tren man hinh console
// @param x: toa do ngang
// @param y: toa do doc
void GotoXY(int x, int y);

// Thiet lap mau chu va mau nen cho console
// @param textColor: ma mau chu
// @param backgroundColor: ma mau nen
void SetConsoleColors(WORD textColor, WORD backgroundColor);

#endif