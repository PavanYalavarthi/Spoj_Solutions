/*
Problem credits: https://www.spoj.com/problems/HOLI/

Nowadays, people have many ways to save money on accommodation when they are on vacation. One of these ways is exchanging houses with other people.

Here is a group of N people who want to travel around the world. They live in different cities, so they can travel to some other people's city and use someone's house temporary. Now they want to make a plan that choose a destination for each person. There are two rules should be satisfied:

All the people should go to one of the other people's city.
Two of them never go to the same city, because they are not willing to share a house.
They want to maximize the sum of all people's travel distance. The travel distance of a person is the distance between the city he lives in and the city he travels to. These N cities have N-1 highways connecting them. The travelers always choose the shortest path when traveling.

Given the highways' information, it is your job to find the best plan, that maximum the total travel distance of all people.

Input
The first line of input contains one integer T (1 <= T <= 10), indicating the number of test cases.

Each test case contains several lines. The first line contains an integer N (2 <= N <= 105), representing the number of cities. Then the following N-1 lines each contains three integers X, Y, Z (1 <= X, Y <= N, 1 <= Z <= 106), means that there is a highway between city X and city Y, and length of that highway.

You can assume all the cities are connected and the highways are bi-directional.

Output
For each test case in the input, print one line: "Case #X: Y", where X is the test case number (starting with 1) and Y represents the largest total travel distance of all people.

Example
Input:
2
4
1 2 3
2 3 2
4 3 2
6
1 2 3
2 3 4
2 4 1
4 5 8
5 6 5

Output:
Case #1: 18
Case #2: 62

#DFS
*/

/*
Solution: 
To get maximum total distance travelled 
for given edge, 2 * cost * minimum no.of vertices is added for every edge
i.e, people of one end shifts to other end.
*/
#include<bits/stdc++.h>
using namespace std;
long long cnt;
int n;
int dfs(int i, vector<vector<pair<int, int>>> & gr, vector<bool>& visited) {
    visited[i] = true;
    int nodes = 1;
    for(auto& [vertex, weight] : gr[i]) {
        if (!visited[vertex]) {
            int nodeCount = dfs(vertex, gr, visited);
            nodes += nodeCount;
            cnt += 2 * weight * min(nodeCount, n - nodeCount);
        }
    }
    return nodes;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    for(int i = 1; i <= t; i++) {
        cin >> n;
        vector<vector<pair<int, int>>> gr(n+1);
        for(int j = 1; j < n; j++) {
            int u, v, cost;
            cin >> u >> v >> cost;
            gr[u].push_back({v, cost});
            gr[v].push_back({u, cost});
        }
        vector<bool>visited(n+1, false);
        cnt = 0;
        dfs(1, gr, visited);
        cout << "Case #" << i << ": " << cnt <<'\n';
    }
    return 0;
}