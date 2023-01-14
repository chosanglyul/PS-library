#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#include "../lib/segtree/segtree_lazy.hpp"

struct Node_seg {
    ll val;
    Node_seg operator+(const Node_seg &y) { return {val+y.val}; }
    void operator()(const ll &lazy, const int l, const int r) { val += lazy*(r-l); }
    Node_seg() {}
    Node_seg(const ll &x) { val = x; }
    Node_seg(const ll &lazy, const int l, const int r) { val = lazy*(r-l); }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, a, b; cin >> n >> a >> b;
    int q = a+b;
    vector<Node_seg> A(n);
    for(auto &i : A) cin >> i.val;
    SegtreeLazyWithoutInf<Node_seg, ll> S(A);
    while(q--) {
        int t, l, r; cin >> t >> l >> r; --l;
        if(t == 1) {
            ll x; cin >> x;
            S.update(l, r, x);
        } else {
            cout << S.query(l, r).val << "\n";
        }
    }
    return 0;
}
