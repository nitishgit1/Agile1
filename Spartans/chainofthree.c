#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 7
#define PLAYER_X 'X'
#define PLAYER_O 'O'
#define EMPTY_SPACE ' '

char board[SIZE][SIZE];

// Initializes the board with empty spaces
void initBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = EMPTY_SPACE;
        }
    }
}

// Prints the board
void printBoard() {
    printf(" ");
    for (int i = 0; i < SIZE; i++) {
        printf(" %d", i);
    }
    printf("\n");

    for (int i = 0; i < SIZE; i++) {
        printf("%d ", i);
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

// Checks if the specified move is valid (within bounds and on an empty space)
bool isValidMove(int x, int y) {
    return x >= 0 && x < SIZE && y >= 0 && y < SIZE && board[x][y] == EMPTY_SPACE;
}

// Checks for a chain of three markers of the same player starting from (x, y)
bool hasChainOfThree(char player, int x, int y) {
    // Horizontal check
    if (y <= SIZE - 3) {
        if (board[x][y] == player && board[x][y + 1] == player && board[x][y + 2] == player) {
            return true;
        }
    }
    if (y >= 2) {
        if (board[x][y] == player && board[x][y - 1] == player && board[x][y - 2] == player) {
            return true;
        }
    }

    // Vertical check
    if (x <= SIZE - 3) {
        if (board[x][y] == player && board[x + 1][y] == player && board[x + 2][y] == player) {
            return true;
        }
    }
    if (x >= 2) {
        if (board[x][y] == player && board[x - 1][y] == player && board[x - 2][y] == player) {
            return true;
        }
    }

    return false;
}

// The computer's move attempting to block PLAYER_X's chains and to create its own chains
void computerMove() {
    // Block PLAYER_X's immediate winning opportunity
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (isValidMove(i, j)) {
                board[i][j] = PLAYER_X;
                if (hasChainOfThree(PLAYER_X, i, j)) {
                    board[i][j] = PLAYER_O;
                    return;
                }
                board[i][j] = EMPTY_SPACE;
            }
        }
    }

    // Attempt to create the longest possible chain for PLAYER_O
    int maxChain = 0;
    int bestX = -1, bestY = -1;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (isValidMove(i, j)) {
                board[i][j] = PLAYER_O;
                int chain = 1;
                // Extend the chain in all possible directions
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        if (dx == 0 && dy == 0) continue;
                        int nx = i + dx, ny = j + dy;
                        while (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE && board[nx][ny] == PLAYER_O) {
                            chain++;
                            nx += dx;
                            ny += dy;
                        }
                    }
                }
                if (chain > maxChain) {
                    maxChain = chain;
                    bestX = i;
                    bestY = j;
                }
                board[i][j] = EMPTY_SPACE;
            }
        }
    }

    // Make the best move found or a random move if no strategic move is possible
    if (bestX != -1 && bestY != -1) {
        board[bestX][bestY] = PLAYER_O;
    } else {
        int x, y;
        do {
            x = rand() % SIZE;
            y = rand() % SIZE;
        } while (!isValidMove(x, y));
        board[x][y] = PLAYER_O;
    }
}

// Main function to control the flow of the game
int main() {
    srand(time(NULL));
    initBoard();
    char currentPlayer = PLAYER_X;

    while (true) {
        printBoard();
        printf("Enter your move (row column): ");
        int x, y;
        scanf("%d %d", &x, &y);

        if (isValidMove(x, y)) {
            board[x][y] = currentPlayer;
            computerMove();  // Computer responds to player's move
        } else {
            printf("Invalid move. Try again.\n");
        }
    }

    return 0;
}
