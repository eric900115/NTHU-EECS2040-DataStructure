#include <iostream>
using namespace std;
int row, col, root_x, root_y;
short **arr;
int min_val = -1;
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
void find(int val, int x, int y, int p_x, int p_y)
{
    bool flag = true;
    for (int i = 0; i < 4; i++)
    {
        int next_x = dir[i][0] + x, next_y = dir[i][1] + y;
        if (next_x < 0 || next_x >= row || next_y < 0 || next_y >= col)
            continue;
        if (arr[next_x][next_y] == 0)
            continue;
        if (next_x != p_x || next_y != p_y)
        {
            flag = false;
            if (arr[next_x][next_y] == -1)
                continue;

            val = val + arr[x][y];
            find(val, next_x, next_y, x, y);
            val = val - arr[x][y];
        }
    }
    if (flag == true)
    {
        val = arr[x][y] + val;

        if (min_val == -1)
        {
            min_val = val;
        }
        else
        {
            if (val < min_val)
                min_val = val;
        }
        val = val - arr[x][y];
    }
}

int main()
{
    cin >> row >> col >> root_x >> root_y;

    arr = new short *[row];

    int val = 0;
    for (int i = 0; i < row; i++)
        arr[i] = new short[col];

    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            cin >> arr[i][j];
    find(val, root_y, root_x, -1, -1);
    cout << min_val << "\n";
}