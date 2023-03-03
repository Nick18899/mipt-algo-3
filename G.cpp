#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stack>
#include <vector>

std::vector<std::vector<int>> FloydUorsh(std::vector<std::vector<int>> graph,
                                         int n) {
  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        graph[i][j] = std::min(graph[i][j], graph[i][k] + graph[k][j]);
      }
    }
  }
  return graph;
}

int Output(int out) {
  if (out > 0 && out < 1000000) {
    return 1;
  }
  return 0;
}

int main() {
  int n, val;
  std::cin >> n;
  std::vector<std::vector<int>> graph;
  graph.assign(n, std::vector<int>(n, 1000000));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> val;
      if (val != 0) {
        graph[i][j] = val;
      }
      if (i == j) {
        graph[i][j] = 0;
      }
    }
  }
  auto res = FloydUorsh(graph, n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i == j) {
        std::cout << 1 << " ";
      } else {
        if (j == n - 1) {
          std::cout << Output(res[i][j]) << '\n';
        } else {
          std::cout << Output(res[i][j]) << " ";
        }
      }
    }
  }
  return 0;
}
