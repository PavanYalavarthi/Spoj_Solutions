/*
Problem Credits :  https://www.spoj.com/problems/CLFLARR/

You have been given an array of n unpainted elements. By unpainted, we mean that each element initially has a value of 0. You have to process q queries of the form l r c, in which you paint all the elements of the array from index l to index r with color c. Assume that, each new color currently being applied to an element overrides its previous color. Output the color of each element after all the queries have been processed.

Note: The problem is guaranteed to be solved using C or C++ programming language.

Input
The first line of input consists of two integers n and q. Next q lines consists of 3 integers l, r and c denoting the starting index, ending index and the color respectively.

1 <= n <= 200000
1 <= q <= 200000
1 <= l <= r <= n
1 <= c <= 1 000 000 000
Output
Output the final color of each element starting from index 1 on a new line.

Example
Input:
4 3
1 3 2
2 4 6
2 3 7

Output:
2
7
7
6
Input:
10 5
3 9 13
1 4 9
2 10 14
2 7 10
6 9 44

Output:
9
10
10
10
10
44
44
44
44
14

#DSU
*/

/*
Solution:

We apply color queries in reverse fashion and use DSU to get next unpainted element

*/
#include<bits/stdc++.h>
using namespace std;
class DSU {
    vector<int>par;
    public:
        DSU(int n) {
            par.resize(n);
            iota(par.begin(), par.end(), 0);
        }

        int find(int x) {
            return (x == par[x] ? x : par[x] = find(par[x]));
        }


        int unite(int i, int j) {
            i = find(i), j= find(j);
            if (i != j) {
                // Par is the maximum of 2 as we needed next unpainted element
                return par[i] = par[j] = max(i, j); 
            }
            return i;
        }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    vector<vector<int>>queries(q, vector<int>(3));
    for(int i =0; i< q; i++) {
        cin >> queries[i][0] >>  queries[i][1] >>  queries[i][2];
    }
    DSU dsu(n + 2);
    vector<int>res(n + 1, 0);
    for(int i = q - 1; i >= 0; i--) {  //Processing queries in reverse fashion
        int index = dsu.find(queries[i][0]), r = queries[i][1], col = queries[i][2];
        while(index <= r) {
            res[index] = col; // Assigning color
            // If index element is colored, uniting index and index + 1, to get next uncolored element
            index = dsu.unite(index, index + 1); 
        }
    }
    for(int i =1; i<= n; i++) 
        cout << res[i] << endl;
    return 0;
}