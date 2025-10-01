#pragma once

//Tinh vi tri cua xau xoay vong co thu tu tu dien nho nhat cua xau s
int minRotation(string s) {
    int n = s.length();
    int x, y, i, j, u, v; // x is the smallest string before string y
    for(x = 0, y = 1; y < n; ++y) {
        i = u = x; j = v = y;
        while (s[i] == s[j]) {
            ++ u; ++ v;
            if (++ i == n) i = 0;
            if (++ j == n) j = 0;
            if (i == x) break; // All strings are equal
        }
        if (s[i] <= s[j]) y = v;
        else { x = y; if(u > y) y = u; }
    }
    return x;
}