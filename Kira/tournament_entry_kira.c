#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define SIZE 7

// void printBoard(char board[SIZE][SIZE]);
bool isValidMove(char board[SIZE][SIZE], int row, int col);
void playMove_kira(char board[SIZE][SIZE], char player, int *x, int *y);
// void initializeBoard(char board[SIZE][SIZE]);
// void scoreBoard(char board[SIZE][SIZE], int countX[5], int countO[5]);
// void printScores(int countX[5], int countO[5]);
// void playGame(char board[SIZE][SIZE], char player1, char player2);
// void runUnitTests();


void playMove_kira(char board[SIZE][SIZE], char player, int *x, int *y) 
{
    if(player=='X')
    {
        if(isValidMove(board,3,3))
        {
            *x = 3;
            *y = 3;
        }
        else{
            for(int row = 0; row < SIZE; row++) {
                for(int col = 0; col < SIZE; col++) {
                    if (board[row][col] == 'O') {
                        if(isValidMove(board,6-row,6-col))
                        {
                                *x =6-row;
                                *y = 6-col;
                        }
                    }
                    }
                }
            }     
    }
}