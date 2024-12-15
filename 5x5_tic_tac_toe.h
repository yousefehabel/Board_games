#ifndef _5_X_5_TIC_TAC_TOE_H
#define _5_X_5_TIC_TAC_TOE_H
#include "BoardGame_Classes.h"

template<typename T>
class Tic_Tac_Toe_board : public Board<T> {
public:
	Tic_Tac_Toe_board();
	bool update_board(int x, int y, T symbol);
	void display_board();
	bool is_win();
	bool is_draw();
	bool game_is_over();
	int get_n_moves();

};

template<typename T>
class _5x5_tic_tac_toe_player : public Player<T> {
public:
	_5x5_tic_tac_toe_player(string name, T symbol);

	void getmove(int& x, int& y);
};

template<typename T>
class _5x5_tic_tac_toe_random_player : public RandomPlayer<T> {
public:
	_5x5_tic_tac_toe_random_player(T symbol);

	void getmove(int& x, int& y);
};

//----------------------------------------------------------------//

#include<iostream>
#include<iomanip>
#include<cctype>
using namespace std;

template<typename T>
Tic_Tac_Toe_board<T>::Tic_Tac_Toe_board() {
	this->rows = this->columns = 5;
	this->board = new char* [this->rows];
	for (int i = 0; i < this->rows; ++i) {
		this->board[i] = new char[this->columns];
		for (int j = 0; j < this->columns; ++j) {
			this->board[i][j] = 0;
		}
	}
	this->n_moves = 0;
}

template<typename T>
bool Tic_Tac_Toe_board<T>::update_board(int x, int y, T mark) {
	if (this->get_n_moves() == 24) {
		++this->n_moves;
		return true;
	}
	if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0)) {
		if (mark == 0) {
			this->n_moves--;
			this->board[x][y] = 0;
		}
		else {
			this->n_moves++;
			this->board[x][y] = toupper(mark);
		}
		return true;
	}
	return false;
}

template<typename T>
void Tic_Tac_Toe_board<T>::display_board() {
	if (this->n_moves <= 24) {
		for (int i = 0; i < this->rows; ++i) {
			cout << "\n+--------+--------+--------+--------+--------+\n";
			for (int j = 0; j < this->columns; ++j) {
				if (j == 0) cout << "|";
				cout << setw(2) << "(" << i << "," << j << ")" << this->board[i][j] << " |";
			}
			if (i == 4) {
				cout << "\n+--------+--------+--------+--------+--------+\n";
			}
		}
	}
}

template<typename T>
int Tic_Tac_Toe_board<T>::get_n_moves() {
	return this->n_moves;
}


template<typename T>
bool Tic_Tac_Toe_board<T>::is_win() {
	int score_X = 0, score_O = 0;
	if (this->n_moves >= 24) {
		// check rows
		for (int i = 0; i < this->rows; i++) {
			for (int j = 0; j <= this->columns - 3; j++) {
				if (this->board[i][j] == 'X' && this->board[i][j + 1] == 'X' && this->board[i][j + 2] == 'X') {
					score_X++;
				}
				if (this->board[i][j] == 'O' && this->board[i][j + 1] == 'O' && this->board[i][j + 2] == 'O') {
					score_O++;
				}
			}
		}
		//check columns
		for (int j = 0; j < this->columns; j++) {
			for (int i = 0; i <= this->rows - 3; i++) {
				if (this->board[i][j] == 'X' && this->board[i + 1][j] == 'X' && this->board[i + 2][j] == 'X') {
					score_X++;
				}
				if (this->board[i][j] == 'O' && this->board[i + 1][j] == 'O' && this->board[i + 2][j] == 'O') {
					score_O++;
				}
			}
		}
		//check diagonals
		for (int i = 0; i <= this->rows - 3; i++) {
			for (int j = 0; j <= this->columns - 3; j++) {
				if (this->board[i][j] == 'X' && this->board[i + 1][j + 1] == 'X' && this->board[i + 2][j + 2] == 'X') {
					score_X++;
				}
				if (this->board[i][j] == 'O' && this->board[i + 1][j + 1] == 'O' && this->board[i + 2][j + 2] == 'O') {
					score_O++;
				}
			}
		}
		// Check reverse diagonals
		for (int i = 0; i <= this->rows - 3; i++) {
			for (int j = 2; j < this->columns; j++) {
				if (this->board[i][j] == 'X' && this->board[i + 1][j - 1] == 'X' && this->board[i + 2][j - 2] == 'X') {
					score_X++;
				}
				if (this->board[i][j] == 'O' && this->board[i + 1][j - 1] == 'O' && this->board[i + 2][j - 2] == 'O') {
					score_O++;
				}
			}
		}
		if (score_O > score_X) {
			return true;
		}
		else if ((score_O == score_X) || (this->n_moves == 24 && score_X > score_O)) {
			return false;
		}
		else {
			return true;
		}
	}
	else {
		return false;
	}
}

template<typename T>
bool Tic_Tac_Toe_board<T>::is_draw() {
	return (this->n_moves == 25 && !is_win());
}

template<typename T>
bool Tic_Tac_Toe_board<T>::game_is_over() {
	return is_win() || is_draw();
}

template<typename T>
_5x5_tic_tac_toe_player<T>::_5x5_tic_tac_toe_player(string name, T symbol) : Player<T>(name, symbol) {}


template<typename T>
void _5x5_tic_tac_toe_player<T>::getmove(int& x, int& y) {
	if (dynamic_cast<Tic_Tac_Toe_board<T>*>(this->boardPtr)->get_n_moves() == 24) {
		x = 0, y = 0;
	}
	else {
		cout << "\nPlease enter your move x and y separated by spaces: ";
		cin >> x >> y;
	}
}

template<typename T>
_5x5_tic_tac_toe_random_player<T>::_5x5_tic_tac_toe_random_player(T symbol) : RandomPlayer<T>(symbol) {
	this->dimension = 5;
	this->name = "Random Computer Player";
	srand(static_cast<unsigned int>(time(0)));
}

template<typename T>
void _5x5_tic_tac_toe_random_player<T>::getmove(int& x, int& y) {
	x = rand() % this->dimension;
	y = rand() % this->dimension;
}


#endif
