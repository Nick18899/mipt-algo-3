#include <algorithm>
#include <iostream>
#include <vector>

bool DFSForCycleSearch(std::vector<std::vector<int>>& graph,
                       std::vector<char>& colors, std::vector<int>& previous,
                       std::pair<int, int>& start_and_end, int top) {
  colors[top] = 'g';
  for (size_t i = 0; i < graph[top].size(); ++i) {
    int to = graph[top][i];
    if (colors[to] == 'w') {
      previous[to] = top;
      if (DFSForCycleSearch(graph, colors, previous, start_and_end, to)) {
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
  std::vector<int> previous;
  previous.assign(n, -1);
  std::vector<char> colors;
  colors.assign(n, 'w');
  std::pair<int, int> start_and_end = {-10, -10};
  for (int i = 1; i < n; ++i) {
    if (DFSForCycleSearch(graph, colors, previous, start_and_end, i)) {
      break;
    }
  }
  if (start_and_end.first == -10) {
    std::cout << "NO";
  } else {
    std::cout << "YES" << '\n';
    std::vector<int> cycle;
    cycle.push_back(start_and_end.first);
    for (int i = start_and_end.second; i != start_and_end.first;
         i = previous[i]) {
      cycle.push_back(i);
    }
    std::reverse(cycle.begin(), cycle.end());
    for (int i : cycle) {
      std::cout << i + 1 << ' ';
    }
  }
  return 0;
}
