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
#define openfiles ifstream cin ("multimap.in"); ofstream cout ("multimap.out");
#define pb push_back
#define eb emplace_back
#define in insert
#define faster ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int INF = 1000000010;
const ll INFLL = 1000000000010000010;
const ld EPS = 0.0000001;
const ll MOD = 1000000123;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define mt make_tuple
#define g0(x) get<0>(x)
#define g1(x) get<1>(x)
#define g2(x) get<2>(x)
#define g3(x) get<3>(x)

struct node {
    pair<int, int> x;
    string s;
    node *l = nullptr, *r = nullptr;

    node(pair<int, int> x_, string s_) {
        x = x_;
        s = s_;
    }
};

struct BST {
    node *head = nullptr;

    BST(pair<int, int> x, string s) {
        head = new node(x, s);
    }

    void add(pair<int, int> x, string s) {
        if (!head) {
            head = new node(x, s);
            return;
        }
        node *cur = head;
        while (true) {
            if (x < cur -> x) {
                if (cur -> l) {
                    cur = cur -> l;
                } else {
                    cur -> l = new node(x, s);
                    return;
                }
            } else if (x > cur -> x) {
                if (cur -> r) {
                    cur = cur -> r;
                } else {
                    cur -> r = new node(x, s);
                    return;
                }
            } else {
                return;
            }
        }
    }

    void pop(pair<int, int> x) {
        if (!head) {
            return;
        }

        node *prev = nullptr;
        node *cur = head;
        node *l = nullptr, *r = nullptr;
        bool right = false;
        while (true) {
            if (x < cur -> x) {
                if (cur -> l) {
                    prev = cur;
                    right = false;
                    cur = cur -> l;
                } else {
                    return;
                }
            } else if (x > cur -> x) {
                if (cur -> r) {
                    prev = cur;
                    right = true;
                    cur = cur -> r;
                } else {
                    return;
                }
            } else {
                l = cur -> l;
                r = cur -> r;
                delete cur;
                break;
            }
        }
        if (!prev) {
            head = l;
        } else if (right) {
            prev -> r = l;
        } else {
            prev -> l = l;
        }
        cur = l;
        if (!cur && !prev) {
            head = r;
        } else if (!cur && right) {
            prev -> r = r;
        } else if (!cur && !right) {
            prev -> l = r;
        }
        if (!cur) return;

        while (cur -> r) {
            cur = cur -> r;
        }
        cur -> r = r;
    }

    vector<string> Ans;

    static void recDel(node *x) {
        if (!x) return;
        recDel(x -> l);
        recDel(x -> r);
        delete x;
    }

    void del() {
        Ans.clear();
        recDel(head);
        head = nullptr;
    }

    void recGet(node *x) {
        if (!x) return;
        Ans.push_back(x -> s);
        recGet(x -> l);
        recGet(x -> r);
    }

    vector<string> &get() {
        Ans.clear();
        recGet(head);
        return Ans;
    }
};

struct myMap {
    vector<vector<pair<string, BST>>> map;
    int mod = 1000027;

    myMap() {
        map.resize(mod);
    }

    int hash(string x) {
        long long hash = 0;
        for (int i = 0; i < x.size(); i++) {
            hash *= 47;
            hash += x[i] - 'a' + 1;
            hash %= MOD;
            while (hash >= MOD) hash -= MOD;
            while (hash < 0) hash += MOD;
        }
        hash %= mod;
        return hash;
    }

    int hash2(string x) {
        long long MOD2 = 1000000411;
        long long hash = 0;
        for (int i = 0; i < x.size(); i++) {
            hash *= 47;
            hash += x[i] - 'a' + 1;
            hash %= MOD2;
            while (hash >= MOD2) hash -= MOD2;
            while (hash < 0) hash += MOD2;
        }
        return hash;
    }

    void add(string x, string y) {
        int d = hash(x);
        for (auto& h : map[d]) {
            if (x == h.ft) {
                h.sd.add({hash(y), hash2(y)}, y);
                return;
            }
        }
        map[d].push_back(make_pair(x, BST({hash(y), hash2(y)}, y)));
    }

    void delAll(string x) {
        int d = hash(x);
        for (int i = 0; i < map[d].size(); i++) {
            if (map[d][i].ft == x) {
                swap(map[d][i], map[d][map[d].size() - 1]);
//                map[d].back().second.del();
                map[d].pop_back();
                return;
            }
        }
        return;
    }

    vector<string> get(string x) {
        int d = hash(x);
        for (auto& y : map[d]) {
            if (y.ft == x) {
                return y.sd.get();
            }
        }
        return vector<string>();
    }

    void del(string x, string y) {
        int d = hash(x);
        for (auto& h : map[d]) {
            if (x == h.ft) {
                h.sd.pop({hash(y), hash2(y)});
                return;
            }
        }
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

    string s;
    myMap O;
//    cin >> s;
//    while (s != "-123") {
    while (cin >> s) {
        string x;
        cin >> x;
        if (s == "put") {
            string y;
            cin >> y;
            O.add(x, y);
        } else if (s == "get") {
            vector<string> ans = O.get(x);
            cout << ans.size();
            for (auto& y : ans) {
                cout << " " << y;
            }
            cout << endl;
        } else if (s == "deleteall") {
            O.delAll(x);
        } else if (s == "delete") {
            string y;
            cin >> y;
            O.del(x, y);
        }
//        cin >> s;
    }



    cerr << endl << "Time : " << ld(clock() - zzz) / CLOCKS_PER_SEC;
}