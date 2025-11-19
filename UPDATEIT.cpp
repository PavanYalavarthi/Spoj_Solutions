/*
Problem credits: https://www.spoj.com/problems/UPDATEIT/

You have an array containing n elements initially all 0. You need to do a number of update operations on it. In each update you specify l, r and val which are the starting index, ending index and value to be added. After each update, you add the 'val' to all elements from index l to r. After 'u' updates are over, there will be q queries each containing an index for which you have to print the element at that index.

Input
First line consists of t, the number of test cases. (1 ≤ t ≤ 10)

Each test case consists of "n u", number of elements in the array and the number of update operations, in the first line (1 ≤ n ≤ 10000 and 1 ≤ u ≤ 100000)

Then follow u lines each of the format "l r val" (0 ≤ l, r < n, 0 ≤ val ≤ 10000)

Next line contains q, the number of queries. (1 ≤ q ≤ 10000)

Next q lines contain an index (0 ≤ index < n)

Output
For each test case, output the answers to the corresponding queries in separate lines.

Example
Input:
1
5 3
0 1 7
2 4 6
1 3 2
3
0
3
4

Output:
7
8
6

#Sweep_line / #Fenwick_tree
*/

/*
Solution:
    Using sweepline algorithm. Adding at l and subtracting at (r + 1)
*/
#include<bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while(t--) {
        int n, q;
        cin >> n >> q;
        vector<int>v(n+1, 0);
        while(q--) {
            int l, r, val;
            cin >> l >> r >> val;
            v[l] += val;
            v[r+1] -= val;
        }
        for(int i =1;i <= n; i++) {
            v[i] += v[i-1];
        }
        cin >> q;
        while(q--) {
            int index;
            cin >> index;
            cout << v[index] << endl;
        }
    }
}


/*Below is the fenwick tree solution */

/*
#include<bits/stdc++.h>
using namespace std;
struct BIT {
    vector<int>v;
    BIT(int n) {
        v.assign(n+2, 0);
    }
    void update(int index, int val) {
        index++;
        while(index < v.size()) {
            v[index] += val;
            index += index & -index;
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
        int n, q;
        cin >> n >> q;
        BIT bit(n);
        while(q--) {
            int l, r, val;
            cin >> l >> r >> val;
            bit.update(l, val);
            bit.update(r+1, -val);
        }
        cin >> q;
        int index;
        while(q--) {
            cin >> index;
            cout << bit.query(index) << endl;
        }
    }
}
*/