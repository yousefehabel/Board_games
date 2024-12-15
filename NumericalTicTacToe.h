#ifndef _NUMERICAL_TIC_TAC_TOE_H
#define _NUMERICAL_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <vector>
#include <set>
#include <algorithm>
#include <iomanip>
using namespace std;

template <typename T>
class NumericalTicTacToeBoard:public Board<T> {
public:
    NumericalTicTacToeBoard ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
private:
    set<int> used_numbers;
    vector<int>AvailableNumbersP1 = {1, 3, 5, 7, 9};
    vector<int>AvailableNumbersP2 = {2, 4, 6, 8};
};

template <typename T>
class NumericalTicTacToePlayer : public Player<T> {
public:
    NumericalTicTacToePlayer (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class NumericalTicTacToeRandomPlayer : public RandomPlayer<T>{
public:
    NumericalTicTacToeRandomPlayer(T symbol);
    void getmove(int &x, int &y) ;
};

//Board to be displayed 
template<class T>
NumericalTicTacToeBoard<T>::NumericalTicTacToeBoard(){
    this->rows = 3;
    this->columns = 3;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) 
    {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) 
        {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}
//update board after each move.
template <typename T>
bool NumericalTicTacToeBoard<T>::update_board(int x, int y, T symbol) {
    if(x == -1 && y == -1) {

        if(symbol == 'X') {
            while (true) {
                x = rand() % this->rows;
                y = rand() % this->columns;
               int rand_number = ((rand() % 5) * 2 + 1);

               if(used_numbers.count(rand_number) == 0 && this->board[x][y] == 0) {
                    used_numbers.insert(rand_number);
                    this->board[x][y] = rand_number + '0';
                    this->n_moves++;
                    return true;
               }
            } 
        } else if (symbol == 'O') {

            while (true) {
                x = rand() % this->rows;
                y = rand() % this->columns;
               int rand_number = ((rand() % 5) * 2);
               if(used_numbers.count(rand_number) == 0 && this->board[x][y] == 0 && rand_number != 0 ) {
                    used_numbers.insert(rand_number);
                    this->board[x][y] = rand_number + '0';
                    this->n_moves++;
                    return true;
               }
            }
        }
    }
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != 0 )  {
        return false;
    }
    while (true) {
        cout << "Available numbers" ;
        if (symbol == 'X'){
            for (const auto& n : AvailableNumbersP1)
            {
                cout << n << " ";
            }
            cout << endl;
        }else if (symbol == 'O') {
            for (const auto& n : AvailableNumbersP2)
            {
                cout << n << " ";
            }
            cout << endl;
        }
        string number;
        int num;
        while (true){
            cout << "Enter num" << endl;
            cin >> number;
            stringstream s1(number);
            if ((s1 >> num && s1.eof())  )
            {
                break;
            }
            else
            {
                cout << "===== Please enter int values =====" << endl;
            }
        }if (symbol == 'X') {
            if (num % 2 == 1 && num >= 1 && num <= 9 && used_numbers.count(num) == 0) 
            {
                this->board[x][y] = num + '0';
                used_numbers.insert(num);
                AvailableNumbersP1.erase(remove(AvailableNumbersP1.begin(), AvailableNumbersP1.end(), num));
                this->n_moves++;
                return true;
            }
        }else if (symbol == 'O') {
            
            if (num % 2 == 0 && num > 0 && num <= 8 && used_numbers.count(num) == 0) {
                this->board[x][y] = num + '0';
                used_numbers.insert(num);
                AvailableNumbersP2.erase(remove(AvailableNumbersP2.begin(), AvailableNumbersP2.end(), num));
                this->n_moves++;
                return true;
            }
        }
        cout << "Invalid num , Please try again.\n";
    }
}
// display the board
template <typename T>
void NumericalTicTacToeBoard<T>::display_board(){
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++){
            cout << "     ";
            cout << setw(3) << this->board[i][j] << " |";
        }
        cout << "\n______________________________";
    }
    cout << "\n \n \n ";
    cout << endl;
}
// check if player won
template <typename T>
bool NumericalTicTacToeBoard<T>::is_win() {
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] - '0') + (this->board[i][1] - '0') + (this->board[i][2] - '0') == 15) {
            return true;
        }
    }
    for (int j = 0; j < this->columns; j++){
        if ((this->board[0][j] - '0') + (this->board[1][j] - '0') + (this->board[2][j] - '0') == 15) {
            return true;
        }
    }
    if ((this->board[0][0] - '0') + (this->board[1][1] - '0') + (this->board[2][2] - '0') == 15) {
        return true;
    }
    if ((this->board[2][0] - '0') + (this->board[1][1] - '0') + (this->board[0][2] - '0') == 15) {
        return true;
    }
    return false;
}
//check for draw

template <typename T>
bool NumericalTicTacToeBoard<T>::is_draw() {
    return (this->n_moves == this->rows * this->columns && !is_win());
}

template <typename T>
bool NumericalTicTacToeBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
NumericalTicTacToePlayer<T>::NumericalTicTacToePlayer(string name, T symbol) : Player<T>(name, symbol) {}
//------------------------------------------
template <typename T>
void NumericalTicTacToePlayer<T>::getmove(int& x, int& y) {
    string inX,inY;
    while (true){
        cout << "Enter row and column: " << endl;
        cin >> inX >> inY;
        stringstream s1(inX);
        stringstream s2(inY);
        if ((s1 >> x && s1.eof()) && (s2 >> y && s2.eof()) && (x != -1 && y != -1) ){
            break;
        }else{
            cout << "===== Please enter int values =====" << endl;
        }
    }
}
template<class T>
NumericalTicTacToeRandomPlayer<T>::NumericalTicTacToeRandomPlayer(T symbol) :RandomPlayer<T>(symbol){  
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}
template <typename T>
void NumericalTicTacToeRandomPlayer<T>::getmove(int& x, int& y) {
    y = -1;
    x = -1; 
}
#endif