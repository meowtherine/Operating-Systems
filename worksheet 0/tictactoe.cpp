#include <stdio.h>
#include <stdbool.h>

char board [3][3]; //create board size, w3, h3

void initialiseBoard(){
    for (int i = 0; i <3; i++) { //rows
        for (int j = 0; j < 3; j++) { //columns
            board[i][j] = ' '; //inner loops, sets contents to ' ', empty state
        }
    }
}

void clearScreen() { //clear terminal of game state + output from end of turn
    printf("\033[H\003[J"); //ANSI escape sequence
}

void printBoard() { //displa visual of current board
    printf("\n");
    printf("  1   2   3 \n");
    printf("1 %c | %c | %c\n", board[0][0], board[0][1], board[0][2]);
    printf("  ---------\n");
    printf("2 %c | %c | %c\n", board[1][0], board[1][1], board[1][2]);
    printf("  ---------\n");
    printf("3 %c | %c | %c\n", board[2][0], board[2][1], board[2][2]);

}

bool isGameOver() { //check if game has ended, bool val (t/f) returned
    for (int i = 0 ; i < 3; i++) { //check rows for same value aka win
        if (board[i][0] != ' ' && board[i][1] && board[i][0] == board[i][2]) {
            return true;
        }
    }

    for (int j=0; j <3; j++) { //check columns for same value aka win
        if (board[0][j] != ' ' && board[0][j] == board[1][j] && board[0][j] == board[2][j]) {
            return true;
        }
    }

    //check diagonals for same value aka win
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
        return true;
    }
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
        return true;
    }

    for (int i = 0; i < 3; i++) { //check for draw, if all cells occupied
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }

    return true;
}

char getWinner() {
    for (int i = 0; i < 3; i++) { //check rows
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
            return board[i][0];
        }
    }

    for (int j = 0; j <3; j++) { //check column
        if (board[0][j] != ' ' && board[0][j] == board[1][j] && board[0][j] == board[2][j]) {
            return board[0][j];
        }
    }

    //check diagonals
    if(board[0][0] != ' ' && board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
        return board[0][0];
    }
    if(board[0][2] != ' ' && board[0][2] == board [1][1] && board[0][2] == board[2][0]) {
        return board[0][2];
    }

    return ' '; //no winner
}

int main() {
    initialiseBoard(); //call board func
    int currentPlayer = 1;

    while (1) {
        clearScreen(); //clear screen func
        printf("Current board state:\n");
        printBoard(); //print board func

        int row,col;
        printf("Player %d, please enter a row and column (e.g., 1 2):", currentPlayer);

        while (scanf("%d %d", &row, &col) != 2) {
            printf("Invalid input, please try again: ");
            while(getchar() != '\n');
        }

        if (row < 1 || row > 3 || col < 1 || col > 3 || board [row - 1][col - 1] != ' ') {
            printf("Invalid move, please try again.\n");
        } else {
            if (currentPlayer == 1) {
                board[row - 1][col - 1] = 'x';
                currentPlayer = 2;
            } else {
                board[row - 1][col - 1] = 'o';
                currentPlayer = 1;
            }
        }

        if (isGameOver()) {
            clearScreen();
            printf("Game over!\n");
            printBoard();
            char winner = getWinner();
            if (winner != ' ') {
                printf("Player %c wins!\n", winner);
            } else {
                printf("It's a draw!\n");
            }
            break;
        }
    }

    return 0;
}