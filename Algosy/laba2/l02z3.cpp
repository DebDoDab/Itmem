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
#define openfiles ifstream cin ("inversions.in"); ofstream cout ("inversions.out");
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
vector<int> A, F;

int get(int r) {
    int ans = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1) {
        ans += F[r];
    }
    return ans;
}

void upd(int r) {
    for (; r < n; r |= (r + 1)) {
        F[r]++;
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

    cin >> n;
    A.resize(n);
    F.resize(100007);
    vector<int> Temp(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
        Temp[i] = A[i];
    }

    sort(Temp.begin(), Temp.end());
    Temp.erase(unique(Temp.begin(), Temp.end()), Temp.end());

    for (int i = 0; i < n; i++) {
        A[i] = lower_bound(Temp.begin(), Temp.end(), A[i]) - Temp.begin();
    }

    ll ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        ans += get(A[i] - 1);
        upd(A[i]);
    }

    cout << ans << endl;


    cerr << endl << "Time : " << ld(clock() - zzz) / CLOCKS_PER_SEC;
}
