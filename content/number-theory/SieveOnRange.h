/**
 * Author: vuhieu
 * Description: sieve on range
 * Time: ask vuhieu
 */
#pragma once

const int MAX_RANGE = (int) 1e6 + 15;
bool isPrime[MAX_RANGE];
pair<int, vector<long long>> sieve_on_range(long long L, long long R) {
    memset(isPrime, true, sizeof isPrime);
    for (long long i = 2; i * i <= R; ++i) {
        for (long long j = max(i * i, (L + i - 1) / i * i); j <= R; j += i) {
            assert(0 <= j - L && j - L < MAX_RANGE);
            isPrime[j - L] = false;
        }
    }
    if (L <= 1) isPrime[1 - L] = false;
    vector<long long> prime;
    for (long long i = L; i <= R; ++i) if (isPrime[i - L]) prime.push_back(i);
    return make_pair((int) prime.size(), prime);
}
