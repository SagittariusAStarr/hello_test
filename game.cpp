#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>

// definicions for easier code manipulation
#define columnNumber 3 
#define rowNumber 10

using namespace std;
using namespace chrono;

char board[columnNumber][rowNumber];

void mainMenu(int height, int width){
    
}

void settingBoard(){                    // function which sets charaters within board
    for(int i = 0; i < rowNumber; i++){
        for(int j = 0; j < columnNumber; j++){
            switch (i)          // switch which asigns chars depends on rows (chars are temporary)
            {
            case 0:
                board[i][j] = '1';
                break;
            case 1:
                board[i][j] = '2';
                break;
            case 2:
                board[i][j] = '3';
                break;
            case 3:
                board[i][j] = '4';
                break;
            case 4:
                board[i][j] = '5';
                break;
            case 5:
                board[i][j] = 'x';
                break;
            case 6:
                board[i][j] = '6';
                break;
            case 7:
                board[i][j] = '7';
                break;
            case 8:
                board[i][j] = '8';
                break;
            case 9:
                board[i][j] = '9';
                break;
            case 10:
                board[i][j] = '0';
            default:            // this statemant shouldn't happened, but in case hear it is
                cout<<"Error in settingBoard function; aborded";
                exit(1);
                break;
            }
        }
    }
}

void rollAnimation(int num1, int num2, int num3, int height, int width){
    string colOffset = "", rowOffset = "";              //this two strings for easier 'board' offset, witch depends on window size
    for(int i = 0; i < height; i++){
        rowOffset = rowOffset + "\n";
    }
    for(int i = 0; i < width; i++){
        colOffset = colOffset + " ";
    }

    for(int i = 0; i < 3*rowNumber; i++){   //first three spins
        system("clear");
        cout<<rowOffset;
        cout<<colOffset<<"|"<<board[(i%rowNumber == 0 ? rowNumber - 1 : i%rowNumber - 1)][0]<<"|"<<board[(i%rowNumber == 0 ? rowNumber - 1 : i%rowNumber - 1)][1]<<"|"<<board[(i%rowNumber == 0 ? rowNumber - 1 : i%rowNumber - 1)][2]<<"|"<<endl;
        cout<<colOffset<<"-------"<<endl;
        cout<<colOffset<<"|"<<board[i%rowNumber][0]<<"|"<<board[i%rowNumber][1]<<"|"<<board[i%rowNumber][2]<<"|"<<endl;
        cout<<colOffset<<"-------"<<endl;
        cout<<colOffset<<"|"<<board[(i%rowNumber == rowNumber - 1 ? 0 : i%rowNumber + 1)][0]<<"|"<<board[(i%rowNumber == rowNumber - 1 ? 0 : i%rowNumber + 1)][1]<<"|"<<board[(i%rowNumber == rowNumber - 1 ? 0 : i%rowNumber + 1)][2]<<"|"<<endl;
        this_thread::sleep_for(milliseconds(100));
    }

    for(int i = 0; i < 2*rowNumber; i++){    //next two spins
        system("clear");
        cout<<rowOffset;
        cout<<colOffset<<"|"<<board[(i%rowNumber == 0 ? rowNumber - 1 : i%rowNumber - 1)][0]<<"|"<<board[(i%rowNumber == 0 ? rowNumber - 1 : i%rowNumber - 1)][1]<<"|"<<board[(i%rowNumber == 0 ? rowNumber - 1 : i%rowNumber - 1)][2]<<"|"<<endl;
        cout<<colOffset<<"-------"<<endl;
        cout<<colOffset<<"|"<<board[i%rowNumber][0]<<"|"<<board[i%rowNumber][1]<<"|"<<board[i%rowNumber][2]<<"|"<<endl;
        cout<<colOffset<<"-------"<<endl;
        cout<<colOffset<<"|"<<board[(i%rowNumber == rowNumber - 1 ? 0 : i%rowNumber + 1)][0]<<"|"<<board[(i%rowNumber == rowNumber - 1 ? 0 : i%rowNumber + 1)][1]<<"|"<<board[(i%rowNumber == rowNumber - 1 ? 0 : i%rowNumber + 1)][2]<<"|"<<endl;
        this_thread::sleep_for(milliseconds(150));
    }

    for(int i = 0; i < rowNumber; i++){     //spin until first number is the same as drawn first number
        if(i == num1){
            break;
        }
        system("clear");
        cout<<rowOffset;
        cout<<colOffset<<"|"<<board[(i%rowNumber == 0 ? rowNumber - 1 : i%rowNumber - 1)][0]<<"|"<<board[(i%rowNumber == 0 ? rowNumber - 1 : i%rowNumber - 1)][1]<<"|"<<board[(i%rowNumber == 0 ? rowNumber - 1 : i%rowNumber - 1)][2]<<"|"<<endl;
        cout<<colOffset<<"-------"<<endl;
        cout<<colOffset<<"|"<<board[i%rowNumber][0]<<"|"<<board[i%rowNumber][1]<<"|"<<board[i%rowNumber][2]<<"|"<<endl;
        cout<<colOffset<<"-------"<<endl;
        cout<<colOffset<<"|"<<board[(i%rowNumber == rowNumber - 1 ? 0 : i%rowNumber + 1)][0]<<"|"<<board[(i%rowNumber == rowNumber - 1 ? 0 : i%rowNumber + 1)][1]<<"|"<<board[(i%rowNumber == rowNumber - 1 ? 0 : i%rowNumber + 1)][2]<<"|"<<endl;
        this_thread::sleep_for(milliseconds(150));
    }

    for(int i = 0; i < rowNumber; i++){     //spin until second number is the same as drawn second number
        if(i == num2){
            break;
        }
        system("clear");
        cout<<rowOffset;
        cout<<colOffset<<"|"<<board[(num1 == 0 ? rowNumber-1 : num1 - 1)][0]<<"|"<<board[(i%rowNumber == 0 ? rowNumber - 1 : i%rowNumber - 1)][1]<<"|"<<board[(i%rowNumber == 0 ? rowNumber - 1 : i%rowNumber - 1)][2]<<"|"<<endl;
        cout<<colOffset<<"-------"<<endl;
        cout<<colOffset<<"|"<<board[num1][0]<<"|"<<board[i%rowNumber][1]<<"|"<<board[i%rowNumber][2]<<"|"<<endl;
        cout<<colOffset<<"-------"<<endl;
        cout<<colOffset<<"|"<<board[(num1 == rowNumber - 1 ? 0 : num1 + 1)][0]<<"|"<<board[(i%rowNumber == rowNumber - 1 ? 0 : i%rowNumber + 1)][1]<<"|"<<board[(i%rowNumber == rowNumber - 1 ? 0 : i%rowNumber + 1)][2]<<"|"<<endl;
        this_thread::sleep_for(milliseconds(150));
    }

    for(int i = 0; i < rowNumber; i++){        //spin one additional time
        system("clear");
        cout<<rowOffset;
        cout<<colOffset<<"|"<<board[(num1 == 0 ? rowNumber-1 : num1 - 1)][0]<<"|"<<board[(num2 == 0 ? rowNumber-1 : num2 - 1)][1]<<"|"<<board[(i%rowNumber == 0 ? rowNumber - 1 : i%rowNumber - 1)][2]<<"|"<<endl;
        cout<<colOffset<<"-------"<<endl;
        cout<<colOffset<<"|"<<board[num1][0]<<"|"<<board[num2][1]<<"|"<<board[i%rowNumber][2]<<"|"<<endl;
        cout<<colOffset<<"-------"<<endl;
        cout<<colOffset<<"|"<<board[(num1 == rowNumber - 1 ? 0 : num1 + 1)][0]<<"|"<<board[(num2 == rowNumber - 1 ? 0 : num2 + 1)][1]<<"|"<<board[(i%rowNumber == rowNumber - 1 ? 0 : i%rowNumber + 1)][2]<<"|"<<endl;
        this_thread::sleep_for(milliseconds(150));
    }

    for(int i = 0; i < rowNumber; i++){     //spin until third number is the same as drawn third number
        if(i == num3){
            break;
        }
        system("clear");
        cout<<rowOffset;
        cout<<colOffset<<"|"<<board[(num1 == 0 ? rowNumber-1 : num1 - 1)][0]<<"|"<<board[(num2 == 0 ? rowNumber-1 : num2 - 1)][1]<<"|"<<board[(i%rowNumber == 0 ? rowNumber - 1 : i%rowNumber - 1)][2]<<"|"<<endl;
        cout<<colOffset<<"-------"<<endl;
        cout<<colOffset<<"|"<<board[num1][0]<<"|"<<board[num2][1]<<"|"<<board[i%rowNumber][2]<<"|"<<endl;
        cout<<colOffset<<"-------"<<endl;
        cout<<colOffset<<"|"<<board[(num1 == rowNumber - 1 ? 0 : num1 + 1)][0]<<"|"<<board[(num2 == rowNumber - 1 ? 0 : num2 + 1)][1]<<"|"<<board[(i%rowNumber == rowNumber - 1 ? 0 : i%rowNumber + 1)][2]<<"|"<<endl;
        this_thread::sleep_for(milliseconds(200));
    }

    return;
}

int main(){
    //check window size
    struct winsize w;                       
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);       

    //draw numbers
    srand(time(NULL));      
    int r1 = rand()%rowNumber, r2 = rand()%rowNumber, r3 = rand()%rowNumber;       
    

    settingBoard();     //fill board
    rollAnimation(r1, r2, r3, w.ws_row/2 - 2, w.ws_col/2 - 3);      //execute roll animation

    return 0;
}