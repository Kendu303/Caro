/*
* File: constants.h
* Author: Nhom 2
* Description: Chua cac hang so va enum duoc su dung trong toan bo game
*/

#ifndef CONSTANTS_H
#define CONSTANTS_H

const int LEFT = 3;  // Vi tri bat dau ve bang tu bien trai
const int TOP = 1;   // Vi tri bat dau ve bang tu bien tren

// Trang thai cua o co: trong, nguoi choi X, hoac nguoi choi O
enum CellState { EMPTY = 0, PLAYER_X = -1, PLAYER_O = 1 };

// Trang thai cua game: Menu chinh, Dang choi, Tam dung
enum class GameStateEnum {
    MAIN_MENU,
    IN_GAME,
    PAUSED
};

#endif