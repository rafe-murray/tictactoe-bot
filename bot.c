#include <stdio.h>
#include <string.h>
//#include <math.h>

//board array: 0's are empty, 1's are X's and 2's are O's
int board[3][3]={{0,0,0},{0,0,0},{0,0,0}};

//the order of tiles to check for the computer to play
//in ordered pairs of xy-coordinates
int checkorder[9][2]={{0,0},{1,1},{2,2},{0,2},{2,0},{0,1},{1,0},{1,2},{2,1}};

//the side the computer is playing as: 1 for X, 2 for O
int team;

//the turn number (each player updating one value on the board constitutes one turn)
int turn=1;

//Coordinates of a square to be changed in the array
//Used by helper functions of computermove()
int x;
int y;

//Checks if there is an empty corner with empty adjacent edges and updates the board array with 
//the computer's number in the corner if one exists. Returns 1 if it succeeds or 0 if it fails.
int unblockedcorner(){
    int output = 0;
    for (int i=0;i<=3;i++){
        if ((board[2&i][2*(1&i)]==0)&&(board[1][2*(1&i)]==0)&&(board[2&i][1]==0)){
            x = 2&i;
            y = 2*(1&i);
            output = 1;
            break;
        }
    }
    return output;
}

//updates the value of one board array entry based on checkorder array
void emptytile(){
    for (int i=0;i<=8;i++){
        if (board[checkorder[i][0]][checkorder[i][1]]==0){
            board[checkorder[i][0]][checkorder[i][1]]=team;
            break;
        }
    }
}

//converts the internal numerical format to X's and O's
char numbertocharacter(int number){
    if (number==1){
        return 'X';
    }
    else if (number==2){
        return 'O';
    }
    else {
        return '-';
    }
}

//prints the current board array in a human readable format
void printboard(){
    int i, j;
    for (i=0;i<=2;i++){
        printf("%i ",(-1)*(i-3));
        for (j=0;j<=2;j++){
            printf("%c",numbertocharacter(board[i][j]));
        }
        printf("\n");
    }
    printf("  %i\n",123);
}

//canwin checks first if the computer can win, then if the human can win, updating the value of x and y variables with the computer's next move accordingly
//returns 1 if it successfully makes a move, otherwise returns 0
int canwin(){
    //n is for number of times the code to test the board array has been run
    int n=0;
    //i and j are used for iteration through the board array
    int i;
    int j;
    //sum is the sum of the moves in the current row/column/diagonal of the board array
    int sum;
    //zerocounter counts how many zeroes are present in the current row/column/diagonal
    int zerocounter;
    //finished tracks whether the function has found a tile to fill: 0 if false and 1 if true
    int finished=0;
    while ((n<=1)&&(finished!=1)){
        //looping through rows to check if they have two moves and one zero
        for (i=0;i<=2;i++){
            sum=0;
            zerocounter=0;
            for (j=0;j<=2;j++){
                sum = sum + board[i][j];
                if (board[i][j]==0){
                    zerocounter++;
                }
            }
            //printf("Row %i sum is %i\n", i, sum);
            //changing the empty tile to the computer's team's number and updating finished to true
            if ((n==0)&&(sum/team==2)&&(zerocounter==1)||\
                (n==1)&&(sum/(team^3)==2)&&(zerocounter==1)){
                    for (j=0;j<=2;j++){
                        if (board[i][j]==0){
                            x=i;
                            y=j;
                        }
                    }         
                    finished=1;
                    break;
            }
        }

        //Doing the same thing for columns
        if (finished==0){
            for (i=0;i<=2;i++){
                sum=0;
                zerocounter=0;
                for (j=0;j<=2;j++){
                    sum = sum + board[j][i];
                    if (board[j][i]==0){
                        zerocounter++;
                    }
                }
                //printf("Column %i sum is %i\n", i, sum);
                //changing the empty tile to the computer's team's number and updating finished to true
                if ((n==0)&&(sum/team==2)&&(zerocounter==1)||\
                    (n==1)&&(sum/(team^3)==2)&&(zerocounter==1)){
                        for (j=0;j<=2;j++){
                            if (board[j][i]==0){
                                x = j;
                                y = i;
                            }
                        }         
                        finished=1;
                }
            }
        }
        //doing the same thing for the diagonals
        if (finished==0){
            sum=0;
            zerocounter=0;
            for (i=0;i<=2;i++){
                sum = sum + board[i][i];
                if (board[i][i]==0){
                    zerocounter++;
                }
            }
            //changing the empty tile to the computer's team's number and updating finished to true
            if ((n==0)&&(sum/team==2)&&(zerocounter==1)||\
                (n==1)&&(sum/(team^3)==2)&&(zerocounter==1)){
                    for (i=0;i<=2;i++){
                        if (board[i][i]==0){
                            x = i;
                            y = i;
                        }
                    }         
                    finished=1;
            }
        }
        //printf("Diagonal %i sum is %i\n", 1, sum);
        //doing the same thing for the other diagonal
        if (finished==0){
            sum=0;
            zerocounter=0;
            for (i=0,j=2;i<=2;i++,j--){
                sum = sum + board[i][j];
                if (board[i][j]==0){
                    zerocounter++;
                }
            }
            //changing the empty tile to the computer's team's number and updating finished to true
            if ((n == 0)&&(sum/team == 2)&&(zerocounter == 1)||\
                (n == 1)&&(sum/(team^3) == 2)&&(zerocounter == 1)){
                    for (i=0,j=2;i<=2;i++,j--){
                        if (board[i][j] == 0){
                            x = i;
                            y = j;
                        }
                    }         
                    finished = 1;
            }
        }
        n++;
    }
    //printf("Diagonal %i sum is %i\n", 2, sum);
    return finished;
}

//determines if the current position is a draw
//returns 1 if true, 0 if false
int draw(){
    int sum = 0;
    for (int i=0; i<=2; i++){
        for (int j=0; j<=2; j++){
                sum = sum + board[i][j];
        }
    }
    if (sum == 13){
        return 1;
    }
    else {
        return 0;
    }
}

int win(){
    for (int i=0;i<=2;i++){
        if (board[i][0]==board[i][1]&&board[i][1]==board[i][2]&&board[i][2]!=0){
            return board[i][0];
        }
        else if (board[0][i]==board[1][i]&&board[1][i]==board[2][i]&&board[2][i]!=0){
            return board[0][i];
        }
        else if (board[0][0]==board[1][1]&&board[1][1]==board[2][2]&&board[2][2]!=0){
            return board[0][0];
        }
        else if (board[0][2]==board[1][1]&&board[1][1]==board[2][0]&&board[2][0]!=0){
            return board[0][2];
        }
    }
    return 0;
}

//updates board with the computer's number in a corner adjacent to an edge filled in by the opponent
//returns 1 if success, 0 if failure
int adjacenttoedge(){
    if ((board[1][0]==(team^3))||(board[0][1]==(team^3))){
        x = 0;
        y = 0;
        return 1;
    }
    else if ((board[1][2]==(team^3))||(board[2][1]==(team^3))){
        x = 2;
        y = 2;
        return 1;
    }
    else return 0;
}

//function that determines the computer's move in a position
//and then updates the board array accordingly
void computermove(){
    if (team==1){
        if (turn==1){
            board[0][0]=team;
        }
        else if ((turn==2)&&(board[1][1]==(team^3))){
            board[2][2]=team;
        }
        else if (turn==2){
            unblockedcorner();
            board[x][y] = team;
        }
        else if (turn>=3){
            if ((canwin()==0)&&(unblockedcorner()==0)){
                emptytile();
            }
            else if (canwin()==0){
                unblockedcorner();
                board[x][y] = team;
            }
            else {
                canwin();
                board[x][y] = team;
            }
        }
    }
    else if (team==2) {
        if ((turn==1)&&(board[1][1]==(team^3))){
            board[0][0]=team;
        }
        else if ((turn==2)&&(board[0][0]==team)&&(board[1][1]==(team^3))){
            if (canwin()==0){
                unblockedcorner();
                board[x][y] = team;
            }
            else {
                canwin();
                board[x][y] = team;
            }
        }
        else if ((turn==1)&&(adjacenttoedge()==0)){
            board[1][1]=team;
        }
        else if ((turn==2)&&(board[1][1]==team)){
            if (canwin()==0){
                for (int i=6;i<=8;i++){
                    if (board[checkorder[i][0]][checkorder[i][1]]==0){
                        board[checkorder[i][0]][checkorder[i][1]]=team;
                        break;
                    }
                }
            }
            else {
                        canwin();
                        board[x][y] = team;
                    }
            }
        else if (turn==1){
            adjacenttoedge();
            board[x][y] = team;
        }
        else if (turn==2){
            if (canwin()==0){
                board[1][1]=team;
            }
            else {
                canwin();
                board[x][y] = team;
            }
        }
        else if (turn>=3){
            if ((canwin()==0)&&(unblockedcorner()==0)){
                emptytile();
            }
            else if (canwin()==0){
                unblockedcorner();
                board[x][y] = team;
            }
            else {
                canwin();
                board[x][y] = team;
            }
        }
    }
    printboard();
}

//Parses user input for a coordinate string and updates the board array accordingly if possible, otherwise calls itself again until the player inputs a valid coordinate
void coordinatechecker(){
    char input[64];
    scanf(" %s", input);
    if ((strlen(input)==5)&&(input[0]=='(')&&(input[2]==',')&&(input[4]==')')&&(input[1]>='1')&&(input[3]>='1')&&(input[1]<='3')&&(input[3]<='3')){
        if (board[(-1)*(input[3]-'3')][(input[1]-'0')-1] == 0){
            board[(-1)*(input[3]-'3')][(input[1]-'0')-1] = team^3;
        }
        else {
            printf("This square is already occupied. Please choose another square:\n");
            coordinatechecker();
        }
    }
    else {
        printf("Please input the coordinates again, this time in the format (x,y) where bottom left is (%i,%i)",1,1);
        coordinatechecker();
    }
}

//Prints messages prompting the player for their move, updates the board accordingly, and then prints the current state of the board
void playermove(){
    printf("Your turn. Choose which box to put your letter in by specifying a point (x,y) where the bottom left is (%i,%i).\n",1,1);
    coordinatechecker();
    printboard();
}

void teamselect(){
    char character[64];
    scanf(" %s", character);
    if ((character[0] == 'x'||character[0] == 'X')&&(strlen(character) == 1)){
        team = 2;
        //*note* this is the computer's team
    }
    else if ((character[0] == 'o'||character[0] == 'O')&&(strlen(character) == 1)){
        team = 1;
        //*note* this is the computer's team
    }
    else {
        printf("Please type either 'X' or 'O'\n");
        teamselect();
    }
}


//main function that runs the game
int main(){
    printf("Select your team: [X/O]:\n");
    teamselect();
    if (team == 2){
        playermove();
    }
    while ((win() == 0)&&(draw()==0)){
        printf("Computer's move:\n");
        computermove();
        if ((win() == 0)&&(draw()==0)){
            playermove();
        }
        turn++;
    }
    if (win()==team){
        printf("Computer wins! Better luck next time.\n");
    }
    else if (win()==(team^3)){
        printf("You win! Congratulations.\n");
    }
    else if (draw() == 1){
        printf("Draw! Play again another time.\n");
    }
    return 0;
}