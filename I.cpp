#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

static constexpr int kInfinity = std::numeric_limits<int>::max();

static const int kInf = 10e3 + 10;

struct Edge {
  int from;
  int to;
  int flow;
  int capacity;

  Edge(int from, int to, int capacity)
      : from(from), to(to), flow(0), capacity(capacity) {}

  Edge(int from, int to, int flow, int capacity)
      : from(from), to(to), flow(flow), capacity(capacity) {}
};

class Graph {
 public:
  Graph(size_t n) : graph_(n, std::vector<size_t>()) { pointer_.assign(n, 0); }

  void AddEdge(int from, int to, int capacity) {
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

  int DFS(size_t vertex, size_t end, int current_flow) {
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
      int flow = DFS(
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

  int DinicAlgo(size_t start, size_t end) {
    int flow = 0;
    while (BFS(start, end)) {
      int delta = 0;
      pointer_.assign(graph_.size(), 0);
      do {
        delta = DFS(start, end, kInfinity);
        flow += delta;
      } while (delta > 0);
    }
    return flow;
  }

 private:
  std::vector<Edge> edges_;
  std::vector<std::vector<size_t>> graph_;
  std::vector<int> dist_;
  std::vector<int> pointer_;
};

void Solution() {
  int num;
  std::cin >> num;
  Graph gr(num + 2);
  int val;
  int max_sum = 0;
  for (int i = 0; i < num; ++i) {
    std::cin >> val;
    if (val >= 0) {
      max_sum += val;
      gr.AddEdge(0, i + 1, val);
    } else {
      gr.AddEdge(i + 1, num + 1, -val);
    }
  }
  int num_of_edges;
  for (int i = 0; i < num; ++i) {
    std::cin >> num_of_edges;
    for (int j = 0; j < num_of_edges; ++j) {
      std::cin >> val;
      gr.AddEdge(i + 1, val, kInf);
    }
  }
  int flow = gr.DinicAlgo(0, num + 1);
  if (flow == 0 || max_sum - flow < 0) {
    std::cout << 0 << '\n';
  } else {
    std::cout << max_sum - flow;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Solution();
}
