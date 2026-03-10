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
    int n, m;
    cin >> n >> m;

    const ll INF64 = (1LL << 60);
    vector<vector<ll>> dist(n, vector<ll>(n, INF64));
    for (int i = 0; i < n; ++i) {
        dist[i][i] = 0;
    }

    for (int i = 0; i < m; ++i) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        --u;
        --v;
        dist[u][v] = w;
        dist[v][u] = w;
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                ckmin(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (dist[0][i] >= INF64) {
            cout << -1 << '\n';
            return;
        }
    }

    const int fm = (1 << n) - 1;
    vector<vector<ll>> dp(1 << n, vector<ll>(n, INF64));
    dp[1][0] = 0;

    for (int mask = 0; mask <= fm; ++mask) {
        for (int v = 0; v < n; ++v) {
            if (dp[mask][v] >= INF64) {
                continue;
            }
            for (int to = 0; to < n; ++to) {
                if (mask & (1 << to)) {
                    continue;
                }
                ckmin(dp[mask | (1 << to)][to], dp[mask][v] + dist[v][to]);
            }
        }
    }

    ll ans = INF64;
    for (int v = 0; v < n; ++v) {
        ckmin(ans, dp[fm][v] + dist[v][0]);
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
