#include <iostream>
#include <ctime>
#include <conio.h>
#include "clui.h"
#include "menus.h"
#include "users.h"
#include "saving.h"
#include "grid.h"

#define middle_row get_window_rows()/2
#define middle_col get_window_cols()/2
#define up 0x48
#define down 0x50
#define right 0x4D
#define left 0x4B
#define Esc 27

using namespace std;

void main_menu(user);
void new_game(user);
void load_game(user);
void scoreboard(user);
void game(int[][9], int[][9], int, int, int, int, user);
void pause_screen();

int main()
{
    while(true)
    {
        srand(time(nullptr));
        user player;
        clear_screen();
        cursor_to_pos(middle_row*2, 1);
        cout<<"name and password shouldnt have space in them";
        cursor_to_pos(1, 1);
        cout<<"enter your name: ";
        cin>>player.name;
        cout<<"enter your password: ";
        cin>>player.password;
        if(user_exists(player) == 1)    login(player);
        else if(user_exists(player) == -1)   create_ac(player);
        else
        {
            cout<<"wrong password!\n";
            delay(300);
            clear_screen();
            continue;
        }
        clear_screen();
        main_menu(player);
    }
    return 0;
}

void main_menu(user player)
{
    print_main_menu(player.name);

    int command;
    cin>>command;
    switch (command)
    {
        case 1:
            clear_screen();
            new_game(player);
            main_menu(player);
            break;
        case 2:
            clear_screen();
            load_game(player);
            main_menu(player);
            break;
        case 3:
            clear_screen();
            scoreboard(player);
            main_menu(player);
            break;
        case 4:
            return;
            break;
        default:
            cursor_to_pos(middle_row + 6, middle_col - 10);
            cout<<"Invalid Number!\n";
            delay(1000);
            clear_screen();
            main_menu(player);
            break;
    }

    return;
}

void new_game(user player)
{
    int grid[9][9] = {0};
    int ans[9][9];
    generate(grid, ans);

    print_difficulty_menu(player.name);

    int command;
    cin>>command;
    switch (command)
    {
    case 1:
        game(grid, ans, 300, 0, 0, 3, player);
        break;
    case 2:
        game(grid, ans, 180, 0, 0, 3, player);
        break;
    case 3:
        game(grid, ans, 120, 0, 0, 3, player);
        break;
    default:
        cursor_to_pos(middle_row + 5, middle_col - 10);
        change_color_rgb(181, 13, 35);
        cout<<"Invalid Number!\n";
        delay(1000);
        clear_screen();
        new_game(player);
        break;
    }

    return;
}


void load_game(user player)
{
    char playername[50];
    strcpy(playername, player.name);
    if(save_count(playername) == 0)
    {
        cursor_to_pos(middle_row, middle_col - 15);
        change_color_rgb(179, 18, 18);
        cout<<"you don't have any saved game!";
        reset_color();
        delay(1000);
        return;
    }
    strcpy(playername, player.name);
    user_save_list(playername);
    char savename[50];
    cursor_to_pos(middle_row + 5, middle_col - 10);
    change_color_rgb(225, 235, 52);
    cout<<"enter your save name(enter return to go back): ";
    reset_color();
    cursor_to_pos(middle_row + 5, middle_col + 37);
    cin>>savename;
    if(strcmp(savename, "return") == 0) return;
    if(save_exists(savename))
    {
        int grid[9][9];
        int ans[9][9];
        int correct;
        int mistakes;
        int maxtime;
        int hint;
        load_save(savename, grid, ans, correct, mistakes, maxtime, hint);
        game(grid, ans, maxtime, correct, mistakes, hint, player);
    }
    else
    {
        cout<<"save doesnt exist!";
        delay(500);
        load_game(player);
    }
    return;
}

void game(int grid[][9], int ans[][9], int maxtime, int correct, int mistakes, int hint, user player)
{
    bool finish = false, win = false;
    time_t start_time = time(nullptr);

    int cursor[] = {0,0}; // x:1 y:0
    print_grid(grid, cursor, player.name, mistakes, hint);

    time_t current_time = time(nullptr);
    time_t pause_time = 0;
    double elapsed_time = difftime(current_time, start_time);

    while(!finish)
    {
        current_time = time(nullptr);
        elapsed_time = difftime(current_time, start_time);
        int minute = (maxtime - (int)(elapsed_time) + (int)(pause_time)) / 60;
        int second = (maxtime - (int)(elapsed_time) + (int)(pause_time)) % 60;
        
        cursor_to_pos(2,1);
        cout<<"Remained Time: "<<minute<<":"<<second<<'\t';

        if(_kbhit())
        {
            char c = getch();
            switch(c)
            {
                case up:
                    go_up(cursor);
                    break;
                case down:
                    go_down(cursor);
                    break;
                case right:
                    go_right(cursor);
                    break;
                case left:
                    go_left(cursor);
                    break;
                case Esc:
                {
                    time_t start_pause = time(nullptr);
                    pause_screen();
                    time_t end_pause = time(nullptr);
                    pause_time += difftime(end_pause, start_pause);
                    break;
                }
                case 'q':
                    finish = true;
                    win = false;
                    break;
                case 's':
                    new_save(player.name, correct, mistakes, grid, ans, (maxtime - (int)(elapsed_time) + (int)(pause_time)), hint);
                    return;
                    break;
                case 'h':
                    if(hint > 0)
                    {
                        hint--;
                        hint_grid(grid, ans);
                    }
                    else
                    {
                        change_color_rgb(140, 21, 21);
                        cursor_to_pos(middle_row + 1, middle_col - 10);
                        cout<<"you don't have any hint!";
                        delay(250);
                    }
                    break;
            }
            if(c >= '1' && c <= '9')
            {
                if(grid[cursor[1]][cursor[0]] == 0 && ans[cursor[1]][cursor[0]] == c-'0') 
                {
                    grid[cursor[1]][cursor[0]] = c-'0';
                    correct++;
                }
                else if(grid[cursor[1]][cursor[0]] == 0)
                {
                    change_color_rgb(140, 21, 21);
                    cursor_to_pos(middle_row + 1, middle_col - 10);
                    cout<<"wrong answer!";
                    mistakes++;
                    delay(250);
                    reset_color();
                }
                else
                {
                    change_color_rgb(140, 21, 21);
                    cursor_to_pos(middle_row + 1, middle_col - 10);
                    cout<<"you can't change here!";
                    delay(250);
                    reset_color();
                }
            }
            print_grid(grid, cursor, player.name, mistakes, hint);
        }

        if((int)(elapsed_time) == maxtime || mistakes == 5)
        {
            finish = true;
            win = false;
        }

        if(empty_count(grid) == 0)
        {
            finish = true;
            win = true;
        }
    }

    clear_screen();
    if(win)
    {
        change_color_rgb(9, 232, 58);
        cursor_to_pos(middle_row - 5, middle_col - 5);
        cout<<"You Won!";
        cursor_to_pos(middle_row - 4, middle_col - 5);
        cout<<"corrects: "<<correct;
        cursor_to_pos(middle_row - 3, middle_col - 5);
        cout<<"mistakes: "<<mistakes;
        cursor_to_pos(middle_row - 2, middle_col - 5);
        cout<<"remained time: "<< (maxtime - (int)(elapsed_time) + (int)(pause_time))<<'s';
        player.win++;
        player.correct += correct;
        player.mistake += mistakes;
        player.score = player.correct - player.mistake;
        player.time_left = (maxtime - (int)(elapsed_time) + (int)(pause_time));
        update_user(player);
        reset_color();
    }
    else
    {
        change_color_rgb(252, 3, 32);
        cursor_to_pos(middle_row - 5, middle_col - 5);
        cout<<"You Lost!";
        cursor_to_pos(middle_row - 4, middle_col - 5);
        cout<<"corrects: "<<correct;
        cursor_to_pos(middle_row - 3, middle_col - 5);
        cout<<"mistakes: "<<mistakes;
        cursor_to_pos(middle_row - 2, middle_col - 5);
        cout<<"remained time: "<< (maxtime - (int)(elapsed_time) + (int)(pause_time))<<'s';
        player.loss++;
        player.correct += correct;
        player.mistake += mistakes;
        player.score = player.correct - player.mistake;
        player.time_left = (maxtime - (int)(elapsed_time) + (int)(pause_time));
        update_user(player);
        reset_color();
    }
    cursor_to_pos(middle_row - 1, middle_col - 5);
    cout<<"press m to go back to main menu";
    while(true)
    {
        char c = getch();
        if(c == 'm')    break;
    }
    return;
}

void pause_screen()
{
    print_pause_screen();
    char c;
    while (true)
    {
        c = getch();
        if(c == Esc)    break;
    }
    return;  
}

void scoreboard(user player)
{
    clear_screen();
    change_color_rgb(148, 57, 24);
    cout<<"You logged in as: "<<player.name<<endl;
    int count = 0;
    user* users = scoreboard(count);
    change_color_rgb(90, 245, 66);
    cursor_to_pos(middle_row - 10, middle_col - 35);
    cout<<"name\t\tscore\t\ttime left\twins\tloss\tcorrects\tmistakes\n";
    reset_color();
    for(int i = 0; i < count; i++)
    {
        cursor_to_pos(middle_row - 9 + i, middle_col - 35);
        cout<< users[i].name << "\t\t" << users[i].score << "\t\t" << users[i].time_left << "s\t\t" << users[i].win << '\t' << users[i].loss << '\t' << users[i].correct << "\t\t" << users[i].mistake << endl;
    }
    delete[] users;
    cursor_to_pos(middle_row - 8 + count, middle_col - 35);
    change_color_rgb(168, 5, 10);
    cout<<"press m to go back";
    char c;
    while(true)
    {
        c = getch();
        if(c == 'm')    break;
    }
    return;
}