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
#define openfiles ifstream cin ("brackets.in"); ofstream cout ("brackets.out");
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
 
int q;
stack<int> o;
 
#define KlishkevichVadimka
signed main()
{
#ifdef KlishkevichVadimka
    openfiles
#endif
    faster;
    clock_t zzz = clock();
 
//    cin >> q; cin.ignore();
    string s;
    while (getline(cin, s)) {
//        string s;
//        getline(cin, s);
        bool cool = true;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(' || s[i] == '[') {
                o.push(s[i]);
            } else if (o.empty()) {
                cool = false;
            } else if (s[i] == ')') {
                if (o.top() != '(') {
                    cool = false;
                } else {
                    o.pop();
                }
            } else if (s[i] == ']') {
                if (o.top() != '[') {
                    cool = false;
                } else {
                    o.pop();
                }
            }
            if (!cool) {
                break;
            }
        }
        if (cool && o.empty()) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
        while (!o.empty()) {
            o.pop();
        }
    }
 
 
    cerr << endl << "Time : " << ld(clock() - zzz) / CLOCKS_PER_SEC;
}
