#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

#include "map"
#include "set"

// alpha

const int kMaxVal = 100010;

struct Edge {
  int start;
  int end;
  int cost;
};

size_t RestoringOfTheSz(std::vector<std::vector<int>>& path, int start,
                        int end) {
  size_t sz = 0;
  int top = start;
  while (top != end) {
    ++sz;
    top = path[top][end];
  }
  return sz;
}

void RestoringOfThePath(std::vector<std::vector<int>>& path, int start, int end,
                        std::map<std::pair<int, int>, int>& edges_id) {
  std::vector<int> way;
  int top = start;
  while (top != end) {
    way.push_back(top);
    top = path[top][end];
  }
  way.push_back(end);
  for (size_t i = 1; i < way.size(); ++i) {
    std::cout << edges_id[{way[i - 1], way[i]}] + 1 << ' ';
  }
}

std::vector<std::vector<int>> FloydUorsh(std::vector<Edge>& edges,
                                         std::vector<std::vector<int>>& graph) {
  auto n = static_cast<int>(graph.size());
  std::vector<std::vector<int>> path;
  path.assign(n, std::vector<int>(n, 0));
  auto m = static_cast<int>(edges.size());
  for (int i = 0; i < m; ++i) {
    path[edges[i].start][edges[i].end] = edges[i].end;
  }
  for (int i = 0; i < n; ++i) {
    path[i][i] = i;
  }
  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      if (graph[i][k] != kMaxVal) {
        for (int j = 0; j < n; ++j) {
          if (graph[i][k] < kMaxVal && graph[k][j] < kMaxVal) {
            if (graph[i][j] > graph[i][k] + graph[k][j]) {
              graph[i][j] = graph[i][k] + graph[k][j];
              path[i][j] = path[i][k];
            }
          }
        }
      }
    }
  }
  return path;
}

bool FordBellmanForCycles(std::vector<std::vector<int>>& graph,
                          std::vector<int>& cities, int n) {
  for (int i = 0; i < n; ++i) {
    if (graph[i][i] < 0) {
      for (size_t j = 1; j < cities.size(); ++j) {
        if (graph[cities[j - 1]][i] < kMaxVal &&
            graph[i][cities[j]] < kMaxVal) {
          return true;
        }
      }
    }
  }
  return false;
}

// alpha

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int m;
  int lectures;
  int n;
  int cost;
  int start, end;
  std::cin >> n >> m >> lectures;
  std::vector<std::vector<int>> graph_mat;
  graph_mat.assign(n, std::vector<int>(n, kMaxVal));
  std::vector<Edge> edges;
  std::map<std::pair<int, int>, int> edges_id;
  for (int i = 0; i < m; ++i) {
    std::cin >> start >> end >> cost;
    --start;
    --end;
    edges.push_back({start, end, -cost});
    edges_id.insert({{start, end}, i});
    graph_mat[start][end] = -cost;
  }
  std::vector<int> cities;
  for (int i = 0; i < lectures; ++i) {
    std::cin >> cost;
    --cost;
    cities.push_back(cost);
  }
  auto paths = FloydUorsh(edges, graph_mat);
  bool cyc = FordBellmanForCycles(graph_mat, cities, n);
  if (cyc) {
    std::cout << "infinitely kind";
  } else {
    size_t sz = 0;
    std::vector<std::vector<int>> result;
    for (int i = 1; i < lectures; ++i) {
      sz += RestoringOfTheSz(paths, cities[i - 1], cities[i]);
    }
    std::cout << sz << '\n';
    for (int i = 1; i < lectures; ++i) {
      RestoringOfThePath(paths, cities[i - 1], cities[i], edges_id);
    }
  }
  return 0;
}
