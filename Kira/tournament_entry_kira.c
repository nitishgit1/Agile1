#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 7

bool isValidMove(char board[SIZE][SIZE], int row, int col);
void playMove_kira(char board[SIZE][SIZE], char player, int *x, int *y);
int checkrow(char board[SIZE][SIZE], char player,int *row,char *plyr);
int checkcol(char board[SIZE][SIZE], char player, int *col,char *plyr);
int checkbestmove(char board[SIZE][SIZE], char player,int row1,int col1,int *x1,int*y1,char plyr1,char plyr2);
int findbestmove(char board[SIZE][SIZE],int row,int col,char finaldec,int *x,int *y);


// Function to check if a move is valid
bool isValidMove(char board[SIZE][SIZE], int row, int col) {
    return (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == ' ');
}

int findbestmove(char board[SIZE][SIZE],int row,int col,char finaldec,int *x,int *y)
{   int j=3;
    if(finaldec=='r')
    {
    
    while(j<7 && j>=0)
    {
        if(board[row][j]==' ')
        {
            break;
        }
        switch(j)
        {
            case 3:j=j+1;
                   break;
            case 4:j=j-2;
                   break;
            case 2:j=j+3;
                   break;
            case 5:j=j-4;
                   break;
            case 1:j=j+5;
                   break;
            case 6:j=j-6;
                   break;
            default:j=10;
                    break;
        }
    }
    }
    int i=3;
    if(finaldec=='c')
    {
    
    while(i<7 && i>=0)
    {
        if(board[i][col]==' ')
        {
            break;
        }
        switch(i)
        {
            case 3:i=i+1;
                   break;
            case 4:i=i-2;
                   break;
            case 2:i=i+3;
                   break;
            case 5:i=i-4;
                   break;
            case 1:i=i+5;
                   break;
            case 6:i=i-6;
                   break;
            default:i=10;
                    break;
        }
    }
    }
    if(i==10)
    {
        i=0;
    }
    if(j==10)
    {
        j=0;
    }
    if(i==3){
        *x=i;
        *y=col;
        if(isValidMove(board,*x,*y))
        { 
            return 0;
        }
    }
    if(j==3){
        *x=row;
        *y=j;
         if(isValidMove(board,*x,*y))
        { 
            return 0;
        }
    }
     if(i==2){
        *x=i;
        *y=col;
         if(isValidMove(board,*x,*y))
        { 
            return 0;
        }
    }
    if(j==2){
        *x=row;
        *y=j;
         if(isValidMove(board,*x,*y))
        { 
            return 0;
        }
    }
     if(i==4){
        *x=i;
        *y=col;
         if(isValidMove(board,*x,*y))
        { 
            return 0;
        }
    }
    if(j==4){
        *x=row;
        *y=j;
         if(isValidMove(board,*x,*y))
        { 
            return 0;
        }
    }
     if(i==1){
        *x=i;
        *y=col;
         if(isValidMove(board,*x,*y))
        { 
            return 0;
        }
    }
    if(j==1){
        *x=row;
        *y=j;
         if(isValidMove(board,*x,*y))
        { 
            return 0;
        }
    }
     if(i==5){
        *x=i;
        *y=col;
         if(isValidMove(board,*x,*y))
        { 
            return 0;
        }
    }
    if(j==5){
        *x=row;
        *y=j;
         if(isValidMove(board,*x,*y))
        { 
            return 0;
        }
    }
     if(i==0){
        *x=i;
        *y=col;
         if(isValidMove(board,*x,*y))
        { 
            return 0;
        }
    }
    if(j==0){
        *x=row;
        *y=j;
         if(isValidMove(board,*x,*y))
        { 
            return 0;
        }
    }
     if(i==6){
        *x=i;
        *y=col;
         if(isValidMove(board,*x,*y))
        { 
            return 0;
        }
    }
    if(j==6){
        *x=row;
        *y=j;
         if(isValidMove(board,*x,*y))
        { 
            return 0;
        }
    }
    
if(finaldec=='r')
{
    *x=row;
    *y=j;
}
if(finaldec=='c')
{
    *x=i;
    *y=col;
}

return 1;

    
  
}
int checkcol(char board[SIZE][SIZE], char player, int *col,char *plyr) {
    int maxConsecutiveX[SIZE] = {0}; // Initialize all elements to 0
    int maxConsecutiveO[SIZE] = {0}; // Initialize all elements to 0
    int spaces[SIZE] = {0}; // Initialize all elements to 0

    // Check columns for 'X' and 'O'
    for (int j = 0; j < SIZE; j++) {
        int consecutiveX = 0;
        int consecutiveO = 0;
        for (int i = 0; i < SIZE; i++) {
            if (board[i][j] == 'X') {
                consecutiveX++;
                if (consecutiveX > maxConsecutiveX[j]) {
                    maxConsecutiveX[j] = consecutiveX;
                    if (i + 1 < SIZE && board[i + 1][j] == ' ') {
                        spaces[j]++;
                    }
                }
            } else {
                consecutiveX = 0;
            }
            if (board[i][j] == 'O') {
                consecutiveO++;
                if (consecutiveO > maxConsecutiveO[j]) {
                    maxConsecutiveO[j] = consecutiveO;
                    if (i + 1 < SIZE && board[i + 1][j] == ' ') {
                        spaces[j]++;
                    }
                }
            } else {
                consecutiveO = 0;
            }
        }
    }

    // Now spaces array contains the count of spaces next to consecutive symbols in each column
    int maxConX = 0;
    int maxConO = 0;
    int colWithMaxConsecutiveX = -1;
    int colWithMaxConsecutiveO = -1;
    for (int j = 0; j < SIZE; j++) {
        if (maxConsecutiveX[j] > maxConX && spaces[j] > 0) {
            maxConX = maxConsecutiveX[j];
            colWithMaxConsecutiveX = j;
        }
        if (maxConsecutiveO[j] > maxConO && spaces[j] > 0) {
            maxConO = maxConsecutiveO[j];
            colWithMaxConsecutiveO = j;
        }
    }

    if (maxConX > maxConO) {
        if (player == 'O') {
            if (maxConX >= maxConO + 1) {
                *col = colWithMaxConsecutiveO;
                *plyr='O';
                return 0;
            }
        }
    } else {
        *col = colWithMaxConsecutiveO;
        *plyr='O';
        return 0;
    }

    *col = colWithMaxConsecutiveX;
    *plyr='X';
    return 1;
}


int checkrow(char board[SIZE][SIZE], char player,int *row,char *plyr) {
    int maxConsecutiveX[SIZE] = {0}; // Initialize all elements to 0
    int maxConsecutiveO[SIZE] = {0}; // Initialize all elements to 0
    int spaces[SIZE] = {0}; // Initialize all elements to 0

    // Check rows for 'X' and 'O'
    for (int i = 0; i < SIZE; i++) {
        int consecutiveX = 0;
        int consecutiveO = 0;
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 'X') {
                consecutiveX++;
                if (consecutiveX > maxConsecutiveX[i]) {
                    maxConsecutiveX[i] = consecutiveX;
                    if (j + 1 < SIZE && board[i][j + 1] == ' ') {
                        spaces[i]++;
                    }
                }
            } else {
                consecutiveX = 0;
            }
            if (board[i][j] == 'O') {
                consecutiveO++;
                if (consecutiveO > maxConsecutiveO[i]) {
                    maxConsecutiveO[i] = consecutiveO;
                    if (j + 1 < SIZE && board[i][j + 1] == ' ') {
                        spaces[i]++;
                    }
                }
            } else {
                consecutiveO = 0;
            }
        }
    }
   
    // Now spaces array contains the count of spaces next to consecutive symbols in each row
    int maxConX = 0;
    int maxConO = 0;
    int rowWithMaxConsecutiveX = -1;
    int rowWithMaxConsecutiveO = -1;
    for (int i = 0; i < SIZE; i++) {
        if (maxConsecutiveX[i] > maxConX && spaces[i] > 0) {
            maxConX = maxConsecutiveX[i];
            rowWithMaxConsecutiveX = i;
        }
        if (maxConsecutiveO[i] > maxConO && spaces[i] > 0) {
            maxConO = maxConsecutiveO[i];
            rowWithMaxConsecutiveO = i;
        }
    }
    if(maxConX>maxConO)
    {
        *row=rowWithMaxConsecutiveX;
        *plyr='X';
        return 1;
    }
    *row=rowWithMaxConsecutiveO;
    *plyr='O';
     // Returning 0, you can modify this according to your requirement
    return 1;
}
int checkbestmove(char board[SIZE][SIZE], char player,int row1,int col1,int *x1,int*y1,char plyr1,char plyr2) {
    int maxConsecutivePlyr1 = 0;
    int consecutivePlyr1 = 0;
    int maxConsecutivePlyr2 = 0;
    int consecutivePlyr2 = 0;

    // Find maximum consecutive symbols for plyr1 in row1
    for (int j = 0; j < SIZE; j++) {
        if (board[row1][j] == plyr1) {
            consecutivePlyr1++;
            if (consecutivePlyr1 > maxConsecutivePlyr1) {
                maxConsecutivePlyr1 = consecutivePlyr1;
            }
        } else {
            consecutivePlyr1 = 0;
        }
    }

    // Find maximum consecutive symbols for plyr2 in col1
    for (int i = 0; i < SIZE; i++) {
        if (board[i][col1] == plyr2) {
            consecutivePlyr2++;
            if (consecutivePlyr2 > maxConsecutivePlyr2) {
                maxConsecutivePlyr2 = consecutivePlyr2;
            }
        } else {
            consecutivePlyr2 = 0;
        }
    }
    char fd;
    
    if(maxConsecutivePlyr1>maxConsecutivePlyr2)
    {   if(plyr2=='O')
        {
        if(maxConsecutivePlyr1==maxConsecutivePlyr2+1)
        {
            if(plyr1=='O')
            {
                fd='r';
            
            }
            else{
                fd='c';
            }

        }
        else{
               fd='r';
        }
        }
        else{
               fd='r';
        }
    }
    else if(maxConsecutivePlyr2>maxConsecutivePlyr1)
    {
        if(plyr1=='O')
        {
        if(maxConsecutivePlyr2==maxConsecutivePlyr1+1)
        {
            if(plyr1=='O')
            {
                fd='c';
            }
            else{
                   fd='r';
            }

        }
        else{
            fd='c';
        }
        }
        else{
            fd='c';
        }

    }
    else{
        if(plyr1=='O')
        {
               fd='r';
        }
        else if(plyr2=='O')
        {
              fd='r';
        }
        else{
               fd='c';
        }
    }
    int fx,fy;
    findbestmove(board,row1,col1,fd,&fx,&fy);
    *x1=fx;
    *y1=fy;
    return 0;
}


// Function to play a move
void playMove_kira(char board[SIZE][SIZE], char player, int *x, int *y) {

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
    else{
    int row1,col1;
    int x1,y1;
    char  plyr1,plyr2;
    int test1=checkrow(board,player,&row1,&plyr1);
    int test2=checkcol(board,player,&col1,&plyr2);
    int test3=checkbestmove(board,player,row1,col1,&x1,&y1,plyr1,plyr2);
    *x=x1;
    *y=y1;
    if(isValidMove(board,x1,y1))
    {   
        int row, col;
    do {
        row = rand() % SIZE;
        col = rand() % SIZE;
    } while (!isValidMove(board, row, col));

    *x = row;
    *y = col;
    }
}
}