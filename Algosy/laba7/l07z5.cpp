#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <chrono>

using namespace std;
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

using ll = long long;
using ull =  unsigned long long;
using ld = long double;
using pii = pair <int, int>;
using pll = pair <ll, ll>;
using t3 = tuple<int, int, int>;

#define endl "\n"
#define ft first
#define sd second
#define openfiles ifstream cin ("avlset.in"); ofstream cout ("avlset.out");
#define pb push_back
#define eb emplace_back
#define in insert
#define faster ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int INF = 1000000010;
const ll INFLL = 1000000000010000010;
const ld EPS = 0.0000001;
const ll MOD = 1000000321;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define mt make_tuple
#define g0(x) get<0>(x)
#define g1(x) get<1>(x)
#define g2(x) get<2>(x)
#define g3(x) get<3>(x)

struct node {
    node *l, *r;
    int x;
    int height;

    node(int x_) {
        x = x_;
        l = r = nullptr;
        height = 1;
    }

    static int getHeight(node *x) {
        return (x ? x->height : 0);
    }

    node(int x_, node *l_, node *r_) {
        x = x_;
        l = l_;
        r = r_;
        height = max(getHeight(l), getHeight(r)) + 1;
    }

    static int bfactor(node *x) {
        if (!x) return 0;
        return getHeight(x->r) - getHeight(x->l);
    }

    static void fixHeight(node *x) {
        if (!x) return;
        x->height = max(getHeight(x->l), getHeight(x->r)) + 1;
    }
};

struct Avl {
    node *root = nullptr;

    void read(int n, vector<tuple<int, int, int>>& o) {
        vector<node *> O(n);
        for (int i = n - 1; i >= 0; i--) {
            int a, b, c;
            tie(a, b, c) = o[i];
            O[i] = new node(a, (b != -1 ? O[b] : nullptr), (c != -1 ? O[c] : nullptr));
        }
        root = (n ? O[0] : nullptr);
    }

    void print(vector<tuple<int, int, int>>& O) {
        function<int(node *)> dfs = [&](node *x) {
            if (!x) return 0;
            int sz = O.size();
            O.emplace_back(x->x, 0, 0);
            get<1>(O[sz]) = dfs(x->l);
            get<2>(O[sz]) = dfs(x->r);
            return sz + 1;
        };
        dfs(root);
    }

    node *left(node *x) {
        node *b = x->r;
        x->r = b->l;
        b->l = x;
        x->fixHeight(x);
        x->fixHeight(b);
        return b;
    }

    node *right(node *x) {
        node *b = x->l;
        x->l = b->r;
        b->r = x;
        x->fixHeight(x);
        x->fixHeight(b);
        return b;
    }

    node *balance(node *x) {
        x->fixHeight(x);
        if (x->bfactor(x) == 2) {
            if (x->r->bfactor(x->r) < 0) {
                x->r = right(x->r);
            }
            return left(x);
        } else if (x->bfactor(x) == -2) {
            if (x->l->bfactor(x->l) > 0) {
                x->l = left(x->l);
            }
            return right(x);
        }
        return x;
    }

    node *insert(node *x, int k) {
        if (!x) return new node(k);
        if (x->x > k) {
            x->l = insert(x->l, k);
        } else if (x->x < k) {
            x->r = insert(x->r, k);
        }
        return balance(x);
    }

    node *removeMin(node *X) {
        if (!X) return nullptr;
        if (!X->r) return X->l;
        X->r = removeMin(X->r);
        return balance(X);
    }

    node *remove(node *X, int x) {
        if (!X) return nullptr;
        if (X->x > x) {
            X->l = remove(X->l, x);
        } else if (X->x < x) {
            X->r = remove(X->r, x);
        } else {
            node *l_ = X->l, *r_ = X->r;
            delete X;
            if (!l_) {
                return r_;
            }
            node *a = l_;
            while (a->r) a = a->r;
            a->l = removeMin(l_);
            a->r = r_;
            return balance(a);
        }
        return balance(X);
    }

    bool check(node *x, int k) {
        if (!x) return false;
        if (x->x > k) {
            return check(x->l, k);
        } else if (x->x < k) {
            return check(x->r, k);
        }
        return true;
    }
};


#define KlishkevichVadimka
signed main()
{
#ifdef KlishkevichVadimka
    openfiles
#endif
    faster;
    clock_t zzz = clock();

    Avl O;

    int q;
    cin >> q;
    while (q--) {
        char a;
        int x;
        cin >> a >> x;
        if (a == 'A') {
            O.root = O.insert(O.root, x);
            cout << O.root->bfactor(O.root) << endl;
        } else if (a == 'D') {
            O.root = O.remove(O.root, x);
            cout << O.root->bfactor(O.root) << endl;
        } else if (a == 'C') {
            if (O.check(O.root, x)) {
                cout << "Y\n";
            } else {
                cout << "N\n";
            }
        }
    }


    cerr << endl << "Time : " << ld(clock() - zzz) / CLOCKS_PER_SEC;
}