#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct user
{
    char name[50];
    char password[50];
    int win = 0;
    int loss = 0;
    int correct = 0;
    int mistake = 0;
    int score = 0;
    int time_left = 0;
};


int user_exists(user player)
{
    fstream user_list;
    user_list.open("user_list.txt", ios::in);
    user temp;
    while(user_list >> temp.name >> temp.password >> temp.win >> temp.loss >> temp.correct >> temp.mistake >> temp.score >> temp.time_left)
    {
        if(strcmp(temp.name, player.name) == 0 && strcmp(temp.password, player.password) == 0)  
        {
            user_list.close();
            return 1;
        }
        else if(strcmp(temp.name, player.name) == 0)
        {
            user_list.close();
            return 0;
        }
    }
    user_list.close();
    return -1;
}

void login(user& player)
{
    fstream user_list;
    user_list.open("user_list.txt", ios::in);
    user temp;
    while(user_list >> temp.name >> temp.password >> temp.win >> temp.loss >> temp.correct >> temp.mistake >> temp.score >> temp.time_left)
    {
        if(strcmp(temp.name, player.name) == 0)
        {
            player = temp;
            user_list.close();
            return;
        }
    }
    return;
}

void create_ac(user player)
{
    fstream user_list;
    user_list.open("user_list.txt", ios::app);
    user_list << player.name << ' ' << player.password << ' ' << player.win << ' ' << player.loss << ' ' << player.correct << ' ' << player.mistake << ' ' << player.score << ' ' << player.time_left << endl;
    user_list.close();
    char filename[50];
    strcpy(filename, player.name);
    strcat(filename, ".txt");
    fstream new_file;
    new_file.open(filename, ios::out);
    new_file.close();
    return;
}

void update_user(user player)
{
    fstream user_list;
    fstream temp_list;
    user temp;
    user_list.open("user_list.txt", ios::in);
    temp_list.open("temp.txt", ios::out);
    while(user_list >> temp.name >> temp.password >> temp.win >> temp.loss >> temp.correct >> temp.mistake >> temp.score >> temp.time_left)
    {
        if(strcmp(temp.name, player.name) == 0)
        {
            temp_list << player.name << ' ' << player.password << ' ' << player.win << ' ' << player.loss << ' ' << player.correct << ' ' << player.mistake << ' ' << player.score << ' ' << player.time_left << endl;
        }
        else
        {
            temp_list << temp.name << ' ' << temp.password << ' ' << temp.win << ' ' << temp.loss << ' ' << temp.correct << ' ' << temp.mistake << ' ' << temp.score << ' ' << temp.time_left << endl;
        }
    }
    user_list.close();
    temp_list.close();
    remove("user_list.txt");
    rename("temp.txt", "user_list.txt");
    return;
}

user* scoreboard(int& count)
{
    //create array:
    fstream user_list;
    user_list.open("user_list.txt", ios::in);
    user temp;
    while(user_list >> temp.name >> temp.password >> temp.win >> temp.loss >> temp.correct >> temp.mistake >> temp.score >> temp.time_left)   count++;
    user_list.close();
    user* users = new user[count];
    user_list.open("user_list.txt", ios::in);
    int i = 0;
    while(user_list >> temp.name >> temp.password >> temp.win >> temp.loss >> temp.correct >> temp.mistake >> temp.score >> temp.time_left)
    {
        users[i] = temp;
        i++;
    }
    user_list.close();

    //sort array:
    for(i = 0; i < count - 1; i++)
    {
        for(int j = 0; j < count - i - 1; j++)
        {
            if(users[j].score < users[j+1].score)
            {
                user temp = users[j];
                users[j] = users[j+1];
                users[j+1] = temp;
            }
            else if(users[j].score == users[j+1].score && users[j].time_left < users[j+1].time_left)
            {
                user temp = users[j];
                users[j] = users[j+1];
                users[j+1] = temp;
            }
        }
    }

    return users;
}