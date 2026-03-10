#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

template <class T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;

template <class T>
bool ckmin(T& a, const T& b) {
    if (b < a) {
        a = b;
        return true;
    }
    return false;
}

template <class T>
bool ckmax(T& a, const T& b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}

#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define sz(x) static_cast<int>((x).size())

constexpr int INF = 1e9;
constexpr ll LINF = 1e18;

mt19937 rng(static_cast<uint32_t>(chrono::steady_clock::now().time_since_epoch().count()));

#ifdef LOCAL
template <class A, class B>
ostream& operator<<(ostream& os, const pair<A, B>& p) {
    return os << '(' << p.first << ", " << p.second << ')';
}

template <class T>
ostream& operator<<(ostream& os, const vector<T>& v) {
    os << '[';
    for (int i = 0; i < sz(v); ++i) {
        if (i) os << ", ";
        os << v[i];
    }
    return os << ']';
}

void debug_out() {
    cerr << '\n';
}

template <class Head, class... Tail>
void debug_out(Head&& head, Tail&&... tail) {
    cerr << ' ' << head;
    debug_out(forward<Tail>(tail)...);
}

#define dbg(...) cerr << "[" #__VA_ARGS__ << "] :", debug_out(__VA_ARGS__)
#else
#define dbg(...) ((void)0)
#endif

void solve() {
    int n, d;
    ll k;
    cin >> n >> d >> k;

    const ll de = 1LL * d * k;
    int ans = 0;

    for (int i = 0; i < n; ++i) {
        ll w;
        cin >> w;
        if (w - de >= 1) {
            ++ans;
        }
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
