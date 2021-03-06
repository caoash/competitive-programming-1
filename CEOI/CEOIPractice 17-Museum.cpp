/*
 * Same idea as editorial, IOI 05-rivers
 *
 * We can solve using dp: dp(i, j, k) = shortest time needed, assuming person is on node i, to visit
 * j unique rooms in i's subtree (i does not count towards j). If k = 0, then the person can end in any room.
 * If k = 1, then the person must return to the i'th room.
 *
 * The transition is dividing the k rooms to visit amongst i's children. To do this in a timely manner,
 * we can either use a second dp or add another parameter to our dp state: index of child.
 * dp(i, j, k, l) = time to visit j unique rooms in i's subtree *from index l onwards.* This is a
 * similar idea to IOI 05-rivers and is also explained in the editorial.
 *
 * To pass the memory limit constraint, memo state should be created dynamically.
 *
 * To pass the final test case, multiple pruning optimizations must be made (for example, if i's subtree
 * only has 10 rooms, then we should not consider j > 10)
 */

//#pragma GCC optimize ("O3")
//#pragma GCC target ("sse4")

#include <bits/stdc++.h>

using namespace std;

template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define F0R1(i, a) for (int i=1; i<=(a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)
#define trav(a, x) for (auto& a : x)
#define MIN(a, b) a = min(a, b)
#define MAX(a, b) a = max(a, b)

#define INF 1000000010
#define LL_INF 4500000000000000000LL
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define pA first
#define pB second
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define eb emplace_back
#define PI acos(-1.0)
// #define MOD (int)(2e+9+11)
#define MOD (int)(1e+9+7)
#define SET(vec, val, size) for (int i = 0; i < size; i++) vec[i] = val;
#define SET2D(arr, val, dim1, dim2) F0R(i, dim1) F0R(j, dim2) arr[i][j] = val;
#define SET3D(arr, val, dim1, dim2, dim3) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) arr[i][j][k] = val;
#define SET4D(arr, val, dim1, dim2, dim3, dim4) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) F0R(l, dim4) arr[i][j][k][l] = val;

#define lb lower_bound
#define ub upper_bound
#define sz(x) (int)x.size()
#define beg(x) x.begin()
#define en(x) x.end()
#define all(x) beg(x), en(x)
#define resz resize
#define SORT(vec) sort(all(vec))
#define RSORT(vec) sort(vec.rbegin(),vec.rend())

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<ll> vl;

// @formatter:off
// Source: Benq (https://github.com/bqi343/USACO) [Modified]
namespace input {
    template<class T> void re(complex<T>& x);
    template<class T1, class T2> void re(pair<T1,T2>& p);
    template<class T> void re(vector<T>& a);
    template<class T, size_t SZ> void re(array<T,SZ>& a);
    template<class T> void reA(T A[], int sz);

    template<class T> void re(T& x) { cin >> x; }
    void re(double& x) { string t; re(t); x = stod(t); }
    void re(ld& x) { string t; re(t); x = stold(t); }
    template<class Arg, class... Args> void re(Arg& first, Args&... rest) {
        re(first); re(rest...);
    }

    template<class T1, class T2> void re(pair<T1,T2>& p) { re(p.pA,p.pB); }
    template<class T> void re(vector<T>& a) { F0R(i,sz(a)) re(a[i]); }
    template<class T, size_t SZ> void re(array<T,SZ>& a) { F0R(i,SZ) re(a[i]); }
    template<class T> void reA(T A[], int sz) { F0R(i, sz) re(A[i]); }

    void setupIO(const string &PROB = "") {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        if (PROB.length() != 0) {
            ifstream infile(PROB + ".in");
            if (infile.good()) {
                freopen((PROB + ".in").c_str(), "r", stdin);
                freopen((PROB + ".out").c_str(), "w", stdout);
            }
        }
    }
}
using namespace input;

namespace output {
    template<class T1, class T2> void prD(const pair<T1,T2>& x);
    template<class T, size_t SZ> void prD(const array<T,SZ>& x);
    template<class T> void prD(const vector<T>& x);
    template<class T> void prD(const set<T>& x);
    template<class T1, class T2> void prD(const map<T1,T2>& x);

    template<class T1, class T2> void pr(const pair<T1,T2>& x);
    template<class T, size_t SZ> void pr(const array<T,SZ>& x);
    template<class T> void pr(const vector<T>& x);
    template<class T> void pr(const set<T>& x);
    template<class T1, class T2> void pr(const map<T1,T2>& x);

    template<class T> void prD(const T& x) { cout << x; }
    template<class Arg, class... Args> void prD(const Arg& first, const Args&... rest) {
        prD(first); prD(rest...);
    }

    template<class T1, class T2> void prD(const pair<T1,T2>& x) {
        prD("{",x.pA,", ",x.pB,"}");
    }
    template<class T> void prDContain(const T& x) {
        prD("{");
        bool fst = 1; for (const auto& a: x) prD(!fst?", ":"",a), fst = 0; // const needed for vector<bool>
        prD("}");
    }
    template<class T, size_t SZ> void prD(const array<T,SZ>& x) { prDContain(x); }
    template<class T> void prD(const vector<T>& x) { prDContain(x); }
    template<class T> void prD(const set<T>& x) { prDContain(x); }
    template<class T1, class T2> void prD(const map<T1,T2>& x) { prDContain(x); }

    void psD() { prD("\n"); }
    template<class Arg> void psD(const Arg& first) {
        prD(first); psD(); // no space at end of line
    }
    template<class Arg, class... Args> void psD(const Arg& first, const Args&... rest) {
        prD(first," "); psD(rest...); // print w/ spaces
    }


    template<class T> void pr(const T& x) { cout << x; }
    template<class Arg, class... Args> void pr(const Arg& first, const Args&... rest) {
        pr(first); pr(rest...);
    }

    template<class T1, class T2> void pr(const pair<T1,T2>& x) {
        pr(x.pA, " ", x.pB);
    }
    template<class T> void prContain(const T& x) {
        bool fst = 1; for (const auto& a: x) pr(!fst?" ":"",a), fst = 0; // const needed for vector<bool>
    }
    template<class T, size_t SZ> void pr(const array<T,SZ>& x) { prContain(x); }
    template<class T> void pr(const vector<T>& x) { prContain(x); }
    template<class T> void pr(const set<T>& x) { prContain(x); }
    template<class T1, class T2> void pr(const map<T1,T2>& x) { prContain(x); }

    void ps() { pr("\n"); }
    template<class Arg> void ps(const Arg& first) {
        pr(first); ps(); // no space at end of line
    }
    template<class Arg, class... Args> void ps(const Arg& first, const Args&... rest) {
        pr(first," "); ps(rest...); // print w/ spaces
    }
}
using namespace output;
// @formatter:on

/* ============================ */

int n, k, x;
vii adj2[10000];
vii adj[10000];
int childCt[10000];
vi childCt2[10000];

int dfs(int u, int p) {
    childCt[u] = 1;
    trav(x, adj2[u]) {
        if (x.pA == p) continue;
        adj[u].pb(x);
        int numC = dfs(x.pA, u);
        childCt[u] += numC;
        childCt2[u].pb(numC);
    }
    F0R(i, sz(childCt2[u])) {
        FOR(j, i+1, sz(childCt2[u])) {
            childCt2[u][i] += childCt2[u][j];
        }
    }
    return childCt[u];
}

vector<vi> memo[10000][2];
int dp(int u, int k, int ret, int idx) {
    if (k == 0) return 0;
    if (k > childCt2[u][idx]) return INF;
    if (idx == sz(adj[u]) - 1) {
        if (ret == 0) return dp(adj[u][idx].pA, k-1, 0, 0) + adj[u][idx].pB;
        return dp(adj[u][idx].pA, k-1, ret, 0) + adj[u][idx].pB*2;
    }
    if (sz(memo[u][ret]) == 0) {
        F0R(i, sz(adj[u])) {
            memo[u][ret].eb(childCt2[u][i] + 1, -1);
        }
    }
    if (memo[u][ret][idx][k] != -1) return memo[u][ret][idx][k];

    // if ret = 0, then we can still avoid returning to parent for one child
    int best = INF;
    MIN(best, dp(u, k, ret, idx+1));
    FOR(i, max(1, k - childCt2[u][idx+1]),min(k, childCt[adj[u][idx].pA]) + 1) {
        MIN(best, dp(u, k - i, ret, idx + 1) + dp(adj[u][idx].pA, i-1, 1, 0) + adj[u][idx].pB*2);
        if (ret == 0) MIN(best, dp(u, k - i, 1, idx + 1) + dp(adj[u][idx].pA, i-1, 0, 0) + adj[u][idx].pB);
    }
    return memo[u][ret][idx][k] = best;
}

int main() {
    setupIO();

    re(n, k, x);
    F0R(i, n-1) {
        int a, b, c; re(a, b, c);
        adj2[--a].pb(mp(--b, c));
        adj2[b].pb(mp(a, c));
    }
    dfs(x-1, x-1);

    ps(dp(x-1, k-1, 0, 0));

    return 0;
}