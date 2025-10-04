#pragma once
const int N = (int) 1e6 + 15;

int power(long long n, long long k, int MOD) {
    int res = 1;
    n %= MOD;
    if (n < 0) n += MOD;

    for (; k > 0; k >>= 1, n = 1LL * n * n % MOD) {
        if (k & 1) res = 1LL * res * n % MOD;
    }
    return res;
}

const int MOD1 = 127657753, MOD2 = 987654319;
const int p1 = 137, p2 = 277;

pair<int, int> pw[N], ipw[N];
int ip1, ip2;

void prec(void) {
    pw[0] = {1, 1};
    for (int i = 1; i < N; ++i) {
        pw[i].first = 1LL * pw[i - 1].first * p1 % MOD1;
        pw[i].second = 1LL * pw[i - 1].second * p2 % MOD2;
    }
    ip1 = power(p1, MOD1 - 2, MOD1);
    ip2 = power(p2, MOD2 - 2, MOD2);

    ipw[0] = {1, 1};
    for (int i = 1; i < N; ++i) {
        ipw[i].first = 1LL * ipw[i - 1].first * ip1 % MOD1;
        ipw[i].second = 1LL * ipw[i - 1].second * ip2 % MOD2;
    }
}

struct Hashing {
    int n;
    string s;
    vector<pair<int, int>> hs;
    Hashing() {}
    Hashing(string _s) {init(_s);}

    void init(string _s) {
        s = _s;
        n = (int) s.length();
        hs.emplace_back(0, 0);
        for (int i = 0; i < n; ++i) {
            pair<int, int> p;
            p.first = (hs[i].first + (1LL * pw[i].first * s[i] % MOD1)) % MOD1;
            p.second = (hs[i].second + (1LL * pw[i].second * s[i] % MOD2)) % MOD2;
            hs.push_back(p);
        }
    }
    pair<int, int> get_hash(int l, int r) {
        assert(1 <= l && l <= r && r <= n);
        pair<int, int> res;
        res.first = (hs[r].first - hs[l - 1].first + MOD1) * 1LL * ipw[l - 1].first % MOD1;
        res.second = (hs[r].second - hs[l - 1].second + MOD2) * 1LL * ipw[l - 1].second % MOD2;
        return res;
    }

    pair<int, int> get_hash(void) {
        return get_hash(1, n);
    }
};
/// need call "prec"