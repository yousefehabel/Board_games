#ifndef _PYRAMID_TIC_TAC_TOE_H
#define _PYRAMID_TIC_TAC_TOE_H
#include "BoardGame_Classes.h"
template <typename T>
class pyramid_tic_tac_toe_board : public Board<T>{
public:
	pyramid_tic_tac_toe_board();
	bool update_board(int x, int y, T symbol);
	void display_board();
	bool is_win();
	bool is_draw();
	bool game_is_over();

};
template <typename T>
class pyramid_tic_tac_toe_player : public Player<T> {
public:
	pyramid_tic_tac_toe_player (string name, T symbol);
	void getmove(int& x, int& y) ;
};
template <typename T>
class pyramid_tic_tac_toe_random_player : public RandomPlayer<T> {
public:
	pyramid_tic_tac_toe_random_player (T symbol);
	void getmove(int &x, int &y);
};

/*-------------------------------------------------------------------------------*/

#include <iostream>
#include <iomanip>
using namespace std;
template<typename T>
pyramid_tic_tac_toe_board<T>::pyramid_tic_tac_toe_board() {
	this->rows = this->columns = 5;
	this->board = new char*[this->rows];
	for (int i = 0; i < this->rows; ++i) {
		this->board[i] = new char[this->columns];
		for (int j = 0; j < this->columns; ++j) {
			this->board[i][j] = 0;
		}
	}
	this->n_moves = 0;
}

template<typename T>
bool pyramid_tic_tac_toe_board<T>::update_board(int x, int y, T mark) {
	if (((x == 2 && y == 2) || (x == 3 && y < this->columns - 1 && y > 0) || (x == 4 && y < this->columns)) && (this->board[x][y] == 0 || mark == 0)) {
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
void pyramid_tic_tac_toe_board<T>::display_board() {
	for (int i = 2; i < 5; ++i) {
		if (i == 2) {
			cout << "\n\t\t  +--------+\n" << setw(19);
		}
		else if (i == 3) {
			cout << "\n\t +--------+--------+--------+\n" << setw(10);
		}
		else {
			cout << "\n+--------+--------+--------+--------+--------+\n";
		}
		for (int j = 4 - i; j < i + 1; ++j) {
			if ((i == 2 && j == 2) || (i == 3 && j == 1) || (i == 4 && j == 0)) {
				cout << "|";
			}
			cout << setw(2) << "(" << i << "," << j << ")" << this->board[i][j] << " |";
		}
		if (i == 4) {
			cout << "\n+--------+--------+--------+--------+--------+\n";
		}
	}
}

template<typename T>
bool pyramid_tic_tac_toe_board<T>::is_win() {
	if ((this->board[2][2] == this->board[3][1] && this->board[3][1] == this->board[4][0] && this->board[2][2] != 0) || (this->board[2][2] == this->board[3][3] && this->board[3][3] == this->board[4][4] && this->board[2][2] != 0)) {
		return true;
	}
	if ((this->board[3][1] == this->board[3][2] && this->board[3][2] == this->board[3][3] && this->board[3][1] != 0) || (this->board[2][2] == this->board[3][2] && this->board[3][2] == this->board[4][2] && this->board[2][2] != 0)) {
		return true;
	}
	for (int i = 0; i < 3; ++i) {
		if (this->board[4][i] == this->board[4][i + 1] && this->board[4][i + 1] == this->board[4][i + 2] && this->board[4][i] != 0) {
			return true;
		}
	}
	return false;
}

template<typename T>
bool pyramid_tic_tac_toe_board<T>::is_draw() {
	return (this->n_moves == 9 && !is_win());
}

template<typename T>
bool pyramid_tic_tac_toe_board<T>::game_is_over() {
	return is_win() || is_draw();
}

template<typename T>
pyramid_tic_tac_toe_player<T>::pyramid_tic_tac_toe_player(string name, T symbol) : Player<T>(name, symbol) {}
template<typename T>
void pyramid_tic_tac_toe_player<T>::getmove(int &x, int &y) {
	cout << "\nPlease enter your move x and y separated by spaces: ";
	cin >> x >> y;
}

template<typename T>
pyramid_tic_tac_toe_random_player<T>::pyramid_tic_tac_toe_random_player(T symbol) : RandomPlayer<T>(symbol) {
	// this->dimension = 5;
	this->name = "Random Computer Player";
	srand(static_cast<unsigned int>(time(0)));
}

template<typename T>
void pyramid_tic_tac_toe_random_player<T>::getmove(int &x, int &y) {
	vector<pair<int, int>> valid_moves = {
		{2, 2}, {3, 1}, {3, 2}, {3, 3},
		{4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 4}
	};
	int random_index = rand() % valid_moves.size();
	x = valid_moves[random_index].first;
	y = valid_moves[random_index].second;
}



#endif
