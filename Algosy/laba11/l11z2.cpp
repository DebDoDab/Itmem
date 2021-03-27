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
#define openfiles ifstream cin ("pathsg.in"); ofstream cout ("pathsg.out");
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
vector<vector<int>> G;
vector<vector<int>> Dist;
 
void dijkstra(int s) {
    set<pair<int, int>> O;
    Dist[s][s] = 0;
    O.insert({0, s});
 
    while (!O.empty()) {
        int x = O.begin()->second;
        O.erase(O.begin());
 
        for (int i = 0; i < n; i++) {
            if (G[x][i] == -1 || x == i) {
                continue;
            }
            if (Dist[s][i] > Dist[s][x] + G[x][i]) {
                O.erase({Dist[s][i], i});
                Dist[s][i] = Dist[s][x] + G[x][i];
                O.insert({Dist[s][i], i});
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
    G.resize(n, vector<int>(n, -1));
    Dist.resize(n, vector<int>(n, INF));
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        G[a][b] = c;
    }
 
    for (int i = 0; i < n; i++) {
        dijkstra(i);
    }
 
    for (auto& x : Dist) {
        for (auto& y : x) {
            cout << y << " ";
        }
        cout << endl;
    }
 
    cerr << endl << "Time : " << ld(clock() - zzz) / CLOCKS_PER_SEC;
}
