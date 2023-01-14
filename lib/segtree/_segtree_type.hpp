template <typename node_t>
struct node_inf {
    bool is_inf = true;
    node_t node;

    static node_inf<node_t> inf() { return node_inf(); }

    node_inf() {
        is_inf = true;
        node = node_t();
    }
    node_inf(const node_t &node) {
        is_inf = false;
        this->node = node;
    }

    node_inf<node_t> operator+(const node_inf<node_t> &y) {
        if(is_inf) return y;
        if(y.is_inf) return node_inf<node_t>(node);
        return node_inf<node_t>(node+y.node);
    }

    template <typename node_lazy>
    void operator+=(const node_inf<node_lazy> &y) {
        if(is_inf) {
            is_inf = y.is_inf;
            if(!y.is_inf) node = node_t(y.node);
        } else if(!y.is_inf) node += y.node;
    }

    template <typename node_query>
    void operator+=(const node_query &y) {
        if(is_inf) {
            is_inf = false;
            node = node_t(y);
        } else node += y;
    }

    template <typename node_lazy, typename index_t>
    void operator()(const node_inf<node_lazy> &y, const index_t l, const index_t r) {
        if(is_inf) {
            is_inf = y.is_inf;
            if(!y.is_inf) node = node_t(y.node, l, r);
        } else if(!y.is_inf) node(y.node, l, r);
    }

    template <typename node_query, typename index_t>
    void operator()(const node_query &y, const index_t l, const index_t r) {
        if(is_inf) {
            is_inf = false;
            node = node_t(y, l, r);
        } else node(y, l, r);
    }
};
