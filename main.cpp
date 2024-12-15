#include <iostream>
#include "4x4_tic_tac_toe.h"
#include "5x5_tic_tac_toe.h"
#include "BoardGame_Classes.h"
#include "FourInARow.h"
#include "NumericalTicTacToe.h"
#include "PyramidMinMaxPlayer.h"
#include "misere_tic_tac_toe.h"
#include "pyramid_tic_tac_toe.h"
#include "ultimateX_O.h"
#include "word_tic_tac_toe.h"
void menu() {
	int c, choice;
	string player1Name, player2Name;
	do {
		cout << "Welcome to FCAI Games.\n";
		cout << "Choose the game:\n";
		cout << "1. Pyramic Tic-Tac-Toe\n";
		cout << "2. Four-in-a-row\n";
		cout << "3. 5x5 Tic-Tac-Toe\n";
		cout << "4. Word Tic-Tac-Toe\n";
		cout << "5. Numerical Tic-Tac-Toe\n";
		cout << "6. Misere Tic-Tac-Toe\n";
		cout << "7. 4x4 Tic-Tac-Toe\n";
		cout << "8. Ultimate Tic-Tac-Toe\n";
		cout << "9. Exit\n";
		cin >> c;
		if (c == 1) {
			Player<char> *players[2];
			pyramid_tic_tac_toe_board<char> *B = new pyramid_tic_tac_toe_board<char>();
			cout << "Welcome to Pyramic Tic-Tac-Toe Game.\n";
			// Set up player 1
			cout << "Enter Player X name: ";
			cin >> player1Name;
			cout << "Choose Player X type:\n";
			cout << "1. Human\n";
			cout << "2. Random Computer\n";
			cout << "3. Smart Computer (AI)\n";
			cin >> choice;
			switch (choice) {
				case 1:
					players[0] = new pyramid_tic_tac_toe_player<char>(player1Name, 'X');
					break;
				case 2:
					players[0] = new pyramid_tic_tac_toe_random_player<char>('X');
					break;
				case 3:
					players[0] = new p_tic_tac_toe_MinMax_Player<char>('X');
					players[0]->setBoard(B);
					break;
				default:
					cout << "Invalid choice for Player 1. Exiting the program.\n";
					return;
			}

			// Set up player 2
			cout << "Enter Player 2 name: ";
			cin >> player2Name;
			cout << "Choose Player 2 type:\n";
			cout << "1. Human\n";
			cout << "2. Random Computer\n";
			cout << "3. Smart Computer (AI)\n";
			cin >> choice;

			switch (choice) {
				case 1:
					players[1] = new pyramid_tic_tac_toe_player<char>(player1Name, 'O');
					break;
				case 2:
					players[1] = new pyramid_tic_tac_toe_random_player<char>('O');
					break;
				case 3:
					players[1] = new p_tic_tac_toe_MinMax_Player<char>('O');
					players[1]->setBoard(B);
					break;
				default:
					cout << "Invalid choice for Player 2. Exiting the program.\n";
					return;
			}
			// Create the game manager and run the game
			GameManager<char> pyramid_tic_tac_toe_game(B, players);
			pyramid_tic_tac_toe_game.run();
			// Clean up
			delete B;
			for (int i = 0; i < 2; ++i) {
				delete players[i];
			}
		} else if (c == 2) {
			Player<char> *players[2];
			FourInARowBoard<char> *B = new FourInARowBoard<char>();
			cout << "Welcome to Four-in-a-row Game.\n";
			// Set up player 1
			cout << "Enter Player X name: ";
			cin >> player1Name;
			cout << "Choose Player X type:\n";
			cout << "1. Human\n";
			cout << "2. Random Computer\n";
			cin >> choice;
			switch (choice) {
				case 1:
					players[0] = new FourInARowPlayer<char>(player1Name, 'X');
					break;
				case 2:
					players[0] = new fourinrowRandom_Player<char>('X');
					break;
				default:
					cout << "Invalid choice for Player X. Exiting the program.\n";
					return;
			}
			// Set up player 2
			cout << "Enter Player O name: ";
			cin >> player2Name;
			cout << "Choose Player O type:\n";
			cout << "1. Human\n";
			cout << "2. Random Computer\n";
			cin >> choice;
			switch (choice) {
				case 1:
					players[1] = new FourInARowPlayer<char>(player2Name, 'O');
					break;
				case 2:
					players[1] = new fourinrowRandom_Player<char>('O');
					break;
				default:
					cout << "Invalid choice for Player O. Exiting the program.\n";
					return;
			}
			GameManager<char> four_in_a_row_game(B, players);
			four_in_a_row_game.run();
			// Clean up
			delete B;
			for (int i = 0; i < 2; ++i) {
				delete players[i];
			}
		} else if (c == 3) {
			Player<char> *players[2];
			Tic_Tac_Toe_board<char> *B = new Tic_Tac_Toe_board<char>();
			cout << "Welcome to 5x5 Tic-Tac-Toe Game.\n";
			// Set up player 1
			cout << "Enter Player X name: ";
			cin >> player1Name;
			cout << "Choose Player X type:\n";
			cout << "1. Human\n";
			cout << "2. Random Computer\n";
			cin >> choice;
			switch (choice) {
				case 1:
					players[0] = new _5x5_tic_tac_toe_player<char>(player1Name, 'X');
					players[0]->setBoard(B);
					break;
				case 2:
					players[0] = new _5x5_tic_tac_toe_random_player<char>('X');
					players[0]->setBoard(B);
					break;
				default:
					cout << "Invalid choice for Player 1. Exiting the program.\n";
					return;
			}
			// Set up player 2
			cout << "Enter Player 2 name: ";
			cin >> player2Name;
			cout << "Choose Player 2 type:\n";
			cout << "1. Human\n";
			cout << "2. Random Computer\n";
			cin >> choice;
			switch (choice) {
				case 1:
					players[1] = new _5x5_tic_tac_toe_player<char>(player2Name, 'O');
					players[1]->setBoard(B);
					break;
				case 2:
					players[1] = new _5x5_tic_tac_toe_random_player<char>('O');
					players[1]->setBoard(B);
					break;
				default:
					cout << "Invalid choice for Player 2. Exiting the program.\n";
					return;
			}
			// Create the game manager and run the game
			GameManager<char> _5x5_tic_tac_toe_game(B, players);
			_5x5_tic_tac_toe_game.run();
			// Clean up
			delete B;
			for (int i = 0; i < 2; ++i) {
				delete players[i];
			}
		} else if (c == 4) {
			Player<char> *players[2];
			word_tic_tac_toe_board<char> *B = new word_tic_tac_toe_board<char>();
			cout << "Welcome to Word Tic-Tac-Toe Game. :)\n";
			// Set up player 1
			cout << "Enter Player 1 name: ";
			cin >> player1Name;
			cout << "Choose Player 1 type:\n";
			cout << "1. Human\n";
			cout << "2. Random Computer\n";
			cin >> choice;
			switch (choice) {
				case 1:
					players[0] = new word_tic_tac_toe_player<char>(player1Name, 0);
					break;
				case 2:
					players[0] = new word_tic_tac_toe_random_player<char>(0);
					break;
				default:
					cout << "Invalid choice for Player 1. Exiting the program.\n";
					return;
			}
			// Set up player 2
			cout << "Enter Player 2 name: ";
			cin >> player2Name;
			cout << "Choose Player 2 type:\n";
			cout << "1. Human\n";
			cout << "2. Random Computer\n";
			cin >> choice;
			switch (choice) {
				case 1:
					players[1] = new word_tic_tac_toe_player<char>(player2Name, 0);
					break;
				case 2:
					players[1] = new word_tic_tac_toe_random_player<char>(0);
					break;
				default:
					cout << "Invalid choice for Player 2. Exiting the program.\n";
					return;
			}
			// Create the game manager and run the game
			GameManager<char> word_tic_tac_toe_game(B, players);
			word_tic_tac_toe_game.run();
			// Clean up
			delete B;
			for (int i = 0; i < 2; ++i) {
				delete players[i];
			}
		} else if (c == 5) {
			Player<char> *players[2];
			NumericalTicTacToeBoard<char> *B = new NumericalTicTacToeBoard<char>();
			cout << "Welcome to Numerical Tic-Tac-Toe.\n";
			// Set up player 1
			cout << "Enter Player 1 name: ";
			cin >> player1Name;
			cout << "Choose Player 1 type:\n";
			cout << "1. Human\n";
			cout << "2. Random Computer\n";
			cin >> choice;
			switch (choice) {
				case 1:
					players[0] = new NumericalTicTacToePlayer<char>(player1Name, 'X');
					break;
				case 2:
					players[0] = new NumericalTicTacToeRandomPlayer<char>('X');
					break;
				default:
					cout << "Invalid choice for Player 1. Exiting the program.\n";
					return;
			}
			// Set up player 2
			cout << "Enter Player 2 name: ";
			cin >> player2Name;
			cout << "Choose Player 2 type:\n";
			cout << "1. Human\n";
			cout << "2. Random Computer\n";
			cin >> choice;
			switch (choice) {
				case 1:
					players[1] = new NumericalTicTacToePlayer<char>(player2Name, 'O');
					break;
				case 2:
					players[1] = new NumericalTicTacToeRandomPlayer<char>('O');
					break;
				default:
					cout << "Invalid choice for Player 2. Exiting the program.\n";
					return;
			}
			GameManager<char> numericalTicTacToegame(B, players);
			numericalTicTacToegame.run();
			// Clean up
			delete B;
			for (int i = 0; i < 2; ++i) {
				delete players[i];
			}
		} else if (c == 6) {
			Player<char> *players[2];
			misere_tic_tac_toe_board<char> *B = new misere_tic_tac_toe_board<char>();
			cout << "Welcome to Misere Tic-Tac-Toe Game.\n";
			// Set up player 1
			cout << "Enter Player X name: ";
			cin >> player1Name;
			cout << "Choose Player X type:\n";
			cout << "1. Human\n";
			cout << "2. Random Computer\n";
			cin >> choice;
			switch (choice) {
				case 1:
					players[0] = new misere_tic_tac_toe_player<char>(player1Name, 'X');
					players[0]->setBoard(B);
					break;
				case 2:
					players[0] = new misere_tic_tac_toe_random_player<char>('X');
					players[0]->setBoard(B);
					break;
				default:
					cout << "Invalid choice for Player 1. Exiting the program.\n";
					return;
			}
			// Set up player 2
			cout << "Enter Player 2 name: ";
			cin >> player2Name;
			cout << "Choose Player 2 type:\n";
			cout << "1. Human\n";
			cout << "2. Random Computer\n";
			cin >> choice;
			switch (choice) {
				case 1:
					players[1] = new misere_tic_tac_toe_player<char>(player2Name, 'O');
					players[1]->setBoard(B);
					break;
				case 2:
					players[1] = new misere_tic_tac_toe_random_player<char>('O');
					players[1]->setBoard(B);
					break;
				default:
					cout << "Invalid choice for Player 2. Exiting the program.\n";
					return;
			}
			// Create the game manager and run the game
			GameManager<char> misere_tic_tac_toe_game(B, players);
			misere_tic_tac_toe_game.run();
			// Clean up
			delete B;
			for (int i = 0; i < 2; ++i) {
				delete players[i];
			}
		} else if (c == 7) {
			Player<char> *players[2];
			_4x4_tic_tac_toe_board<char> *B = new _4x4_tic_tac_toe_board<char>();
			cout << "Welcome to 4x4 Tic-Tac-Toe Game.\n";
			// Set up player 1
			cout << "Enter Player X name: ";
			cin >> player1Name;
			cout << "Choose Player X type:\n";
			cout << "1. Human\n";
			cout << "2. Random Computer\n";
			cin >> choice;
			switch (choice) {
				case 1:
					players[0] = new _4x4_tic_tac_toe_player<char>(player1Name, 'X');
					players[0]->setBoard(B);
					break;
				case 2:
					players[0] = new _4x4_tic_tac_toe_random_player<char>('X');
					players[0]->setBoard(B);
					break;
				default:
					cout << "Invalid choice for Player X. Exiting the program.\n";
					return;
			}
			// Set up player 2
			cout << "Enter Player 2 name: ";
			cin >> player2Name;
			cout << "Choose Player 2 type:\n";
			cout << "1. Human\n";
			cout << "2. Random Computer\n";
			cin >> choice;
			switch (choice) {
				case 1:
					players[1] = new _4x4_tic_tac_toe_player<char>(player2Name, 'O');
					players[1]->setBoard(B);
					break;
				case 2:
					players[1] = new _4x4_tic_tac_toe_random_player<char>('O');
					players[1]->setBoard(B);
					break;
				default:
					cout << "Invalid choice for Player O. Exiting the program.\n";
					return;
			}
			// Create the game manager and run the game
			GameManager<char> _4x4_tic_tac_toe_game(B, players);
			_4x4_tic_tac_toe_game.run();
			// Clean up
			delete B;
			for (int i = 0; i < 2; ++i) {
				delete players[i];
			}
		} else if (c == 8) {
			Player<char> *players[2];
			Ult_X_OBoard<char> *B = new Ult_X_OBoard<char>();

			// Set up player 1
			cout << "Enter Player X name: ";
			cin >> player1Name;
			cout << "Choose Player X type:\n";
			cout << "1. Human\n";
			cout << "2. Random Computer\n";
			cin >> choice;
			switch (choice) {
				case 1:
					players[0] = new X_O_ULT_player<char>(player1Name, 'X');
					break;
				case 2:
					players[0] = new X_O_ULT_Random_player<char>('X');
					break;
				default:
					cout << "Invalid choice for Player X. Exiting the program.\n";
					return;
			}
			// Set up player 2
			cout << "Enter Player O name: ";
			cin >> player2Name;
			cout << "Choose Player O type:\n";
			cout << "1. Human\n";
			cout << "2. Random Computer\n";
			cin >> choice;
			switch (choice) {
				case 1:
					players[1] = new X_O_ULT_player<char>(player2Name, 'O');
					break;
				case 2:
					players[1] = new X_O_ULT_Random_player<char>('O');
					break;
				default:
					cout << "Invalid choice for Player O. Exiting the program.\n";
					return;
			}
			GameManager<char> UltimateXO(B, players);
			UltimateXO.run();
			// Clean up
			delete B;
			for (int i = 0; i < 2; ++i) {
				delete players[i];
			}
		} else if (c == 9) {
			return;
		} else {
			cout << "Invalid choice, please try again\n";
		}
	} while (1);
}

int main() {
	menu();
}
