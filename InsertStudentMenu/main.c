#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "standers.h"
#define up_key 72
#define down_key 80
#define right_key 77
#define left_key 75
#define exit_key 27
#define enter_key 13
#define home_key 71
#define back_key 8

// creat student struct
struct student {
    u8 name[10];
    u8 gender;
    u8 age;
    s32 id;
};

void SetColor(int ForgC) {
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}

void gotoxy(int x, int y) {
    COORD coord = {0, 0};
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Add_student(struct student students[], int count);
void display_students(struct student students[], int count);

int main()
{
    char key;
    int arrow = 1; // initial position
    int studentCount = 0;
    struct student students[100];
 while (1) {

 system("cls");

// Display menue
    switch (arrow){
        // new is red
        case 1:
            system("cls");
            gotoxy(2,1);
            SetColor(4);
            printf("New");
            gotoxy(2,4);
            SetColor(15);
            printf("Display");
            gotoxy(2,7);
            SetColor(15);
            printf("Exit");
            break;
        // display is red
        case 2:
            system("cls");
            gotoxy(2,1);
            SetColor(15);
            printf("New");
            gotoxy(2,4);
            SetColor(4);
            printf("Display");
            gotoxy(2,7);
            SetColor(15);
            printf("Exit");
            break;
        // exit is red
        case 3:
            system("cls");
            gotoxy(2,1);
            SetColor(15);
            printf("New");
            gotoxy(2,4);
            SetColor(15);
            printf("Display");
            gotoxy(2,7);
            SetColor(4);
            printf("Exit");
            break;
    }

 // start navigation

    key=getch(); // press key
    if(-32 == key){ // extend or normal
     key = getch(); // extend
     switch (key){
     case up_key: // 72
       arrow --;
     if ( arrow < 1 ){
            arrow = 3;}
            break;
   case down_key: //80
     arrow ++;
        if (arrow > 3 ){
            arrow=1;}
            break;
    }
    }
    else{  // normal key
    switch(key){
    case home_key:
    system("cls");
    arrow =1;
    break;
    case exit_key: //end
    exit(0);
    break;
    // get in by press enter
    case enter_key:
    system("cls");
   switch (arrow){
       char ch;
    case 1:
        // start insertion student by student
        do{
        Add_student(students, studentCount);
        studentCount++;
        printf("Continue?? Y / N :");
        printf("\n");
        ch = getch();
        }while (121 == ch || 89 == ch); // Y || y
            key = home_key;  // return to home
        break;
    case 2:
        // display
        display_students(students, studentCount);

        //return home by only pressing backspace or left arrow
        do{
        ch = getch();
        }while (ch != back_key && ch != left_key);
            key = home_key;
        break;
    case 3:
        exit(0);
        break;
    default:
        break;
    }
    break;
    default:
        break;
    }
    }
}
 return 0;
}
// pass students array and size // the size is the number of students that user add but less than 100, count == student count to link
void Add_student(struct student students[], int count) {
    if (count < 100) {
        printf("Enter name: ");
        scanf(" %[^\n]s", students[count].name);
        printf("Enter age: ");
        scanf("%d", &students[count].age);
        printf("Enter ID: ");
        scanf("%d", &students[count].id);
        printf("Enter Gender : ");
        scanf(" %c", &students[count].gender);
        printf("%d Students added.\n",count+1);
    } else {
        printf("You can't add more than 100 students.\n");
    }
}
  // count == studentcount
void display_students(struct student students[], int count) {
    if (count > 0) {
        for (int i = 0; i < count; i++) {
                printf ("Student %d \n",i+1);
            printf("Name: %s \nAge: %d \nID: %d \nGender: %c\n",
                students[i].name,
                students[i].age,
                students[i].id,
                students[i].gender
            );
        }
    } else {
        printf("No student records to display.\n");
    }
}
