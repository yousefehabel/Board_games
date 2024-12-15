#ifndef _WORD_TIC_TAC_TOE_H
#define _WORD_TIC_TAC_TOE_H
#include "BoardGame_Classes.h"

template<typename T>
class word_tic_tac_toe_board : public Board<T> {
public:
	word_tic_tac_toe_board();
	bool update_board(int x, int y, T symbol);
	void display_board();
	bool is_win();
	bool is_draw();
	bool game_is_over();
};

template<typename T>
class word_tic_tac_toe_player : public Player<T> {
public:
	word_tic_tac_toe_player(string name, T symbol);

	void getmove(int &x, int &y);
};

template<typename T>
class word_tic_tac_toe_random_player : public RandomPlayer<T> {
public:
	word_tic_tac_toe_random_player(T symbol);
	void getmove(int &x, int &y);
};

/*-------------------------------------------------------------------------------*/

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

template<typename T>
word_tic_tac_toe_board<T>::word_tic_tac_toe_board() {
	this->rows = this->columns = 3;
	this->board = new char *[this->rows];
	for (int i = 0; i < this->rows; i++) {
		this->board[i] = new char[this->columns];
		for (int j = 0; j < this->columns; j++) {
			this->board[i][j] = 0;
		}
	}
	this->n_moves = 0;
}

template<typename T>
bool word_tic_tac_toe_board<T>::update_board(int x, int y, T mark) {
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

template<typename T>
void word_tic_tac_toe_board<T>::display_board() {
	for (int i = 0; i < this->rows; ++i) {
		cout << "\n+--------+--------+--------+\n";
		for (int j = 0; j < this->columns; ++j) {
			if (j == 0) cout << "|";
			cout << setw(2) << "(" << i << "," << j << ")" << this->board[i][j] << " |";
		}
		if (i == 2) {
			cout << "\n+--------+--------+--------+\n";
		}
	}
}

template<typename T>
bool word_tic_tac_toe_board<T>::is_win() {
	string word;
	ifstream file_in("dic.txt");
	while (getline(file_in, word)) {
		for (int i = 0; i < this->rows; i++) {
			if ((this->board[i][0] == word[0] && this->board[i][1] == word[1] && this->board[i][2] == word[2]) ||
				(this->board[i][0] == word[2] && this->board[i][1] == word[1] && this->board[i][2] == word[0]) ||
				(this->board[0][i] == word[2] && this->board[1][i] == word[1] && this->board[2][i] == word[0]) ||
				(this->board[0][i] == word[0] && this->board[1][i] == word[1] && this->board[2][i] == word[2])) {
				return true;
			}
		}
		if ((this->board[0][0] == word[0] && this->board[1][1] == word[1] && this->board[2][2] == word[2]) ||
		    (this->board[0][2] == word[0] && this->board[1][1] == word[1] && this->board[2][0] == word[2])) {
			return true;
		}
	}
	return false;
}

template <typename T>
bool word_tic_tac_toe_board<T>::is_draw() {
	return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool word_tic_tac_toe_board<T>::game_is_over() {
	return is_win() || is_draw();
}

template <typename T>
word_tic_tac_toe_player<T>::word_tic_tac_toe_player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void word_tic_tac_toe_player<T>::getmove(int& x, int& y) {
	char c;
	cout << "\nPlease enter your move x and y (0 to 2) and the character separated by spaces: ";
	cin >> x >> y >> c;
	this->symbol = c;

}

template <typename T>
word_tic_tac_toe_random_player<T>::word_tic_tac_toe_random_player(T symbol) : RandomPlayer<T>(symbol) {
	this->dimension = 3;
	this->name = "Random Computer Player";
	srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void word_tic_tac_toe_random_player<T>::getmove(int& x, int& y) {
	x = rand() % this->dimension;
	y = rand() % this->dimension;
	int random_index = rand() % 26;
	this->symbol = 'A' + random_index;
}

#endif
