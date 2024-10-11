/**
 * Author: ngthanhtrung23
 * Description:	PersistentArray
 */
template<typename T>
struct PersistentArray {
    static const int LOG = 4;
    static const int FULL_MASK = (1<<LOG) - 1;

    struct Node {
        T x;
        array<Node*, 1<<LOG> child;
        Node(const T& _x) : x(_x) {
            fill(child.begin(), child.end(), nullptr);
        }
        Node(const Node& n) : x(n.x) {
            copy(n.child.begin(), n.child.end(), child.begin());
        }
    };

    // get p-th element in `t` version
    static T get(Node* t, int p) {
        if (t == NULL) return 0;
        return p ? get(t->child[p & FULL_MASK], p >> LOG) : t->x;
    }

    // set p-th element in `t` version to x, and return new version
    static Node* set(Node* t, int p, const T& x) {
        t = (t == NULL) ? new Node(0) : new Node(*t);
        if (p == 0) t->x = x;
        else {
            auto ptr = set(t->child[p & FULL_MASK], p >> LOG, x);
            t->child[p & FULL_MASK] = ptr;
        }
        return t;
    }

    // init a persistent array and return root node
    Node* build(const vector<T>& v) {
        Node* root = NULL;
        for (int i = 0; i < (int) v.size(); i++) {
            root = set(root, i, v[i]);
        }
        return root;
    }
};