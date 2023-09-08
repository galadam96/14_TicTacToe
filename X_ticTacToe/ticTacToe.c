//Date: 2023.08.18
//Purpose: TicTacToe game for 2 local players in console


#include <stdio.h>
#include <stdlib.h>

/*Function prototypes*/
void showBoard(char board[3][3]);
void updateBoard(char board[3][3], int input, int *playerTurn);
int getInput(char board[3][3]);
char checkWinner(char board[3][3]);

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

	while (isNewGame != 'n') {

		while (gameRunning == 1) {
			system("cls"); // Clears the console
			printf("\t Tic Tac Toe\n \n");
			printf("Player 1 (X) - Player 2 (O)\n\n");
			showBoard(board);
			printf("\nPlayer %i, enter a number: ", playerTurn);

			winner = checkWinner(board);
			if (winner != ' ') {
				if (winner == 'X') {
					printf("Winner is X!");
					gameRunning = 0;
					break;
				}
				else if (winner == 'O') {
					printf("Winner is O!");
					gameRunning = 0;
					break;
				}
				else if (winner == 'D') {
					printf("DRAW!");
					gameRunning = 0;
					break;
				}
			}

			//printf("\nDEBUG: input is:%i \n", input);

			input = getInput(board);
			updateBoard(board, input, &playerTurn);
			
		}

		/*New Game choice*/
		//!!BUG: Once you type y or n, you have to do again, it does not recognize the first input. Maybe buffer issue.
		//!FIX: SPACE before %c solved the issue. Clears the residue of previous input.
		while (gameRunning == 0) {
			printf("\n Do you want to start a new game? [y/n] ");
			scanf_s(" %c", &isNewGame);
	
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


int getInput(char board[3][3]) {
	//Gets input from user and validates it
	int input = 0;
	int result;
	int row, col;
	
	while (1) {

		result = scanf_s("%i", &input); // Store scanf_s return value (1 if valid parameter specifier is given)
		//Invalid input (not number)
		if (result != 1) {
			printf("\nInvalid input. Only numbers from 1 to 9!\n");
			// Clear input buffer 
			int c;
			while ((c = getchar()) != '\n' && c != EOF);
		}

		//Invalid number (not 1-9)
		else if (input < 1 || input > 9) {
			printf("\nInvalid number. Choose from 1 to 9!\n");
			// Clear input buffer 
			int c;
			while ((c = getchar()) != '\n' && c != EOF);
		}

		//Valid input
		else {
			row = (input - 1) / 3;
			col = (input - 1) % 3;

			//Occupied space already
			if (board[row][col] == 'O' || board[row][col] == 'X') {
			printf("\nThis space is already occupied. Choose another one!\n");
			}

			//Valid input, not occupied
			else {
				break;
			}
		}
	}
	
	return input;
}

void updateBoard(char board[3][3], int input, int *playerTurn) {
	//Updates the board based on player input with X and O-s.
	//PASS BY REFERENCE: modifies the array by giving the address of the variable and not the value.
	//The array in C gets passed as a memory address by default. To to do the same with a variable: use pointers

	int row = (input - 1) / 3;
	int col = (input - 1) % 3;

	if (*playerTurn == 1) {
		board[row][col] = 'X';
		*playerTurn = 2;
	}
	else if (*playerTurn == 2) {
		board[row][col] = 'O';
		*playerTurn = 1;
	}
	
	return;
}

char checkWinner(char board[3][3]) {
	//Check if somebody won. Return winner char or D for draw
	char winner = ' ';
	int totalMoves = 0;

	// Checks for diagonals 

	if (board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X') {
		winner = 'X';
	}
	else if (board[0][2] == 'X' && board[1][1] == 'X' && board[2][0] == 'X') {
		winner = 'X';
	}

	else if (board[0][0] == 'O' && board[1][1] == 'O' && board[2][2] == 'O') {
		winner = 'O';
	}

	else if (board[0][2] == 'O' && board[1][1] == 'O' && board[2][0] == 'O') {
		winner = 'O';
	}

	// Check for rows and columns

	for (int i = 0; i < 3; i++) {

		//Rows
		if (board[i][0] == 'X' && board[i][1] == 'X' && board[i][2] == 'X') {
			winner = 'X';
		}
		else if (board[i][0] == 'O' && board[i][1] == 'O' && board[i][2] == 'O') {
			winner = 'O';
		}

		//Columns
		else if (board[0][i] == 'X' && board[1][i] == 'X' && board[2][i] == 'X') {
			winner = 'X';
		}

		else if (board[0][i] == 'O' && board[1][i] == 'O' && board[2][i] == 'O') {
			winner = 'O';
		}
	}

	//Check for draw 
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == 'X' || board[i][j] == 'O') {
				totalMoves++;
			}
		}
	}

	if (totalMoves == 9) {
		winner = 'D';
	}

	return winner;
}
