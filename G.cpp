#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

static constexpr long long kInfinity = std::numeric_limits<long long>::max();

struct Edge {
  long long from;
  long long to;
  long long flow;
  long long capacity;

  Edge(long long from, long long to, long long capacity)
      : from(from), to(to), flow(0), capacity(capacity) {}

  Edge(long long from, long long to, long long flow, long long capacity)
      : from(from), to(to), flow(flow), capacity(capacity) {}
};

class Graph {
 public:
  Graph(size_t n) : graph_(n, std::vector<size_t>()) { pointer_.assign(n, 0); }

  void AddEdge(long long from, long long to, long long capacity) {
    edges_.emplace_back(from, to, capacity);
    size_t edge_id = edges_.size() - 1;
    edges_.emplace_back(to, from, 0);
    size_t back_edge_id = edges_.size() - 1;
    graph_[from].push_back(edge_id);
    graph_[to].push_back(back_edge_id);
  }

  bool BFS(size_t start, size_t end) {
    dist_.assign(graph_.size(), kInfinity);
    std::queue<size_t> queue;
    dist_[start] = 0;
    queue.push(start);
    while (!queue.empty() && dist_[end] == kInfinity) {
      size_t vertex = queue.front();
      queue.pop();
      for (size_t i = 0; i < graph_[vertex].size(); ++i) {
        size_t id = graph_[vertex][i];
        if (dist_[edges_[id].to] == kInfinity &&
            edges_[id].flow < edges_[id].capacity) {
          queue.push(edges_[id].to);
          dist_[edges_[id].to] = dist_[edges_[id].from] + 1;
        }
      }
    }
    return dist_[end] != kInfinity;
  }

  long long DFS(size_t vertex, size_t end, long long current_flow) {
    if (current_flow <= 0) {
      return 0;
    }
    if (vertex == end) {
      return current_flow;
    }
    for (; pointer_[vertex] < static_cast<int>(graph_[vertex].size());
         ++pointer_[vertex]) {
      size_t to_id = graph_[vertex][pointer_[vertex]];
      size_t to = edges_[to_id].to;
      if (dist_[to] != dist_[vertex] + 1 ||
          edges_[to_id].flow == edges_[to_id].capacity) {
        continue;
      }
      long long flow = DFS(
          to, end,
          std::min(current_flow, edges_[to_id].capacity - edges_[to_id].flow));
      if (flow > 0) {
        edges_[to_id].flow += flow;
        edges_[to_id ^ 1].flow -= flow;
        return flow;
      }
    }
    return 0;
  }

  long long DinicAlgo(std::vector<long long>& flows, size_t start, size_t end) {
    long long flow = 0;
    while (BFS(start, end)) {
      long long delta = 0;
      pointer_.assign(graph_.size(), 0);
      do {
        delta = DFS(start, end, kInfinity);
        flow += delta;
      } while (delta > 0);
    }
    for (size_t i = 0; i < edges_.size(); i += 2) {
      flows[i / 2] = edges_[i].flow;
    }
    return flow;
  }

 private:
  std::vector<Edge> edges_;
  std::vector<std::vector<size_t>> graph_;
  std::vector<long long> dist_;
  std::vector<int> pointer_;
};

void Solution() {
  long long num;
  long long num_edges;
  std::cin >> num >> num_edges;
  Graph gr(num);
  std::vector<std::pair<long long, long long>> edges;
  for (long long i = 0; i < num_edges; ++i) {
    long long from;
    long long to;
    long long capacity;
    std::cin >> from >> to >> capacity;
    --from;
    --to;
    gr.AddEdge(from, to, capacity);
  }
  std::vector<long long> flows(num_edges, 0);
  std::cout << gr.DinicAlgo(flows, 0, num - 1) << '\n';
  for (long long flow : flows) {
    std::cout << flow << '\n';
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Solution();
}
