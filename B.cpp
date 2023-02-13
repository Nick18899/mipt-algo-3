#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  long long a;
  long long b;
  long long c;
  long long m;
  long long n;
  std::cin >> n >> m;
  long long start;
  long long end;
  std::cin >> start >> end;
  std::vector<std::vector<std::pair<long long, long long>>> graph(n + 1);
  for (long long i = 0; i < m; ++i) {
    std::cin >> a >> b >> c;
    graph[a].emplace_back(b, c);
  }
  if (start == end) {
    std::cout << 0;
  } else {
    std::vector<std::queue<long long>> at_dist(31);
    at_dist[0].push(start);
    std::vector<long long> distances;
    distances.assign(n + 1, 1000000000);
    distances[start] = 0;
    for (long long i = 0; i < (n)*31; ++i) {
      while (!at_dist[i % 31].empty()) {
        long long current = at_dist[i % 31].front();
        at_dist[i % 31].pop();
        if (distances[current] > i) {
          continue;
        }
        for (size_t j = 0; j < graph[current].size(); ++j) {
          long long to = graph[current][j].first;
          long long cost = graph[current][j].second;
          if (distances[to] > distances[current] + cost) {
            distances[to] = distances[current] + cost;
            at_dist[distances[to] % 31].push(to);
          }
        }
      }
    }
    if (distances[end] == 1000000000) {
      std::cout << -1;
    } else {
      std::cout << distances[end];
    }
  }
}
