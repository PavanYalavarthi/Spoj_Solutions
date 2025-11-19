/*
Sequence (ai) of natural numbers is defined as follows:

ai = bi (for i <= k)
ai = c1ai-1 + c2ai-2 + ... + ckai-k (for i > k)

where bj and cj are given natural numbers for 1<=j<=k. Your task is to compute am + am+1 + am+2 + ... + an for given m <= n and output it modulo a given positive integer p.

Input
On the first row there is the number C of test cases (equal to about 50).
Each test contains four lines:
k - number of elements of (c) and (b) (1 <= k <= 15)
b1, ... bk - k natural numbers where 0 <= bj <= 109 separated by spaces.
c1, ... ck - k natural numbers where 0 <= cj <= 109 separated by spaces.
m, n, p - natural numbers separated by spaces (1 <= m <= n <= 1018, 1<= p <= 108).

Output
Exactly C lines, one for each test case: (am + am+1 + am+2 + ... + an) modulo p.

Example
Input:
1
2
1 1
1 1
2 10 1000003

Output:
142

#matrix_multiplication #matrix_exponentiation
*/


/*
Solution: build transformation matrix for  s(a(n+1)) = s(a(n)) +  c1ai-1 + c2ai-2 + ... + ckai-k 
and ans = s(a(n)) - s(a(m-1))
*/

#include<bits/stdc++.h>
using namespace std;

int MOD; 

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

long long getSum(Matrix coefficentMatrix, vector<long long>& b, long long n) {
    int k = b.size();
    if(n <= k) {
        long long sum = 0;
        for(int i = 0; i < n; i++) {
            sum = (sum + b[i]) % MOD;
        }
        return sum;
    }
    long long sum =0;
    for(int i =0; i < k; i++) {
        sum = (sum + b[i]) % MOD;
    }

     // ans is coefficentMatrix ^(n - k) * b
    Matrix powerN = coefficentMatrix.power(n-k);
    vector<long long> powerNTopRow = powerN.a[0];
    long long ans = sum * powerNTopRow[0] % MOD;
    for(int i=1; i <= k;i ++) {
        ans = (ans + powerNTopRow[i]*b[k - i] % MOD) % MOD;
    }
    return ans;
}

long long solve() {
    int k;
    cin >> k;
    vector<long long>c(k), b(k);
    for(int i=0; i < k; i++) cin >> b[i];
    for(int i =0;i < k; i++) cin >> c[i];

    
    /*Creating coefficent matrix
    [ 1 c1 c2 c3 ... ck] [sk  ] = [sk+1]
    [ 0 c1 c2 c3 ... ck] [bk  ] = [bk+1]
    [ 0  1  0  0 ...  0] [bk-1] = [bk  ]
            .
            .
            .
    [ 0  0  0  0 ... 0] [b1  ] = [b2   ]
    */
    Matrix coeffientMatrix(k + 1);
    coeffientMatrix.a[0][0] = 1;
    for(int j = 1; j <= k; j++) {
        coeffientMatrix.a[0][j] = coeffientMatrix.a[1][j] = c[j - 1];
    }
    for(int i = 2; i <= k; i++) {
        coeffientMatrix.a[i][i-1] = 1;
    }

    long long m, n;
    cin >> m >> n >> MOD;
    return (getSum(coeffientMatrix, b, n) - getSum(coeffientMatrix, b, m-1) + MOD) % MOD;
}


int main() {
    int t;
    cin >> t;
    while(t--) {
        cout << solve() << endl;
    }
}