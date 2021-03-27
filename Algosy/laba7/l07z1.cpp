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
#define openfiles ifstream cin ("balance.in"); ofstream cout ("balance.out");
#define pb push_back
#define eb emplace_back
#define in insert
#define faster ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int INF = 1000000010;
const ll INFLL = 1000000000010000010;
const ld EPS = 0.0000001;
const ll MOD = 1000000321;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define mt make_tuple
#define g0(x) get<0>(x)
#define g1(x) get<1>(x)
#define g2(x) get<2>(x)
#define g3(x) get<3>(x)

struct node {
    int x;
    int l, r;
    int b = -INF;
    int h = 1;
};

int n;
vector<node> A;

void balance(int x) {
    if (A[x].l != -1 && A[A[x].l].b == -INF) balance(A[x].l);
    if (A[x].r != -1 && A[A[x].r].b == -INF) balance(A[x].r);
    A[x].h = 1;
    if (A[x].l != -1) A[x].h = max(A[x].h, A[A[x].l].h + 1);
    if (A[x].r != -1) A[x].h = max(A[x].h, A[A[x].r].h + 1);
    A[x].b = 0;
    if (A[x].r != -1) A[x].b += A[A[x].r].h;
    if (A[x].l != -1) A[x].b -= A[A[x].l].h;
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
        cin >> x.x >> x.l >> x.r;
        x.l--, x.r--;
    }

    for (int i = 0; i < n; i++) {
        if (A[i].b == -INF) {
            balance(i);
        }
        cout << A[i].b << endl;
    }



    cerr << endl << "Time : " << ld(clock() - zzz) / CLOCKS_PER_SEC;
}