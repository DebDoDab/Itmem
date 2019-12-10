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
#define openfiles ifstream cin ("bstsimple.in"); ofstream cout ("bstsimple.out");
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

struct node {
    int x;
    node *l = nullptr, *r = nullptr;

    node(int x_) {
        x = x_;
    }
};

struct BST {
    node *head = nullptr;

    void add(int x) {
        if (!head) {
            head = new node(x);
            return;
        }
        node *cur = head;
        while (true) {
            if (x < cur -> x) {
                if (cur -> l) {
                    cur = cur -> l;
                } else {
                    cur -> l = new node(x);
                    return;
                }
            } else if (x > cur -> x) {
                if (cur -> r) {
                    cur = cur -> r;
                } else {
                    cur -> r = new node(x);
                    return;
                }
            } else {
                return;
            }
        }
    }

    void pop(int x) {
        if (!head) {
            return;
        }

        node *prev = nullptr;
        node *cur = head;
        node *l = nullptr, *r = nullptr;
        bool right = false;
        while (true) {
            if (x < cur -> x) {
                if (cur -> l) {
                    prev = cur;
                    right = false;
                    cur = cur -> l;
                } else {
                    return;
                }
            } else if (x > cur -> x) {
                if (cur -> r) {
                    prev = cur;
                    right = true;
                    cur = cur -> r;
                } else {
                    return;
                }
            } else {
                l = cur -> l;
                r = cur -> r;
                delete cur;
                break;
            }
        }
        if (!prev) {
            head = l;
        } else if (right) {
            prev -> r = l;
        } else {
            prev -> l = l;
        }
        cur = l;
        if (!cur && !prev) {
            head = r;
        } else if (!cur && right) {
            prev -> r = r;
        } else if (!cur && !right) {
            prev -> l = r;
        }
        if (!cur) return;

        while (cur -> r) {
            cur = cur -> r;
        }
        cur -> r = r;
    }

    bool exists(int x) {
        if (!head) {
            return false;
        }
        node *cur = head;
        while (true) {
            if (x < cur -> x) {
                if (cur -> l) {
                    cur = cur -> l;
                } else {
                    return false;
                }
            } else if (x > cur -> x) {
                if (cur -> r) {
                    cur = cur -> r;
                } else {
                    return false;
                }
            } else {
                return true;
            }
        }
    }

    int next(int x) {
        if (!head) {
            return INF;
        }
        int ans = INF;
        node *cur = head;
        while (true) {
            if (x < cur -> x) {
                ans = min(ans, cur -> x);
                if (cur -> l) {
                    cur = cur -> l;
                } else {
                    return ans;
                }
            } else if (x >= cur -> x) {
                if (cur -> r) {
                    cur = cur -> r;
                } else {
                    return ans;
                }
            }
        }
    }

    int prev(int x) {
        if (!head) {
            return -INF;
        }
        int ans = -INF;
        node *cur = head;
        while (true) {
            if (x <= cur -> x) {
                if (cur -> l) {
                    cur = cur -> l;
                } else {
                    return ans;
                }
            } else if (x > cur -> x) {
                ans = max(ans, cur -> x);
                if (cur -> r) {
                    cur = cur -> r;
                } else {
                    return ans;
                }
            }
        }
    }
};

#define KlishkevichVadimka
signed main()
{
#ifdef KlishkevichVadimka
    openfiles
#endif
    faster;
    clock_t zzz = clock();

    string s;
    BST O;
//    cin >> s;
//    while (s != "-123") {
    while (cin >> s) {
        int x;
        cin >> x;
        if (s == "insert") {
            O.add(x);
        } else if (s == "delete") {
            O.pop(x);
        } else if (s == "exists") {
            if (O.exists(x)) {
                cout << "true\n";
            } else {
                cout << "false\n";
            }
        } else if (s == "next") {
            int ans = O.next(x);
            if (ans == INF) {
                cout << "none\n";
            } else {
                cout << ans << endl;
            }
        } else if (s == "prev") {
            int ans = O.prev(x);
            if (ans == -INF) {
                cout << "none\n";
            } else {
                cout << ans << endl;
            }
        }
//        cin >> s;
    }



    cerr << endl << "Time : " << ld(clock() - zzz) / CLOCKS_PER_SEC;
}