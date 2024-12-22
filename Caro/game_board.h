/*
* File: game_board.h
* Author: Nhom 2
* Description: Quan ly ban co va cac thao tac tren ban co
*/

#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include "types.h"
#include <vector>

class GameBoard {
public:
    // Khoi tao ban co voi kich thuoc mac dinh la 12x12
    // @param size: kich thuoc ban co
    GameBoard(int size = 12);

    // Dat lai trang thai ban co ve ban dau
    void Reset();

    // Ve ban co ra man hinh
    void Draw();

    // Kiem tra va cap nhat trang thai cua o co tai toa do x, y
    // @param x: toa do ngang
    // @param y: toa do doc
    // @return: Trang thai cua o sau khi kiem tra
    CellState CheckCell(int x, int y, bool isXTurn);

    // Kiem tra dieu kien thang/thua/hoa
    // @return: -1 neu X thang, 1 neu O thang, 0 neu hoa, 2 neu chua ket thuc
    int TestWinCondition();

    // Lay ban co hien tai
    // @return: Ma tran ban co
    const std::vector<std::vector<_POINT>>& GetBoard() const;

    // Nap ban co tu du lieu co san
    // @param board: Ma tran ban co moi
    void LoadBoard(const std::vector<std::vector<_POINT>>& board);

    // Lay kich thuoc ban co
    // @return: Kich thuoc ban co
    int GetSize() const;

private:
    std::vector<std::vector<_POINT>> _board;  // Ma tran luu trang thai ban co
    int _size;                                // Kich thuoc ban co
};

#endif