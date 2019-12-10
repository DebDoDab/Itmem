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
#define openfiles ifstream cin ("map.in"); ofstream cout ("map.out");
#define pb push_back
#define eb emplace_back
#define in insert
#define faster ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int INF = 1000000010;
const ll INFLL = 1000000000010000010;
const ld EPS = 0.0000001;
const ll MOD = 1000000411;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define mt make_tuple
#define g0(x) get<0>(x)
#define g1(x) get<1>(x)
#define g2(x) get<2>(x)
#define g3(x) get<3>(x)

struct myMap {
    vector<vector<pair<string, string>>> map;
    int mod = 1000029;

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

    void add(string x, string y) {
        int d = hash(x);
        for (auto& h : map[d]) {
            if (x == h.ft) {
                h.sd = y;
                return;
            }
        }
        map[d].push_back(make_pair(x, y));
    }

    void del(string x) {
        int d = hash(x);
        for (int i = 0; i < map[d].size(); i++) {
            if (map[d][i].ft == x) {
                swap(map[d][i], map[d][map[d].size() - 1]);
                map[d].pop_back();
                return;
            }
        }
        return;
    }

    string get(string x) {
        int d = hash(x);
        for (auto y : map[d]) {
            if (y.ft == x) {
                return y.sd;
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
        }
    }


    cerr << endl << "Time : " << ld(clock() - zzz) / CLOCKS_PER_SEC;
}
