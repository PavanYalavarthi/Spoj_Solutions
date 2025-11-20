/*
Problem credits: https://www.spoj.com/problems/MIXTURES/


Harry Potter has n mixtures in front of him, arranged in a row. Each mixture has one of 100 different colors (colors have numbers from 0 to 99).

He wants to mix all these mixtures together. At each step, he is going to take two mixtures that stand next to each other and mix them together, and put the resulting mixture in their place.

When mixing two mixtures of colors a and b, the resulting mixture will have the color (a+b) mod 100.

Also, there will be some smoke in the process. The amount of smoke generated when mixing two mixtures of colors a and b is a x b.

Find out what is the minimum amount of smoke that Harry can get when mixing all the mixtures together.

Input
There will be a number of test cases in the input.

The first line of each test case will contain n, the number of mixtures, 1 <= n <= 100.

The second line will contain n integers between 0 and 99 - the initial colors of the mixtures.

Output
For each test case, output the minimum amount of smoke.

Example
Input:
2
18 19
3
40 60 20

Output:
342
2400
In the second test case, there are two possibilities:

first mix 40 and 60 (smoke: 2400), getting 0, then mix 0 and 20 (smoke: 0); total amount of smoke is 2400
first mix 60 and 20 (smoke: 1200), getting 80, then mix 40 and 80 (smoke: 3200); total amount of smoke is 4400
The first scenario is a much better way to proceed.

#Dynamic_programming
*/

/*
Solution: 
Similar to matrix chain multiplication, but here playing with prefix sums
*/
#include<bits/stdc++.h>
using namespace std;

int cummulativeSum(vector<int> & prefixSum, int i, int j) {
    return (prefixSum[j] - prefixSum[i-1] + 100) % 100;
}
int helper(vector<int> & prefixSum, int i, int j, vector<vector<int>> &dp) {
    if (i == j) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    int ans = INT_MAX;
    for(int k = i; k < j; k++) {
        ans = min(ans, helper(prefixSum, i, k, dp) + helper(prefixSum, k + 1, j, dp) + cummulativeSum(prefixSum, i, k) * cummulativeSum(prefixSum, k + 1, j));
    }
    return dp[i][j] = ans;
}
int main() {
    int t;
    cin.tie(nullptr)->sync_with_stdio(false);
    while(true) {
        int n;
        if(cin >> n) {
            vector<int>prefixSum(n +1);
            prefixSum[0] = 0;
            for(int i = 1; i<= n; i++) {
                cin >> prefixSum[i];
                prefixSum[i] = (prefixSum[i] +  prefixSum[i-1]) % 100;
            }
            vector<vector<int>> dp (n + 1, vector<int>(n+1, -1));
            cout << helper(prefixSum,1, n, dp) << endl;
        } else {
            break;
        }
    }
}