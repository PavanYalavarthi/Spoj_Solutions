/*
Problem credits: https://www.spoj.com/problems/NUMTSN/

A number is said to be a 369 number if:

The count of 3s is equal to the count of 6s and the count of 6s is equal to the count of 9s.
The count of 3s is at least 1.
For Example 12369, 383676989, 396 all are 369 numbers whereas 213, 342143, 111 are not.

Given A and B find how many 369 numbers are there in the interval [A, B]. Print the answer modulo 1000000007.

Input
The first line contains the number of test cases (T) followed by T lines each containing 2 integers A and B.

Output
For each test case output the number of 369 numbers between A and B inclusive.

Constraints
T ≤ 100

1 ≤ A ≤ B ≤ 1050

Example
Input:
3
121 4325
432 4356
4234 4325667

Output:
60
58
207159


#Digit_DP
*/

/*
Solution: 
    Can be solved using digit DP. But if individual count of 3s, 6s, 9s is used we get TLE

    So, we compress to count6-count3 and count9 - count3

    As, max value is 10^50 => count63 or count93 lies between [-16, 16]. So, initial values of cnt63 and cnt93 is set 16, to avoid negative for indexation

    And, if cnt63 or cnt93 becomes 33 ( > intial value of 16 + max value 16) or negative, exiting by returning 0.

    Rest is default Digit DP template
*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MOD 1000000007
ll dp[51][33][33][2][2];
ll helper(int pos, int cnt63, int cnt93, bool is3Present, bool tight, string& s) {
    if (pos == s.size()) return is3Present && cnt63 == 16 && cnt93 == 16;
    if(cnt63 == 33 || cnt93 == 33 || cnt93 < 0 || cnt63 < 0) return 0;
    ll& ans = dp[pos][cnt63][cnt93][is3Present][tight];
    if(ans != -1) return ans;
    ans = 0;
    int up_bound = tight ? s[pos] - '0' : 9;
    for(int i = 0; i <= up_bound; i++) {
        bool is3 = (i == 3), is6 = (i ==6), is9 = (i == 9);
        (ans += helper(pos + 1, cnt63 + (is6 - is3), cnt93 + (is9 - is3), is3Present | is3, tight & (i == up_bound), s)) %= MOD;
    }
    return ans;
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--) {
        string l, r;
        cin >> l >> r;
        memset(dp, -1, sizeof(dp));
        ll ans = helper(0, 16, 16, false, true, r);
        memset(dp, -1, sizeof(dp));
        int i = l.size() - 1;
        while(l[i] == '0') l[i--] = '9';
        l[i]--;
        cout << (ans - helper(0, 16, 16, false, true, l) + MOD) % MOD << endl;
    }
    return 0;
}