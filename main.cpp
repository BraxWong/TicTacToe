#include <iostream>
#include <string>
#include <limits>
using namespace std;

//Class for player 1, mainly to store the symbol as private to prevent tempering, and a public method to return the symbol. Same for player 2's class
class Player1 {
    public:
        //Initialize statement so the compiler will not complain
        Player1() {score = 0; symbol = "O";}
        string returnSymbol() {return symbol;}
        void increment() {score+=1;}
        void returnScore() {cout << "player1:" << score << endl;}
    private:
        int score;
        string symbol;
};

class Player2 {
    public:
        //Initialize statement so the compiler will not complain
        Player2() {score = 0, symbol = "X";}
        string returnSymbol() {return symbol;}
        void increment() {score+=1;}
        void returnScore() {cout << "player2:" << score << endl;}
    private:
        int score;
        string symbol;
};

//To maintain the state of the field
class Field {
    public:
        //When an object is created, it will call initial() to create the playing field
        Field() {initial();}
        //A string array to store the state
        string field[3][3];
        //Used at the beginning to clear the playing field
        void initial() {for(int i = 0; i < 3; i++){for(int j = 0; j < 3; j++){field[i][j] = " ";}}};
        //To set the symbol at the designated position
        bool set(int row, int column, string symbol);
        //Prints the field
        void printField();
        //Starts the game
        void startGame(Player1 *player1, Player2 *player2);
        //Check whether the game is done
        bool gameEnd(string symbol);
        //Check if the field is full but winning conditions are not met
        bool fieldFull();
};

bool Field::fieldFull() {
    //Traverse the entire 2D array
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            //if even a single slot is empty, return false and exit
            if(field[i][j] == " "){
                return false;
            }
        }
    }
    //Else it is full
    return true;
}

bool Field::set(int row, int column, string symbol) {
    //if the input is less than 1 but larger than 3, exit the method
    if(row < 1 || row > 3 || column < 1 || column > 3) { 
        cout << "Has to be in the range of 1 to 3\n"; 
        return false;
    }
    //if the slot is occupied already, exit the method  
    if(field[row-1][column-1] == "O" || field[row-1][column-1] == "X"){
        cout << "That slot is occupied!\n";
        return false;
    }
    //Else set the symbol at the designated slot 
    field[row-1][column-1] = symbol;
    return true;
}

bool Field::gameEnd(string symbol) {
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            //if it is column 0, that means it can go horizontal, diagonal and vertical
            if(j == 0){
                if(i == 0){
                    //Diagonal 
                    if(field[i][j] == symbol && field[i+1][j+1] == symbol && field[i+2][j+2] == symbol){
                        return true;
                    }
                }
                //Horizontal
                if(field[i][j] == symbol && field[i][j+1] == symbol && field[i][j+2] == symbol){
                    return true;
                }
                //Vertical
                else if(field[i][j] == symbol && field[i+1][j] == symbol && field[i+2][j] == symbol){
                    return true;
                }
            }
            //if it is column 2, it can go diagonal and horizontal
            else if(j == 2){
                //diagonal
                if(i == 0){
                    if(field[i][j] == symbol && field[i+1][j-1] == symbol && field[i+2][j-2] == symbol){
                        return true;
                    }
                }
                //Vertical
                else if(field[i][j] == symbol && field[i+1][j] == symbol && field[i+2][j] == symbol){
                    return true;
                }
            }
            //it is column 1, it can only go vertical
            else {
                 //Vertical
                if(field[i][j] == symbol && field[i+1][j] == symbol && field[i+2][j] == symbol){
                    return true;
                }
            }
        }
    }
    //check if the field is full, if so, end the game
    if(fieldFull()){
        return true;
    }
    //It is not over just yet
    return false;
}
void Field::startGame(Player1 *player1, Player2 *player2) {
    //Creates 2 objects, player 1 and 2

    //to store user inputs and pass in to the methods later on
    int row, column;
    printField();
    while(true){
        while(true){
            //Player 1's turn
            cout << "It's player 1's turn!\n" << "Please select the row you would like your symbol to be in\n";
            //User input stores in variable row
            cin >> row;
            cout << "Please select the column you would like your symbol to be in\n";
            //User input stores in variable column
            cin >> column;
            //Setting it
            if(set(row,column,player1->returnSymbol())){
                break;
            };
        }
        //Print out the playing field
        printField();
        //If gameEnd returns true, that means player 1 wins
        if(gameEnd(player1->returnSymbol())){
            cout << "Player 1 wins!!!\n";
            //Increase player 1's score
            player1->increment();
            cout << "Score:\n";
            //Printing out the scores
            player1->returnScore();
            player2->returnScore();
            cout << "\n";
            break;
        }
        while(true){
            //Player 2's turn
            cout << "It's player 2's turn!\n" << "Please select the row you would like your symbol to be in\n";
            //User input stores in variable row
            cin >> row;
            cout << "Please select the column you would like your symbol to be in\n";
            //User input stores in variable column
            cin >> column;
            //Setting it
            if(set(row,column,player2->returnSymbol())) {
                break;
            }
        }
        //Print out the playing field
        printField();
        //If gameEnd returns true, that means player 1 wins
        if(gameEnd(player2->returnSymbol())){
            cout << "Player 2 wins!!!\n";
            //Increase player 2's score
            player2->increment();
            cout << "Score:\n";
            //Printing out the scores
            player1->returnScore();
            player2->returnScore();
            cout << "\n";
            break;
        }
    }
}
void Field::printField() {
    //printing out the top row
    for(int i = 0; i < 3; i++){
        cout << "-------\n";
        for(int j = 0; j < 3; j++){
            //Printing out each slot
            cout << "|" <<field[i][j];
        }
        cout << "|\n";
    }
    cout << "-------\n";
}


int main() {
    cout << "Tic Tac Toe. Created By Brax. Version 1.0.1\n";
    Player1 player1 = Player1(); Player2 player2 = Player2(); 
    
    while(true){
        //Creating the field object
        Field playMat;
        //to store whether the user wants to play again or not
        string tryAgain;
        //Starting the game, have to pass by reference instead since the score will be reset to 0 every time.
        playMat.startGame(&player1,&player2);
        //Clear out previous user inputs
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Try again? (Y/N)";
        //Storing the user input into tryAgain
        getline(cin,tryAgain);
        //If it is N, the game is over
        if(tryAgain == "N" || tryAgain == "n"){
            break;
        }
    }
    return 0;
}
