/**
 * Author: ngthanhtrung23
 * License: idk
 * Source: idk
 * Description: Select subset of items, such that sum(weights) <= capacity 
 * and sum(values) is maximum. An item can be selected unlimited number of times
 * Time: idk
 * Status: idk
 */
#pragma once

int knapsack_unbounded(int capacity, vector<int> weights, vector<int> values) {
    int n = weights.size();
    vector<int> f(capacity + 1, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = weights[i]; j <= capacity; ++j) {
            f[j] = max(f[j], f[j-weights[i]] + values[i]);
        }
    }

    return *max_element(f.begin(), f.end());
}
