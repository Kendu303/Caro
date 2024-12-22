/*
* File: main.cpp
* Author: Nhom 5
* Description: 
*/

#include "game_state.h"
#include "console_utils.h"

int main() {
    FixConsoleWindow();
    SetConsoleColors(0, 15); // Chu mau den, nen mau trang

    GameState game;
    game.ShowMenu();

    return 0;
}