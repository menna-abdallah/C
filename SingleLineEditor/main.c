#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define right_key 77
#define left_key 75
#define exit_key 27
#define enter_key 13
#define home_key 71
#define back_key 8
#define max_size 20

void gotoxy(int x, int y) {
    COORD coord = {0, 0};
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
int main()
{
    char key;
    int arrow = 0;
    char str[max_size];
    str[arrow]='\0';
    gotoxy (0,2);
    printf("Start Typing . . . . . .\n");
    gotoxy(0,4);
    while(1){

        key=getch();
        if(-32 == key){
        key = getch();
        switch (key){

            // go left
            case left_key:
        if(arrow>0){
                gotoxy(arrow-1,4);
                arrow--;}
            break;
             //go right
            case right_key:
               if (arrow < max_size && str[arrow] != '\0'){
                gotoxy(arrow+1,4);
                arrow++;
               }
            break;}
            }
        else{
            switch (key)
            {
                // getting character in run time
            default:
                 str[arrow] = (char) key;
                 printf("%c",str[arrow]);
                 arrow++;
             break;
                // go back through the line and delete
            case back_key:
                if (arrow >0){
                for (int i = arrow - 1; i < max_size; i++) {
                    str[i] = str[i + 1];
                }
                arrow--;
                system("cls");
                gotoxy (0,2);
                printf("Start Typing . . . . . .\n");
                gotoxy(0,4);
                printf("%s",str);
                gotoxy(arrow-1,4);
            }
                break;
                  // printing string after press enter key
            case enter_key:
                printf(" \n%s",str);
                break;

                // exit the program
            case exit_key:
                exit(0);
                break;
        }
    }
    }
    return 0;
    }
