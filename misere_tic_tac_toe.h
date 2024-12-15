#ifndef MISERE_TIC_TAC_TOE_H_INCLUDED
#define MISERE_TIC_TAC_TOE_H_INCLUDED

#include "BoardGame_Classes.h"

Player<char>* Globalptr[2];
template <typename T>
class misere_tic_tac_toe_board : public Board<T> {
public:
    misere_tic_tac_toe_board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    int count_three_in_a_row(char symbol);
};

template <typename T>
class player : public Player<T> {
public:
	player (string name, T symbol);
	void getmove(int& x, int& y) ;
};

template <typename T>
class random_Player : public RandomPlayer<T> {
public:
    random_Player(T symbol);
    void getmove(int& x, int& y);
};

#include <iostream>
#include <iomanip>
#include <cctype>
#include <string>

using namespace std;

template <typename T>
misere_tic_tac_toe_board<T>::misere_tic_tac_toe_board() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
    Globalptr[0] = player1;
    Globalptr[1] = player2;
}

template <typename T>
bool misere_tic_tac_toe_board<T>::update_board(int x, int y, T mark) {
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0)) {
        if (mark == 0) {
            this->n_moves--;
            this->board[x][y] = 0;
        } else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }
        return true;
    }
    return false;
}

template <typename T>
void misere_tic_tac_toe_board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

template <typename T>
bool misere_tic_tac_toe_board<T>::is_win() {
    int countX = count_three_in_a_row('X');
    int countO = count_three_in_a_row('O');

    if (countX > 0) {
        cout << "The winner is: " << Globalptr[1]->getname() << " (Player O wins!)\n";
        return true;
    } else if (countO > 0) {
        cout << "The winner is: " << Globalptr[0]->getname() << " (Player X wins!)\n";
        return true;
    } else {
        return false;
    }
}

template <typename T>
int misere_tic_tac_toe_board<T>::count_three_in_a_row(char symbol) {
    int count = 0;
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->columns - 2; ++j) {
            if (this->board[i][j] == symbol && this->board[i][j + 1] == symbol && this->board[i][j + 2] == symbol) {
                count++;
            }
        }
    }
    for (int i = 0; i < this->rows - 2; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            if (this->board[i][j] == symbol && this->board[i + 1][j] == symbol && this->board[i + 2][j] == symbol) {
                count++;
            }
        }
    }
    for (int i = 0; i < this->rows - 2; ++i) {
        for (int j = 0; j < this->columns - 2; ++j) {
            if (this->board[i][j] == symbol && this->board[i + 1][j + 1] == symbol && this->board[i + 2][j + 2] == symbol) {
                count++;
            }
        }
    }
    for (int i = 0; i < this->rows - 2; ++i) {
        for (int j = 2; j < this->columns; ++j) {
            if (this->board[i][j] == symbol && this->board[i + 1][j - 1] == symbol && this->board[i + 2][j - 2] == symbol) {
                count++;
            }
        }
    }

    return count;
}

template <typename T>
bool misere_tic_tac_toe_board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}
template <typename T>
bool misere_tic_tac_toe_board<T>::game_is_over() {
    return is_win() || is_draw();
}
template <typename T>
player<T>::player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

template <typename T>
random_Player<T>::random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}

#endif

