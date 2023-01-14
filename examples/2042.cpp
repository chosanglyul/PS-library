#include <bits/stdc++.h>
using namespace std;

#include "../lib/segtree/segtree.hpp"
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, a, b; cin >> n >> a >> b;
    int q = a+b;
    vector<__int128_t> A(n);
    for(auto &i : A) { long long x; cin >> x; i = x; }
    SegtreeWithoutInf<__int128_t> S(A);
    while(q--) {
        int t; cin >> t;
        if(t == 1) {
            int j; long long x; cin >> j >> x; --j;
            S.update(j, x-A[j]); A[j] = x;
        } else {
            int l, r; cin >> l >> r;
            cout << (long long)S.query(--l, r) << "\n";
        }
    }
    return 0;
}
