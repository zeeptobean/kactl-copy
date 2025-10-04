#pragma once
template<class T> struct BIT {
    int n; vector<T> v;
    BIT(int _n = 0) {
        n = _n;
        v.assign(n + 6, 0);
    }
    void upd(int p, T val) {
        for (; p <= n; p += (p & -p)) v[p] += val;
    }
    T get(int p) {
        T res = 0;
        for (; p >= 1; p -= (p & -p))
            res += v[p];
        return res;
    }
    T get(int l, int r) {
        if (l > r) return 0;
        return l <= 1 ? get(r) : get(r) - get(l - 1);
    }
};
