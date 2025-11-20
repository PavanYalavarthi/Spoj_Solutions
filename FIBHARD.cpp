/*
Problem description: https://www.spoj.com/problems/FIBHARD/


The problem author is not a very nice person. He wants you to calculate the Nth Fibonacci number, which is defined as:

Fibonacci formula

Because the author is not very nice, the size of N can be huge, really huge. The exact size of N is in the Constraints section.

Input
The first line contains a single integer T, the number of test cases.

The next T lines contain a single integer N.

Output
For each of the T lines, output the Nth Fibonacci number, modulo 998244353.

Example
Input:
5
0
1
1234
345639696828452375
419384601238473729475639183948326177846782649592628790267300203877

Output:
0
1
4936310
213237811
389871463
Constraints
0 <= N <= 10^15000000
1 <= T <= 100

#pisano
*/

/*
Solution:
For pisano period, if p is prime and p is congruent to +-3 mod 10, then it divides 2(p+1)

and mod i.e, 998244353 is 3 MOD 10,  pisano period repeats so, ans = fib(n % 2(998244353 + 1))
*/

#include <bits/stdc++.h>
using namespace std;

#define M 998244353

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

long mod(string s, int m) {
    long res = 0;
    for(int i= 0; i < s.size(); i++) {
        res = (res * 10 % m + (s[i] - '0')) % m;
    }
    return res;
}

int main() {
    F[0] = F[1] = 1;
    int pisanoPeriod = 2 *(M + 1); 
	int t;
	cin >> t;
	while(t--) {
	   string s;
	   cin >> s;
	   long modM = mod(s, pisanoPeriod);
	   cout << (modM == 0 ? 0 : f(modM - 1)) << '\n';
	}
}
