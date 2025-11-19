/*

Problem credits: https://www.spoj.com/problems/GSS1/

You are given a sequence A[1], A[2] ... A[N] . ( |A[i]| ≤ 15007 , 1 ≤ N ≤ 50000 ). A query is defined as follows:

Query(x, y) = Max { a[i] + a[i+1] + ... + a[j] ; x ≤ i ≤ j ≤ y }.

Given M queries, your program must output the results of these queries.

Input
The first line of the input file contains the integer N.
In the second line, N numbers follow.
The third line contains the integer M.
M lines follow, where line i contains 2 numbers xi and yi.
Output
Your program should output the results of the M queries, one query per line.

Example
Input:
3 
-1 2 3
1
1 2

Output:
2

#Segment_tree #Divide_and_conquer
*/

/*
Solution:

Using divide an conquer approach and segment tree as its a range query

*/
#include<bits/stdc++.h>
using namespace std;
struct Node {
    int prefix, suffix, total, best;
};

struct SegmentTree {
    vector<Node>tree;
    int n;
    Node getParentNode(Node left, Node right) {
        Node node;
        node.prefix = max(left.prefix, left.total + right.prefix);
        node.suffix = max(right.suffix, right.total + left.suffix);
        node.total = left.total + right. total;
        node.best = max(max(left.best, right.best), left.suffix + right.prefix);
        return node;
    }
    Node build(int l, int r, int index, vector<int>& arr) {
        if (l == r) {
            Node node;
            node.prefix = node.suffix = node.total = node.best = arr[l];
            return tree[index] = node;
        }
        int mid = (l + r) / 2;
        Node left = build(l, mid, 2* index + 1, arr);
        Node right = build(mid + 1, r, 2 * index + 2, arr);
        return tree[index] = getParentNode(left, right);
    }

    Node query(int l, int r, int query_start, int query_end, int index) {
        if(query_start > r || l > query_end) { //No overlap
            Node node;
            node.prefix = node.suffix = node.best = -15008; // As min value possible is -15007
            node.total = 0;
            return node;
        }
        if(query_start <= l && r <= query_end) return tree[index];
        int mid = (l + r) / 2;
        Node left = query(l, mid, query_start, query_end, 2* index + 1);
        Node right = query(mid + 1, r, query_start, query_end, 2 * index + 2);
        return getParentNode(left, right);
    }

    void build(vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        build(0,n - 1, 0, arr);
    }

    int  query(int l, int r) {
        l--, r--;
        return query(0, n-1, l, r, 0).best;
    }
};

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int>v(n);
    for(int i =0;i < n; i++) cin >> v[i];
    int q;
    cin >> q;
    SegmentTree segmentTree;
    segmentTree.build(v);
    while(q--) {
        int l, r;
        cin >> l >> r;
        cout << segmentTree.query(l, r) << '\n';
    }
    return 0;
}