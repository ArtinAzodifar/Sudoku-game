#include <iostream>
#include <ctime>

using namespace std;

bool is_ok(int grid[][9], int row, int col, int number)
{
    for (int i = 0; i < 9; i++) 
    {
        if (grid[row][i] == number || grid[i][col] == number || grid[row-(row%3)+i/3][col-(col%3)+i%3] == number) 
            return false;
    }
    return true;
}

bool fill_grid(int grid[][9], int row, int col)
{
    if(row == 8 && col == 9)    return true;
    else if(col == 9)    return fill_grid(grid, row+1, 0);

    //unsorted 1-9:
    int numbers[] = {1,2,3,4,5,6,7,8,9};
    for(int i = 1; i < 9; i++) 
    {
        int j = rand() % (i+1);
        int temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
    }

    for (int i = 0; i < 9; i++) 
    {
        if (is_ok(grid, row, col, numbers[i])) 
        {
            grid[row][col] = numbers[i];
            if (fill_grid(grid, row, col+1)) return true;
            else    grid[row][col] = 0;
        }
    }
    return false;
}

void generate(int grid[][9], int ans[][9])
{
    fill_grid(grid, 0, 0);

    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)  ans[i][j] = grid[i][j];
    }

    //empty 4 cells of each 9x9:
    for (int i = 0; i < 9; i += 3) 
    {
        for (int j = 0; j < 9; j += 3) 
        {
            int count = 0;
            while (count < 4) 
            {
                int r = rand() % 3; // 0,1,2
                int c = rand() % 3; //0,1,2
                if (grid[i + r][j + c] != 0) 
                {
                    grid[i + r][j + c] = 0;
                    count++;
                }
            }
        }
    }
    return;
}

void hint_grid(int grid[][9], int ans[][9])
{
    while(true)
    {
        int i = rand() % 9;
        int j = rand() % 9;
        if(grid[i][j] == 0)
        {
            grid[i][j] = ans[i][j];
            break;
        }
    }
    return;
}