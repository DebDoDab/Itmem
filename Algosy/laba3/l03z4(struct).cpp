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
 
struct priorQueue {
    pair<int, int> heap[2000010];
    int pos[2000010];
    int pointer = 0;
 
    void siftUp(int i) {
        while (i && heap[i].first < heap[(i - 1) >> 1].first) {
            swap(pos[heap[i].second], pos[heap[(i - 1) >> 1].second]);
            swap(heap[i], heap[(i - 1) >> 1]);
            i = (i - 1) >> 1;
        }
    }
    void siftDown(int i) {
        while ((i << 1) + 1 < pointer) {
            int j = (i << 1) + 1;
            if (j + 1 < pointer && heap[j + 1].first < heap[j].first) {
                j++;
            }
            if (heap[i].first <= heap[j].first) {
                break;
            }
            swap(pos[heap[i].second], pos[heap[j].second]);
            swap(heap[i], heap[j]);
            i = j;
        }
    }
    void add(int x, int k) {
        heap[pointer] = make_pair(x, k);
        pos[k] = pointer;
        pointer++;
        siftUp(pointer - 1);
    }
    int del() {
        if (pointer == 0) {
            return (INF << 1);
        }
        int x = heap[0].first;
        pointer--;
        swap(pos[heap[0].second], pos[heap[pointer].second]);
        swap(heap[0], heap[pointer]);
        siftDown(0);
        return x;
    }
    void edit(int k, int x) {
        heap[pos[k]].first = x;
        siftUp(pos[k]);
    }
};
 
priorQueue o;
 
#define KlishkevichVadimka
signed main()
{
#ifdef KlishkevichVadimka
    openfiles
#endif
    faster;
    clock_t zzz = clock();
 
    int n;
    vector<int> A;
    cin >> n;
    A.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
        o.add(A[i], i);
    }
    for (int i = 0; i < n; i++) {
        cout << o.del() << " ";
    }
 
    /*int h = 1;
    string s;
 
    int q;
    cin >> q; cin.ignore();
    while (q--) {
//    while (getline(cin, s)) {
        getline(cin, s);
        if (s[0] == 'p') {
            int x = 0;
            for (int i = 5; i < s.size(); i++) {
                x *= 10;
                x += s[i] - '0';
            }
            o.add(x, h);
        } else if (s[0] == 'e') {
            int x = o.del();
            if (x == (INF << 1)) {
                cout << "*\n";
            } else {
                cout << x << endl;
            }
        } else if (s[0] == 'd') {
            int x = 0;
            int i = 13;
            for (; i < s.size(); i++) {
                if (s[i] == ' ') {
                    i++;
                    break;
                }
                x *= 10;
                x += s[i] - '0';
            }
            int y = 0;
            for (; i < s.size(); i++) {
                y *= 10;
                y += s[i] - '0';
            }
            o.edit(x, y);
        }
        h++;
    }*/
 
 
 
    cerr << endl << "Time : " << ld(clock() - zzz) / CLOCKS_PER_SEC;
}
