#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define SIZE 7
void playMove(char board[SIZE][SIZE], char player, int *x, int *y) {
    int maxScore = 0;
    int bestX = -1, bestY = -1;

    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (isValidMove(board, i, j)) {
                
                board[i][j] = player;

                
                int scoreX = i + j; 
                int scoreO = 0;
                for (int oi = 0; oi < SIZE; oi++) {
                    for (int oj = 0; oj < SIZE; oj++) {
                        if (isValidMove(board, oi, oj)) {
                            
                            int score = oi * SIZE + oj; 
                            scoreO = score > scoreO ? score : scoreO;
                        }
                    }
                }

