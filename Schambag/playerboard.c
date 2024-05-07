#include <stdio.h>

void printBoard(char board[7][7]) {
  // Print column numbers
  printf("  ");
  for (int col = 0; col < 7; col++) {
    printf(" %d ", col);
  }
  printf("\n");

  // Print top border
  printf("  ");
  for (int col = 0; col < 7 * 4 + 1; col++) {
    printf("-");
  }
  printf("\n");

  for (int row = 0; row < 7; row++) {
    // Print row numbers
    printf("%d |", row);
    for (int col = 0; col < 7; col++) {
      // Set background color based on cell content
      if (board[row][col] == 'X') {
        printf(
            "\033[0;41m\033[1;30m"); // Background color: red, Text color: black
      } else if (board[row][col] == 'O') {
        printf("\033[0;42m\033[1;30m"); // Background color: green, Text color:
                                        // black
      } else {
        printf("\033[0;47m\033[1;30m"); // Background color: white, Text color:
                                        // black
      }
      printf(" %c ", board[row][col]);
      printf("\033[0m"); // Reset colors
      printf("|");
    }
    printf("\n");

    // Print inner border
    printf("  ");
    for (int col = 0; col < 7; col++) {
      printf("----");
    }
    printf("\n");
  }
}

int haveWon(char board[7][7], char player) {
  // check the rows
  for (int row = 0; row < 7; row++) {
    for (int col = 0; col < 5; col++) {
      if (board[row][col] == player && board[row][col + 1] == player &&
          board[row][col + 2] == player) {
        return 1;
      }
    }
  }

  // check for columns
  for (int col = 0; col < 7; col++) {
    for (int row = 0; row < 5; row++) {
      if (board[row][col] == player && board[row + 1][col] == player &&
          board[row + 2][col] == player) {
        return 1;
      }
    }
  }

  // check diagonals
  for (int row = 0; row < 5; row++) {
    for (int col = 0; col < 5; col++) {
      if (board[row][col] == player && board[row + 1][col + 1] == player &&
          board[row + 2][col + 2] == player) {
        return 1;
      }
      if (board[row][col + 2] == player && board[row + 1][col + 1] == player &&
          board[row + 2][col] == player) {
        return 1;
      }
    }
  }

  return 0;
}

int isBoardFull(char board[7][7]) {
  for (int row = 0; row < 7; row++) {
    for (int col = 0; col < 7; col++) {
      if (board[row][col] == ' ') {
        return 0; // Board is not full
      }
    }
  }
  return 1; // Board is full
}

int main() {
  char board[7][7];
  for (int row = 0; row < 7; row++) {
    for (int col = 0; col < 7; col++) {
      board[row][col] = ' ';
    }
  }

  char player = 'X';

  while (1) {
    printBoard(board);
    printf("\nPlayer %c enter: ", player);
    int row, col;
    scanf("%d %d", &row, &col);
    printf("\n");

    if (row < 0 || row >= 7 || col < 0 || col >= 7) {
      printf("Invalid move. Try again!\n");
      continue;
    }

    if (board[row][col] == ' ') {
      board[row][col] = player; // place the element

      if (isBoardFull(board)) {
        printf("The board is full! It's a draw.\n");
        break; // End the game if the board is full
      }
      player = (player == 'X') ? 'O' : 'X'; // switch player
    } else {
      printf("Invalid move. Try again!\n");
    }
  }

  return 0;
}