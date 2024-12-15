
#ifndef _4X4_TIC_TAC_TOE_H
#define _4X4_TIC_TAC_TOE_H
#include "BoardGame_Classes.h"

template <typename T>
class _4x4_tic_tac_toe_board : public Board<T> {
public:
	_4x4_tic_tac_toe_board();
	bool update_board(int x , int y , T symbol);
	void display_board();
	bool is_win();
	bool is_draw();
	bool game_is_over();
	T getCell(const int &x, const int &y);
};

template <typename T>
class _4x4_tic_tac_toe_player : public Player<T> {
public:
	_4x4_tic_tac_toe_player (string name, T symbol);
	void getmove(int& x, int& y) ;

};

template <typename T>
class _4x4_tic_tac_toe_random_player : public RandomPlayer<T>{
public:
	_4x4_tic_tac_toe_random_player (T symbol);
	void getmove(int &x, int &y) ;
};

/*----------------------------------------------------------------------------------*/

#include <iostream>
#include <iomanip>
using namespace std
;
template<typename T>
_4x4_tic_tac_toe_board<T>::_4x4_tic_tac_toe_board() {
	bool flag = false;
	this->rows = this->columns = 4;
	this->board = new char *[this->rows];
	for (int i = 0; i < this->rows; i++) {
		this->board[i] = new char[this->columns];
		for (int j = 0; j < this->columns; j++) {
			if (i == 0) {
				this->board[i][j] = (flag ? 'X' : 'O');
				flag = !flag;
			}
			else if (i == 3) {
				this->board[i][j] = (!flag ? 'X' : 'O');
				flag = !flag;
			}
			else {
				this->board[i][j] = 0;
			}
		}
	}
	this->n_moves = 8;
}

template <typename T>
bool _4x4_tic_tac_toe_board<T>::update_board(int x, int y, T mark) {
	if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
		if (mark == 0){
			this->n_moves--;
			this->board[x][y] = 0;
		}
		else {
			this->board[x][y] = toupper(mark);
		}

		return true;
	}
	return false;
}

template<typename T>
void _4x4_tic_tac_toe_board<T>::display_board() {
	for (int i = 0; i < this->rows; ++i) {
		cout << "\n+--------+--------+--------+--------+\n";
		for (int j = 0; j < this->columns; ++j) {
			if (j == 0) cout << "|";
			cout << setw(2) << "(" << i << "," << j << ")" << this->board[i][j] << " |";
		}
		if (i == 3) {
			cout << "\n+--------+--------+--------+--------+\n";
		}
	}
}
template <typename T>bool _4x4_tic_tac_toe_board<T>::is_win() {
	int win_length = 3;
	auto check_sequence = [&](int x, int y, int dx, int dy) {
		T first = this->board[x][y];
		if (first == 0) return false;
		for (int k = 1; k < win_length; ++k) {
			int nx = x + k * dx, ny = y + k * dy;
			if (nx < 0 || nx >= this->rows || ny < 0 || ny >= this->columns || this->board[nx][ny] != first) {
				return false;
			}
		}
		return true;
	};

	for (int i = 0; i < this->rows; ++i) {
		for (int j = 0; j < this->columns; ++j) {
			if (check_sequence(i, j, 0, 1) || // Horizontal
					check_sequence(i, j, 1, 0) || // Vertical
					check_sequence(i, j, 1, 1) || // Diagonal (top-left to bottom-right)
					check_sequence(i, j, 1, -1)) { // Diagonal (top-right to bottom-left)
				return true;
					}
		}
	}
	return false;
}

template <typename T>
bool _4x4_tic_tac_toe_board<T>::is_draw() {
	return false;
}

template <typename T>
bool _4x4_tic_tac_toe_board<T>::game_is_over() {
	return is_win() || is_draw();
}
template<typename T>
T _4x4_tic_tac_toe_board<T>::getCell(const int &x, const int &y) {
	return this->board[x][y];
}


template <typename T>
_4x4_tic_tac_toe_player<T>::_4x4_tic_tac_toe_player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void _4x4_tic_tac_toe_player<T>::getmove(int& x, int& y) {
	int i, j;
	cout << "\nPlease enter index your symbol i and j and your move x and y (0 to 3) separated by spaces: ";
	cin >> i >> j >> x >> y;
	if (((x == i && y == j - 1) || (x == i && y == j + 1) || (x == i - 1 && y == j) || (x == i + 1 && y == j)) && this->symbol == dynamic_cast<_4x4_tic_tac_toe_board<T>*>(this->boardPtr)->getCell(i, j) && this->boardPtr->update_board(x, y, this->symbol)) {
		this->boardPtr->update_board(x, y, 0);
		this->boardPtr->update_board(i, j, 0);
	} else {
		x = -1, y = -1;
	}
}


template <typename T>
_4x4_tic_tac_toe_random_player<T>::_4x4_tic_tac_toe_random_player(T symbol) : RandomPlayer<T>(symbol) {
	this->dimension = 4;
	this->name = "Random Computer Player";
	srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void _4x4_tic_tac_toe_random_player<T>::getmove(int& x, int& y) {
	vector<pair<int, int>> indices;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (dynamic_cast<_4x4_tic_tac_toe_board<T>*>(this->boardPtr)->getCell(i, j) == this->symbol) {
				indices.push_back({i, j});
			}
		}
	}
	int random_index = rand() % indices.size();
	this->boardPtr->update_board(indices[random_index].first, indices[random_index].second, 0);
	vector<pair<int, int>> moves;
	if (this->boardPtr->update_board(indices[random_index].first + 1, indices[random_index].second, this->symbol)) {
		this->boardPtr->update_board(indices[random_index].first + 1, indices[random_index].second, 0);
		moves.push_back({indices[random_index].first + 1, indices[random_index].second});
	} else if (this->boardPtr->update_board(indices[random_index].first - 1, indices[random_index].second, this->symbol)) {
		this->boardPtr->update_board(indices[random_index].first - 1, indices[random_index].second, 0);
		moves.push_back({indices[random_index].first - 1, indices[random_index].second});
	} else if (this->boardPtr->update_board(indices[random_index].first, indices[random_index].second + 1, this->symbol)) {
		this->boardPtr->update_board(indices[random_index].first, indices[random_index].second + 1, 0);
		moves.push_back({indices[random_index].first, indices[random_index].second + 1});
	} else if (this->boardPtr->update_board(indices[random_index].first, indices[random_index].second - 1, this->symbol)) {
		this->boardPtr->update_board(indices[random_index].first, indices[random_index].second - 1, 0);
		moves.push_back({indices[random_index].first, indices[random_index].second - 1});
	}
	random_index = rand() % moves.size();
	x = moves[random_index].first;
	y = moves[random_index].second;
}
#endif
