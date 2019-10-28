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
#define openfiles ifstream cin ("postfix.in"); ofstream cout ("postfix.out");
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
 
    string s;
    getline(cin, s);
    s += " ";
    string temp = "";
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == ' ') {
            if (temp.size() > 1 || (temp[0] >= '0' && temp[0] <= '9')) {
                int x = 0;
                for (int j = 0; j < temp.size(); j++) {
                    x *= 10;
                    x += temp[j] - '0';
                }
                o.push(x);
            } else if (temp[0] == '-') {
                int x = o.top();
                o.pop();
                int y = o.top();
                o.pop();
                o.push(y - x);
            } else if (temp[0] == '+') {
                int x = o.top();
                o.pop();
                int y = o.top();
                o.pop();
                o.push(x + y);
            } else if (temp[0] == '*') {
                int x = o.top();
                o.pop();
                int y = o.top();
                o.pop();
                o.push(x * y);
            } else {
//                cout << "UNDEFINED\n";
//                return 1;
            }
            temp = "";
        } else {
            temp += s[i];
        }
    }
 
    cout << o.top() << endl;
 
 
    cerr << endl << "Time : " << ld(clock() - zzz) / CLOCKS_PER_SEC;
}
