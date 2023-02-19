#include <iostream>
#include <limits>
#include <vector>

#include "algorithm"

static constexpr size_t kInfty = std::numeric_limits<size_t>::max();

void BridgesDfs(const std::vector<std::vector<size_t>>& graph,
                const std::vector<std::pair<size_t, size_t>>& edges,
                std::pair<std::pair<std::vector<size_t>&, std::vector<size_t>&>,
                          std::pair<size_t, size_t>>
                    p2,
                std::pair<std::vector<size_t>&, size_t&> p3) {
  std::vector<size_t>& time_in = p2.first.first;
  std::vector<size_t>& f_up = p2.first.second;
  size_t vertex = p2.second.first;
  size_t edge_id = p2.second.second;
  std::vector<size_t>& bridges = p3.first;
  size_t& time = p3.second;
  time_in[vertex] = time++;
  f_up[vertex] = time_in[vertex];
  for (auto from_edge_id : graph[vertex]) {
    if (from_edge_id == edge_id) {
      continue;
    }
    auto& edge = edges[from_edge_id];
    size_t to = edge.first == vertex ? edge.second : edge.first;
    if (to == vertex) {
      continue;
    }
    if (time_in[to] != kInfty) {
      f_up[vertex] = std::min(f_up[vertex], time_in[to]);
    } else {
      BridgesDfs(graph, edges, {{time_in, f_up}, {to, from_edge_id}},
                 {bridges, time});
      f_up[vertex] = std::min(f_up[to], f_up[vertex]);
    }
    if (f_up[to] > time_in[vertex]) {
      bridges.push_back(from_edge_id);
    }
  }
}

std::vector<size_t> GetBridges(
    const std::vector<std::vector<size_t>>& graph,
    const std::vector<std::pair<size_t, size_t>>& edges) {
  size_t num_vertex = graph.size();
  std::vector<size_t> time_in(num_vertex, kInfty);
  std::vector<size_t> f_up(num_vertex, kInfty);
  std::vector<size_t> bridges;
  size_t current_time = 0;
  for (size_t i = 0; i < num_vertex; ++i) {
    if (time_in[i] == kInfty) {
      BridgesDfs(graph, edges, {{time_in, f_up}, {i, kInfty}},
                 {bridges, current_time});
    }
  }
  return bridges;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  std::vector<std::vector<size_t>> graph(
      n, std::vector<size_t>());  // edges from v (id)
  std::vector<std::pair<size_t, size_t>> edges;
  edges.reserve(m);
  for (size_t id = 0; id < m; ++id) {
    size_t from;
    size_t to;
    std::cin >> from >> to;
    --to;
    --from;
    edges.emplace_back(std::min(from, to), std::max(from, to));
    graph[from].push_back(id);
    graph[to].push_back(id);
  }
  auto bridges = GetBridges(graph, edges);
  std::cout << bridges.size() << '\n';
  std::sort(bridges.begin(), bridges.end());
  for (auto id : bridges) {
    std::cout << id + 1 << " ";
  }
  return 0;
}
