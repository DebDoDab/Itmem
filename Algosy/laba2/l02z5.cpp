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
#define openfiles ifstream cin ("kth.in"); ofstream cout ("kth.out");
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

int n, k;
int a, b, c;
vector<int> A;

int kth_elementh(vector<int>& A, int l, int r, int k) {
    while (true) {
        if (r - l < 2) {
            if (r == l + 1 && A[r] < A[l]) {
                swap(A[r], A[l]);
            }
            return A[k];
        }
        int m = (l + r) >> 1;
        if (A[l] > A[m]) swap(A[l], A[m]);
        if (A[l] > A[r]) swap(A[l], A[r]);
        if (A[m] > A[r]) swap(A[m], A[r]);
        swap(A[m], A[l + 1]);

        int i = l + 1, j = r;
        do {
            while (A[++i] < A[l + 1]) {}
            while (A[--j] > A[l + 1]) {}
            if (i <= j) swap(A[i], A[j]);
        } while (i <= j);

        swap(A[l + 1], A[j]);

        if (j >= k) {
            r = j - 1;
        }
        if (j <= k) {
            l = i;
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

    cin >> n >> k;
    if (n == 1) {
        int a, b, c, d, e;
        cin >> a >> b >> c >> d >> e;
        cout << d << endl;
        return 0;
    }
    A.resize(n);
    cin >> a >> b >> c;
    cin >> A[0] >> A[1];

    for (int i = 2; i < n; i++) {
        A[i] = a * A[i-2] + b * A[i-1] + c;
    }

    cout << kth_elementh(A, 0, n - 1, k - 1);

    cerr << endl << "Time : " << ld(clock() - zzz) / CLOCKS_PER_SEC;
}
