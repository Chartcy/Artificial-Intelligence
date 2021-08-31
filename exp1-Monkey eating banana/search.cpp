#include <bits/stdc++.h>

using namespace std;
#define inf 0x3f3f3f3f
#define maxn 2001000

int cnt;

template<typename T>
struct Persistable_Segment_Tree {//可持久化数组
    int lc[maxn << 5], rc[maxn << 5], rt[maxn], cnt;
    T val[maxn << 5];

    void build(int &cur, int l, int r, vector<T> &v) {//建立
        cur = ++cnt;
        if (l == r) {
            val[cur] = v[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(lc[cur], l, mid, v);
        build(rc[cur], mid + 1, r, v);
        return;
    }

    void updata(int &cur, int pre, int l, int r, int x, T v) {//单点版本更新
        cur = ++cnt;
        lc[cur] = lc[pre];
        rc[cur] = rc[pre];
        val[cur] = val[pre];
        if (l == r) {
            val[cur] = v;
            return;
        }
        int mid = (l + r) >> 1;
        if (x <= mid) {
            updata(lc[cur], lc[pre], l, mid, x, v);
        } else {
            updata(rc[cur], rc[pre], mid + 1, r, x, v);
        }
    }

    T query(int cur, int l, int r, int x) {//单点版本查询
        if (l == r) {
            return val[cur];
        }
        int mid = (l + r) >> 1;
        if (x <= mid) {
            return query(lc[cur], l, mid, x);
        } else {
            return query(rc[cur], mid + 1, r, x);
        }
    }

    void dfs(int cur, vector<T> &v) {//版本遍历
        if (lc[cur]) {
            dfs(lc[cur], v);
        }
        if (lc[cur] == 0 && rc[cur] == 0) {
            v.push_back(val[cur]);
        }
        if (rc[cur]) {
            dfs(rc[cur], v);
        }
        return;
    }
};

Persistable_Segment_Tree<pair<int, int> > T;

struct node {
    pair<int, int> pos;
    int pre, onbox;
    bitset<64> banana;
    double w;

    node() {}

    node(pair<int, int> pos, bitset<64> banana, int pre, int onbox, double w) : pos(pos), banana(banana), pre(pre),
                                                                                onbox(onbox),
                                                                                w(w) {}

    bool operator<(const node &x) const {
        return w > x.w;
    }
} state[maxn];

struct cmp {
    bool operator()(const int &x, const int &y) const {
        return state[x].w > state[y].w;
    }
};

double dis(pair<int, int> x, pair<int, int> y, double w = 1.0) {
    return w *
           sqrt(1LL * (x.first - y.first) * (x.first - y.first) + 1LL * (x.second - y.second) * (x.second - y.second));
}

void print(int now) {
    if (now == 0) {
        return;
    }
    print(state[now].pre);
    if (state[now].pre == 0) {
        cout << "The initial position of the monkey is (" << state[now].pos.first << "," << state[now].pos.second << ")"
             << endl;
    } else if (state[now].onbox == -1) {
        if (state[now].pos.first != state[state[now].pre].pos.first ||
            state[now].pos.second != state[state[now].pre].pos.second) {//如果当前节点和上个节点位置发生改变
            cout << "Monkey pushes the NO." << state[state[now].pre].onbox + 1 << " box from ("
                 << state[state[now].pre].pos.first << ","
                 << state[state[now].pre].pos.second << ") to (" << state[now].pos.first << ","
                 << state[now].pos.second << ")" << endl;
        }
        cout << "Monkey climbs up the box to pick the banana" << endl;
        cout << "Monkey climbs down the box" << endl;
    } else {
        if (state[now].pos.first != state[state[now].pre].pos.first ||
            state[now].pos.second != state[state[now].pre].pos.second) {//如果当前节点和上个节点位置发生改变
            cout << "Monkey goes directly from (" << state[state[now].pre].pos.first << ","
                 << state[state[now].pre].pos.second << ") to (" << state[now].pos.first << ","
                 << state[now].pos.second << ")" << endl;
        }
    }
}

void solve(int sx, int sy, vector<pair<int, int> > &banana, vector<pair<int, int> > &box, double W) {
    priority_queue<int, vector<int>, cmp> q;//以代价作为比较参数的小根堆
    double mx = inf;
    int ans = 0;
    state[++cnt] = node(make_pair(sx, sy), bitset<64>(0LL), 0, -1, 0.0);//初始状态
    T.build(T.rt[cnt], 0, box.size() - 1, box);
    q.push(cnt);
    while (q.size()) {
        int u = q.top();
        q.pop();
        if (state[u].banana.count() == banana.size()) {
            if (mx > state[u].w) {
                mx = state[u].w, ans = u;
            }
            continue;
        }
        if (state[u].w > mx) {
            continue;
        }
        if (state[u].onbox == -1) {//当手上没有箱子的时候选择前往一个箱子的目的地
            vector<pair<int, int> > v;
            T.dfs(T.rt[u], v);
            for (int i = 0; i < v.size(); i++) {
                state[++cnt] = node(v[i], state[u].banana, u, i,
                                    state[u].w + dis(state[u].pos, v[i]));
                T.rt[cnt] = T.rt[u];
                q.push(cnt);
            }
        } else {//当手上有箱子选择一个没有摘过的香蕉
            for (int i = 0; i < banana.size(); i++) {
                if (state[u].banana[i] == false) {
                    state[++cnt] = node(banana[i], state[u].banana.set(i), u, -1,
                                        state[u].w + dis(state[u].pos, banana[i], W));
                    state[u].banana.reset(i);
                    T.updata(T.rt[cnt], T.rt[u], 0, box.size() - 1, state[u].onbox, banana[i]);
                    q.push(cnt);
                }
            }
        }
    }
    print(ans);//输出路径
    cout << "The final cost is " << state[ans].w << endl;
}

int sx, sy, n, m, x, y;
double w;
vector<pair<int, int> > box, banana;


signed main() {
    ios::sync_with_stdio(false);
    cout << "Input the initial position of the monkey:(x,y)" << endl;
    cin >> sx >> sy;
    cout << "Input the number of the bananas:n" << endl;
    cin >> n;
    while (n > 64) {
        cout << "n is too large,please re-enter:n" << endl;
        cin >> n;
    }
    for (int i = 1; i <= n; i++) {
        cout << "Input the NO." << i << " banana's position:(x,y)" << endl;
        cin >> x >> y;
        banana.push_back(make_pair(x, y));
    }
    cout << "Input the number of the boxes:m" << endl;
    cin >> m;
    for (int i = 1; i <= m; i++) {
        cout << "Input the NO." << i << " box's position:(x,y)" << endl;
        cin >> x >> y;
        box.push_back(make_pair(x, y));
    }
    cout << "Input the cost of pushing the box:w" << endl;
    cin >> w;
    solve(sx, sy, banana, box, w);
    return 0;
}
