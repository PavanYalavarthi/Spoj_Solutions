/*
Problem Credits: https://www.spoj.com/problems/AGGRCOW/

Farmer John has built a new long barn, with N (2 ≤ N ≤ 100,000) stalls. The stalls are located along a straight line at positions x1 ... xN (0 ≤ xi ≤ 1,000,000,000).

His C (2 ≤ C ≤ N) cows don't like this barn layout and become aggressive towards each other once put into a stall. To prevent the cows from hurting each other, FJ wants to assign the cows to the stalls, such that the minimum distance between any two of them is as large as possible. What is the largest minimum distance?

Input
t – the number of test cases, then t test cases follows.

Line 1: Two space-separated integers: N and C
Lines 2..N+1: Line i+1 contains an integer stall location, xi
Output
For each test case output one integer: the largest minimum distance.

Example
Input:
1
5 3
1
2
8
4
9

Output:
3
Explanation
FJ can put his 3 cows in the stalls at positions 1, 4 and 8, resulting in a minimum distance of 3.

#binary_search
*/

/*
Solution:
    Success on distance is a monotonic function. So, using binary search to find the maximum distance possible
*/
#include<bits/stdc++.h>
using namespace std;

bool isPossible(vector<int>& stalls, int dis, int C) {
    int prev = stalls[0], count = 1;
    for(int i = 1; i < stalls.size(); i++) {
        if (stalls[i] - prev >= dis) {
            prev = stalls[i];
            count++;
            if (count == C) return true;
        }
    }
    return false;
}
int main() {
    int t;
    cin >> t;
    while(t--) {
        int N, C;
        cin >> N >> C;
        vector<int>stalls(N);
        for(int i = 0; i < N; i++) {
            cin >> stalls[i];
        }
        sort(stalls.begin(), stalls.end());
        int start = 1, end = stalls.back() - stalls.front(), ans;
        while(start <= end) {
            int mid = (start + end) / 2;
            if(isPossible(stalls, mid, C)) {
                ans = mid;
                start = mid + 1;
            } else {
                end = mid -1;
            }
        }
        cout << ans << endl;
    }
}