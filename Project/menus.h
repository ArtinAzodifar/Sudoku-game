#include <iostream>
#include "clui.h"

#define middle_row get_window_rows()/2
#define middle_col get_window_cols()/2

using namespace std;

//main menu screen:
void print_main_menu(const char* username)
{
    clear_screen();
    change_color_rgb(148, 57, 24);
    cout<<"You logged in as: "<<username<<endl;
    change_color_rgb(36, 24, 148);
    cursor_to_pos(middle_row, middle_col - 10);
    cout<<"Game Options:\n";

    cursor_to_pos(middle_row + 1, middle_col - 10);
    reset_color();
    cout<<"1: ";
    change_color_rgb(153, 9, 16);
    cout<<"New Game\n";

    cursor_to_pos(middle_row + 2, middle_col - 10);
    reset_color();
    cout<<"2: ";
    change_color_rgb(153, 9, 16);
    cout<<"Play a saved game\n";

    cursor_to_pos(middle_row + 3, middle_col - 10);
    reset_color();
    cout<<"3: ";
    change_color_rgb(153, 9, 16);
    cout<<"Scoreboard\n";

    cursor_to_pos(middle_row + 4, middle_col - 10);
    reset_color();
    cout<<"4: ";
    change_color_rgb(153, 9, 16);
    cout<<"Exit\n";

    cursor_to_pos(middle_row + 5, middle_col - 10);
    reset_color();
    cout<<"Enter a number from 1-4: ";

    return;
}


//select difficulty screen:
void print_difficulty_menu(const char* username)
{
    clear_screen();
    change_color_rgb(148, 57, 24);
    cout<<"You logged in as: "<<username<<endl;
    reset_color();
    cursor_to_pos(middle_row, middle_col - 10);
    cout<<"Select difficulty:\n";

    cursor_to_pos(middle_row + 1, middle_col - 10);
    cout<<"1: ";
    change_color_rgb(13, 181, 72);
    cout<<"easy (5min)\n";

    cursor_to_pos(middle_row + 2, middle_col - 10);
    reset_color();
    cout<<"2: ";
    change_color_rgb(237, 237, 38);
    cout<<"medium (3min)\n";

    cursor_to_pos(middle_row + 3, middle_col - 10);
    reset_color();
    cout<<"3: ";
    change_color_rgb(181, 13, 35);
    cout<<"hard (2min)\n";

    cursor_to_pos(middle_row + 4, middle_col - 10);
    reset_color();
    cout<<"select a number from 1-3: ";
    
    return;
}


//grid screen:
void print_grid(int grid[][9], int cursor[], const char* username, int mistakes, int hint)
{
    clear_screen();
    cursor_to_pos(2, middle_col - 10);
    change_color_rgb(252, 3, 32);
    cout<<"mistakes: "<<mistakes<<"/5";
    cursor_to_pos(2, middle_col + 5);
    change_color_rgb(31, 224, 64);
    cout<<"hints: "<<hint<<"/3";    
    cursor_to_pos(1,1);
    change_color_rgb(148, 57, 24);
    cout<<"You logged in as: "<<username<<endl;
    int row = middle_row - 10;
    for(int i = 0; i < 9; i++)
    {
        cursor_to_pos(row, middle_col - 10);
        for(int j = 0; j < 9; j++)
        {
            reset_color();
            if(cursor[0] == j && cursor[1] == i)
            {
                change_color_rgb(66, 147, 245);
                cout<<grid[i][j];
                if(j == 2 ||  j== 5)    cout<<"\t";
                else    cout<<" ";
            }
            else
            {
                cout<<grid[i][j];
                if(j == 2 ||  j== 5)    cout<<"\t";
                else    cout<<" ";
            }
        }
        if(i == 2 || i == 5)    row++;
        row++;
    }
    cursor_to_pos(middle_row - 10, middle_col - 10);

    return;
}


//pause screen:
void print_pause_screen()
{
    clear_screen();
    cursor_to_pos(middle_row, middle_col - 15);
    cout<<"Game is paused";
    cursor_to_pos(middle_row + 1, middle_col - 15);
    cout<<"press Esc again to return to the game";
    return;
}


//empty cells of grid:
int empty_count(int grid[][9])
{
    int count = 0;

    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            if(grid[i][j] == 0) count++;
        }
    }

    return count;
}



//navigations:
void go_up(int cursor[])
{
    if(cursor[1] != 0)  cursor[1]--;
    return;
}
void go_down(int cursor[])
{
    if(cursor[1] != 8)  cursor[1]++;
    return;
}
void go_right(int cursor[])
{
    if(cursor[0] != 8)  cursor[0]++;
    return;
}
void go_left(int cursor[])
{
    if(cursor[0] != 0)  cursor[0]--;
    return;
}