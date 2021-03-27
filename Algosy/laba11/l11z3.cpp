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
#define openfiles ifstream cin ("pathbgep.in"); ofstream cout ("pathbgep.out");
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
 
int n, m;
vector<vector<pair<int, int>>> G;
vector<int> Dist;
 
void dijkstra(int s) {
    set<pair<int, int>> O;
    Dist[s] = 0;
    O.insert({0, s});
 
    while (!O.empty()) {
        int x = O.begin()->second;
        O.erase(O.begin());
 
        for (auto& y : G[x]) {
            if (y.second == -1 || x == y.first) {
                continue;
            }
            if (Dist[y.first] > Dist[x] + y.second) {
                O.erase({Dist[y.first], y.first});
                Dist[y.first] = Dist[x] + y.second;
                O.insert({Dist[y.first], y.first});
            }
        }
    }
}
 
#define KlishkevichVadimka
signed main()
{
#ifdef KlishkevichVadimka
    openfiles
#endif
    faster;
    clock_t zzz = clock();
 
    cin >> n >> m;
    G.resize(n);
    Dist.resize(n, INF);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        G[a].push_back({b, c});
        G[b].push_back({a, c});
    }
 
    for (int i = 0; i < 1; i++) {
        dijkstra(i);
    }
 
    for (auto& x : Dist) {
        cout << x << " ";
    }
    cout << endl;
 
    cerr << endl << "Time : " << ld(clock() - zzz) / CLOCKS_PER_SEC;
}
