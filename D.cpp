#include <cmath>
#include <iostream>
#include <set>
#include <vector>

#include "algorithm"

const long long kMaxVal = 30000;

struct Edge {
  long long start;
  long long end;
  long long cost;
};

std::vector<long long> FordBellman(
    std::vector<std::vector<std::pair<long long, long long>>>& graph,
    std::vector<Edge>& edges, long long start, long long m) {
  std::vector<long long> distances(graph.size(), kMaxVal);
  distances[start] = 0;
  for (size_t i = 0; i < graph.size(); ++i) {
    for (int j = 0; j < m; ++j) {
      if (distances[edges[j].start] < kMaxVal) {
        distances[edges[j].end] = std::min(
            distances[edges[j].end], distances[edges[j].start] + edges[j].cost);
      }
    }
  }
  return distances;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  long long n, m, a, b, c;
  std::cin >> n >> m;
  std::vector<std::vector<std::pair<long long, long long>>> graph(n);
  std::vector<Edge> edges;
  for (int i = 0; i < m; ++i) {
    std::cin >> a >> b >> c;
    --a;
    --b;
    edges.push_back({a, b, c});
    graph[a].emplace_back(b, c);
  }
  std::vector<long long> result = FordBellman(graph, edges, 0, m);
  for (auto i : result) {
    std::cout << i << " ";
  }
  return 0;
}
