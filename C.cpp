#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
const long long kMaxSize = INT64_MAX;

struct Vec {
  long long distance;
  long long id;
  long long time;

  Vec(long long d, long long id, long long tm)
      : distance(d), id(id), time(tm) {}

  Vec() : distance(0), id(0), time(0) {}
};

struct Edge {
  long long end;
  long long cost;
  long long time;
};

bool operator<(const Vec& edge1, const Vec& edge2) {
  if (edge1.distance == edge2.distance) {
    if (edge1.time == edge2.time) {
      return edge1.id < edge2.id;
    }
    return edge1.time < edge2.time;
  }
  return edge1.distance < edge2.distance;
}

bool operator>(const Vec& edge1, const Vec& edge2) { return edge2 < edge1; }

bool operator==(const Vec& edge1, const Vec& edge2) {
  if (edge1.distance == edge2.distance) {
    if (edge1.id == edge2.id) {
      return edge1.time == edge2.time;
    }
  }
  return false;
}

std::pair<long long, long long> DijkstraRes(
    std::vector<std::vector<long long>> dist, long long t, long long n) {
  std::pair<long long, long long> res(t, dist[n - 1][t]);
  for (long long time_it = 0; time_it <= t; time_it++) {
    if (dist[n - 1][time_it] < res.second) {
      res = {time_it, dist[n - 1][time_it]};
    }
  }
  return res;
}

std::pair<long long, long long> Dijkstra(
    std::vector<std::vector<std::pair<long long, long long>>>& path,
    std::vector<std::vector<Edge>>& edges, long long n, long long start,
    long long t) {
  std::vector<std::vector<long long>> dist(
      n, std::vector<long long>(t + 1, kMaxSize));
  dist[0][0] = 0;
  std::set<Vec> vertexes;
  vertexes.insert({dist[start][0], start, 0});

  while (!vertexes.empty()) {
    long long top = vertexes.begin()->id;
    long long time = vertexes.begin()->time;
    vertexes.erase(vertexes.begin());
    for (auto curr_vert : edges[top]) {
      long long cur_id = curr_vert.end;
      long long cur_time = curr_vert.time;
      long long cur_cost = curr_vert.cost;
      if (time + cur_time <= t &&
          dist[top][time] + cur_cost < dist[cur_id][time + cur_time]) {
        vertexes.erase(
            Vec(dist[cur_id][time + cur_time], cur_id, time + cur_time));
        dist[cur_id][time + cur_time] = dist[top][time] + cur_cost;
        path[cur_id][time + cur_time] = {top, time};
        vertexes.insert(
            Vec(dist[cur_id][time + cur_time], cur_id, time + cur_time));
      }
    }
  }
  return DijkstraRes(dist, t, n);
}

void PrintOfResult(const std::vector<long long>& res) {
  std::cout << res.size() << '\n';
  for (auto el : res) {
    std::cout << el + 1 << ' ';
  }
}

void PrepOfResult(
    std::vector<std::vector<std::pair<long long, long long>>>& path,
    long long n, long long last) {
  std::vector<long long> res;
  res.push_back(n - 1);
  long long vertex_idx = path[n - 1][last].first;
  long long vertex_time = path[n - 1][last].second;
  res.push_back(vertex_idx);
  while (vertex_idx != 0) {
    auto pair_vert = path[vertex_idx][vertex_time];
    vertex_idx = pair_vert.first;
    vertex_time = pair_vert.second;
    res.push_back(vertex_idx);
  }
  std::reverse(res.begin(), res.end());
  PrintOfResult(res);
}

void EdgesInput(std::vector<std::vector<Edge>>& edges, long long m) {
  long long start, end, cost, time;
  for (long long i = 0; i < m; i++) {
    std::cin >> start >> end >> cost >> time;
    start--;
    end--;
    edges[start].push_back({end, cost, time});
    edges[end].push_back({start, cost, time});
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  long long n, m, t;
  std::cin >> n >> m >> t;
  std::vector<std::vector<Edge>> edges(n);
  EdgesInput(edges, m);
  std::vector<std::vector<std::pair<long long, long long>>> path(
      n, std::vector<std::pair<long long, long long>>(t + 1, {-1, -1}));
  std::pair<long long, long long> result = Dijkstra(path, edges, n, 0, t);
  if (result.second == kMaxSize) {
    std::cout << -1;
  } else {
    std::cout << result.second << '\n';
    PrepOfResult(path, n, result.first);
  }
  return 0;
}
