#include "_segtree_type.hpp"
#include <vector>
#include <cstddef>

template <typename node_seg, typename node_query = node_seg, typename index_t = int>
class Segtree {
	private:
	const size_t n;
	std::vector<node_seg> seg;

	void init(const size_t i, const index_t s, const index_t e, const std::vector<node_seg> &A) {
	    if(s+1 == e) seg[i] = A[s];
	    else {
	        init(i<<1, s, s+e>>1, A);
	        init(i<<1|1, s+e>>1, e, A);
	        seg[i] = seg[i<<1]+seg[i<<1|1];
	    }
	}

	void update(const size_t i, const index_t s, const index_t e, const index_t j, const node_query &x) {
		if(j >= e || s > j) return;
		if(s+1 == e) seg[i] += x;
		else {
			update(i<<1, s, s+e>>1, j, x);
			update(i<<1|1, s+e>>1, e, j, x);
			seg[i] = seg[i<<1]+seg[i<<1|1];
		}
	}

	node_seg query(const size_t i, const index_t s, const index_t e, const index_t l, const index_t r) const {
		if(e <= l || r <= s) return node_seg::inf();
		if(l <= s && e <= r) return seg[i];
		return query(i<<1, s, s+e>>1, l, r)+query(i<<1|1, s+e>>1, e, l, r);
	}

	public:
	Segtree(const std::vector<node_seg> &A) : n(A.size()) {
		seg.resize(4*n, node_seg::inf());
	    init(1, 0, n, A);
	}
	void update(const index_t j, const node_query &x) { update(1, 0, n, j, x); }
	node_seg query(const index_t l, const index_t r) const { return query(1, 0, n, l, r); }
};

template <typename node_seg, typename node_query = node_seg, typename index_t = int>
class SegtreeWithoutInf {
	private:
	using node_inf_seg = node_inf<node_seg>;
	using seg_t = Segtree<node_inf_seg, node_query, index_t>;
	seg_t seg;

	public:
	SegtreeWithoutInf(const int n) : seg(seg_t(std::vector<node_inf_seg>(n, node_inf_seg::inf()))) {}
	SegtreeWithoutInf(const std::vector<node_seg> &A) : seg(seg_t(std::vector<node_inf_seg>(A.begin(), A.end()))) {}
	void update(const index_t j, const node_query &x) { seg.update(j, x); }
	node_seg query(const index_t l, const index_t r) const { 
		node_inf_seg res = seg.query(l, r).node;
		if(res.is_inf) return node_seg();
		else return res.node;
	}
};
