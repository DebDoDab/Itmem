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
#define openfiles ifstream cin ("antiqs.in"); ofstream cout ("antiqs.out");
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
vector<int> A;

int opa(int l, int r, vector<int>& A) {
    int i = l, j = r, key = A[(l + r) / 2];
    do {
        while (A[i] < key) i++;
        while (A[j] > key) j--;
        if (i <= j) {
            swap(A[i], A[j]);
            i++, j--;
        }
    } while (i <= j);
    ll ans = 1;
    if (l < j) ans += opa(l, j, A);
    if (i < r) ans += opa(i, r, A);
    return ans;
}
int qs(vector<int> A) {
    return opa(0, n-1, A);
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
    if (n == 1) {
        cout << 1 << endl;
        return 0;
    }

    A.resize(n);
    A[0] = 2;
    A[1] = 1;

    for (int i = 2; i < n; i++) {
        int m = i / 2;
        A[i] = i + 1;
        swap(A[i], A[m]);
    }

//    cerr << qs(A) << endl;

    for (auto x : A) cout << x << " ";
    cout << endl;

    cerr << endl << "Time : " << ld(clock() - zzz) / CLOCKS_PER_SEC;
}
