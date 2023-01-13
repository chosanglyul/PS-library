#include "_segtree_type.hpp"
#include <vector>

template <typename node_seg, typename node_lazy, typename node_query = node_lazy, typename index_t = int>
    requires Indexable<index_t> && Lazyable<node_seg, node_lazy, node_query, index_t>
class SegtreeLazy {
    private:
    const size_t n;
    std::vector<node_seg> seg;
    std::vector<node_lazy> lazy;

    void prop(const size_t i, const index_t s, const index_t e) {
        if(!(s+1 == e)) {
            lazy[i<<1] += lazy[i];
            seg[i<<1](lazy[i], s, s+e>>1);
            lazy[i<<1|1] += lazy[i];
            seg[i<<1|1](lazy[i], s+e>>1, e);
        }
        lazy[i] = node_lazy::inf();
    }

    void init(const size_t i, const index_t s, const index_t e, std::vector<node_seg> &A) {
        if(s+1 == e) seg[i] = A[s];
        else {
            init(i<<1, s, s+e>>1, A);
            init(i<<1|1, s+e>>1, e, A);
            seg[i] = seg[i<<1]+seg[i<<1|1];
        }
    }

    void update(const size_t i, const index_t s, const index_t e, const index_t l, const index_t r, const node_query &x) {
        prop(i, s, e);
        if(r <= s || e <= l) return;
        if(l <= s && e <= r) {
            seg[i](x, s, e);
            lazy[i] += x;
        } else {
            update(i<<1, s, s+e>>1, l, r, x);
            update(i<<1|1, s+e>>1, e, l, r, x);
            seg[i] = seg[i<<1]+seg[i<<1|1];
        }
    }

    node_seg query(const size_t i, const index_t s, const index_t e, const index_t l, const index_t r) {
        prop(i, s, e);
        if(r <= s || e <= l) return node_seg::inf();
        if(l <= s && e <= r) return seg[i];
        return query(i<<1, s, s+e>>1, l, r)+query(i<<1|1, s+e>>1, e, l, r);
    }

    public:
    SegtreeLazy(std::vector<node_seg> &A) : n(A.size()) {
        seg.resize(4*n, node_seg::inf());
        lazy.resize(4*n, node_lazy::inf());
        init(1, 0, n, A);
    }
    void update(const index_t l, const index_t r, const node_query &x) { update(1, 0, n, l, r, x); }
    node_seg query(const index_t l, const index_t r) { return query(1, 0, n, l, r); }
};
