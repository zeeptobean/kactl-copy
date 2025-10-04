#pragma once
struct Node {
    Node() {}
};
Node compare(const Node& a, const Node& b) {
    Node res;
    ...
    return res;
}
struct SegTree {
    int n; vector<Node> st;
    SegTree(const int& _n = 0) {init(_n);}
    void init(const int& _n = 0) {
        n = _n;
        st.assign(4 * n + 15, Node());
    }
    void push(int id, int l, int r) {
        int mid = (l + r) >> 1;
        int x = id << 1, y = x | 1;
    }
    void upd(int id, int l, int r, int i, int val) {
        if (i < l || i > r) return;
        if (l == r) return;
        push(id, l, r);
        int mid = (l + r) >> 1;
        int x = id << 1, y = x | 1;
        upd(x, l, mid, i, val);
        upd(y, mid + 1, r, i, val);
        st[id] = compare(st[x], st[y]);
    }
    Node get(int id, int l, int r, int u, int v) {
        if (r < u || l > v) return Node();
        if (u <= l && r <= v) return st[id];
        push(id, l, r);
        int mid = (l + r) >> 1;
        int x = id << 1, y = x | 1;
        Node L = get(x, l, mid, u, v);
        Node R = get(y, mid + 1, r, u, v);
        return compare(L, R);
    }
    void upd(int i, int val) {
        upd(1, 1, n, i, val);
    }
    Node get(int l, int r) {
        return get(1, 1, n, l, r);
    }
};