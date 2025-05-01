#include <iostream>
#include <cstring>
#include <fstream>
#include "clui.h"

#define middle_row get_window_rows()/2
#define middle_col get_window_cols()/2

using namespace std;

int save_count(char player[50])
{
    strcat(player, ".txt");
    int count = 0;
    fstream save_list;
    save_list.open(player, ios::in);
    char savename[50];
    while(save_list >> savename)    count++;
    save_list.close();
    return count;
}


bool save_exists(const char* savename)
{
    fstream save_list;
    save_list.open("save_list.txt", ios::in);
    char name[50];
    while(save_list >> name)
    {
        if(strcmp(name, savename) == 0) 
        {
            save_list.close();
            return true;
        }
    }
    save_list.close();
    return false;
}


void user_save_list(char player[50])
{
    clear_screen();
    strcat(player, ".txt");
    fstream save_list;
    save_list.open(player, ios::in);
    char savename[50];
    int i = 0;
    while(save_list >> savename)
    {
        cursor_to_pos(middle_row - 5 + i, middle_col - 10);
        cout<<savename<<endl;
        i++;
    }
    save_list.close();
    return;
}


void new_save(const char* player, int correct, int mistakes, int grid[][9], int ans[][9], int maxtime, int hint)
{
    clear_screen();
    cursor_to_pos(middle_row - 5, middle_col - 10);
    cout<<"enter your save name: ";
    char savename[50];
    cursor_to_pos(middle_row - 5, middle_col + 12);
    cin>>savename;
    if(!save_exists(savename))
    {
        fstream save_list;
        save_list.open("save_list.txt", ios::app);
        save_list << savename << endl;
        save_list.close();

        fstream user_save_list;
        char filename[50];
        strcpy(filename, player);
        strcat(filename, ".txt");
        user_save_list.open(filename, ios::app);
        user_save_list << savename << endl;
        user_save_list.close();

        strcat(savename, ".txt");
        fstream savefile;
        savefile.open(savename, ios::out);
        for(int i = 0; i < 9; i++)
        {
            for(int j = 0; j < 9; j++)  savefile << grid[i][j] << ' ';
            savefile << endl;
        }
        for(int i = 0; i < 9; i++)
        {
            for(int j = 0; j < 9; j++)  savefile << ans[i][j] << ' ';
            savefile << endl;
        }
        savefile << correct << endl << mistakes << endl << maxtime << endl << hint;
        savefile.close();
        cursor_to_pos(middle_row, middle_col - 5);
        change_color_rgb(13, 166, 44);
        cout<<"game saved!\n";
        reset_color();
        delay(500);
    }
    else
    {
        cursor_to_pos(middle_row, middle_col - 5);
        change_color_rgb(166, 13, 23);
        cout<<"this name already exists!";
        reset_color();
        delay(1000);
        new_save(player, correct, mistakes, grid, ans, maxtime, hint);
    }
    return;
}


void load_save(char savename[50], int grid[][9], int ans[][9], int& correct, int& mistakes, int& maxtime, int& hint)
{
    strcat(savename, ".txt");
    fstream savefile;
    savefile.open(savename, ios::in);
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)  savefile >> grid[i][j];
    }
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)  savefile >> ans[i][j];
    }
    savefile >> correct >> mistakes >> maxtime >> hint;
    savefile.close();
    return;
}