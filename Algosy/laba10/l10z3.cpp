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
#define openfiles ifstream cin ("spantree.in"); ofstream cout ("spantree.out");
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
    long double d;
    int a, b;
 
    bool operator<(const edge& x) const {
        return d < x.d || (d == x.d && a < x.a) || (d == x.d && a == x.a && b < x.b);
    }
};
 
int n, m;
vector<pair<int, int>> A;
vector<edge> G;
 
#define KlishkevichVadimka
signed main()
{
#ifdef KlishkevichVadimka
    openfiles
#endif
    faster;
    clock_t zzz = clock();
 
    cin >> n;
    A.resize(n);
 
    for (int i = 0; i < n; i++) {
        cin >> A[i].first >> A[i].second;
//        A[i].first = rng() % 20000 - 10000;
//        A[i].second = rng() % 20000 - 10000;
    }
 
    auto dist = [=](int a, int b) {
        return sqrtl((A[a].first - A[b].first) * (A[a].first - A[b].first) +
                    (A[a].second - A[b].second) * (A[a].second - A[b].second));
    };
 
    vector<int> Used(n);
    vector<long double> minE(n, INF);
    minE[0] = 0;
    long double ans = 0;
 
    for (int i = 0; i < n; i++) {
        int v = -1;
        for (int j = 0; j < n; j++) {
            if (!Used[j] && (v == -1 || minE[j] < minE[v])) {
                v = j;
            }
        }
        ans += minE[v];
        Used[v] = 1;
        for (int j = 0; j < n; j++) {
            long double x;
            if ((x = dist(v, j)) < minE[j]) {
                minE[j] = x;
            }
        }
    }
 
    cout << fixed << setprecision(10) << ans << endl;
 
 
 
 
    cerr << endl << "Time : " << ld(clock() - zzz) / CLOCKS_PER_SEC;
}
