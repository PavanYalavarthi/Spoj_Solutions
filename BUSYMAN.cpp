/*
Problem Credits: https://www.spoj.com/problems/BUSYMAN/

You are actually very busy man. You have a big schedule of activities. Your aim is to do as much as activities as possible.

In the given figure, if you go to date with crush, you cannot participate in the coding contest and you can’t watch the movie. Also if you play DotA, you can’t study for the exam. If you study for the exam you can’t sleep peacefully. The maximum number of activities that you can do for this schedule is 3. 

Either you can

watch movie, play DotA and sleep peacefully (or)
date with crush, play DotA and sleep peacefully
Input
The first line consists of an integer T, the number of test cases. For each test case the first line consists of an integer N, the number of activities. Then the next N lines contains two integers m and n, the start and end time of each activity.

Output
For each test case find the maximum number of activities that you can do.

Constraints
1 ≤ T ≤10
1 ≤ N ≤ 100000
0 ≤ start < end ≤ 1000000

Example
Input
3
3
3 9
2 8
6 9
4
1 7
5 8
7 8
1 8
6
7 9
0 10
4 5
8 9
4 10
5 7

Output:
1
2
3

#greedy

*/

/*
Solution: Taking greedy on completing max tasks in given end time
*/
#include<bits/stdc++.h>
using namespace std;
int main() {
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<pair<int, int>> activities(n);
        for(int i =0; i< n; i++) {
            cin >> activities[i].second >> activities[i].first;
        }
        sort(activities.begin(), activities.end()); // Sorting on end time.
        int ans = 1, end = activities[0].first;
        for(int i = 1; i < activities.size(); i++) {
            if (activities[i].second >= end) { // If start time is after the picked task end time, we can pick this
                end = activities[i].first;
                ans++;
            }
        }
        cout << ans << endl;
    }
    return 0;
}