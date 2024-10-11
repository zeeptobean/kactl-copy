/**
 * Author: ngthanhtrung23
 * Description: Minimum number of operations to transform string a => string b
 * Time: idk
 */
#pragma once

int edit_distance(string a, string b) {
    int la = a.size();
    int lb = b.size();
    a = " " + a + " ";
    b = " " + b + " ";
    vector<vector<int>> f(la + 1, vector<int> (lb + 1, la + lb));

    for (int j = 0; j <= lb; ++j) f[0][j] = j;
    for (int i = 0; i <= la; ++i) f[i][0] = i;

    for (int i = 1; i <= la; ++i) {
        for (int j = 1; j <= lb; ++j) {
            if (a[i] == b[j]) f[i][j] = f[i-1][j-1];
            else f[i][j] = 1 + min({
                    f[i-1][j-1],  // modify
                    f[i][j-1],    // remove b[j]
                    f[i-1][j]});    // remove a[i]      
        }
    }
    return f.back().back();
}
