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
#define openfiles ifstream cin ("chinese.in"); ofstream cout ("chinese.out");
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
 
struct edge {
    int b;
    int w;
 
    edge(int b_, int w_) {
        b = b_;
        w = w_;
    }
};
 
int n, m;
vector<vector<edge>> G;
vector<int> Used;
 
long long findMST(vector<vector<edge>>& G, int n, int root);
int dfs(int root, vector<vector<edge>>& G);
 
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
 
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        G[a].emplace_back(b, c);
    }
 
    Used.assign(n, 0);
    if (dfs(0, G) != n) {
        cout << "NO\n";
        return 0;
    }
 
 
    cout << "YES\n";
    cout << findMST(G, n, 0) << endl;
 
 
 
    cerr << endl << "Time : " << ld(clock() - zzz) / CLOCKS_PER_SEC;
}
 
int dfs(int root, vector<vector<edge>>& G) {
    Used[root] = 1;
    int ans = 1;
    for (auto& edge : G[root]) {
        if (!Used[edge.b]) {
            ans += dfs(edge.b, G);
        }
    }
    return ans;
}
 
vector<int> Order;
void dfs1(int x, vector<vector<edge>>& G) {
    Used[x] = 1;
    for (auto& edge : G[x]) {
        if (!Used[edge.b]) {
            dfs1(edge.b, G);
        }
    }
    Order.push_back(x);
}
 
void dfs2(int x, vector<vector<edge>>& G, vector<int>& Components, int clr) {
    Used[x] = 1;
    Components[x] = clr;
    for (auto& edge : G[x]) {
        if (!Used[edge.b]) {
            dfs2(edge.b, G, Components, clr);
        }
    }
}
 
int condensation(vector<int>& Components, int n, vector<vector<edge>>& G) {
    Order.clear();
    Used.assign(n, 0);
    for (int i = 0; i < n; i++) {
        if (!Used[i]) {
            dfs1(i, G);
        }
    }
 
    vector<vector<edge>> GR(n);
    for (int i = 0; i < n; i++) {
        for (auto& edge : G[i]) {
            GR[edge.b].emplace_back(i, edge.w);
        }
    }
 
    Used.assign(n, 0);
    int clr = 0;
    for (int i = 0; i < n; i++) {
        if (!Used[Order[n - i - 1]]) {
            dfs2(Order[n - i - 1], GR, Components, clr++);
        }
    }
    return clr;
}
 
long long findMST(vector<vector<edge>>& G, int n, int root) {
    long long ans = 0;
    vector<int> mins(n, INF);
    for (int i = 0; i < n; i++) {
        for (auto& edge : G[i]) {
            mins[edge.b] = min(mins[edge.b], edge.w);
        }
    }
    for (int i = 0; i < n; i++) {
        if (i == root) continue;
        ans += mins[i];
    }
    vector<vector<edge>> zeroG(n);
    for (int i = 0; i < n; i++) {
        for (auto& edge : G[i]) {
            if (edge.w == mins[edge.b]) {
                zeroG[i].emplace_back(edge.b, 0);
            }
        }
    }
    Used.assign(n, 0);
    if (dfs(root, zeroG) == n) {
        return ans;
    }
 
    vector<int> Components(n);
    int clr = condensation(Components, n, zeroG);
 
    vector<vector<edge>> newG(clr);
    for (int i = 0; i < n; i++) {
        for (auto& edge : G[i]) {
            if (Components[edge.b] != Components[i]) {
                newG[Components[i]].emplace_back(Components[edge.b], edge.w - mins[edge.b]);
            }
        }
    }
 
    return ans + findMST(newG, clr, Components[root]);
}
