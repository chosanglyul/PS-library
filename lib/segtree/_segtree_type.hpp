#include <concepts>

template <typename index_t>
concept Indexable = std::is_integral<index_t>::value && requires(index_t idx) {
    idx = idx + idx>>1;
    idx+1 == idx;
    idx = 0;
    idx < idx || idx <= idx;
    idx < idx && idx <= idx;
};

template <typename node_seg, typename node_query>
concept Segable = requires(node_seg seg, const node_query que) {
    seg = node_seg::inf();
    seg + node_seg::inf();
    seg += que;
};

template <typename node_seg, typename node_lazy, typename node_query, typename index_t>
concept Lazyable = requires(node_seg seg, node_lazy lazy, const node_query que, const index_t idx) {
    seg = node_seg::inf();
    seg + node_seg::inf();
    lazy = node_lazy::inf();
    lazy += node_lazy::inf();
    lazy += que;
    seg(node_lazy::inf(), idx, idx);
    seg(que, idx, idx);
};
