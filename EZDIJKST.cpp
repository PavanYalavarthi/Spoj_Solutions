/*
Problem credits : https://www.spoj.com/problems/EZDIJKST/ 

Determine the shortest path between the specified vertices in the graph given in the input data.

Hint: You can use Dijkstra's algorithm.
Hint 2: if you're a lazy C++ programmer, you can use set and cin/cout (with sync_with_stdio(0)) - it should suffice.

Input
first line - one integer - number of test cases
For each test case the numbers V, K (number of vertices, number of edges) are given.
Then K lines follow, each containing the following numbers separated by a single space:
ai, bi, ci
It means that the graph being described contains an edge from ai to bi, with a weight of ci.
Below the graph description a line containing a pair of integers A, B is present.
The goal is to find the shortest path from vertex A to vertex B.
All numbers in the input data are integers in the range 0..10000.

Output
For each test case your program should output (in a separate line) a single number C - the length of the shortest path from vertex A to vertex B. In case there is no such path, your program should output a single word "NO" (without quotes)

Example
Input:
3
3 2
1 2 5
2 3 7
1 3
3 3
1 2 4
1 3 7
2 3 1
1 3
3 1
1 2 4
1 3

Output:
12
5
NO

#Dijstra
*/

/*
Solution: Dijstra Algo. 
Imp :(Graph is directed)
*/
#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--) {
        int n, e;
        cin >> n >> e;
        vector<int>dist(n+1, INT_MAX);
        vector<pair<int, int>>gr[n + 1];
        for(int i = 0; i< e; i++) {
            int x, y, w;
            cin >> x >> y >> w;
            gr[x].push_back({w, y});
        }
        set<pair<int,int>> s;
        int src, target;
        cin >> src >> target;
        dist[src] = 0;
        s.insert({0, src});
        while (!s.empty()) {
            auto [weight, vertex] = *s.begin();
            if (vertex == target) break;
            s.erase(s.begin());
            for(auto &[w, y] : gr[vertex]) {
                if (weight + w < dist[y]) {
                    s.erase({dist[y], y});
                    dist[y] = weight + w;
                    s.insert({dist[y], y});
                }
            }
        }
        if (dist[target] == INT_MAX)
            cout << "NO\n";
        else
            cout << dist[target] << '\n';
    }
    return 0;
}
