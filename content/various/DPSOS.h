/**
 * Author: Hanh Pham Van
 * Description: DP SOS
 */
#define MASK(n) (1LL << (n))
#define BIT(x, i) (((x) >> (i)) & 1)
int a[MASK(20) + 2], sum[MASK(20) + 2];

memset(sum, 0, sizeof sum);
for (int mask = 0; mask < MASK(n); mask++) sum[mask] = a[mask];

for (int i = 0; i < n; i++) for (int mask = 0; mask < MASK(n); mask++) if (BIT(mask, i))
sum[mask] += sum[mask - MASK(i)]; 