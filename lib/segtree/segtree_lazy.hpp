#include "_segtree_type.hpp"
#include <vector>

template <typename node_seg, typename node_lazy, typename index_t = int>
    requires Indexable<index_t> && Segable<node_seg> && Lazyable<node_seg, node_lazy, index_t>
class SegtreeLazy {

};
