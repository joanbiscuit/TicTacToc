#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int player1 = 1;
int player2 = 2;
int board[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

void printBoard(int* board){
    printf("%d | %d | %d\n", board[0], board[1], board[2]);
    printf("---------\n");
    printf("%d | %d | %d\n", board[3], board[4], board[5]);
    printf("---------\n");
    printf("%d | %d | %d\n", board[6], board[7], board[8]);
}


void play(int player, int* board){
    int row;
    int column;
    bool correct_input = false;
    while(!correct_input){
        printf("Player %d, Select a tile to play in (x, y): ", player);
        scanf("%d, %d", &row, &column);
        if( row > 0 && row <= 3 && column > 0 && column <= 3){ //check that input is within bounds
	    if(board[3*(row-1) + (column-1)] == 0){ //check that the position has not already been taken
                board[3*(row-1) + (column-1)] = player;
	        correct_input = true;
            }
	}
    }
}

bool threeInARow(int player){
    //check diagonals
    if(board[4] == player){
        //check main diagonal
        if((board[0] == player) && (board[8] == player))
            return true;
        //check reverse diagonal
        if((board[2] == player) && (board[6] == player))
            return true;   
    }
    //check horizontals and verticals
    for(int i = 0; i < 3; i++){
        //horizontals
        if((board[3*i] == player) && (board[3*i + 1] == player) && (board[3*i + 2] == player)){
            return true;
	}
        //verticals
        if((board[i] == player) && (board[i+3] == player) && (board[i+6] == player)){
            return true;
	}
    }
    return false;
}


//return 1 if player 1 has won, or 2 if player 2 has won, or return 0 if nobody has won
int checkWin(int* board){
    for(int i = 1; i < 3; i++){
        if(threeInARow(i))
            return i;
    }
    return 0;
}

int main()
{
    bool finished = false; //bool to see if the game is finished (someone won or a tie)
    int x = 0; //integer to keep track of whose turn it is
    int winner = 0;
    while (!finished){
        play(x%2+1, board); //let one player play
        printBoard(board); //print the updated board
	winner = checkWin(board);
        if(winner != 0){
            finished = true;
        }
        x++;
        if(x == 9){
            finished = true;
        }
    }
    if(winner == 0){
        printf("No one wins :(");
    }
    else{
        printf("Player %d has won!", winner);
    }
    return 0;
}
