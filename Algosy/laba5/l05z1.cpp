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

//#define endl "\n"
#define ft first
#define sd second
#define openfiles ifstream cin ("set.in"); ofstream cout ("set.out");
#define pb push_back
#define eb emplace_back
#define in insert
#define faster ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int INF = 1000000010;
const ll INFLL = 1000000000010000010;
const ld EPS = 0.0000001;
const ll MOD = 1000000007;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define mt make_tuple
#define g0(x) get<0>(x)
#define g1(x) get<1>(x)
#define g2(x) get<2>(x)
#define g3(x) get<3>(x)

struct mySet {
    vector<vector<int>> set;
    int mod = 1000029;

    mySet() {
        set.resize(mod);
    }

    int hash(int x) {
        return ((x % mod) + mod) % mod;
    }

    void add(int x) {
        int d = hash(x);
        bool cool = false;
        for (int y : set[d]) {
            if (y == x) {
                cool = true;
            }
        }
        if (cool) return;
        set[d].push_back(x);
    }

    void del(int x) {
        int d = hash(x);
        for (int i = 0; i < set[d].size(); i++) {
            if (set[d][i] == x) {
                swap(set[d][i], set[d][set[d].size() - 1]);
                set[d].pop_back();
                return;
            }
        }
        return;
    }

    bool exists(int x) {
        int d = hash(x);
        for (int y : set[d]) {
            if (y == x) {
                return true;
            }
        }
        return false;
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

    mySet o;

    string s;
    while (cin >> s) {
        int x;
        cin >> x;
        if (s == "insert") {
            o.add(x);
        } else if (s == "delete") {
            o.del(x);
        } else if (s == "exists") {
            if (o.exists(x)) {
                cout << "true\n";
            } else {
                cout << "false\n";
            }
        }
    }


    cerr << endl << "Time : " << ld(clock() - zzz) / CLOCKS_PER_SEC;
}
