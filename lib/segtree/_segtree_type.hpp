#include <concepts>

template <typename index_t>
concept Indexable = std::is_integral<index_t>::value && requires(index_t idx) {
    idx = idx<<1;
    idx = idx<<1|1;
    idx = idx+idx>>1;
    idx+1 == idx;
    idx = 0;
};

template <typename node_seg>
concept Segable = requires(node_seg seg) {
    seg+node_seg::inf();
};

template <typename node_lazy, typename node_seg, typename index_t>
concept Lazyable = requires(node_lazy lazy, node_seg seg, index_t idx) {
    lazy+node_lazy::inf();
    lazy(seg, idx, idx);
};