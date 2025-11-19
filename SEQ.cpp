/*

Problem credits: https://www.spoj.com/problems/SEQ/

Sequence (ai) of natural numbers is defined as follows:

   ai = bi (for i ≤ k)
   ai = c1ai-1 + c2ai-2 + ... + ckai-k (for i > k)

where bj and cj are given natural numbers for 1 ≤ j ≤ k. Your task is to compute an for given n and output it modulo 109.

Input
On the first row there is the number C of test cases (equal to about 1000).

Each test contains four lines:

k - number of elements of (c) and (b) (1 ≤ k ≤ 10)
b1 ... bk - k natural numbers where 0 ≤ bj ≤ 109 separated by spaces
c1 ... ck - k natural numbers where 0 ≤ cj ≤ 109 separated by spaces
n - natural number (1 ≤ n ≤ 109)

Output
Exactly C lines, one for each test case: an modulo 109.

Example
Input:
3
3
5 8 2
32 54 6
2
3
1 2 3
4 5 6
6
3
24 354 6
56 57 465
98765432

Output:
8
714
257599514

#matrix_multiplication #matrix_exponentiation
*/

/*
Solution: build transformation matrix for  ai = c1ai-1 + c2ai-2 + ... + ckai-k 
*/

#include<bits/stdc++.h>

#define MOD 1000000000
using namespace std;

struct Matrix {
    int n;
    vector<vector<long long>> a;

    Matrix(int _n, bool identity = false) {
        n = _n;
        a.assign(n, vector<long long>(n, 0));
        if(identity) {
            for(int i =0 ; i < n; i++)
                a[i][i] = 1;
        }
    }

    // Matrix multiplication
    Matrix operator*(const Matrix &other) const {
        Matrix res(n);
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                for (int j = 0; j < n; j++) {
                    res.a[i][j] += (a[i][k] * other.a[k][j]) % MOD;
                    if (res.a[i][j] >= MOD) res.a[i][j] -= MOD;
                }
            }
        }
        return res;
    }

    // Fast exponentiation
    Matrix power(long long exp) const {
        Matrix base = *this;
        Matrix result(n, true);
        while (exp > 0) {
            if (exp & 1) result = result * base;
            base = base * base;
            exp >>= 1;
        }
        return result;
    }
};

long long solve() {
    int k;
    cin >> k;
    vector<long long>c(k), b(k);
    for(int i=0; i < k; i++) cin >> b[i];
    for(int i =0;i < k; i++) cin >> c[i];
    int n;
    cin >> n;
    if (n <= k) {
        return b[n-1] % MOD;
    }

    /*Creating coefficent matrix
    [c1 c2 c3 ... ck] [bk  ] = [bk+1]
    [ 1  0  0 ...  0] [bk-1] = [bk  ]
    [ 0  1  0 ...  0] [bk-2] = [bk-1]
            .
            .
            .
    [ 0  0  0 ...1 0] [b1  ] = [b2]
    */
    Matrix coeffientMatrix(k);
    coeffientMatrix.a[0] = c;
    for(int i = 1; i < k; i++) {
        coeffientMatrix.a[i][i-1] = 1;
    }

    // ans is coefficentMatrix ^(n - k) * b
    Matrix powerN = coeffientMatrix.power(n-k);
    vector<long long> powerNTopRow = powerN.a[0];
    long long ans =0;
    for(int i=0;i <k;i ++) {
        ans = (ans + powerNTopRow[i]*b[k - i - 1] % MOD) % MOD;
    }
    return ans;
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        cout << solve() << endl;
    }
}