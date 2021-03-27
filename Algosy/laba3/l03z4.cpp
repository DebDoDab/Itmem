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
const ll INFLL = 1000000000010000010;
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
 
vector<int> Heap;
 
void siftUp(vector<int>& Heap, int i) {
    while (i && Heap[i] < Heap[(i - 1) >> 1]) {
        swap(Heap[i], Heap[(i - 1) >> 1]);
        i = (i - 1) >> 1;
    }
}
 
void siftDown(vector<int>& Heap, int i) {
    while ((i << 1) + 1 < Heap.size()) {
        int j = (i << 1) + 1;
        if (j + 1 < Heap.size() && Heap[j + 1] < Heap[j]) {
            j++;
        }
        if (Heap[i] <= Heap[j]) {
            break;
        }
        swap(Heap[i], Heap[j]);
        swap(i, j);
    }
}
 
void add(vector<int>& Heap, int x) {
    Heap.push_back(x);
    siftUp(Heap, Heap.size() - 1);
}
 
int pop(vector<int>& Heap) {
    int x = Heap[0];
    Heap[0] = Heap.back();
    Heap.erase(Heap.end() - 1);
    siftDown(Heap, 0);
    return x;
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
 
    for (int i = 0; i < n; i++) {
        add(Heap, A[i]);
    }
 
    for (int i = 0; i < n; i++) {
        cout << pop(Heap) << " ";
    }
    cout << endl;
 
 
    cerr << endl << "Time : " << ld(clock() - zzz) / CLOCKS_PER_SEC;
}
