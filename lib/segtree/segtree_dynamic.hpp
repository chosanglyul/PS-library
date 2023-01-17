#include "_segtree_type.hpp"
#include <vector>

template <typename node_seg, typename node_query = node_seg, typename index_t = int>
class SegtreeDynamic {
    private:
    const index_t n;
    static const size_t MAX = __UINT32_MAX__;
    struct Node {
        size_t l, r;
        node_seg val = node_seg::inf();
        static Node inf() { return {MAX, MAX, node_seg::inf()}; }
    };
    vector<Node> seg;

    void make(size_t &i) {
        if(i == MAX) {
            i = seg.size();
            seg.push_back(Node::inf());
        }
    }

    void update(const size_t i, const index_t s, const index_t e, const index_t j, const node_query &x) {
        if(s+1 == e) seg[i].val += x;
        else {
            int mi = s+e>>1;
            if(j < mi) { make(seg[i].l); update(seg[i].l, s, mi, j, x); }
            else { make(seg[i].r); update(seg[i].r, mi, e, j, x); }
            seg[i].val = node_seg::inf();
            if(seg[i].l != MAX) seg[i].val = seg[i].val + seg[seg[i].l].val;
            if(seg[i].r != MAX) seg[i].val = seg[i].val + seg[seg[i].r].val;
        }
    }

    node_seg query(const size_t i, const index_t s, const index_t e, const index_t l, const index_t r) const {
        if(i == MAX || r <= s || e <= l) return node_seg::inf();
        if(l <= s && e <= r) return seg[i].val;
        return query(seg[i].l, s, s+e>>1, l, r)+query(seg[i].r, s+e>>1, e, l, r);
    }
    
    public:
    SegtreeDynamic(const index_t n) : n(n) { seg = {Node::inf()}; }
    void update(const index_t j, const node_query &x) { update(0, 0, n, j, x); }
    node_seg query(const index_t l, const index_t r) const { return query(0, 0, n, l, r); }
};
