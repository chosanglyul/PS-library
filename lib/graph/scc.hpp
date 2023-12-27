#ifndef __GRAPH_SCC_H_
#define __GRAPH_SCC_H_

#include <vector>
#include <algorithm>

struct SCC {
    private:
    int n;
    std::vector<bool> chk;
    std::vector<std::vector<int>> E, F;

    void dfs(int x, std::vector<std::vector<int>> &E, std::vector<int> &st) {
        if(chk[x]) return;
        chk[x] = true;
        for(auto i : E[x]) dfs(i, E, st);
        st.push_back(x);
    }

    public:
    SCC(std::vector<std::vector<int>> &E) {
        n = E.size();
        this->E = E;
        F.resize(n);
        chk.resize(n, false);
        for(int i = 0; i < n; i++)
            for(auto j : E[i]) F[j].push_back(i);
    }

    std::vector<std::vector<int>> getSCC() {
        std::vector<int> st;
        std::fill(chk.begin(), chk.end(), false);
        for(int i = 0; i < n; i++) dfs(i, E, st);
        std::reverse(st.begin(), st.end());
        std::fill(chk.begin(), chk.end(), false);
        std::vector<std::vector<int>> scc;
        for(int i = 0; i < n; i++) {
            if(chk[st[i]]) continue;
            std::vector<int> T;
            dfs(st[i], F, T);
            scc.push_back(T);
        }
        return scc;
    }
};

#endif
