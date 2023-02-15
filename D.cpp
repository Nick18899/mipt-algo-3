#include <algorithm>
#include <iostream>
#include <vector>

void DFS(std::vector<std::vector<int>>& graph, std::vector<bool>& used,
         std::vector<int>& result, int top) {
  used[top] = true;
  result.push_back(top);
  for (size_t i = 0; i < graph[top].size(); ++i) {
    int to = graph[top][i];
    if (!used[to]) {
      DFS(graph, used, result, to);
    }
  }
}

void LookingForComponents(std::vector<std::vector<int>>& graph,
                          std::vector<bool>& used,
                          std::vector<std::vector<int>>& components, int n) {
  std::vector<int> component;
  for (int i = 0; i < n; ++i) {
    if (!used[i]) {
      component.clear();
      DFS(graph, used, component, i);
      components.push_back(component);
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
  int a;
  int b;
  for (int i = 0; i < m; ++i) {
    std::cin >> a >> b;
    graph[a - 1].push_back(b - 1);
    graph[b - 1].push_back(a - 1);
  }
  std::vector<std::vector<int>> result;
  std::vector<bool> used;
  used.assign(n, false);
  LookingForComponents(graph, used, result, n);
  std::cout << result.size() << '\n';
  for (auto& i : result) {
    std::cout << i.size() << '\n';
    for (size_t j = 0; j < i.size(); ++j) {
      if (j != i.size() - 1) {
        std::cout << i[j] + 1 << ' ';
      } else {
        std::cout << i[j] + 1 << '\n';
      }
    }
  }
}
