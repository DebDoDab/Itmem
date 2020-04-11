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
#define openfiles ifstream cin ("path.in"); ofstream cout ("path.out");
#define pb push_back
#define eb emplace_back
#define in insert
#define faster ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int INF = 1000000010;
const ll INFLL = 8000000000010000010;
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
vector<char> Endless;
 
bool ford(int s) {
    Dist[s] = 0;
    deque<int> endless;
    bool cool = false;
    for (int i = 0; i < n; i++) {
        cool = false;
        for (int x = 0; x < n; x++) {
            if (Dist[x] == INFLL) {
                continue;
            }
            for (auto& y : G[x]) {
                if (Dist[y.first] > Dist[x] + y.second) {
                    cool = true;
                    Dist[y.first] = Dist[x] + y.second;
                    Dist[y.first] = max(Dist[y.first], -INFLL);
                    if (i > n - 2 && !Endless[y.first]) {
                        Endless[y.first] = true;
                        endless.push_back(y.first);
                    }
                }
            }
        }
        if (!cool) {
            break;
        }
    }
 
    while (!endless.empty()) {
        int x = endless.front();
        endless.pop_front();
        for (auto& y : G[x]) {
            if (!Endless[y.first]) {
                Endless[y.first] = true;
                endless.push_back(y.first);
            }
        }
    }
 
    return cool;
}
 
#define KlishkevichVadimka
signed main()
{
#ifdef KlishkevichVadimka
    openfiles
#endif
    faster;
    clock_t zzz = clock();
 
    cin >> n >> m >> s;
    s--;
    G.resize(n);
    Dist.resize(n, INFLL);
    Endless.resize(n, false);
    for (int i = 0; i < m; i++) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        a--, b--;
        G[a].push_back({b, c});
    }
 
    ford(s);
 
    for (int i = 0; i < n; i++) {
        if (Dist[i] == INFLL) {
            cout << "*\n";
        } else if (Endless[i]) {
            cout << "-\n";
        } else {
            cout << Dist[i] << "\n";
        }
    }
 
    cerr << endl << "Time : " << ld(clock() - zzz) / CLOCKS_PER_SEC;
}
