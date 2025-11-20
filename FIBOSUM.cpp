/*
Problem credits: https://www.spoj.com/problems/FIBOSUM/

FIBOSUM - Fibonacci Sum
no tags 

The Fibonacci sequence is defined by the following relation:

F(0) = 0
F(1) = 1
F(N) = F(N - 1) + F(N - 2), N ≥ 2
Your task is very simple. Given two non-negative integers N and M, you have to calculate the sum (F(N) + F(N + 1) + ... + F(M)) mod 1000000007.

Input
The first line contains an integer T (the number of test cases). Then, T lines follow. Each test case consists of a single line with two non-negative integers N and M.

Output
For each test case you have to output a single line containing the answer for the task.

Example
Input:
3
0 3
3 5
10 19

Output:
4
10
10857
Constraints
T <= 1000
0 <= N <= M <= 10^9

#fibonacci
*/

/*
Solution: 

fib(0) + fib(1) + .. fib(n) = fib(n+2) - 1;

so fib(m) + fib(m+1) + .. fib(n) = fib(n+2) - fib(m+1)
*/ 

#include <bits/stdc++.h>
using namespace std;

#define M 1000000007

unordered_map<int, long long> F;

long f(long n) {
	if (F.count(n)) return F[n];
	long k=n/2;
	if (n%2==0) { // n=2*k
		return F[n] = (f(k)*f(k) + f(k-1)*f(k-1)) % M;
	} else { // n=2*k+1
		return F[n] = (f(k)*f(k+1) + f(k-1)*f(k)) % M;
	}
}

int main() {
    F[0] = F[1] = 1;
    int t;
	cin >> t;
	while(t--) {
	   int n,m;
	   cin >> m >> n;
	   cout << (f(n + 1) - f(m) + M) % M<< '\n';
	}
}
