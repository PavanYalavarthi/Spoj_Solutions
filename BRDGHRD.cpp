/*
Problem Credits: https://www.spoj.com/problems/BRDGHRD/

The tribe soon discovers that just communication is not enough and wants to meet each other to form a joint force against the terminator. But there is a deep canyon that needs to crossed. Points have been identified on both sides on which bridge ends can be made. But before the construction could be started, a witch Chudael predicted that a bridge can only be built between corresponding end points, i.e. a bridge starting from the ith end point on one side can only end on the ith end point on the other side, where the position of end points is seen in the order in which the points were identified. If not, it would lead to the end of the tribe. The tribe just wants to make as many non-overlapping bridges as possible, with the constraint in mind.

Input
The first line of the input contains test cases t. It is followed by 3xt lines, 3 for each test case. The first line of input for each test case contains the number of end points identified on each side, n (1 <= n <= 105). The second line contains x-coordinates of end points identified on the first side and similarly the third line contains the x-coordinates of corresponding end points identified on the other side. The end points are inputted in the order in which they were identified. The x-coordinates can range between -106 to 106.

Output
You are required to output a single line for each test case. The line contains a single integer - the maximum number of bridges possible with the constraints explained above.

Example
Input:
3
4
2 5 8 10
6 4 1 2
3
5 3 10
6 4 1
6
1 2 3 4 5 6
3 4 5 6 1 2

Output:
2
2
4
Explanation
For the first test case, two non-overlapping bridges can be formed between the 3rd and 4th end points on each side.

(This problem is based on BRIDGE.)

#LIS
*/

/*
Solution:
    Question is to find no.of bridges that can be construted without overlapping and not expecting ith index. (Similar to Russian Doll Envelope of Leetcode)

    We sort vector on starting points, so starting points are sorted,
    Now find LIS on end points.
*/
#include<bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<pair<int,int>> v(n);
        for(int i=0; i <n; i++) cin >> v[i].first;
        for(int i=0; i <n; i++) cin >> v[i].second;
        sort(v.begin(), v.end());
        vector<int> dp;
        dp.push_back(v[0].second);
        for(int i =1 ;i < n; i++) {
            int index = lower_bound(dp.begin(), dp.end(), v[i].second + 1) - dp.begin();
            if (index == dp.size()) dp.push_back(v[i].second);
            else dp[index] = v[i].second;
        }
        cout << dp.size() << '\n';
    }
}