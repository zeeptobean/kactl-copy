#pragma once
void prefixSum3d(int A[L][R][C]) {
    int pre[L][R][C];
    pre[0][0][0] = A[0][0][0];

    for (int i = 1; i < L; i++)
        pre[i][0][0] = pre[i - 1][0][0] + A[i][0][0];
    for (int i = 1; i < R; i++)
        pre[0][i][0] = pre[0][i - 1][0] + A[0][i][0];
    for (int i = 1; i < C; i++)
        pre[0][0][i] = pre[0][0][i - 1] + A[0][0][i];

    for (int k = 1; k < L; k++)
        for (int i = 1; i < R; i++)
            pre[k][i][0] = A[k][i][0] + pre[k - 1][i][0] + pre[k][i - 1][0] - pre[k - 1][i - 1][0];
    for (int i = 1; i < R; i++)
        for (int j = 1; j < C; j++)
            pre[0][i][j] = A[0][i][j] + pre[0][i - 1][j] + pre[0][i][j - 1] - pre[0][i - 1][j - 1];
    for (int j = 1; j < C; j++)
        for (int k = 1; k < L; k++)
            pre[k][0][j] = A[k][0][j] + pre[k - 1][0][j] + pre[k][0][j - 1] - pre[k - 1][0][j - 1];
    for (int k = 1; k < L; k++)
        for (int i = 1; i < R; i++)
            for (int j = 1; j < C; j++)
                pre[k][i][j] = A[k][i][j]
                               + pre[k - 1][i][j] + pre[k][i - 1][j] + pre[k][i][j - 1]
                               - pre[k - 1][i - 1][j] - pre[k][i - 1][j - 1] - pre[k - 1][i][j - 1]
                               + pre[k - 1][i - 1][j - 1];
}