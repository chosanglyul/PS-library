#include <bits/stdc++.h>
using namespace std;

#include "../lib/segtree/segtree.hpp"
#include "../lib/segtree/segtree_2d.hpp"

struct Node {
    int x;
    static Node inf() { return {0}; }
    Node operator+(const Node &y) { return {x+y.x}; }
    void operator+=(const Node &y) { x += y.x; }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    Segtree2D<Node, Node, int, Segtree<Node, Node, int>> S(n, n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            Node x; cin >> x.x;
            S.update(i, j, x);
        }
    }
    for(int i = 0; i < m; i++) {
        int w; cin >> w;
        if(w == 0) {
            int x, y; Node c; cin >> x >> y >> c.x;
            c.x -= S.query(x-1, x, y-1, y).x;
            S.update(--x, --y, c);
        } else {
            int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
            cout << S.query(--x1, x2, --y1, y2).x << "\n";
        }
    }
    return 0;
}