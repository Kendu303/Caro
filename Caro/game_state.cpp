/*
* File: game_state.cpp
* Author: Nhom 2
* Description: Cai dat cac phuong thuc cua lop GameState, xu ly trang thai va luong game
*/

#include "game_state.h"
#include "console_utils.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <vector>
#include <windows.h>

// Khoi tao trang thai game mac dinh
GameState::GameState()
{
    _board = GameBoard(12);              // Khoi tao ban co 12x12
    _turn = true;                        // Luot dau tien la X
    _currentX = _board.GetBoard()[0][0].x;  // Vi tri con tro ban dau
    _currentY = _board.GetBoard()[0][0].y;
    _player1Wins = 0;                    // So tran thang ban dau
    _player2Wins = 0;
    _currentGameState = GameStateEnum::MAIN_MENU;  // Bat dau tu man hinh menu
}

// Bat dau mot van choi moi
void GameState::StartGame() {
    // Neu dang o menu chinh, reset toan bo du lieu
    if (_currentGameState == GameStateEnum::MAIN_MENU) {
        _board.Reset();
        _currentGameState = GameStateEnum::IN_GAME;
    }

    // Ve ban co va bat dau vong lap game
    _board.Draw();
    GotoXY(_currentX, _currentY);

    while (_currentGameState != GameStateEnum::MAIN_MENU) {
        // Kiem tra trang thai thang/thua/hoa
        int result = _board.TestWinCondition();
        if (result == PLAYER_X || result == PLAYER_O || result == 0) {
            ProcessFinish(result);
            return;
        }

        GotoXY(_currentX, _currentY);

        // Xu ly input tu nguoi choi
        if (_kbhit()) {
            int key = _getch();
            switch (key) {
            case 27:  // Phim ESC - Tam dung game
                ShowPauseMenu();
                if (_currentGameState == GameStateEnum::MAIN_MENU) {
                    return;
                }
                _board.Draw();
                GotoXY(_currentX, _currentY);
                break;

            case 'W': case 'w':  // Di chuyen len
                MoveUp();
                break;

            case 'S': case 's':  // Di chuyen xuong
                MoveDown();
                break;

            case 'A': case 'a':  // Di chuyen trai
                MoveLeft();
                break;

            case 'D': case 'd':  // Di chuyen phai
                MoveRight();
                break;

            case 13:  // Phim Enter - Danh dau nuoc di
                if (_board.CheckCell(_currentX, _currentY, _turn) != EMPTY) {
                    _turn = !_turn;  // Doi luot choi
                    _board.Draw();
                    GotoXY(_currentX, _currentY);
                }
                break;
            }
        }
    }
}

// Hien thi menu chinh
void GameState::ShowMenu() {
    HideConsoleCursor();

    const std::vector<std::string> menu = {
        "Bat dau tro choi moi",
        "Huong dan",
        "Tai game da luu",
        "Thoat"
    };
    int selectedOption = 0;

    // Tim menu item dai nhat de tinh kich thuoc hop
    size_t maxLength = 0;
    for (const auto& item : menu) {
        maxLength = std::max<size_t>(maxLength, item.length());
    }

    // Tinh toan vi tri va kich thuoc hop menu
    const int leftPadding = 6;
    const int boxWidth = static_cast<int>(maxLength) + leftPadding + 10;
    const int boxHeight = static_cast<int>(menu.size()) + 2;
    const int startX = (120 - boxWidth) / 2;
    const int startY = (30 - boxHeight) / 2;

    while (true) {
        system("cls");

        // Ve vien tren
        GotoXY(startX, startY);
        std::cout << "+" << std::string(boxWidth - 2, '-') << "+";

        // Ve cac muc menu
        for (size_t i = 0; i < menu.size(); i++) {
            GotoXY(startX, startY + static_cast<int>(i) + 1);
            std::cout << "|" << std::string(leftPadding, ' ');

            if (i == static_cast<size_t>(selectedOption)) {
                // Muc dang chon
                std::cout << "> " << menu[i] << " <";
                std::cout << std::string(boxWidth - leftPadding - menu[i].length() - 6, ' ');
            }
            else {
                // Muc binh thuong
                std::cout << menu[i];
                std::cout << std::string(boxWidth - leftPadding - menu[i].length() - 2, ' ');
            }
            std::cout << "|";
        }

        // Ve vien duoi
        GotoXY(startX, startY + boxHeight - 1);
        std::cout << "+" << std::string(boxWidth - 2, '-') << "+";

        // Xu ly phim bam
        int key = _getch();
        if (key == 'W' || key == 'w') {
            selectedOption = (selectedOption + static_cast<int>(menu.size()) - 1) % static_cast<int>(menu.size());
        }
        else if (key == 'S' || key == 's') {
            selectedOption = (selectedOption + 1) % static_cast<int>(menu.size());
        }
        else if (key == 13) {  // Enter - Chon muc menu
            switch (selectedOption) {
            case 0: {  // Bat dau tro choi moi
                ShowConsoleCursor(true);
                StartGame();
                HideConsoleCursor();
                break;
            }
            case 1: {  // Huong dan
                ShowConsoleCursor(true);
                ShowInstructions();
                HideConsoleCursor();
                break;
            }
            case 2: {  // Tai game
                ShowConsoleCursor(true);
                std::string filename;
                std::cout << "Nhap ten file: ";
                std::cin >> filename;
                LoadGame(filename);
                HideConsoleCursor();
                break;
            }
            case 3: {  // Thoat
                ShowConsoleCursor(true);
                exit(0);
            }
            }
        }
    }
}

// Xu ly ket thuc tran dau
void GameState::ProcessFinish(int result) {
    system("cls");
    if (result == PLAYER_X) {
        std::cout << "Nguoi choi X thang!\n";
        _player1Wins++;
    }
    else if (result == PLAYER_O) {
        std::cout << "Nguoi choi O thang!\n";
        _player2Wins++;
    }
    else {
        std::cout << "Hoa!\n";
    }

    // Hien thi thong ke
    std::cout << "So tran thang cua X: " << _player1Wins
        << "\nSo tran thang cua O: " << _player2Wins << std::endl;

    if (AskContinue() == 'Y') {
        // Chi reset ban co, giu nguyen thong ke
        _board.Reset();
        _board.Draw();
        GotoXY(_currentX, _currentY);
        _currentGameState = GameStateEnum::IN_GAME;
        StartGame();
    }
    else {
        // Reset toan bo va tro ve menu
        _board.Reset();
        _player1Wins = 0;
        _player2Wins = 0;
        ShowMenu();
    }
}

// Hoi nguoi choi co muon tiep tuc
char GameState::AskContinue() {
    char choice;
    do {
        std::cout << "Ban co muon choi tiep khong? (Y/N): ";
        std::cin >> choice;
        choice = toupper(choice);
    } while (choice != 'Y' && choice != 'N');
    return choice;
}

// Cac ham di chuyen con tro
void GameState::MoveRight() {
    if (_currentX < _board.GetBoard()[_board.GetSize() - 1][_board.GetSize() - 1].x) {
        _currentX += 4;
        GotoXY(_currentX, _currentY);
    }
}

void GameState::MoveLeft() {
    if (_currentX > _board.GetBoard()[0][0].x) {
        _currentX -= 4;
        GotoXY(_currentX, _currentY);
    }
}

void GameState::MoveDown() {
    if (_currentY < _board.GetBoard()[_board.GetSize() - 1][_board.GetSize() - 1].y) {
        _currentY += 2;
        GotoXY(_currentX, _currentY);
    }
}

void GameState::MoveUp() {
    if (_currentY > _board.GetBoard()[0][0].y) {
        _currentY -= 2;
        GotoXY(_currentX, _currentY);
    }
}

// Hien thi menu tam dung
void GameState::ShowPauseMenu() {
    if (_currentGameState != GameStateEnum::IN_GAME) {
        return;
    }

    _currentGameState = GameStateEnum::PAUSED;
    int selectedOption = 0;
    const std::vector<std::string> menu{
        "Tiep tuc",
        "Luu game",
        "Thong tin",
        "Tro ve menu chinh"
    };

    while (_currentGameState == GameStateEnum::PAUSED) {
        system("cls");
        std::cout << "=== Menu Tam Dung ===" << std::endl;

        for (size_t i = 0; i < menu.size(); i++) {
            std::cout << (i == static_cast<size_t>(selectedOption) ? " > " : "   ")
                << menu[i]
                << (i == static_cast<size_t>(selectedOption) ? " <" : "") << std::endl;
        }

        int key = _getch();
        if (key == 'W' || key == 'w') {
            selectedOption = (selectedOption + static_cast<int>(menu.size()) - 1) % static_cast<int>(menu.size());
        }
        else if (key == 'S' || key == 's') {
            selectedOption = (selectedOption + 1) % static_cast<int>(menu.size());
        }
        else if (key == 27) {  // ESC
            _currentGameState = GameStateEnum::IN_GAME;
            return;
        }
        else if (key == 13) {  // Enter
            switch (selectedOption) {
            case 0: {  // Tiep tuc
                _currentGameState = GameStateEnum::IN_GAME;
                return;
            }
            case 1: {  // Luu game
                system("cls");
                std::string filename;
                std::cout << "\n\nNhap ten file de luu (vi du: game1.txt): ";
                std::cin >> filename;
                SaveGame(filename);
                _currentGameState = GameStateEnum::IN_GAME;
                return;
            }
            case 2: {  // Thong tin
                ShowAbout();
                break;
            }
            case 3: {  // Tro ve menu chinh
                _board.Reset();
                _currentGameState = GameStateEnum::MAIN_MENU;
                return;
            }
            }
        }
    }
}

// Luu trang thai game
void GameState::SaveGame(const std::string& filename) {
    std::string fullFilename = filename;
    if (fullFilename.find(".txt") == std::string::npos) {
        fullFilename += ".txt";
    }

    std::ofstream file(fullFilename, std::ios::out);
    if (!file.is_open()) {
        std::cout << "\nLoi: Khong the tao file luu game!\n";
        Sleep(1000);
        return;
    }

    // Ghi phien ban file
    file << "CARO_GAME_SAVE_v1\n";

    // Ghi kich thuoc ban co
    file << _board.GetSize() << "\n";

    // Ghi luot choi hien tai
    file << (_turn ? "1" : "0") << "\n";

    // Ghi so tran thang
    file << _player1Wins << " " << _player2Wins << "\n";

    // Ghi trang thai ban co
    const auto& boardData = _board.GetBoard();
    for (int i = 0; i < _board.GetSize(); i++) {
        for (int j = 0; j < _board.GetSize(); j++) {
            file << static_cast<int>(boardData[i][j].c) << " ";
        }
        file << "\n";
    }

    // Ghi vi tri con tro
    file << _currentX << " " << _currentY << "\n";

    file.close();
    std::cout << "\nDa luu game vao file " << fullFilename << " thanh cong!\n";
    Sleep(1000);
}

// Tai game da luu
void GameState::LoadGame(const std::string& filename) {
    std::string fullFilename = filename;
    if (fullFilename.find(".txt") == std::string::npos) {
        fullFilename += ".txt";
    }

    std::ifstream file(fullFilename);
    if (!file.is_open()) {
        std::cout << "\nLoi: Khong the mo file " << fullFilename << "!\n";
        Sleep(1500);
        return;
    }

    try {
        // Doc va kiem tra phien ban
        std::string version;
        std::getline(file, version);
        if (version != "CARO_GAME_SAVE_v1") {
            throw std::runtime_error("Dinh dang file khong hop le");
        }

        // Doc kich thuoc ban co
        int boardSize;
        file >> boardSize;
        if (boardSize <= 0 || boardSize > 20) {
            throw std::runtime_error("Kich thuoc ban co khong hop le");
        }

        // Doc luot choi
        int turn;
        file >> turn;
        _turn = (turn == 1);

        // Doc so tran thang
        file >> _player1Wins >> _player2Wins;

        // Doc trang thai ban co
        std::vector<std::vector<_POINT>> newBoard(boardSize, std::vector<_POINT>(boardSize));
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                int cellState;
                file >> cellState;
                if (cellState < -1 || cellState > 1) {
                    throw std::runtime_error("Trang thai o co khong hop le");
                }
                newBoard[i][j].c = static_cast<CellState>(cellState);
                newBoard[i][j].x = LEFT + 4 * j;
                newBoard[i][j].y = TOP + 2 * i;
            }
        }

        // Doc vi tri con tro
        file >> _currentX >> _currentY;

        // Cap nhat ban co
        _board.LoadBoard(newBoard);

        file.close();
        std::cout << "\nTai game thanh cong!\n";
        Sleep(1000);

        // Bat dau game da tai
        _currentGameState = GameStateEnum::IN_GAME;
        StartGame();
    }
    catch (const std::exception& e) {
        std::cout << "\nLoi khi tai file: " << e.what() << "\n";
        file.close();
        Sleep(1500);
    }
}

// Hien thi huong dan choi
void GameState::ShowInstructions() {
    system("cls");
    std::cout << "Huong dan choi:\n\n";
    std::cout << "1. Nguoi choi X di truoc.\n";
    std::cout << "2. Su dung phim W, A, S, D de di chuyen tren ban co.\n";
    std::cout << "3. Nhan Enter de danh dau nuoc di.\n";
    std::cout << "4. Nguoi choi nao co 5 quan co lien tiep truoc se thang!\n";
    std::cout << "5. Nhan ESC de tam dung tro choi.\n\n";
    std::cout << "Nhan phim bat ky de tro ve menu...";
    _getch();
}

// Hien thi thong tin nhom
void GameState::ShowAbout() {
    system("cls");
    SetConsoleOutputCP(65001);  // Ho tro hien thi tieng Viet Unicode

    std::cout << "=== Thong tin nhom ===" << std::endl << std::endl;
    std::cout << "* Le Duc Minh - 24127448" << std::endl;
    std::cout << "* Vu Duy Kha - 24127178" << std::endl;
    std::cout << "* Do Khac Thanh Cong - 24127332" << std::endl;
    std::cout << "* Le Si Toan - 24127558" << std::endl;
    std::cout << "* Luong Duc Toan - 24127309" << std::endl << std::endl;

    std::cout << "Nhan phim bat ky de tro ve...";
    _getch();
}