/**
 * Author: gspvh
 * Description: Calculate combinatorial
 * prepare $O(n)$, query $O(n/ln(n))$, whatever modulo. 
 */
#define MAX 1000100
bool notPrime[MAX];
vector<int> primes;

//prime sieve
notPrime[0] = notPrime[1] = true;
for (int i = 2; 1LL * i * i < MAX; i++) if (!notPrime[i])
	for (int j = i * i; j < MAX; j += i) notPrime[j] = true;
for (int i = 2; i < MAX; i++) if (!notPrime[i]) primes.push_back(i);

int comb(int k, int n) {
	if (k > n) return 0;    
	int res = 1;
	for (int p : primes) {
		if (p > n) break;
		int exp = 0; //calcuate p exponentation
		for (long long tmp = p; tmp <= n; tmp *= p)
			exp += n / tmp - k / tmp - (n - k) / tmp;
		res = 1LL * res * pw(p, exp) % MOD;
    }
	return res;
}