#ifndef __SEGTREE_SEGTREE_2D_H_
#define __SEGTREE_SEGTREE_2D_H_

#include "_segtree_type.hpp"
#include "segtree_dynamic.hpp"
#include <vector>

template <typename node_seg, typename node_query = node_seg, typename index_t = int, typename seg_t = SegtreeDynamic<node_seg, node_query, index_t>>
class Segtree2D {
    private:
    const size_t n;
    vector<seg_t> seg;

    void update(const size_t i, const index_t js, const index_t je, const index_t j, const index_t k, const node_query &x) {
        if(j >= je || j < js) return;
        seg[i].update(k, x);
        if(js+1 != je) {
            update(i<<1, js, js+je>>1, j, k, x);
            update(i<<1|1, js+je>>1, je, j, k, x);
        }
    }

    node_seg query(const size_t i, const index_t js, const index_t je, const index_t jl, const index_t jr, const index_t kl, const index_t kr) {
        if(je <= jl || jr <= js) return node_seg::inf();
        if(jl <= js && je <= jr) return seg[i].query(kl, kr);
        return query(i<<1, js, js+je>>1, jl, jr, kl, kr)+query(i<<1|1, js+je>>1, je, jl, jr, kl, kr);
    }

    public:
    Segtree2D(const size_t n, const size_t m) : seg(vector<seg_t>(4*n, seg_t(m))), n(n) {}
    void update(const index_t j, const index_t k, const node_query &x) { update(1, 0, n, j, k, x); }
    node_seg query(const index_t jl, const index_t jr, const index_t kl, const index_t kr) { return query(1, 0, n, jl, jr, kl, kr); }
};

#endif
