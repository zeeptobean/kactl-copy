/**
 * Author: vuhieu
 * Description: ps-profits, ws-weights, ms-maximum limit of each element
 * W-maximum weight
 * Time: O(n*W) 
 */ 
int boundedKnapsack(vector<int> ps, vector<int> ws, vector<int> ms, int W) {
  int n = ps.size();
  vector<vector<int>> dp(n + 1, vector<int>(W + 1));
  for (int i = 0; i < n; ++i) {
    for (int s = 0; s < ws[i]; ++s) {
      int alpha = 0;
      queue<int> que;
      deque<int> peek;
      for (int w = s; w <= W; w += ws[i]) {
        alpha += ps[i];
        int a = dp[i][w] - alpha;
        que.push(a);
        while (!peek.empty() && peek.back() < a) peek.pop_back();
        peek.push_back(a);
        while (que.size() > ms[i] + 1) {
          if (que.front() == peek.front()) peek.pop_front();
          que.pop();
        }
        dp[i + 1][w] = peek.front() + alpha;
      }
    }
  }
  int ans = 0;
  for (int w = 0; w <= W; ++w)
    ans = max(ans, dp[n][w]);
  return ans;
}