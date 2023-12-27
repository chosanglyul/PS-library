#ifndef __SEGTREE_FENWICKTREE_H_
#define __SEGTREE_FENWICKTREE_H_

#include <vector>

class FenwickTree {
    private:
    int n;
    std::vector<long long> seg;

    long long query(int i) {
        long long ans = 0LL;
        while(i) {
            ans += seg[i];
            i -= (i & -i);
        }
        return ans;
    }

    public:
    FenwickTree(int n) {
        this->n = n;
        seg.resize(n+1, 0LL);
    }

    long long query(int l, int r) { return query(r) - query(l-1); }

    void update(int i, long long x) {
        while(i <= n) {
            seg[i] += x;
            i += (i & -i);
        }
    }
};

#endif
