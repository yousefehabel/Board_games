#ifndef _FOUR_IN_A_ROW_H
#define _FOUR_IN_A_ROW_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm> 
using namespace std;

// For in row Board Implementation
template <typename T>
class FourInARowBoard : public Board<T> {
public:
    FourInARowBoard();
    bool update_board(int x, int y, T symbol) ;
    void display_board() ;
    bool is_win() ;
    bool is_draw() ;
    bool game_is_over() ;
};

template <typename T>
class FourInARowPlayer : public Player<T> {
public:
    FourInARowPlayer(string name, T symbol);
    void getmove(int& x, int& y) ;
};


template <typename T>
class fourinrowRandom_Player : public RandomPlayer<T>{
public:
    fourinrowRandom_Player (T symbol);
    void getmove(int &x, int &y) ;
};


//--------------------------------------- IMPLEMENTATION

// Constructor for FourInARowBoard
template <typename T>
FourInARowBoard<T>::FourInARowBoard() {
    this->rows = 6;
    this->columns = 7;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns](); 
    }
    this->n_moves = 0;
}

// Update the board with a move
template <typename T>
bool FourInARowBoard<T>::update_board(int x, int y, T symbol) {
    if (y < 0 || y >= this->columns || x != 0 || symbol == 0) return false;

    for (int i = this->rows - 1; i >= 0; i--) {
        if (this->board[i][y] == 0) {
            this->board[i][y] = toupper(symbol);
            this->n_moves++;
            return true;
        }
    }
    return false; 
}

// Display the board
template <typename T>
void FourInARowBoard<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "| ";
        for (int j = 0; j < this->columns; j++) {
            cout << setw(2) << (this->board[i][j] ? this->board[i][j] : '.') << " | ";
        }
        cout << "\n";
    }
    cout << "   0    1    2    3    4    5    6\n";
} 

// Check for a win condition
template <typename T>
bool FourInARowBoard<T>::is_win() {
    // Directions: right, down, diagonal-right-down, diagonal-left-down
    vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};

    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] == 0) continue;

            for (auto& dir : directions) {
                int count = 1;
                for (int step = 1; step < 4; step++) {
                    int ni = i + step * dir.first;
                    int nj = j + step * dir.second;
                    if (ni < 0 || ni >= this->rows || nj < 0 || nj >= this->columns || this->board[ni][nj] != this->board[i][j])
                        break;
                    count++;
                }
                if (count == 4) return true;
            }
        }
    }
    return false;
}

// Check for draw 
template <typename T>
bool FourInARowBoard<T>::is_draw() {
    return this->n_moves == this->rows * this->columns && !is_win();
}

// Check if game is over
template <typename T>
bool FourInARowBoard<T>::game_is_over() {
    return is_win() || is_draw();
}


// Constructor for Four in row Player
template <typename T>
FourInARowPlayer<T>::FourInARowPlayer(string name, T symbol) : Player<T>(name, symbol) {}

// Get move for Four in row Player
template <typename T>
void FourInARowPlayer<T>::getmove(int& x, int& y) {
    cout << "\n" << this->name << ", enter column (0 to 6): ";
    cin >> y;
    x = 0; 

}


template <typename T>
fourinrowRandom_Player<T>::fourinrowRandom_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 7;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  
}

template <typename T>
void fourinrowRandom_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 6
    y = rand() % this->dimension;
}



#endif
