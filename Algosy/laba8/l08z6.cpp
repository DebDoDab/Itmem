#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <chrono>
 
using namespace std;
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
 
using ll = long long;
using ull =  unsigned long long;
using ld = long double;
using pii = pair <int, int>;
using pll = pair <ll, ll>;
using t3 = tuple<int, int, int, int>;
 
#define endl "\n"
#define ft first
#define sd second
#define openfiles ifstream cin ("input.txt"); ofstream cout ("output.txt");
#define pb push_back
#define eb emplace_back
#define in insert
#define faster ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int INF = 1000000010;
const ll INFLL = 1000000000010000010;
const ld EPS = 0.0000001;
const ll MOD = 1000000123;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
#define mt make_tuple
#define g0(x) get<0>(x)
#define g1(x) get<1>(x)
#define g2(x) get<2>(x)
#define g3(x) get<3>(x)
 
int n, m;
vector<vector<int>> G;
vector<vector<int>> D;
pair<int, int> start, finish;
 
const vector<int> T1 = {0, 0, 1, -1};
const vector<int> T2 = {1, -1, 0, 0};
const vector<char> C = {'L', 'R', 'U', 'D'};
 
#define KlishkevichVadimka
signed main()
{
#ifdef KlishkevichVadimka
    openfiles
#endif
    faster;
    clock_t zzz = clock();
 
    cin >> n >> m;
    G.resize(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char x;
            cin >> x;
            if (x == '#') {
                G[i][j] = -1;
            } else if (x == 'S') {
                start = {i, j};
            } else if (x == 'T') {
                finish = {i, j};
            }
        }
    }
 
    auto bfs = [&](pair<int, int> st, pair<int, int> fn, string& s) {
        G[st.first][st.second] = 1;
        deque<pair<int, int>> O = {st};
 
        while (!O.empty()) {
            pair<int, int> x = O.front();
            O.pop_front();
            for (int i = 0; i < 4; i++) {
                if (x.first + T1[i] < 0 || x.first + T1[i] >= n ||
                        x.second + T2[i] < 0 || x.second + T2[i] >= m) {
                    continue;
                }
                if (G[x.first + T1[i]][x.second + T2[i]] == 0) {
                    G[x.first + T1[i]][x.second + T2[i]] = G[x.first][x.second] + 1;
                    O.push_back(make_pair(x.first + T1[i], x.second + T2[i]));
                }
 
            }
        }
 
        if (G[fn.first][fn.second] == 0) {
            return;
        }
 
        pair<int, int> x = fn;
        while (x != st) {
            for (int i = 0; i < 4; i++) {
                if (x.first + T1[i] < 0 || x.first + T1[i] >= n ||
                    x.second + T2[i] < 0 || x.second + T2[i] >= m) {
                    continue;
                }
 
                if (G[x.first + T1[i]][x.second + T2[i]] == G[x.first][x.second] - 1) {
                    s += C[i];
                    x.first += T1[i];
                    x.second += T2[i];
                    break;
                }
            }
        }
        reverse(s.begin(), s.end());
    };
 
    string s;
 
    bfs(start, finish, s);
 
    if (!s.size()) {
        cout << "-1\n";
        return 0;
    }
 
    cout << s.size() << endl << s << endl;
 
 
    cerr << endl << "Time : " << ld(clock() - zzz) / CLOCKS_PER_SEC;
}
