void playMove(char board[SIZE][SIZE], int *x, int *y) {
    int bestScore = INT_MIN;
    int bestMoveX = -1, bestMoveY = -1;

    // Define the scoring weights for consecutive sequences of 'X' values
    int offensiveScoreWeights[] = {0, 3, 10, 25, 56, 119, 250}; // Adjusted weights for 'X'
    int defensiveScoreWeights[] = {0, 2, 9, 24, 55, 118, 249}; // Adjusted weights for 'O'

    // Iterate over all possible moves  
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (isValidMove(board, row, col)) {
                // Try making the move for 'X'
                board[row][col] = 'X';

                // Evaluate the score based on consecutive 'X' values
                int score = 0;
                int countX = 0; // Counter for consecutive 'X' values
                int countO = 0; // Counter for consecutive 'O' values
                for (int i = 0; i < SIZE; i++) {
                    // Check horizontally
                    if (board[row][i] == 'X') {
                        countX++;
                    } else if (board[row][i] == 'O') {
                        countO++;
                    } else {
                        score += offensiveScoreWeights[countX] - defensiveScoreWeights[countO];
                        countX = 0;
                        countO = 0;
                    }
                    // Check vertically
                    if (board[i][col] == 'X') {
                        countX++;
                    } else if (board[i][col] == 'O') {
                        countO++;
                    } else {
                        score += offensiveScoreWeights[countX] - defensiveScoreWeights[countO];
                        countX = 0;
                        countO = 0;
                    }
                }
                score += offensiveScoreWeights[countX] - defensiveScoreWeights[countO]; // Check for the last streak

                // Update the best move if the score is higher
                if (score > bestScore) {
                    bestScore = score;
                    bestMoveX = row;
                    bestMoveY = col;
                }

                // Undo the move
                board[row][col] = ' ';
            }
        }
    }

    // Set the best move found
    *x = bestMoveX;
    *y = bestMoveY;
}
