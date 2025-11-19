/*

Problem credits: https://www.spoj.com/problems/COT/

You are given a tree with N nodes. The tree nodes are numbered from 1 to N. Each node has an integer weight.

We will ask you to perform the following operation:

u v k : ask for the kth minimum weight on the path from node u to node v
Input
In the first line there are two integers N and M. (N, M ≤ 100000)

In the second line there are N integers. The ith integer denotes the weight of the ith node.

In the next N-1 lines, each line contains two integers u v, which describes an edge (u, v).

In the next M lines, each line contains three integers u v k, which means an operation asking for the kth minimum weight on the path from node u to node v.

Output
For each operation, print its result.

Input:
8 5
105 2 9 3 8 5 7 7
1 2
1 3
1 4
3 5
3 6
3 7
4 8
2 5 1
2 5 2
2 5 3
2 5 4
7 8 2 

Output:
2
8
9
105
7 

#persistent_segment_trees
*/
#include<bits/stdc++.h>
using namespace std;
#define MAX_N 1000001
#define LOG_MAX_N 17
int parent[MAX_N][LOG_MAX_N], depth[MAX_N];
vector<int>gr[MAX_N];

// Getting LCA using binary lifting
int LCA(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    int diff_depth = depth[u] - depth[v];
    for(int i = 0; i < LOG_MAX_N; i++) {
        if(diff_depth & (1 << i)) {
            u = parent[u][i];
        }
    }
    if(u == v) return u;

    for(int i = LOG_MAX_N - 1; i >= 0; i--) {
        if(parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    return parent[u][0];
}

struct Node {
    int count;
    Node *left, *right;
    Node(int count, Node *left, Node *right) {
        this->count = count;
        this->left = left;
        this->right = right;
    }
};

struct PersistentSegmentTree {
    vector<Node*>rootNodes;
    vector<int>coordinate_compression;
    Node* nullNode;
    Node* build(int left, int right, int weight, Node* indexNode) {
        if(left == right) {
            // When reached the node, increment the count and return new node.
            return new Node(indexNode->count + 1, nullptr, nullptr);
        }

        int mid = (left + right) >> 1;

        if(weight <= mid) { //If weight is less than mid, forwarding to left tree
            Node* newLeft = build(left, mid, weight, indexNode->left);
            return new Node(indexNode->count + 1, newLeft, indexNode->right);
        } else {
            Node* newRight = build(mid + 1, right, weight, indexNode->right);
            return new Node(indexNode->count + 1, indexNode->left, newRight);
        }
    }

    int query(Node* u, Node* v, Node* lca, Node* par_lca, int left, int right, int k) {
        // If there is a single node, then thats the answer
        if (left == right) {
            return left;
        }

        //Seeing the count in left subtree
        int count = u->left->count + v->left->count - lca->left->count - par_lca->left->count;

        int mid = (left + right) >> 1;
        if (count >= k) //If count is >= k, the element resides in left subtree
            return query(u->left, v->left, lca->left, par_lca->left, left, mid, k);
        return query(u->right, v->right, lca->right, par_lca->right, mid + 1, right, k - count);
    }

    void dfsBuild(int cur, int par, const vector<int>& weights) {
        parent[cur][0] = par;
        depth[cur] = depth[par] + 1;
        // Get coordinate compressed weight value
        int idx = lower_bound(coordinate_compression.begin(), coordinate_compression.end(), weights[cur - 1]) - coordinate_compression.begin();
        rootNodes[cur] = build(0, coordinate_compression.size() - 1, idx, rootNodes[par]);
        for (int child : gr[cur]) {
            if (child != par)
                dfsBuild(child, cur, weights);
        }
    }

    void build(vector<int>& weights) {
        int n = weights.size();
        rootNodes.resize(weights.size() + 1);

         // Coordinate compression
        coordinate_compression = weights;
        sort(coordinate_compression.begin(), coordinate_compression.end());
        coordinate_compression.erase(unique(coordinate_compression.begin(), coordinate_compression.end()), coordinate_compression.end());

        Node* nullNode = new Node(0, nullptr, nullptr);
        nullNode->left = nullNode->right = nullNode;
        rootNodes[0] = nullNode;

        depth[0] = 0;
        dfsBuild(1, 0, weights);
    }

    int query(int u, int v, int k) {
        int lca = LCA(u, v);
        int compressed_weight = query(rootNodes[u], rootNodes[v], rootNodes[lca], rootNodes[parent[lca][0]], 0, coordinate_compression.size() - 1, k);
        return coordinate_compression[compressed_weight];
    }
};

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n>> m;
    vector<int>weights(n);
    for(int i = 0; i< n; i++) {
        cin >> weights[i];
    }

    // Forming adjacent list for the graph
    for(int i =0, u, v; i< n-1;i++) {
        cin >> u >> v;
        gr[u].push_back(v);
        gr[v].push_back(u);
    }



    PersistentSegmentTree segTree;
    segTree.build(weights);

     // Building parent array using binary lifting
    for(int i = 1;i < LOG_MAX_N; i++) {
        for(int j = 2; j <= n ;j++) {
            parent[j][i] = parent[parent[j][i-1]][i-1];
        }
    }

    while(m--) {
        int u, v, k;
        cin >> u >> v >> k;
        cout << segTree.query(u, v, k) << '\n';
    }
    return 0;
}