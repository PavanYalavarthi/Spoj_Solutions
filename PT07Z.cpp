/*

Problem credits: https://www.spoj.com/problems/PT07Z/

You are given an unweighted, undirected tree. Write a program to output the length of the longest path (from one node to another) in that tree. The length of a path in this case is number of edges we traverse from source to destination.

Input
The first line of the input file contains one integer N - number of nodes in the tree (0 < N <= 10000). Next N-1 lines contain N-1 edges of that tree - Each line contains a pair (u, v) means there is an edge between node u and node v (1 <= u, v <= N).

Output
Print the length of the longest path on one line.

Example
Input:
3
1 2
2 3

Output:
2

*/

/*
Solution:
basic DFS and store 2 max for given vertex. 

Ans will be max(max1 + max2) ie., path pasing through vertex and it returns max depth from the vertex to its child
*/
#include<bits/stdc++.h>
using namespace std;
int ans = 0;
int dfs(int node, int par, vector<int>gr[]) {
    int max1 = 0, max2 = 0;
    for(int child: gr[node]) {
        if (child != par) {
            int len = dfs(child, node, gr) + 1;
            if(len > max1) {
                max2 = max1;
                max1 = len;
            } else if(len > max2) {
                max2 = len;
            }
        }
    }
    ans = max(ans, max1 + max2);
    return max1;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int>gr[n + 1];
    for(int i = 1; i<n;i++) {
        int a, b;
        cin >> a >> b;
        gr[a].push_back(b);
        gr[b].push_back(a);
    }
    dfs(1, 0, gr);
    cout << ans;
}