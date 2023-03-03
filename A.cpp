#include <cmath>
#include <iostream>
#include <set>
#include <vector>

const long long kMaxVal = 2009000999;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  long long k, n, m, a, b, c;
  std::cin >> k;
  std::vector<std::vector<std::vector<std::pair<long long, long long>>>> graph;
  long long start;
  std::vector<long long> starts;
  for (long long p = 0; p < k; ++p) {
    std::cin >> n >> m;
    std::vector<std::vector<std::pair<long long, long long>>> vec(n);
    for (long long j = 0; j < m; ++j) {
      std::cin >> a >> b >> c;
      vec[a].emplace_back(b, c);
      vec[b].emplace_back(a, c);
    }
    graph.push_back(vec);
    std::cin >> start;
    starts.push_back(start);
  }
  std::vector<std::vector<long long>> distances;
  for (long long p = 0; p < k; ++p) {
    distances.emplace_back(graph[p].size(), kMaxVal);
    std::set<std::pair<long long, long long>> queue;
    start = starts[p];
    distances[p][start] = 0;
    queue.insert({0, start});
    while (!queue.empty()) {
      long long top = queue.begin()->second;
      queue.erase(queue.begin());
      for (size_t j = 0; j < graph[p][top].size(); ++j) {
        long long to = graph[p][top][j].first;
        long long length = graph[p][top][j].second;
        if (distances[p][top] + length < distances[p][to]) {
          if (queue.find({distances[p][to], to}) != queue.end()) {
            queue.erase({distances[p][to], to});
          }
          distances[p][to] = distances[p][top] + length;
          queue.insert({distances[p][to], to});
        }
      }
    }
  }
  for (auto& distance : distances) {
    for (size_t j = 0; j < distance.size(); ++j) {
      if (j != distance.size() - 1) {
        std::cout << distance[j] << " ";
      } else {
        std::cout << distance[j] << '\n';
      }
    }
  }
  return 0;
}
