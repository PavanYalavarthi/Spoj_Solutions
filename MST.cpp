/*
Problem credits: https://www.spoj.com/problems/MST/

Find the minimum spanning tree of the graph.

Input
On the first line there will be two integers N - the number of nodes and M - the number of edges. (1 <= N <= 10000), (1 <= M <= 100000)
M lines follow with three integers i j k on each line representing an edge between node i and j with weight k. The IDs of the nodes are between 1 and n inclusive. The weight of each edge will be <= 1000000.

Output
Single number representing the total weight of the minimum spanning tree on this graph. There will be only one possible MST.

Example
Input:
4 5
1 2 10
2 3 15
1 3 5
4 2 2
4 3 40

Output:
17

#mst
*/

/*
Solution: MST code
*/
#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<bool>visted(n + 1, false);
    vector<pair<int, int>> gr[n +1];
    for(int i = 0; i< m; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        gr[x].push_back({w, y});
        gr[y].push_back({w, x});
    }
    priority_queue<pair<int, int>> pq;
    int ans = 0;
    pq.push({0, 1});
    while(!pq.empty()) {
        auto& [weight, vertex] = pq.top();
        pq.pop();
        if(visited[vertex]) continue;
        visited[vertex] = true;
        for(auto &[w, y] : gr[vertex]) {
            if(!visited[y])
                pq.push({-w, y});
        }
        ans -= weight;
    }
    cout << ans;
    return 0;
}
