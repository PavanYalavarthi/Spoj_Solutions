/*
Problem Credits: https://www.spoj.com/problems/DSUBSEQ/

Given a string, count the number of distinct subsequences of it (including empty subsequence). For the uninformed, a subsequence of a string is a new string which is formed from the original string by deleting some of the characters without disturbing the relative positions of the remaining characters.
For example, "AGH" is a subsequence of "ABCDEFGH" while "AHG" is not.

Input
First line of input contains an integer T which is equal to the number of test cases. You are required to process all test cases. Each of next T lines contains a string s.

Output
Output consists of T lines. Ith line in the output corresponds to the number of distinct subsequences of ith input string. Since, this number could be very large, you need to output ans%1000000007 where ans is the number of distinct subsequences.

Example
Input:
3
AAA
ABCDEFG
CODECRAFT

Output:
4
128
496
Constraints and Limits
T <= 100, length(S) <= 100000
All input strings shall contain only uppercase letters.

#dp
*/

/*
Solution: 
    dp[i] => no.of distinct subsequences till index i
    dp[i] = 2* dp[i-1]  // dp[i-1] + (for every dp[i-1]th subsequence we add s[i])
                - dp[lastIndex of s[i]]  // As those are extra added e.g: BAA => BA which is already counted 
*/

#include<bits/stdc++.h>
using namespace std;
#define MOD 1000000007
int main() {
    int t;
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> t;
    while(t--) {
        string s;
        cin >> s;
        int n = s.size();
        vector<int>dp(n + 1);
        vector<int>last(26, -1);
        dp[0] = 1;
        for(int i = 1; i<= n; i++) {
            dp[i] = (2 * dp[i - 1]) % MOD;
            int lastIndex = last[s[i-1] - 'A'];
            if(lastIndex != -1) dp[i] = (dp[i] - dp[lastIndex] + MOD)%MOD;
            last[s[i-1] - 'A'] = i - 1;
        }
        cout << dp[n] << '\n';
    }
    return 0;
}