// types.h
/*
* File: types.h
* Author: Nhom 2
* Description: Dinh nghia cac kieu du lieu dung trong game
*/

#ifndef TYPES_H
#define TYPES_H

#include "constants.h"

// Cau truc luu tru thong tin cua mot o co tren ban co
struct _POINT {
    int x, y;     // Toa do x, y tren man hinh console
    CellState c;  // Trang thai cua o co (X, O, hoac trong)
};

#endif