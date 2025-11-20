/*
problem credits: https://www.spoj.com/problems/ARRAYSUB/

Given an array and an integer k, find the maximum for each and every contiguous subarray of size k.

Input
The number n denoting number of elements in the array then after a new line we have the numbers of the array and then k in a new line.

n < 106
k < 105
1 <= k <= n

and each element of the array is between 0 and 106.

(Edited: In fact, n <= 105)

Output
Print the output array.

Example
Input:
9
1 2 3 1 4 5 2 3 6
3

Output:
3 3 4 5 5 5 6

#Sliding_window
*/

/*
Solution:
    Use Deque, and maintain sorted order (Greater at front)
    and pop front if element is out of silding window.
*/

#include<bits/stdc++.h>
using namespace std;
int main() {
    int n, k;
    cin >> n;
    vector<int>v(n);
    for(int i = 0; i< n; i++) cin >> v[i];
    cin >> k;
    deque<int>q;
    for(int i = 0; i < k; i++) {
        while(!q.empty() && v[q.back()] <= v[i]) q.pop_back();
        q.push_back(i);
    }
    for(int i = k; i < n; i++) {
        cout << v[q.front()] << " ";
        while(!q.empty() && q.front() <= i - k) q.pop_front(); // removing element that are outside sliding window
        while(!q.empty() && v[q.back()] <= v[i]) q.pop_back(); // removing element that are smaller than current element
        q.push_back(i);
    }
    cout << v[q.front()];
    return 0;
}