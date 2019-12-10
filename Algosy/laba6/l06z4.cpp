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
#define openfiles ifstream cin ("quack.in"); ofstream cout ("quack.out");
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

vector<string> Commands;
unordered_map<string, int> Labels;
vector<int> Variables('z' - 'a' + 1);
deque<unsigned short> Q;

#define KlishkevichVadimka
signed main()
{
#ifdef KlishkevichVadimka
    openfiles
#endif
    faster;
    clock_t zzz = clock();

    string command;
//    cin >> command;
//    while (command != "-123") {
    while (cin >> command) {
        if (command[0] == ':') {
            Labels[command.substr(1)] = Commands.size();
//            cerr << command.substr(1) << endl;
        }
        Commands.push_back(command);
//        cin >> command;
    }

    for (int current = 0; current < Commands.size(); current++) {
        if (Commands[current][0] == '+') {
//            assert(Q.size() >= 2);
            int x = Q.front(); Q.pop_front();
            int y = Q.front(); Q.pop_front();
            Q.push_back(x + y);
        } else if (Commands[current][0] == '-') {
//            assert(Q.size() >= 2);
            int x = Q.front(); Q.pop_front();
            int y = Q.front(); Q.pop_front();
            Q.push_back(x - y);
        } else if (Commands[current][0] == '*') {
//            assert(Q.size() >= 2);
            int x = Q.front(); Q.pop_front();
            int y = Q.front(); Q.pop_front();
            Q.push_back(x * y);
        } else if (Commands[current][0] == '/') {
//            assert(Q.size() >= 2);
            int x = Q.front(); Q.pop_front();
            int y = Q.front(); Q.pop_front();
            if (y) Q.push_back(x / y);
            else Q.push_back(0);
        } else if (Commands[current][0] == '%') {
//            assert(Q.size() >= 2);
            int x = Q.front(); Q.pop_front();
            int y = Q.front(); Q.pop_front();
            if (y) Q.push_back(x % y);
            else Q.push_back(0);
        } else if (Commands[current][0] == '>') {
//            assert(Q.size() >= 1);
            int x = Q.front(); Q.pop_front();
            Variables[Commands[current][1] - 'a'] = x;
        } else if (Commands[current][0] == '<') {
            int x = Variables[Commands[current][1] - 'a'];
            Q.push_back(x);
        } else if (Commands[current] == "P") {
//            assert(Q.size() >= 1);
            int x = Q.front(); Q.pop_front();
            cout << x << endl;
        } else if (Commands[current][0] == 'P') {
            cout << Variables[Commands[current][1] - 'a'] << endl;
        } else if (Commands[current] == "C") {
//            assert(Q.size() >= 1);
            int x = Q.front(); Q.pop_front();
            cout << (unsigned char)(x);
        } else if (Commands[current][0] == 'C') {
            cout << (unsigned char)(Variables[Commands[current][1] - 'a']);
        } else if (Commands[current][0] == ':') {
            continue;
        } else if (Commands[current][0] == 'J') {
            current = Labels[Commands[current].substr(1)] - 1;
        } else if (Commands[current][0] == 'Z') {
            if (Variables[Commands[current][1] - 'a']) {
                continue;
            }
            current = Labels[Commands[current].substr(2)] - 1;
        } else if (Commands[current][0] == 'E') {
            if (Variables[Commands[current][1] - 'a'] != Variables[Commands[current][2] - 'a']) {
                continue;
            }
            current = Labels[Commands[current].substr(3)] - 1;
        } else if (Commands[current][0] == 'G') {
            if (Variables[Commands[current][1] - 'a'] <= Variables[Commands[current][2] - 'a']) {
                continue;
            }
            current = Labels[Commands[current].substr(3)] - 1;
        } else if (Commands[current] == "Q") {
            return 0;
        } else {
            Q.push_back(stoi(Commands[current]));
        }
    }



    cerr << endl << "Time : " << ld(clock() - zzz) / CLOCKS_PER_SEC;
}