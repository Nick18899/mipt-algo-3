#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

static constexpr int kInfinity = std::numeric_limits<int>::max();

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
  Graph(size_t n) : graph(n, std::vector<size_t>()) { pointer_.assign(n, 0); }

  void AddEdge(int from, int to, int capacity) {
    edges.emplace_back(from, to, capacity);
    size_t edge_id = edges.size() - 1;
    edges.emplace_back(to, from, 0);
    size_t back_edge_id = edges.size() - 1;
    graph[from].push_back(edge_id);
    graph[to].push_back(back_edge_id);
  }

  bool BFS(size_t start, size_t end) {
    dist_.assign(graph.size(), kInfinity);
    std::queue<size_t> queue;
    dist_[start] = 0;
    queue.push(start);
    while (!queue.empty() && dist_[end] == kInfinity) {
      size_t vertex = queue.front();
      queue.pop();
      for (size_t i = 0; i < graph[vertex].size(); ++i) {
        size_t id = graph[vertex][i];
        if (dist_[edges[id].to] == kInfinity &&
            edges[id].flow < edges[id].capacity) {
          queue.push(edges[id].to);
          dist_[edges[id].to] = dist_[edges[id].from] + 1;
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
    for (; pointer_[vertex] < static_cast<int>(graph[vertex].size());
         ++pointer_[vertex]) {
      size_t to_id = graph[vertex][pointer_[vertex]];
      size_t to = edges[to_id].to;
      if (dist_[to] != dist_[vertex] + 1 ||
          edges[to_id].flow == edges[to_id].capacity) {
        continue;
      }
      int flow = DFS(
          to, end,
          std::min(current_flow, edges[to_id].capacity - edges[to_id].flow));
      if (flow > 0) {
        edges[to_id].flow += flow;
        edges[to_id ^ 1].flow -= flow;
        return flow;
      }
    }
    return 0;
  }

  int DinicAlgo(size_t start, size_t end) {
    int flow = 0;
    while (BFS(start, end)) {
      int delta = 0;
      pointer_.assign(graph.size(), 0);
      do {
        delta = DFS(start, end, kInfinity);
        flow += delta;
      } while (delta > 0);
    }
    return flow;
  }

  std::vector<Edge> edges;
  std::vector<std::vector<size_t>> graph;

 private:
  std::vector<int> dist_;
  std::vector<int> pointer_;
};

void Solution() {
  int num;
  std::cin >> num;
  std::vector<int> wins(num);
  int sz = num * num + 2;
  Graph gr(sz);
  for (int i = 0; i < num; ++i) {
    std::cin >> wins[i];
  }
  std::vector<int> num_of_games(num);
  for (int i = 0; i < num; ++i) {
    std::cin >> num_of_games[i];
    if (i != 0) {
      if (num_of_games[0] + wins[0] - wins[i] < 0) {
        std::cout << "NO";
        return;
      }
      gr.AddEdge(i, sz - 1, num_of_games[0] + wins[0] - wins[i]);
    }
  }
  int val;
  for (int i = 0; i < num; ++i) {
    for (int j = 0; j < num; ++j) {
      std::cin >> val;
      if (j > i && i != 0 && val > 0) {
        gr.AddEdge(sz - 2, (i + 1) * num + j, val);
        gr.AddEdge((i + 1) * num + j, i, kInfinity);
        gr.AddEdge((i + 1) * num + j, j, kInfinity);
      }
    }
  }
  gr.DinicAlgo(sz - 2, sz - 1);
  for (auto edg : gr.graph[sz - 2]) {
    if (gr.edges[edg].flow != gr.edges[edg].capacity) {
      std::cout << "NO";
      return;
    }
  }
  std::cout << "YES";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Solution();
}
