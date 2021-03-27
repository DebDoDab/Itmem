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
#define openfiles ifstream cin ("sort.in"); ofstream cout ("sort.out");
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

void msort(vector<int>& A, int l, int r) {
    if (l == r) return;
    int m = (l + r) / 2;
    msort(A, l, m);
    msort(A, m + 1, r);
    vector<int> B(m - l + 1), C(r - m);
    for (int i = l; i <= m; i++) {
        B[i - l] = A[i];
    }
    for (int i = m + 1; i <= r; i++) {
        C[i - m - 1] = A[i];
    }
    int itl = 0, itr = 0;
    for (int i = l; i <= r; i++) {
        if (itl == B.size()) {
            A[i] = C[itr++];
        } else if (itr == C.size()) {
            A[i] = B[itl++];
        } else if (B[itl] < C[itr]) {
            A[i] = B[itl++];
        } else {
            A[i] = C[itr++];
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

    cin >> n;
    A.resize(n);
    for (auto& x : A) cin >> x;
    msort(A, 0, n - 1);

    for (auto x : A) {
        cout << x << " ";
    } cout << endl;

    cerr << endl << "Time : " << ld(clock() - zzz) / CLOCKS_PER_SEC;
}
