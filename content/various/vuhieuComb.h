/**
 * Author: gspvh
 * Description: Calculate combinatorial
 * prepare $O(n)$, query $O(n/ln(n))$, whatever modulo. 
 * Để có thể tính được với một modulo bất kì, ta không được sử dụng các biểu thức có phép chia.
 * Vì vậy, ta sẽ phân tích số C(k, n) ra thừa số nguyên tố để được một biểu thức chỉ toàn phép nhân.
 * Áp dụng công thức: $C(k, n) = n! / k! / (n-k)!$
 * Ta thấy C(k, n) là một phép nhân/chia của các giai thừa. Do đó, ta cần phân tích n! ra TSNT, 
 * và phần tích k!, (n-k)! theo cách hoàn toàn tương tự, từ đó ta suy ra được phân tích của C(k, n)
 * Vấn đề bây giờ là làm thế nào để phân tích n! ra thừa số nguyên tố. Như đã biết, với mọi số nguyên tố p, 
 * n! chia hết cho p khi và chỉ khi n >= p. Như thế, n! có các ước nguyên tố là mọi số nguyên tố từ 1 đến n.
 * Do đó, với mỗi số nguyên tố p <= n, ta cần tìm số mũ của nó, tức tìm số k lớn nhất để n! chia hết cho $p^k$
 * Kết quả: số mũ của p trong phân tích ra TSNT của n! là $n / p + n / (p^2) + n / (p^3)$ + ...
 * Phép chia là phép chia làm tròn xuống, vì vậy, sẽ đến một lúc mẫu số > n, khi đó, phân số có giá trị = 0. 
 * Do đó, tổng trên không vô hạn.
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