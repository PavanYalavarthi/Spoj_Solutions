/*
Problem credits: https://www.spoj.com/problems/TOURIST/

A lazy tourist wants to visit as many interesting locations in a city as possible without going one step further than necessary. Starting from his hotel, located in the north-west corner of city, he intends to take a walk to the south-east corner of the city and then walk back. When walking to the south-east corner, he will only walk east or south, and when walking back to the north-west corner, he will only walk north or west. After studying the city map he realizes that the task is not so simple because some areas are blocked. Therefore he has kindly asked you to write a program to solve his problem.

Given the city map (a 2D grid) where the interesting locations and blocked areas are marked, determine the maximum number of interesting locations he can visit. Locations visited twice are only counted once.

Input
The first line in the input contains the number of test cases (at most 20). Then follow the cases. Each case starts with a line containing two integers, W and H (2 <= W, H <= 100), the width and the height of the city map. Then follow H lines, each containing a string with W characters with the following meaning:

. Walkable area
* Interesting location (also walkable area)
# Blocked area
You may assume that the upper-left corner (start and end point) and lower-right corner (turning point) are walkable, and that a walkable path of length H + W - 2 exists between them.

Output
For each test case, output a line containing a single integer: the maximum number of interesting locations the lazy tourist can visit.

Example
Input:
2
9 7
*........
.....**#.
..**...#*
..####*#.
.*.#*.*#.
...#**...
*........
5 5
.*.*.
*###.
*.*.*
.###*
.*.*.

Output:
7
8

#dp
*/

/*
Solution:
Take two tourist starting from top left and get max for all possible combinations as second tourist mimics the coming back tourist.

just make sure, you dont count * twice for 2 tourists when landed on same cell.
*/
#include<bits/stdc++.h>
using namespace std;
int w, h;
int dir[] = {0,1,0,1,1,0,1,0,0,1};
int dp[100][100][100];
int helper(vector<string> & grid, int x1, int y1, int x2, int y2) {
    if(x1 == h or x2 == h or y1 == w or y2 == w or grid[x1][y1] == '#' or grid[x2][y2] == '#') return 0;
    if(dp[x1][y1][x2] != -1) return dp[x1][y1][x2];
    int ans = 0;
    for(int i = 0; i<7; i+=2) {
        ans = max(ans, helper(grid, x1 + dir[i], y1 + dir[i+1], x2 + dir[i+2], y2 + dir[i+3]));
    }
    ans += (grid[x1][y1] == '*');
    if (x1 != x2) ans += (grid[x2][y2] == '*');
    return dp[x1][y1][x2] = ans;
}
int main() {
    int t;
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> t;
    while(t--) {
        cin >> w >> h;
        vector<string> grid(h);
        for(int i=0; i<h; i++) {
            cin >> grid[i];
        }
        memset(dp, -1, sizeof(dp));
        cout << helper(grid, 0, 0, 0, 0) << endl;
    }
    return 0;
} 