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
#define openfiles ifstream cin ("rotation.in"); ofstream cout ("rotation.out");
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
        return getHeight(x->r) - getHeight(x->l);
    }

    static void fixHeight(node *x) {
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
        root = O[0];
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

    node *left(node* X) {
        if (!X) return X;
        node *a = X;
        node *b = X->r;
        node *y = (b ? b->l : nullptr);
        if (b) b->l = a;
        a->r = y;
        if (root == a) root = b;
        return b;
    }

    node *right(node* X) {
        if (!X) return X;
        node *a = X;
        node *b = X->l;
        node *y = (b ? b->r : nullptr);
        if (b) b->r = a;
        a->l = y;
        if (root == a) root = b;
        return b;
    }

    node *balance(node *X) {
        X->fixHeight(X);
        if (X->bfactor(X) == 2) {
            if (X->bfactor(X->r) < 0) {
                X->r = right(X->r);
            }
            return left(X);
        } else if (X->bfactor(X) == -2) {
            if (X->bfactor(X->l) > 0) {
                X->l = left(X->l);
            }
            return right(X);
        }
        return X;
    }

    node *insert(node *X, int x) {
        if (!X) return new node(x);
        if (X->x > x) {
            X->l = insert(X->l, x);
        } else {
            X->r = insert(X->r, x);
        }
        return balance(X);
    }

    node *removeMin(node *X) {
        if (!X) return nullptr;
        if (!X->l) return X->r;
        X->l = removeMin(X->l);
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
            if (!r_) {
                return l_;
            }
            node *a = r_;
            while (a->l) a = a->l;
            a->r = removeMin(r_);
            a->l = l_;
            return balance(a);
        }
        return balance(X);
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

    int n;
    cin >> n;
    vector<tuple<int, int, int>> o(n);
    for (auto& x : o) {
        int a, b, c;
        cin >> a >> b >> c;
        b--, c--;
        x = make_tuple(a, b, c);
    }
    Avl O;
    O.read(n, o);

    O.balance(O.root);

    o.clear();
    O.print(o);
    cout << o.size() << endl;
    for (auto& x : o) {
        int a, b, c;
        tie(a, b, c) = x;
        cout << a << " " << b << " " << c << endl;
    }


    cerr << endl << "Time : " << ld(clock() - zzz) / CLOCKS_PER_SEC;
}