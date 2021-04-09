#include <bits/stdc++.h>
using namespace std;
#define MAXN 100000
#define MAXM 500000
#define INF 0x7fffffff
#define MAXSGTSIZE 131072

int n, m, s;
int head[MAXN + 10], nxt[MAXM + 10], to[MAXM + 10], length[MAXM + 10], cnt;
int sgtSize, sgtMin[(MAXSGTSIZE << 1) + 10], sgtMini[(MAXSGTSIZE << 1) + 10];
int dist[MAXN + 10];

inline void add_edge(int x, int y, int z) {
    nxt[++cnt] = head[x];
    head[x] = cnt;
    to[cnt] = y;
    length[cnt] = z;
}

inline void sgt_seti(int i, int x) {
    int j;

    for (i += sgtSize - 1, sgtMin[i] = x; i > 1; i >>= 1) {
        if (sgtMin[i] < sgtMin[i ^ 1]) {
            j = i;
        } else {
            j = i ^ 1;
        }
        if (sgtMin[i >> 1] == sgtMin[j] && sgtMini[i >> 1] == sgtMini[j]) {
            break;
        }
        sgtMin[i >> 1] = sgtMin[j];
        sgtMini[i >> 1] = sgtMini[j];
    }
}

/*inline int sgt_min(int* ansp, int i, int j) {
    int ans = INF;

    for (*ansp = 0, i += sgtSize - 1, j += sgtSize - 1; i != j; i >>= 1, j >>= 1) {
        if (~i & 1) {
            if (ans > sgtMin[i]) {
                ans = sgtMin[i];
                *ansp = sgtMini[i];
            }
            i ^= 1;
        }
        if (j & 1) {
            if (ans > sgtMin[j]) {
                ans = sgtMin[j];
                *ansp = sgtMini[j];
            }
            j ^= 1;
        }
    }
    if (ans > sgtMin[i]) {
        ans = sgtMin[i];
        *ansp = sgtMini[i];
    }
    return ans;
}*/

inline void sgt_build() {
    int i;

    for (i = 1; i < n; i <<= 1) {
        NULL;
    }
    sgtSize = i;
    for (i = sgtSize; i < sgtSize << 1; ++i) {
        sgtMini[i] = i - sgtSize + 1;
        sgtMin[i] = INF;
    }
    for (i = sgtSize - 1; i; --i) {
        sgtMini[i] = sgtMini[i << 1];
        sgtMin[i] = INF;
    }
}

inline void dijkstra_sp() {
    int i, j, x, y, z;

    for (i = 1; i <= n; ++i) {
        dist[i] = INF;
    }
    dist[s] = 0;
    sgt_seti(s, 0);
    //while (sgt_min(x, 1, n) != INF) {
    while (sgtMin[1] != INF) {
        x = sgtMini[1];
        sgt_seti(x, INF);
        for (i = head[x]; i; i = nxt[i]) {
            y = to[i], z = length[i];
            if (dist[x] < dist[y] - z) {
                sgt_seti(y, dist[x] + z);
                dist[y] = dist[x] + z;
            }
        }
    }
}

int main() {
    int i, j, x, y, z;

    scanf("%d%d%d", &n, &m, &s);
    sgt_build();
    for (i = 1; i <= m; ++i) {
        scanf("%d%d%d", &x, &y, &z);
        add_edge(x, y, z);
    }
    dijkstra_sp();
    for (i = 1; i <= n; ++i) {
        printf("%d%c", dist[i], " \n"[i == n]);
    }
    return 0;
}