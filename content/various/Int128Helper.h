/**
 * Author: ngthanhtrung23
 * Description: i128 helper function
 */
using i128 = __int128_t;
i128 str2i128(string str) {
    i128 ret = 0;
    bool minus = false;
    for (auto c : str) {
        if (c == '-') minus = true;
        else ret = ret * 10 + c - '0';
    }
    return minus ? -ret : ret;
}
istream &operator>>(istream &is, i128 &x) {
    string s;
    return is >> s, x = str2i128(s), is;
}
ostream &operator<<(ostream &os, const i128 &x) {
    i128 tmp = x;
    if (tmp == 0) return os << 0;
    vector<int> ds;
    if (tmp < 0) {
        os << '-';
        while (tmp) {
            int d = tmp % 10;
            if (d > 0) d -= 10;
            ds.emplace_back(-d), tmp = (tmp - d) / 10;
        }
    } else {
        while (tmp) ds.emplace_back(tmp % 10), tmp /= 10;
    }
    reverse(ds.begin(), ds.end());
    for (auto i : ds) os << i;
    return os;
}
i128 my_abs(i128 n) {
    if (n < 0) return -n;
    return n;
}
i128 gcd(i128 a, i128 b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}
int ctz128(i128 n) {    // Count trailing zeroes
    if (!n) return 128;
    if (!static_cast<uint64_t>(n)) {
        return __builtin_ctzll(static_cast<uint64_t>(n >> 64)) + 64;
    } else {
        return __builtin_ctzll(static_cast<uint64_t>(n));
    }
}