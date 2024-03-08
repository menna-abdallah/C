#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define BOARD_SIZE 3

char board[BOARD_SIZE][BOARD_SIZE];
char playerSymbol;
char computerSymbol;

void resetBoard();
void printBoard();
int checkFreeSpaces();
int playerMove();
void computerMove();
char checkWinner();
void printWinner(char);
void choosePlayerSymbol();

int main() {
    char winner = ' ';
    char response = ' ';

    do {
        winner = ' ';
        response = ' ';
        choosePlayerSymbol();
        resetBoard();

        while(winner == ' ' && checkFreeSpaces() != 0) {
            printBoard();
            playerMove();
            winner = checkWinner();
            if(winner != ' ' || checkFreeSpaces() == 0) {
                break;
            }

            computerMove();
            winner = checkWinner();
            if(winner != ' ' || checkFreeSpaces() == 0) {
                break;
            }
        }

        printBoard();
        printWinner(winner);

        printf("\nWould you like to play again? (Y/N): ");
        // Clear the input buffer before taking new input
        while ((getchar()) != '\n');
        scanf("%c", &response);
        response = toupper(response);
    } while (response == 'Y');

    printf("Thanks for playing!");

    return 0;
}

void resetBoard() {
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard() {
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
}

int checkFreeSpaces() {
    int freeSpaces = 0;
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            if(board[i][j] == ' ') {
                freeSpaces++;
            }
        }
    }
    return freeSpaces;
}

int playerMove() {
    int x, y;
    int moveValid = 0;

    while (!moveValid) {
        printf("Enter row #(1-3): ");
        scanf("%d", &x);
        printf("Enter column #(1-3): ");
        scanf("%d", &y);

        x--; // Adjust for 0 indexing
        y--; // Adjust for 0 indexing

        if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE || board[x][y] != ' ') {
            printf("Invalid move, try again.\n");
        } else {
            board[x][y] = playerSymbol;
            moveValid = 1;
        }
    }
    return moveValid;
}

void computerMove() {
    srand(time(0)); // Seed for randomness
    int x, y;
    if(checkFreeSpaces() > 0) {
        do {
            x = rand() % BOARD_SIZE;
            y = rand() % BOARD_SIZE;
        } while(board[x][y] != ' ');

        board[x][y] = computerSymbol;
    }
}

char checkWinner() {
    // Check rows, columns, and diagonals for a win
    for(int i = 0; i < BOARD_SIZE; i++) {
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') return board[i][0];
        if(board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') return board[0][i];
    }
    if(board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') return board[0][0];
    if(board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') return board[0][2];

    return ' ';
}

void printWinner(char winner) {
    if(winner == playerSymbol) {
        printf("Congratulations! You've won!\n");
    } else if(winner == computerSymbol) {
        printf("The computer has won. Try again next time!\n");
    } else {
        printf("It's a draw!\n");
    }
}

void choosePlayerSymbol() {
    printf("Choose your symbol (X/O): ");
    while ((getchar()) != '\n');
    scanf("%c", &playerSymbol);
    playerSymbol = toupper(playerSymbol);

    while(playerSymbol != 'X' && playerSymbol != 'O') {
        printf("Invalid choice. Please choose X or O: ");
        while ((getchar()) != '\n'); // Clear the input buffer again
        scanf("%c", &playerSymbol);
        playerSymbol = toupper(playerSymbol);
    }

    computerSymbol = (playerSymbol == 'X') ? 'O' : 'X';
}
