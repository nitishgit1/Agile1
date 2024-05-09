#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define SIZE 7

void playMove(char board[SIZE][SIZE], char player, int *x, int *y);

void playMove(char board[SIZE][SIZE], char player, int *x, int *y) {
    int row, col;

    // Function to check for a chain of given length starting from a given position (row, col)
    bool hasChainOfLength(char player, int x, int y, int length) {
        int dx[] = {1, 0}; // Possible directions: right, down
        int dy[] = {0, 1};

        for (int i = 0; i < 2; ++i) {
            int count = 1; // Count of consecutive player symbols
            int nx = x + dx[i], ny = y + dy[i];
            while (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE && board[nx][ny] == player) {
                count++;
                nx += dx[i];
                ny += dy[i];
            }
            nx = x - dx[i];
            ny = y - dy[i];
            while (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE && board[nx][ny] == player) {
                count++;
                nx -= dx[i];
                ny -= dy[i];
            }
            if (count >= length) {
                return true;
            }
        }
        return false;
    }

    // Loop through all positions and check if opponent has a sequence of three, four, or five
    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            if (isValidMove(board, row, col)) {
                board[row][col] = player;
                char opponent = (player == 'X') ? 'O' : 'X';
                if (hasChainOfLength(opponent, row, col, 3)) {
                    *x = row;
                    *y = col;
                    board[row][col] = ' ';
                    return;
                } else if (hasChainOfLength(opponent, row, col, 4)) {
                    *x = row;
                    *y = col;
                    board[row][col] = ' ';
                    return;
                } else if (hasChainOfLength(opponent, row, col, 5)) {
                    *x = row;
                    *y = col;
                    board[row][col] = ' ';
                    return;
                }
                board[row][col] = ' ';
            }
        }
    }

    // If opponent has no immediate threat, play randomly
    do {
        row = rand() % SIZE;
        col = rand() % SIZE;
    } while (!isValidMove(board, row, col));

    *x = row;
    *y = col;
}
