#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

void DFS(std::vector<std::vector<int>>& graph, std::vector<bool>& used,
         std::vector<int>& result, int top) {
  used[top] = true;
  for (size_t i = 0; i < graph[top].size(); ++i) {
    int to = graph[top][i];
    if (!used[to]) {
      DFS(graph, used, result, to);
    }
  }
  result.push_back(top);
}

bool DFSForCycleSearch(std::vector<std::vector<int>>& graph,
                       std::vector<char>& colors,
                       std::pair<int, int>& start_and_end, int top) {
  colors[top] = 'g';
  for (size_t i = 0; i < graph[top].size(); ++i) {
    int to = graph[top][i];
    if (colors[to] == 'w') {
      if (DFSForCycleSearch(graph, colors, start_and_end, to)) {
        return true;
      }
    } else if (colors[to] == 'g') {
      start_and_end.first = to;
      start_and_end.second = top;
      return true;
    }
  }
  colors[top] = 'b';
  return false;
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
  }
  std::vector<int> result;
  std::vector<bool> used(n);
  for (int i = 0; i < n; ++i) {
    used[i] = false;
  }
  std::vector<int> previous;
  std::vector<char> colors;
  colors.assign(n, 'w');
  std::pair<int, int> start_and_end = {-10, -10};
  for (int i = 0; i < n; ++i) {
    if (DFSForCycleSearch(graph, colors, start_and_end, i)) {
      break;
    }
  }
  if (start_and_end.first != -10) {
    std::cout << -1;
    return 0;
  }
  for (int v = 0; v < n; ++v) {
    if (!used[v]) {
      DFS(graph, used, result, v);
    }
  }
  std::reverse(result.begin(), result.end());
  for (auto i : result) {
    std::cout << i + 1 << " ";
  }
  return 0;
}
