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
#define openfiles ifstream cin ("race.in"); ofstream cout ("race.out");
#define pb push_back
#define eb emplace_back
#define in insert
#define faster ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int INF = 1000000010;
const ll INFLL = 1000000000000000010;
const ld EPS = 0.0000001;
const ll MOD = 1000000007;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define mt make_tuple
#define g0(x) get<0>(x)
#define g1(x) get<1>(x)
#define g2(x) get<2>(x)
#define g3(x) get<3>(x)

int n;
vector<tuple<string, int, string>> A;

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
        string country, nick;
        cin >> country >> nick;
        A[i] = mt(country, i, nick);
    }

    sort(A.begin(), A.end());

    string last = "%";
    for (int i = 0; i < n; i++) {
        if (last != g0(A[i])) {
            cout << "=== " << g0(A[i]) << " ===\n";
            last = g0(A[i]);
        }
        cout << g2(A[i]) << endl;
    }


    cerr << endl << "Time : " << ld(clock() - zzz) / CLOCKS_PER_SEC;
}
