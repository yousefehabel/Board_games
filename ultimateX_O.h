#ifndef _Ultimate_X_O_H
#define _Ultimate_X_O_H

#include "BoardGame_Classes.h"
#include <vector>
#include "3x3X_O.h"
template <typename T>
class Ult_X_OBoard:public Board<T>
{
private:
    vector<pair<int ,int>>PLyr;
    X_O_Board<char>* x_o_board;
    int X_NOW;
    int Y_NOW;
public:
    Ult_X_OBoard ();
    static  int nn;
    static  int X;
    static  int Y;
    bool update_board (int x , int y , T mark);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class X_O_ULT_player : public Player<T> {
public:
    X_O_ULT_player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class X_O_ULT_Random_player : public RandomPlayer<T>{
public:
    X_O_ULT_Random_player (T symbol);
    void getmove(int &x, int &y) ;
};

//_____________________________________________________________________________________________
#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

template <typename T>

Ult_X_OBoard<T>::Ult_X_OBoard()
{
    X_NOW = -1;
    Y_NOW = -1;
    this->rows = 9;
    this->columns = 9;
    this->n_moves = 0;
    this->board = new char*[this->rows];
    for(int i = 0;i<this->rows;i++)
    {
        this->board[i] = new char[this->columns];
        for(int j = 0; j<this->columns; j++)
        {
            this->board[i][j] = 0;
        }
    }
    x_o_board = new X_O_Board<char>();
}

template<class T>
bool Ult_X_OBoard<T>::update_board(int gridX, int gridY, T mark)
{
    int nnn = 0;
    if(gridX==-1&&gridX==-1)
    {
        if(nn==0) {
            gridX=rand()%3;
            gridY=rand()%3;
            for( auto & i:PLyr ) {
                if(i.first==gridX&&i.second==gridY) {
                    nn=0;
                    return false;
                }
            }
        }else {
            gridX=X;
            gridY=Y;
            for( auto & i : PLyr ) {
                if(i.first==gridX&&i.second==gridY) {
                    nn=0;
                    return false;
                }
            }
        }
        X_NOW = gridX;
        Y_NOW = gridY;
        int FirstX = gridX * 3;
        int FirstY = gridY * 3;
        for (int i = FirstX; i < FirstX + 3; i++)
        {
            for (int i2 = FirstY; i2 < FirstY + 3; i2++)
            {
                if (this->board[i][i2] =='O'||this->board[i][i2] =='X')
                {
                    nnn++;
                }
            }
        }
        if(nnn<9) {
            int subX ,x1,y1;
            int subY;
            do {
                subX=rand()%3;
                subY=rand()%3;
                x1 = gridX * 3 + subX;
                y1 = gridY * 3 + subY;
            }while(this->board[x1][y1] == 'X' || this->board[x1][y1] == 'O');
            if (!(x1 < 0 || x1 >= this->rows || y1 < 0 || y1 >= this->columns) && (this->board[x1][y1] == 0 || mark == 0))
            {
                if (mark == 0)
                {
                    this->n_moves--;
                    this->board[x1][y1] = 0;
                }
                else
                {
                    this->n_moves++;
                    this->board[x1][y1] = toupper(mark);
                }
            }
            X = subX;
            Y = subY;
            nn = 0;
            return true;
        }
        return false;
    }{
        for( auto & i:PLyr ) {
            if(i.first==gridX&&i.second==gridY) {
                return false;
            }
        }
        if (gridX > 2 || gridX < 0 || gridY > 2 || gridY < 0)
        {
            return false;
        }
        X_NOW = gridX;
        Y_NOW = gridY;
        int FirstX = gridX * 3;
        int FirstY = gridY * 3;
        for (int i = FirstX; i < FirstX + 3; i++)
        {
            for (int i2 = FirstY; i2 < FirstY + 3; i2++)
            {
                if (this->board[i][i2] =='O'||this->board[i][i2] =='X')
                {
                    nnn++;
                }
            }
        }
        if(nnn<9)
        {
            cout << "Please enter your move x and y (0 to 2)" << endl;
            int subX, subY;
            cin >> subX >> subY;
            while (subX > 2 || subX < 0 || subY > 2 || subY < 0)
            {
                cout << "invalid. Enter new x and y (0 to 2): ";
                cin >> subX >> subY;
            }
            int x1 = gridX * 3 + subX;
            int y1 = gridY * 3 + subY;
            while ((this->board[x1][y1] == 'X' || this->board[x1][y1] == 'O') )
            {
                cout << "Place already taken. Please enter new x and y: ";
                cin >> subX >> subY;
                x1 = gridX * 3 + subX;
                y1 = gridY * 3 + subY;
            }
            if (!(x1 < 0 || x1 >= this->rows || y1 < 0 || y1 >= this->columns) && (this->board[x1][y1] == 0 || mark == 0))
            {
                if (mark == 0)
                {
                    this->n_moves--;
                    this->board[x1][y1] = 0;
                }
                else
                {
                    this->n_moves++;
                    this->board[x1][y1] = toupper(mark);
                }
            }
            X = subX;
            Y = subY;

            nn = 0;
            return true;
        }
        return false;
    }

}

template <typename T>
void Ult_X_OBoard<T>::display_board()
{
    cout << "            (0,0)                         (0,1)                           (0,2)      \n";
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            int localRow = i % 3, localCol = j % 3;

            cout <<  "(" << localRow << "," << localCol << ")";
            cout << ' ' << this->board[i][j] << ' ';
            if ((j + 1) % 3 == 0 && j < 8)
            {
                cout << " |*| ";
            }
            else if(j != 8)
            {
                cout << "| ";
            }
        }
        cout << '\n';
        if ((i + 1) % 3 == 0 && i < 8)
        {
            if(i == 2)
            {
                cout << "__________________________________________________________________________________________";
                cout << '\n';
                cout << "           (1,0)                        (1,1)                          (1,2)      \n";
            }
            else if(i == 5)
            {
                cout << "__________________________________________________________________________________________";
                cout << '\n';
                cout << "           (2,0)                        (2,1)                          (2,2)      \n";
            }

        }
        else if(i != 8)
        {
            cout << "---------------------------     ---------------------------     ---------------------------";
            cout << '\n';
        }
    }
    cout << "\n \n \n ";
}

template <typename T>
bool Ult_X_OBoard<T>::is_draw() {
    return (this->n_moves == 81 && !is_win());
}

// Return tru if there is winner
template <typename T>
bool Ult_X_OBoard<T>::is_win()
{
    if(X_NOW != -1 && Y_NOW != -1)
    {
        vector< vector<char> > vc(3,vector<char>(3,0));
        int temp_x = X_NOW,temp_y = Y_NOW;
        int idx1 = 0,idx2 = 0;
        for(int i = (X_NOW * 3);i < (X_NOW * 3) + 3 ;i++)
        {

            for(int j = (Y_NOW * 3);j < (Y_NOW * 3) + 3;j++)
            {
                vc[idx1][idx2++] = this->board[i][j];
            }
            idx1++;   idx2 = 0;
        }
        //__________________________________________________________________
        for (int i = 0; i < vc.size(); i++)
        {
            if(vc[i][0] == vc[i][1] && vc[i][1] == vc[i][2] && vc[i][0] != 0)
            {
                if(vc[i][0] == 'X')
                {
                    x_o_board->update_board(temp_x,temp_y,'X');
                }
                else
                {
                    x_o_board->update_board(temp_x,temp_y,'O');
                }
                PLyr.emplace_back(temp_x,temp_y);
            }
            if(vc[0][i] == vc[1][i] && vc[1][i] == vc[2][i] && vc[0][i] != 0)
            {
                if(vc[0][i] == 'X')
                {
                    x_o_board->update_board(temp_x,temp_y,'X');
                }
                else
                {
                    x_o_board->update_board(temp_x,temp_y,'O');
                }
                PLyr.emplace_back(temp_x,temp_y);
            }
        }
        //________________________________________________
        if(vc[0][0] == vc[1][1] && vc[1][1] == vc[2][2] && vc[0][0] != 0)
        {
            if(vc[0][0] == 'X')
            {
                x_o_board->update_board(temp_x,temp_y,'X');
            }
            else
            {
                x_o_board->update_board(temp_x,temp_y,'O');
            }
            PLyr.emplace_back(temp_x,temp_y);
        }
        if(vc[0][2] == vc[1][1] && vc[1][1] == vc[2][0] && vc[0][2] != 0)
        {
            if(vc[0][2] == 'X')
            {
                x_o_board->update_board(temp_x,temp_y,'X');
            }
            else
            {
                x_o_board->update_board(temp_x,temp_y,'O');
            }
            PLyr.emplace_back(temp_x,temp_y);
        }
        if(x_o_board->is_win())
        {
            return true;
        }
    }
    return false;
}

template <typename T>
bool Ult_X_OBoard<T>::game_is_over()
{
    return ( is_win() || is_draw() );
}
//_______________________________________________________________________________________________________________________
// Constructor for X_O_Player
template <typename T>
X_O_ULT_player<T>::X_O_ULT_player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void X_O_ULT_player<T>::getmove(int& x, int& y)
{
    if ( Ult_X_OBoard<T>::nn== 0)
    {
        string inX,inY;
        while (true)
        {
            cout << "Please enter your move x and y (0 to 2)" << endl;
            cin >> inX >> inY;

            stringstream ss1(inX);
            stringstream ss2(inY);
            if ((ss1 >> x && ss1.eof()) && (ss2 >> y && ss2.eof()) && (x != -1 && y != -1))
            {
                break;
            }
            else
            {
                cout << "Enter integer values Please " << endl;
            }
        }
    }
    else
    {
        x = Ult_X_OBoard<T>::X;
        y = Ult_X_OBoard<T>::Y;
        Ult_X_OBoard<T>::nn = 0;
    }
}
// Constructor for X_O_Random_Player
template <typename T>
X_O_ULT_Random_player<T>::X_O_ULT_Random_player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  
}

template <typename T>
void X_O_ULT_Random_player<T>::getmove(int& x, int& y) {
    x=-1;
    y=-1;
}
//_____________________________________________________________________________________________________
template<class T>
int Ult_X_OBoard<T>::nn= 0;

template<class T>
int Ult_X_OBoard<T>::X= -1;

template<class T>
int Ult_X_OBoard<T>::Y= -1;

#endif 