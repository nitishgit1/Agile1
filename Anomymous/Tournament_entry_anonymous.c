#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define SIZE 7

void playMove(char board[SIZE][SIZE], char player, int *x, int *y) {
    int centerX = SIZE / 2;
    int centerY = SIZE / 2;
    int offsetX = rand() % 3 - 1; 
    int offsetY = rand() % 3 - 1; 
    *x = centerX + offsetX;
    *y = centerY + offsetY;
    if (*x < 0 || *x >= SIZE) {
        *x = rand() % SIZE; 
    }
    if (*y < 0 || *y >= SIZE) {
        *y = rand() % SIZE; 
    }
    while (!(*x >= 0 && *x < SIZE && *y >= 0 && *y < SIZE && board[*x][*y] == ' ')) {
        *x = rand() % SIZE;
        *y = rand() % SIZE;
    }
}
