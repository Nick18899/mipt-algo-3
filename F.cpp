#include <algorithm>
#include <iostream>
#include <vector>

void DFSForComponents(std::vector<std::vector<int>>& graph,
                      std::vector<bool>& used, std::vector<int>& order,
                      int top) {
  used[top] = true;
  for (size_t i = 0; i < graph[top].size(); ++i) {
    int to = graph[top][i];
    if (!used[to]) {
      DFSForComponents(graph, used, order, to);
    }
  }
  order.push_back(top);
}

void DFS(std::vector<std::vector<int>>& graph_tr, std::vector<bool>& used,
         std::vector<int>& components, int top, int num_of_comp) {
  used[top] = true;
  components[top] = num_of_comp;
  for (size_t i = 0; i < graph_tr[top].size(); ++i) {
    int to = graph_tr[top][i];
    if (!used[to]) {
      DFS(graph_tr, used, components, to, num_of_comp);
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int m;
  int n;
  std::cin >> n >> m;
  std::vector<std::vector<int>> graph(n);
  std::vector<std::vector<int>> graph_transponed(n);
  int a;
  int b;
  for (int i = 0; i < m; ++i) {
    std::cin >> a >> b;
    graph[a - 1].push_back(b - 1);
    graph_transponed[b - 1].push_back(a - 1);
  }
  std::vector<int> component(n);
  std::vector<int> order;
  std::vector<bool> used;
  used.assign(n, false);
  for (int i = 0; i < n; ++i) {
    if (!used[i]) {
      DFSForComponents(graph, used, order, i);
    }
  }
  // used.clear();
  used.assign(n, false);
  std::vector<std::vector<int>> result;
  int num_of_comp = 1;
  for (int i = 0; i < n; ++i) {
    int top = order[n - i - 1];
    if (!used[top]) {
      DFS(graph_transponed, used, component, top, num_of_comp);
      num_of_comp++;
    }
  }
  std::cout << num_of_comp - 1 << '\n';
  for (int i = 0; i < n; ++i) {
    std::cout << component[i] << " ";
  }
  return 0;
}
