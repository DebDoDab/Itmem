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
using t3 = tuple<int, int, int>;
 
#define endl "\n"
#define ft first
#define sd second
#define openfiles ifstream cin ("binsearch.in"); ofstream cout ("binsearch.out");
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
 
int n, m;
vector<int> A;
 
int upperBound(vector<int>& A, int x) {
    int l = 0, r = A.size();
    for (int i = 0; i < 50 && l < r; i++) {
        int m = (l + r) >> 1;
        if (l == m) m++;
        if (A[m] > x) {
            r = m - 1;
        } else {
            l = m;
        }
    }
    return l;
}
int lowerBound(vector<int>& A, int x) {
    int l = 0, r = A.size();
    for (int i = 0; i < 50 && l < r; i++) {
        int m = (l + r) >> 1;
        if (A[m] < x) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    return l;
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
    A.resize(n);
    for (auto& x : A) {
        cin >> x;
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        int a = lowerBound(A, x) + 1, b = min(upperBound(A, x) + 1, n);
        if (a < n && A[a - 1] == x) {
            cout << a << " " << b << endl;
        } else {
            cout << -1 << " " << -1 << endl;
        }
    }
 
 
    cerr << endl << "Time : " << ld(clock() - zzz) / CLOCKS_PER_SEC;
}
