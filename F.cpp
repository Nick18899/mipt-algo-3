#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
#include "cmath"
#include "set"

void DFS(int v, std::vector<bool>& used, std::vector<int>& parents, std::vector<std::vector<int>>& graph, std::vector<int>& depths) {
    used[v] = true;
    for (auto u : graph[v]) {
        if (!used[u]) {
            depths[u] = depths[v] + 1;
            parents[u] = v;
            DFS(u, used, parents,graph,depths);
        }
    }
}

int LCA(int u, int v, int logn, std::vector<std::vector<int>>& ancestors, std::vector<int>& depths) {
    if (u == v) {
        return v;
    }
    if (depths[v] > depths[u]) {
        std::swap(v, u);
    }
    int delta = depths[u] - depths[v];
    for (int d = logn; d >= 0; --d) {
        if ((1 << d) & delta) {
            u = ancestors[u][d];
            delta -= (1 << d);
        }
    }
    for (int d = logn; d >= 0; --d) {
        if (ancestors[v][d] != ancestors[u][d]) {
            v = ancestors[v][d];
            u = ancestors[u][d];
        }
    }
    return ancestors[v][0];
}

int LCALength(int u, int v, int logn, std::vector<std::vector<int>>& ancestors, std::vector<int>& depths) {
    return depths[u] + depths[v] - 2*depths[LCA(u, v, logn, ancestors, depths)];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n, a, b, q;
    std::cin >> n;
    int logn = static_cast<int>(floor(log2(n))) + 1;
    std::vector<std::vector<int>> graph(n);
    for (int i = 0; i < n - 1; ++i) {
        std::cin >> a >> b;
        --a;
        --b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    int root = 0;
    std::vector<bool> used(n, false);
    std::vector<int> depths(n, 0);
    std::vector<int> parents(n, root);
    parents[root] = root;
    DFS(root, used, parents, graph, depths);
    std::vector<std::vector<int>> ancestors;
    ancestors.assign(n, std::vector<int>(logn + 1, root));
    for (int i = 0; i < n; ++i) {
        ancestors[i][0] = parents[i];
    }
    for (int d = 1; d <= logn; ++d){
        for (int i = 0; i < n; ++i) {
            ancestors[i][d] = ancestors[ancestors[i][d-1]][d-1];
        }
    }
    std::cin >> q;
    for (int i = 0; i < q; ++i) {
        std::cin >> a >> b;
        --a;
        --b;
        std::cout << LCALength(a, b, logn, ancestors, depths) << '\n';
    }
    return 0;
}
