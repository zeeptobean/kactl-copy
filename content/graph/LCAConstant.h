/**
 * Author: vuhieu
 * Description: O(1) LCA and RMQ
 * Time: O(1) query, O(n \log n) precompute
 */

template <class T>
struct RMQ { // 0-based
  vector<vector<T>> rmq;
  T kInf = numeric_limits<T>::max();
  void build(const vector<T>& V) {
    int n = V.size(), on = 1, dep = 1;
    while (on < n) on *= 2, ++dep;
    rmq.assign(dep, V);
 
    for (int i = 0; i < dep - 1; ++i)
      for (int j = 0; j < n; ++j) {
        rmq[i + 1][j] = min(rmq[i][j], rmq[i][min(n - 1, j + (1 << i))]);
      }
  }
  T query(int a, int b) { // [a, b)
    if (b <= a) return kInf;
    int dep = 31 - __builtin_clz(b - a); // log(b - a)
    return min(rmq[dep][a], rmq[dep][b - (1 << dep)]);
  }
};

struct LCA { // 0-based
  int LG, N;
  vector<int> enter, depth, exxit;
  vector<vector<int>> G, par;
  vector<pair<int, int>> linear;
  RMQ<pair<int, int>> rmq;
  int timer = 0;
  LCA() {} 
  LCA(int n) {
    N = n;
    LG = __lg(N) + 1;
    enter.assign(n + 1, -1);
    exxit.assign(n + 1, -1);
    depth.resize(n + 1);
    G.resize(n + 1);
    par.assign(n + 1, vector<int>(LG + 1, -1));
    linear.resize(2 * n + 1); 
  }
  void init(int n) {
    N = n;
    LG = __lg(N) + 1;
    enter.assign(n + 1, -1);
    exxit.assign(n + 1, -1);
    depth.resize(n + 1);
    G.resize(n + 1);
    par.assign(n + 1, vector<int>(LG + 1, -1));
    linear.resize(2 * n + 1); 
  }
  void dfs(int node, int dep) {
    linear[timer] = {dep, node};
    enter[node] = timer++;
    depth[node] = dep;
    sz[node] = 1;
    for (auto vec : G[node])
    if (enter[vec] == -1) {
      par[vec][0] = node;
      dfs(vec, dep + 1);
      linear[timer++] = {dep, node};
      sz[node] += sz[vec];
    }
    exxit[node] = timer;
  }
  void add_edge(int a, int b) {
    G[a].push_back(b);
    G[b].push_back(a);
  }
  void build(int root) {
    dfs(root, 0);
    rmq.build(linear);
  }
  void build_par(void) {
    for (int j = 1; j < LG; ++j) 
      for (int i = 1; i <= N; ++i) if (par[i][j - 1] != -1) {
        par[i][j] = par[par[i][j - 1]][j - 1];
    }
  }
  int kth(int node, int k) {
    for (int i = k; i > 0; i ^= (i & -i)) {
      int ind = __builtin_ctz(i);
      if (par[node][ind] != -1) node = par[node][ind];
    }
    return node;
  }
  int tin(int u) { return enter[u] + 1; }
  int tout(int u) { return exxit[u] + 1; }
  int query(int a, int b) {
    if (a == 0 || b == 0) return max(a, b);
    a = enter[a], b = enter[b];
    return rmq.query(min(a, b), max(a, b) + 1).second;
  }
  int queryLOG(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    for (int i = LG - 1; i >= 0; --i) if (depth[par[u][i]] >= depth[v]) {
      u = par[u][i];
    }
    if (u == v) return u;
    for (int i = LG - 1; i >= 0; --i) if (par[u][i] != par[v][i]) {
      u = par[u][i];
      v = par[v][i];
    }
    return par[u][0];
  }
  int dist(int a, int b) {
    return depth[a] + depth[b] - 2 * depth[query(a, b)];
  }
};
