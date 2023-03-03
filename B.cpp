#include <cmath>
#include <iostream>
#include <set>
#include <vector>

const long long kMaxVal = INT64_MAX;

std::vector<long long> Dijkstra(
    std::vector<std::vector<std::pair<long long, long long>>>& graph,
    long long start) {
  std::vector<long long> distances(graph.size(), kMaxVal);
  std::set<std::pair<long long, long long>> queue;
  distances[start] = 0;
  queue.insert({0, start});
  while (!queue.empty()) {
    long long top = queue.begin()->second;
    queue.erase(queue.begin());
    for (size_t j = 0; j < graph[top].size(); ++j) {
      long long to = graph[top][j].first;
      long long length = graph[top][j].second;
      if (distances[top] + length < distances[to]) {
        if (queue.find({distances[to], to}) != queue.end()) {
          queue.erase({distances[to], to});
        }
        distances[to] = distances[top] + length;
        queue.insert({distances[to], to});
      }
    }
  }
  return distances;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  long long n, m, k, a, b, c;
  std::cin >> n >> m >> k;
  std::vector<std::vector<std::pair<long long, long long>>> graph(n);
  std::vector<long long> infected_tops(k);
  for (int i = 0; i < k; ++i) {
    std::cin >> a;
    infected_tops[i] = a - 1;
  }
  for (int i = 0; i < m; ++i) {
    std::cin >> a >> b >> c;
    graph[--a].emplace_back(--b, c);
    graph[b].emplace_back(a, c);
  }
  long long start, med;
  std::cin >> start >> med;
  --start;
  --med;
  std::vector<long long> results;
  std::vector<long long> med_time = Dijkstra(graph, med);
  bool flag = true;
  if (med_time[start] == kMaxVal) {
    std::cout << -1;
  } else {
    for (int i = 0; i < k; ++i) {
      if (med_time[infected_tops[i]] <= med_time[start]) {
        std::cout << -1;
        flag = false;
        break;
      }
    }
    if (flag) {
      std::cout << med_time[start];
    }
  }
  return 0;
}
