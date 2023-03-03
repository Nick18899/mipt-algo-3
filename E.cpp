#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stack>
#include <vector>

const long long kMaxVal = 100000;

struct Edge {
  long long start;
  long long end;
  long long cost;
};

std::vector<Edge> TransformGraphToEdges(
    std::vector<std::vector<long long>> graph, long long n) {
  std::vector<Edge> edges;
  for (long long i = 0; i < n; ++i) {
    for (long long j = 0; j < n; ++j) {
      if (graph[i][j] != kMaxVal) {
        edges.push_back({i, j, graph[i][j]});
      }
    }
  }
  return edges;
}

void FordBellmanForCycles(std::vector<Edge>& edges, long long start,
                          long long m, long long n) {
  std::vector<long long> distances(n);
  std::vector<long long> cycle(n, -1);
  distances[start] = 0;
  long long flag = -1;
  for (long long i = 0; i < n; ++i) {
    flag = -1;
    for (long long j = 0; j < m; ++j) {
      if (distances[edges[j].end] > distances[edges[j].start] + edges[j].cost) {
        distances[edges[j].end] =
            std::max(-kMaxVal, distances[edges[j].start] + edges[j].cost);
        cycle[edges[j].end] = edges[j].start;
        flag = edges[j].end;
      }
    }
  }
  if (flag == -1) {
    std::cout << "NO";
  } else {
    long long buffer = flag;
    for (long long i = 0; i < n; ++i) {
      buffer = cycle[buffer];
      if (buffer == -1) {
        std::cout << "NO";
        return;
      }
    }
    std::vector<long long> path;
    for (long long i = buffer;; i = cycle[i]) {
      path.push_back(i);
      if (i == buffer && path.size() > 1) {
        break;
      }
    }
    std::reverse(path.begin(), path.end());
    std::cout << "YES" << '\n' << path.size() << '\n';
    for (auto i : path) {
      std::cout << i + 1 << " ";
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  long long n, val;
  std::cin >> n;
  std::vector<std::vector<long long>> graph;
  graph.assign(n, std::vector<long long>(n, kMaxVal));
  for (long long i = 0; i < n; ++i) {
    for (long long j = 0; j < n; ++j) {
      std::cin >> val;
      graph[i][j] = val;
    }
  }
  auto edges = TransformGraphToEdges(graph, n);
  FordBellmanForCycles(edges, 0, static_cast<long long>(edges.size()), n);
  return 0;
}
