#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define SIZE 7

bool hasChainOfLength(char player, int x, int y, int length, int direction, char board[SIZE][SIZE]);
void playMove_three(char board[SIZE][SIZE], char player, int *x, int *y) ;

bool hasChainOfLength(char player, int x, int y, int length, int direction, char board[SIZE][SIZE]) {
    int dx[] = {1, 0};  // right (horizontal), down (vertical)
    int dy[] = {0, 1};
    int nx, ny, count;

    // Check in both forward and backward directions
    for (int dir = 0; dir < 2; dir++) {
        count = 1;
        nx = x + dx[direction];
        ny = y + dy[direction];

        // Forward check
        while (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE && board[nx][ny] == player) {
            count++;
            nx += dx[direction];
            ny += dy[direction];
        }

        // Reset and check backward
        nx = x - dx[direction];
        ny = y - dy[direction];
        while (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE && board[nx][ny] == player) {
            count++;
            nx -= dx[direction];
            ny -= dy[direction];
        }

        if (count >= length) return true;
    }
    return false;
}

void playMove_three(char board[SIZE][SIZE], char player, int *x, int *y) {
    int row, col;

    // Priority to block opponent from winning
    char opponent = (player == 'X') ? 'O' : 'X';
    for (int length = 4; length >= 3; length--) {
        for (row = 0; row < SIZE; row++) {
            for (col = 0; col < SIZE; col++) {
                if (board[row][col] == ' ') {
                    board[row][col] = opponent;
                    if (hasChainOfLength(opponent, row, col, length, 0, board) || hasChainOfLength(opponent, row, col, length, 1, board)) {
                        *x = row;
                        *y = col;
                        board[row][col] = ' ';
                        return;
                    }
                    board[row][col] = ' ';
                }
            }
        }
    }

    // Check for winning or extending own chains
    for (int length = 4; length >= 2; length--) {
        for (row = 0; row < SIZE; row++) {
            for (col = 0; col < SIZE; col++) {
                if (board[row][col] == ' ') {
                    board[row][col] = player;
                    if (hasChainOfLength(player, row, col, length, 0, board) || hasChainOfLength(player, row, col, length, 1, board)) {
                        *x = row;
                        *y = col;
                        return;
                    }
                    board[row][col] = ' ';
                }
            }
        }
    }

    // Default move: random valid move
    do {
        row = rand() % SIZE;
        col = rand() % SIZE;
    } while (!isValidMove(board, row, col));

    *x = row;
    *y = col;
}

