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
#define openfiles ifstream cin ("matching.in"); ofstream cout ("matching.out");
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
    int a, b, c, f;
 
    edge(int a_, int b_, int c_, int f_) {
        a = a_;
        b = b_;
        c = c_;
        f = f_;
    }
};
 
int n, m, k, y;
vector<edge> Edges;
vector<vector<int>> G;
vector<int> Used;
vector<int> Cur;
int s, t;
 
#define KlishkevichVadimka
signed main()
{
#ifdef KlishkevichVadimka
    openfiles
#endif
    faster;
    clock_t zzz = clock();
 
    auto addEdge = [&](int x, int y, int c) {
        G[x].push_back(Edges.size());
        Edges.emplace_back(x, y, c, 0);
        G[y].push_back(Edges.size());
        Edges.emplace_back(y, x, 0, 0);
    };
 
    auto addFlow = [&](int e, int flow) {
        Edges[e].f += flow;
        Edges[e ^ 1].f -= flow;
    };
 
    auto bfs = [&]() {
        deque<int> O = {s};
        Used[s] = 1;
        while(!O.empty() && !Used[t]) {
            int x = O.front();
            O.pop_front();
            for (auto& e: G[x]) {
                auto edge = Edges[e];
                if (edge.c - edge.f <= 0) continue;
 
                if (!Used[edge.b]) {
                    O.push_back(edge.b);
                    Used[edge.b] = Used[x] + 1;
                }
            }
        }
 
        return Used[t];
    };
 
    function<int(int, int)> dfs = [&](int x, int f) {
        if (x == t || !f) {
            return f;
        }
        for (; Cur[x] < G[x].size(); Cur[x]++) {
            auto edge = Edges[G[x][Cur[x]]];
 
            if (Used[edge.b] == Used[x] + 1) {
                int flow = dfs(edge.b, min(f, edge.c - edge.f));
                if (flow) {
                    addFlow(G[x][Cur[x]], flow);
                    return flow;
                }
            }
        }
        return 0;
    };
 
    cin >> y >> k >> m;
    n = y + k + 2;
    s = 0, t = n - 1;
    G.resize(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        b += y;
        addEdge(a, b, 1);
    }
    for (int i = 0; i < y; i++) {
        addEdge(s, i + 1, 1);
    }
    for (int i = y; i < y + k; i++) {
        addEdge(i + 1, t, 1);
    }
 
    int ans = 0;
    Used.assign(n, 0);
    Cur.assign(n, 0);
    while(bfs()) {
        int curAns = 0;
        while(curAns = dfs(0, INF)) {
            ans += curAns;
        }
        Used.assign(n, 0);
        Cur.assign(n, 0);
    }
 
    cout << ans << endl;
 
 
    cerr << endl << "Time : " << ld(clock() - zzz) / CLOCKS_PER_SEC;
}
