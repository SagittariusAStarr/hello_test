#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fstream>
#include <ctype.h>
#include <stdio.h>
#include <termios.h>
#include <algorithm>

// definicions for easier code manipulation
#define columnNumber 3 
#define rowNumber 10

using namespace std;
using namespace chrono;

char board[columnNumber][rowNumber];

struct termios orig_termios;

void disableRawMod(){ //Disabling Raw Mod
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios); //setting default terminal attributes
    system("setterm -cursor on"); //setting cursor on
	return;
}

void enableRawMod(){ //Enabling Raw Mod
	tcgetattr(STDIN_FILENO, &orig_termios); //getting default terminal attributes
	atexit(disableRawMod); //making program execute function for disabling Raw Mod

	struct termios raw = orig_termios; //copying default attr. into rew struct
    raw.c_iflag &= ~(IXON | ICRNL);                  //modifing raw structs terminal attributes 
	raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN); //here's too
    raw.c_cc[VMIN] = 0;     //min input for read
    raw.c_cc[VTIME] = 1;    //time for read (100ms)

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw); //setting raw attr. into terminal
    system("setterm -cursor off"); //cursor off, why not
	
	return;
}

int mainMenu(int height, int width){           //display manu with options to choose (obviously)
    string colOffset = "", rowOffset1 = "", rowOffset2 = "", rowOffset3 = "", color[2] = {"\033[7m","\033[0m"};
    system("clear");

    if(width < 100 || height < 30){         //check if window is enough to display logo, if not display smaller one
        if(height < 16 || width < 30){          //if window is even more small, display error message
            cout<<"\033[1;31m Window too small, please extend it \033[0m";
            exit(1);
        }

        for(int i = 0; i < 6; i++){         //set vertical offset
            colOffset += "\n";
        }
        for(int i = 0; i < (width/2 - 2); i++){         //set first horizontal offset
            rowOffset1 += " ";
        }
        for(int i = 0; i < (width/2 - 5); i++){         //set second horizontal offset
            rowOffset2 += " ";
        }

        while(true){            //display cutoff menu
            cout<<colOffset<<rowOffset1<<"GAME"<<endl<<endl<<endl<<endl;
            cout<<rowOffset2<<"-=-=-=-=-=-"<<endl<<endl;
            cout<<rowOffset1<<"PLAY"<<endl<<endl;
            cout<<rowOffset1<<"EXIT"<<endl<<endl;
            cout<<rowOffset2<<"-=-=-=-=-=-";
            exit(0);

        }
    }
    else{               //if window size is enough
        
        for(int i = 0; i < 6; i++){         //set vertical offset
            colOffset += "\n";
        }
        for(int i = 0; i < (width/2 - 44); i++){        //set first horizontal offset
            rowOffset1 += " ";
        }
        for(int i = 0; i < (width/2 - 5); i++){         //set second horizontal offset
            rowOffset2 += " ";
        }
        for(int i = 0; i < (width/2 - 2); i++){         //set third horizontal offset
            rowOffset3 += " ";
        }
        
        
        fstream logo;       
        string gameLogo;
        logo.open("AddFiles/logo.txt", ios::in);    //open file with logo
        if(!(logo.good())){         //if file does not exist, set error message as a logo insted 
            gameLogo = rowOffset1;
            gameLogo += "\033[1;31m Logo file does not found \033[0m";
        }
        else{           //if logo file exist, write logo in string 
            string wayAround;
            while(getline(logo, wayAround)){
                gameLogo += rowOffset1;
                gameLogo += wayAround;
                gameLogo += "\n";
            }
            logo.close();           //close file
        }

        while(true){        //display full size menu
            char holder;
            int count = 0;
                system("clear");
                cout<<colOffset<<gameLogo<<endl<<endl<<endl<<endl;
                cout<<rowOffset2<<"-=-=-=-=-=-"<<endl<<endl;
                cout<<rowOffset3<<color[0]<<"PLAY\033[0m"<<endl<<endl;
                cout<<rowOffset3<<color[1]<<"EXIT\033[0m"<<endl<<endl;
                cout<<rowOffset2<<"-=-=-=-=-=-"<<endl;
                while(read(STDIN_FILENO, &holder, 1) == 1){
                    if((holder == 27 && count == 0) || (holder == 91 && count == 1) || ((holder == 65 || holder == 66) && count == 2)){
                        count++;
                        if(count == 3){
                            swap(color[0], color[1]);
                            break;
                        }
                    }
                    else if(holder == 13){
                        if(color[0] == "\033[7m"){
                            return 0;
                        }
                        else if(color[1] == "\033[7m"){
                            return 1;
                        }
                        else{
                            cout<<"Error apeared in mainMenu function, aborded"<<endl;
                            exit(1);
                        }
                    }
                    else{
                        count == 0;
                    }
                }
            }
    }
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

    char holder;
    while(read(STDIN_FILENO, &holder, 1) == 1 && holder != 0){}   //cleaning users input after animation in case they spamed on a keyboard
    cout<<endl<<colOffset<<"Press anything to continue..."<<endl;
    while(true){
        if(read(STDIN_FILENO, &holder, 1) == 1){        //waiting for user input to gave 'em some time to see thier roll
            break;
        }
    }    

    return;
}

int main(){
    enableRawMod();
    //check window size
    struct winsize w;                       
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);       

    //draw numbers
    srand(time(NULL));      
    
    int r1 = rand()%rowNumber, r2 = rand()%rowNumber, r3 = rand()%rowNumber, menuOutput;       

    while(true){

        menuOutput = mainMenu(w.ws_row, w.ws_col);

        switch(menuOutput){  //what you choose on menu, is processing here
            case 0:
                r1 = rand()%rowNumber; 
                r2 = rand()%rowNumber; 
                r3 = rand()%rowNumber;       
                settingBoard();     //fill board
                rollAnimation(r1, r2, r3, w.ws_row/2 - 2, w.ws_col/2 - 3);      //execute roll animation
                break;
            case 1:
                exit(0);
                break;
            default:
                cout<<"Error apeared in main function in switch section, aborded"<<endl;
                exit(1);
                break;
        }
    }
    return 0;
}