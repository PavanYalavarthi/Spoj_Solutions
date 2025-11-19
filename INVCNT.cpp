/*
Problem credits: https://www.spoj.com/problems/INVCNT/

Let A[0 ... n - 1] be an array of n distinct positive integers. If i < j and A[i] > A[j] then the pair (i, j) is called an inversion of A. Given n and an array A your task is to find the number of inversions of A.

Input
The first line contains t, the number of testcases followed by a blank space. Each of the t tests start with a number n (n ≤ 200000). Then n + 1 lines follow. In the ith line a number A[i - 1] is given (A[i - 1] ≤ 107). The (n + 1)th line is a blank space.

Output
For every test output one line giving the number of inversions of A.

Example
Input:
2

3
3
1
2

5
2
3
8
6
1


Output:
2
5

#inversion_count #fenwick_tree
*/

/*
Solution:
    Using fenwick tree to store freq of numbers, used coordinate compression to minimize the size
*/
#include<bits/stdc++.h>
using namespace std;

struct BIT {
    vector<int>v;
    BIT(int n) {
        v.assign(n + 1, 0);
    }

    void update(int index, int val) {
        index++;
        while(index < v.size()) {
            v[index] += val;
            index += (index & -index);
        }
    }

    int query(int index) {
        index++;
        int sum = 0;
        while(index > 0) {
            sum += v[index];
            index -= index & -index;
        }
        return sum;
    }
};

int main() {
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<int>v(n);
        for(int i =0; i<n; i++) {
            cin >> v[i];
        }

        //Coordinate compression
        vector<int> temp(v.begin(), v.end());
        sort(temp.begin(), temp.end());
        temp.erase(unique(temp.begin(), temp.end()), temp.end());
        for(int& x: v) {
            x = lower_bound(temp.begin(), temp.end(), x) - temp.begin();
        }

        BIT bit(n);
        long count = 0;
        for(int i = n -1; i>= 0; i--) {
            count += bit.query(v[i] -1); // get count of all numbers < v[i]
            bit.update(v[i], 1); // Increase count of v[i]
        }
        cout << count << endl;
    }
}
