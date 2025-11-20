/*
Problem Credits: https://www.spoj.com/problems/DEFKIN

Theodore implements a new strategy game “Defense of a Kingdom”. On each level a player defends the Kingdom that is represented by a rectangular grid of cells. The player builds crossbow towers in some cells of the grid. The tower defends all the cells in the same row and the same column. No two towers share a row or a column.

The penalty of the position is the number of cells in the largest undefended rectangle. For example, the position shown on the picture has penalty 12.

This position has a penalty of 12.

Help Theodore write a program that calculates the penalty of the given position.

Input
The first line of the input file contains the number of test cases.

Each test case consists of a line with three integer numbers: w - width of the grid, h - height of the grid and n - number of crossbow towers (1 <= w, h <= 40 000; 0 <= n <= min(w, h)).

Each of the following n lines contains two integer numbers xi and yi - the coordinates of the cell occupied by a tower (1 <= xi <= w; 1 <= yi <= h).

Output
For each test case, output a single integer number - the number of cells in the largest rectangle that is not defended by the towers.

Example
Input:
1
15 8 3
3 8
11 2
8 6

Output:
12

#greedy
*/
/*
    Greedy based approach.
    1. Push all x coordinates along with 0 and w + 1  (as these are boundaries)
    2. Push all y coordinates along with 0 and h + 1  (as these are boundaries)
    3. sort them
    4. find biggest x_delta and y_delta, multiplication gives area of maximum rectangle
*/
#include<bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while(t--) {
        int w, h, n;
        cin >> w >> h >> n;
        vector<int>x_axis(n+2), y_axis(n+2);
        for(int i = 0; i < n; i++) {
            cin >> x_axis[i]>> y_axis[i];
        }
        x_axis[n] = y_axis[n] = 0;
        x_axis[n+1] = w+1;
        y_axis[n+1] = h+1;
        sort(x_axis.begin(), x_axis.end());
        sort(y_axis.begin(), y_axis.end());
        int max_delta_x = 0, max_delta_y = 0;
        for(int i = 1; i< x_axis.size(); i++) {
            max_delta_x = max(max_delta_x, x_axis[i] - x_axis[i-1] - 1);
            max_delta_y = max(max_delta_y, y_axis[i] - y_axis[i-1] - 1);
        }
        cout << (long)max_delta_x * max_delta_y << endl;

    }
}