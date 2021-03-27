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
using t3 = tuple<int, int, int, int>;

#define endl "\n"
#define ft first
#define sd second
#define openfiles ifstream cin ("linkedmap.in"); ofstream cout ("linkedmap.out");
#define pb push_back
#define eb emplace_back
#define in insert
#define faster ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int INF = 1000000010;
const ll INFLL = 1000000000010000010;
const ld EPS = 0.0000001;
const ll MOD = 1000000123;
//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define mt make_tuple
#define g0(x) get<0>(x)
#define g1(x) get<1>(x)
#define g2(x) get<2>(x)
#define g3(x) get<3>(x)

struct node {
    string x, y;
    node *prev, *next;

    node (string x_ = "", string y_ = "", node *prev_ = nullptr, node *next_ = nullptr) {
        x = x_;
        y = y_;
        next = next_;
        prev = prev_;
    }

    void del() {
        x = "";
        y = "none";
        prev = nullptr;
        next = nullptr;
    }
};

struct trash {
    node a[200005];
    int last = 0;

    void push(node x) {
        a[last++] = x;
    }

    node *back() {
        return &a[last - 1];
    };
} trash;


struct myMap {
    vector<vector<node *>> map;
    node *last = nullptr;
    int mod = 1000027;

    myMap() {
        map.resize(mod);
    }

    int hash(string& x) {
        long long hash = 0;
        for (int i = 0; i < x.size(); i++) {
            hash *= 123;
            hash += (MOD + x[i] - 'A' + 1);
            hash %= MOD;
        }
        return hash % mod;
    }

    void add(string x, string y) {
        int h = hash(x);
        for (auto p : map[h]) {
            if (p -> x == x) {
                p -> y = y;
                return;
            }
        }
        trash.push(node(x, y));
        map[h].push_back(trash.back());
        push(map[h].back());
    }

    void push(node *x) {
        if (last == nullptr) {
            last = x;
            return;
        }
        x -> prev = last;
        last -> next = x;
        last = x;
    }

    void del(string x) {
        int h = hash(x);
        for (int i = 0; i < map[h].size(); i++) {
            if (map[h][i] -> x == x) {
                pop(map[h][i]);
                swap(map[h][i], map[h].back());
                map[h].pop_back();
                return;
            }
        }
    }

    void pop(node *x) {
        if (!x -> next) {
            last = x -> prev;
            if (last) last -> next = nullptr;
        } else {
            x -> next -> prev = x -> prev;
            if (x -> prev) x -> prev -> next = x -> next;
        }
        x -> del();
    }

    string get(string x) {
        int h = hash(x);
        for (auto p : map[h]) {
            if (p -> x == x) {
                return p -> y;
            }
        }
        return "none";
    }

    string prev(string x) {
        int h = hash(x);
        for (auto p : map[h]) {
            if (p -> x == x) {
                if (p -> prev) {
                    return p -> prev -> y;
                } else {
                    return "none";
                }
            }
        }
        return "none";
    }

    string next(string x) {
        int h = hash(x);
        for (auto p : map[h]) {
            if (p -> x == x) {
                if (p -> next) {
                    return p -> next -> y;
                } else {
                    return "none";
                }
            }
        }
        return "none";
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

    myMap o;

    string s;
    while (cin >> s) {
        string x;
        cin >> x;
        if (s == "put") {
            string y;
            cin >> y;
            o.add(x, y);
        } else if (s == "delete") {
            o.del(x);
        } else if (s == "get") {
            cout << o.get(x) << endl;
        } else if (s == "prev") {
            cout << o.prev(x) << endl;
        } else if (s == "next") {
            cout << o.next(x) << endl;
        }
    }


    cerr << endl << "Time : " << ld(clock() - zzz) / CLOCKS_PER_SEC;
}
