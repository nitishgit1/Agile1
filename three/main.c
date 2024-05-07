#include <stdio.h>

//Function Declarations
#define SIZE 7


void initializeBoard(char board[SIZE][SIZE]){
    int i, j;
    for(i=0; i<SIZE; i++){
        for(j=0; j<SIZE; j++){
            board[i][j] = ' ';
        }
    }
}

void printBoard(char board[SIZE][SIZE]){
    int i, j;
    for(i=0; i<SIZE; i++){
        for(j=0; j<SIZE; j++){
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}

int playMove(char board[SIZE][SIZE], char player, int *x, int *y){
    int validMove=1;
    printf("Player %c move:\n", player);
    printf("Input x coordinate:\n");
    scanf("%d", x);
    printf("Input y coordinate:\n");
    scanf("%d", y);
    if(((*x)>=0 && (*x)<SIZE) &&((*y)>=0 &&(*y)<SIZE) &&board[*x][*y]==' '){
        board[*x][*y]= player;
        printBoard(board);
    }
    else{
        validMove = 0;
    }

    return validMove;

}

int scoreBoard(char board[SIZE][SIZE], int countX[SIZE], int countO[SIZE]){
    /*
    for i in SIZE;
    if board[]
    */
}
printScores(char board[SIZE][SIZE]);
playGame(char board[SIZE][SIZE], char player1,char player2);

int main(void){
    char board[SIZE][SIZE];
    initializeBoard(board);
    printBoard(board);
    char player1 = 'x';
    char player2 = 'o';
    char p = player1;
    int x,y;
    int countX[SIZE], countO[SIZE];
    int win = scoreBoard(board, countX, countO);
    playMove(board, p, &x, &y);
    printBoard(board);
    while(!scoreBoard(board, countX, countO)){
        playMove(board, p, countX, countO);
                if(p ==player1){
                    p=player2;
                }
                else{
                    p=player1;
                }
        
    }
    return 0;
}
