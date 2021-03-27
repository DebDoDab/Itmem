//#pragma GCC optimize("O3")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2")
#pragma GCC optimize("unroll-loops")
 
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
#define openfiles ifstream cin ("negcycle.in"); ofstream cout ("negcycle.out");
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
 
int n, m, s;
vector<vector<pair<int, long long>>> G;
vector<long long> Dist;
vector<int> Parent;
vector<int> Used;
 
vector<int> ford(int s) {
    Dist.assign(n, 0);
    deque<int> endless;
    Parent.resize(n, -1);
    int cool = -1;
    for (int i = 0; i < n; i++) {
        cool = -1;
        for (int x = 0; x < n; x++) {
            for (auto& y : G[x]) {
                if (Dist[y.first] > Dist[x] + y.second) {
                    Dist[y.first] = Dist[x] + y.second;
                    cool = y.first;
                    Parent[y.first] = x;
                }
            }
        }
    }
 
    if (cool == -1) {
        return vector<int>();
    }
 
    Used.resize(n);
    vector<int> Ans;
    function<bool(int)> cycle = [&] (int x) {
        if (Used[x]) {
            Used[x] = 0;
            Ans.push_back(x);
            return true;
        }
        Used[x] = 1;
        if (cycle(Parent[x]) && Used[x]) {
            Ans.push_back(x);
            return true;
        }
        return false;
    };
 
    cycle(cool);
 
    return Ans;
}
 
#define KlishkevichVadimka
signed main()
{
#ifdef KlishkevichVadimka
    openfiles
#endif
    faster;
    clock_t zzz = clock();
 
    cin >> n;
    s--;
    G.resize(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
//            if (i == j) continue;
            G[i].push_back({j, x});
        }
    }
 
    vector<int> Ans = ford(s);
 
    if (Ans.size()) {
        cout << "YES\n" << Ans.size() + 1 << endl;
        for (auto &x : Ans) {
            cout << x + 1 << " ";
        }
        cout << Ans.front() + 1 << endl;
    } else {
        cout << "NO\n";
    }
 
    cerr << endl << "Time : " << ld(clock() - zzz) / CLOCKS_PER_SEC;
}
