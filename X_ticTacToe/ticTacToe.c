//Date: 2023.08.18
//Purpose: TicTacToe game for 2 local players in console
//BUGS: Line 75 New Game Choice: Once you type y or n, you have to do again, it does not recognize the first input. Maybe buffer issue.
//BUGS: When you win, last character does not get drawn
//BUGS: Not all rows and columns checks right for winner
//TBD: Diagonal check for winner
//TBD: When no more steps is possible, give DRAW text and ask for a new game.

#include <stdio.h>
#include <stdlib.h>

/*Function prototypes*/
void showBoard(char board[3][3]);
void updateBoard(char board[3][3], int input, int *playerTurn);
int getInput(void);
void changePlayerTurn(int *turn);
char checkWinner(char board[3][3]);

/*Global variables*/

int showErrorMessageOccupied = 0;
int showErrorMessageValidNum = 0;

/*Main game loop*/
int main() {
	int playerTurn = 1;
	int input = 1;
	char winner = ' ';
	char isNewGame = ' ';
	int gameRunning = 1;

	char board[3][3] = {
		{'1','2','3'},
		{'4','5','6'},
		{'7','8','9'},
	};

	while (1) {
		while (gameRunning == 1) {
			printf("\t Tic Tac Toe\n \n");
			printf("Player 1 (X) - Player 2 (O)\n\n");
			showBoard(board);
			printf("\nPlayer %i, enter a number: ", playerTurn);

			//printf("\nDEBUG: input is:%i \n", input);
			//Gives error message for invalid numbers. Valid numbers: 1-9
			if (showErrorMessageValidNum == 1)
			{
				printf("\nInvalid number. Choose from 1 to 9!\n");;
				showErrorMessageValidNum = 0;
			}

			if (showErrorMessageOccupied == 1) {
				printf("\nThis space is already occupied. Choose another one!\n");
				showErrorMessageOccupied = 0;
			}
			input = getInput();
			updateBoard(board, input, &playerTurn);
			winner = checkWinner(board);
			if (winner != ' ') {
				if (winner == 'X') {
					//system("cls");
					//showBoard(board);
					printf("Winner is X!");
					gameRunning = 0;
					break;
				}
				else if (winner == 'O') {
					//system("cls");
					//showBoard(board);
					printf("Winner is O!");
					gameRunning = 0;
					break;
				}
			}
			system("cls"); // Clears the console	
		}

		/*New Game choice*/
		//!!BUG: Once you type y or n, you have to do again, it does not recognize the first input. Maybe buffer issue.
		while (gameRunning == 0) {
			printf("\n Do you want to start a new game? [y/n] ");
			scanf_s("%c", &isNewGame);
			//isNewGame = getchar(); // Gets 1 character input
			//getchar(); // Consumes the newline character from the buffer
			// Clears the buffer from residual space and enters from previous input
			int c;
			while ((c = getchar()) != '\n' && c != EOF);


			if (isNewGame == 'y') {
				//Reset variables and return to game loop
				gameRunning = 1;
				playerTurn = 1;
				input = 1;
				winner = ' ';
				isNewGame = ' ';
				
				// Reset board

				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						board[i][j] = '1' + i * 3 + j;
					}
					
				}
				system("cls");
				break;
			}
			else if (isNewGame == 'n') {
				printf("\n\n\nBye!\n\n\n");
				break;
			}
			else {
				printf("Type y or n only!");
			}
		}
	}
	
	return 0;
}

/*Function definitions*/

void showBoard(char board[3][3]) {
	//Shows the player board 


	printf("\t|\t|\n");
	printf("   %c    |   %c   |   %c    \n", board[0][0], board[0][1], board[0][2]);
	printf("________|_______|________\n");

	printf("\t|\t|\n");
	printf("   %c    |   %c   |   %c    \n", board[1][0], board[1][1], board[1][2]);
	printf("________|_______|________\n");

	printf("\t|\t|\n");
	printf("   %c    |   %c   |   %c    \n", board[2][0], board[2][1], board[2][2]);
	printf("\t|\t|\n");
	
	return;



}
//updateBoard handles playerTurn change by pointers simply.
/*void changePlayerTurn(int* turn) {
	//Return which player shall go next.
	if (*turn == 1) {
		*turn = 2;
	}
	else if (*turn == 2) {
		*turn = 1;
	}
	return;
}*/

int getInput(void) {
	//Gets input from user
	int input;
	scanf_s("%i", &input);
	return input;
}

void updateBoard(char board[3][3], int input, int *playerTurn) {
	//Updates the board based on player input with X and O-s.
	//PASS BY REFERENCE: modifies the array by giving the address of the variable and not the value.
	//! Look it UP: what is the diff between this and changePlayerTurn. Here I do not return anything.
	//! Ans: The array in C gets passed as a memory address by default. To to do the same with a variable: use pointers

	int row = (input - 1) / 3;
	int col = (input - 1) % 3;

	if (input < 1 || input > 9) {
		showErrorMessageValidNum = 1;
	}

	else if (board[row][col] == 'O' || board[row][col] == 'X') {
		showErrorMessageOccupied = 1; //Check for already occupied spaces, give error message
	}
	else if (*playerTurn == 1) {
		board[row][col] = 'X';
		//changePlayerTurn(playerTurn);
		*playerTurn = 2;
	}
	else if (*playerTurn == 2) {
		board[row][col] = 'O';
		//changePlayerTurn(playerTurn);
		*playerTurn = 1;
	}
	
	return;
}


char checkWinner(char board[3][3]) {
	//!!!!BUG: Only works for 1st row
	//Check if somebody won. Return winner char or D for draw
	char winner = ' ';

	//check Rows
	for (int i = 0; i < 3; i++) {
		if(board[i][0] == board[i][1] && board[i][0] == board[i][2]){
			if (board[i][0] == 'X') {
				winner = 'X';
				break;
			}
			if (board[i][0] == 'O') {
				winner = 'O';
				break;
			}

		}
	}

	for (int j = 0; j < 3; j++) {
		if (board[0][j] == board[1][j] && board[0][j] == board[2][j]) {
			if (board[j][0] == 'X') {
				winner = 'X';
				break;
			}
			if (board[j][0] == 'O') {
				winner = 'O';
				break;
			}
		}
	}

	return winner;
}
