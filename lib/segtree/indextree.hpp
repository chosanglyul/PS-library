#ifndef __SEGTREE_INDEXTREE_H_
#define __SEGTREE_INDEXTREE_H_

#include <vector>

class IndexTree {
    private:
    int n;
    std::vector<long long> seg;

    public:
    IndexTree(std::vector<long long> &A) {
        n = A.size();
        seg.resize(2*n, 0LL);
        for(int i = 0; i < n; i++) seg[i+n] = A[i];
        for(int i = n-1; i; i--) seg[i] = seg[i<<1]+seg[i<<1|1];
    }

    long long query(int l, int r) {
        long long ans = 0LL;
        for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if(l&1) ans += seg[l++];
            if(r&1) ans += seg[--r];
        }
        return ans;
    }

    void update(int i, long long x) {
        for(i += n; i; i >>= 1) seg[i] += x;
    }
};

#endif
