/*
* File: game_state.h
* Author: Nhom 2
* Description: Quan ly trang thai game va cac chuc nang chinh cua game
*/

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "game_board.h"
#include "constants.h"
#include <string>

class GameState {
public:
    // Khoi tao trang thai game moi
    GameState();

    // Bat dau mot van choi moi
    void StartGame();

    // Hien thi menu chinh
    void ShowMenu();

    // Hien thi menu tam dung
    void ShowPauseMenu();

    // Luu trang thai game hien tai
    // @param filename: Ten file luu
    void SaveGame(const std::string& filename);

    // Tai trang thai game da luu
    // @param filename: Ten file tai
    void LoadGame(const std::string& filename);

    // Hien thi huong dan choi
    void ShowInstructions();

    // Hien thi thong tin nhom
    void ShowAbout();

private:
    GameBoard _board;                // Ban co
    bool _turn;                      // Luot choi (true: X, false: O)
    int _currentX, _currentY;        // Vi tri con tro hien tai
    int _player1Wins, _player2Wins;  // So tran thang cua moi nguoi choi
    GameStateEnum _currentGameState;   // Trang thai hien tai cua game

    // Xu ly ket thuc tran
    // @param result: Ket qua tran dau (-1: X thang, 1: O thang, 0: hoa)
    void ProcessFinish(int result);

    // Hoi nguoi choi co muon tiep tuc
    // @return: 'Y' neu tiep tuc, 'N' neu khong
    char AskContinue();

    // Cac ham di chuyen con tro
    void MoveRight();
    void MoveLeft();
    void MoveUp();
    void MoveDown();
};

#endif