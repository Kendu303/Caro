/*
* File: game_board.cpp
* Author: Nhom 2
* Description: Cai dat cac phuong thuc cua lop GameBoard, xu ly ban co
*/

#include "game_board.h"
#include "console_utils.h"
#include <iostream>

// Khoi tao ban co voi kich thuoc cho truoc
GameBoard::GameBoard(int size) : _size(size) {
    Reset();
}

// Thiet lap lai trang thai ban dau cua ban co
void GameBoard::Reset() {
    _board.clear();
    _board.resize(_size, std::vector<_POINT>(_size));

    // Khoi tao toa do va trang thai cho tung o
    for (int i = 0; i < _size; i++) {
        for (int j = 0; j < _size; j++) {
            _board[i][j].x = LEFT + 4 * j;    // Moi o cach nhau 4 don vi theo chieu ngang
            _board[i][j].y = TOP + 2 * i;     // Moi o cach nhau 2 don vi theo chieu doc
            _board[i][j].c = EMPTY;           // Ban dau tat ca cac o deu trong
        }
    }
}

// Ve ban co ra man hinh
void GameBoard::Draw() {
    system("cls");  // Xoa man hinh truoc khi ve
    for (int i = 0; i < _size; i++) {
        for (int j = 0; j < _size; j++) {
            GotoXY(_board[i][j].x, _board[i][j].y);
            // Hien thi X, O hoac dau cham theo trang thai cua o
            if (_board[i][j].c == PLAYER_X) std::cout << "X";
            else if (_board[i][j].c == PLAYER_O) std::cout << "O";
            else std::cout << ".";
        }
    }
}

// Kiem tra va cap nhat trang thai cua o tai toa do x, y
CellState GameBoard::CheckCell(int x, int y, bool isXTurn) {
    for (int i = 0; i < _size; i++) {
        for (int j = 0; j < _size; j++) {
            if (_board[i][j].x == x && _board[i][j].y == y && _board[i][j].c == EMPTY) {
                // Thay doi trang thai cua o thanh X hoac O tuy theo luot
                _board[i][j].c = isXTurn ? PLAYER_X : PLAYER_O;
                return _board[i][j].c;
            }
        }
    }
    return EMPTY; // Tra ve EMPTY neu o khong hop le
}

// Kiem tra dieu kien thang/thua/hoa
int GameBoard::TestWinCondition() {
    // Mang luu huong kiem tra (ngang, doc, cheo phai, cheo trai)
    int dx[] = { 0, 1, 1, 1 };
    int dy[] = { 1, 0, 1, -1 };

    // Kiem tra tung o tren ban co
    for (int i = 0; i < _size; i++) {
        for (int j = 0; j < _size; j++) {
            if (_board[i][j].c == EMPTY) continue;  // Bo qua o trong

            CellState currMark = _board[i][j].c;
            // Kiem tra theo 4 huong
            for (int d = 0; d < 4; d++) {
                int count = 1;
                // Kiem tra 4 o tiep theo theo huong hien tai
                for (int step = 1; step < 5; step++) {
                    int ni = i + step * dx[d];
                    int nj = j + step * dy[d];
                    // Kiem tra gioi han ban co
                    if (ni < 0 || ni >= _size || nj < 0 || nj >= _size) break;
                    if (_board[ni][nj].c == currMark) count++;
                    else break;
                }
                if (count == 5) return currMark;  // Co nguoi thang
            }
        }
    }

    // Kiem tra xem con o trong nao khong
    for (int i = 0; i < _size; i++) {
        for (int j = 0; j < _size; j++) {
            if (_board[i][j].c == EMPTY) return 2;  // Van con o trong, game chua ket thuc
        }
    }
    return 0;  // Hoa (khong con o trong va khong ai thang)
}

// Lay ban co hien tai
const std::vector<std::vector<_POINT>>& GameBoard::GetBoard() const {
    return _board;
}

// Nap ban co tu du lieu co san
void GameBoard::LoadBoard(const std::vector<std::vector<_POINT>>& board) {
    _board = board;
}

// Lay kich thuoc ban co
int GameBoard::GetSize() const {
    return _size;
}