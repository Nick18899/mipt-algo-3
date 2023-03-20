#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

class DST {
 public:
  DST(long long n) : parent_(n), rank_(n, 0) {
    for (long long i = 0; i < n; ++i) {
      parent_[i] = i;
    }
  }

  bool IsSame(long long u, long long v) { return Find(u) == Find(v); }

  long long Find(long long v) {
    if (parent_[v] == v) return v;
    parent_[v] = Find(parent_[v]);
    return parent_[v];
  }

  void Union(long long u, long long v) {
    long long root_u = Find(u);
    long long root_v = Find(v);
    if (root_u != root_v) {
      if (rank_[root_u] < rank_[root_v]) {
        std::swap(root_v, root_u);
      }
      parent_[root_v] = root_u;
      if (rank_[root_u] == rank_[root_v]) {
        rank_[root_u] += 1;
      }
    }
  }

 private:
  std::vector<long long> parent_;
  std::vector<long long> rank_;
};

struct Edge {
  long long from;
  long long to;
  long long weight;
};

std::vector<Edge> MSTKruscal(long long n, std::vector<Edge>& edges) {
  std::sort(edges.begin(), edges.end(), [](const Edge& e1, const Edge& e2) {
    return e1.weight < e2.weight;
  });
  DST dst_vertexes(n);
  std::vector<Edge> answer;
  answer.reserve(n - 1);
  long long founded = 0;
  for (auto& edge : edges) {
    if (!dst_vertexes.IsSame(edge.from, edge.to)) {
      ++founded;
      dst_vertexes.Union(edge.from, edge.to);
      answer.push_back(edge);
    }
    if (founded == n - 1) {
      break;
    }
  }
  return answer;
}

int main() {
  long long n, m;
  std::cin >> n >> m;
  std::vector<Edge> edges;
  for (long long i = 0; i < m; ++i) {
    long long from, to, weight;
    std::cin >> from >> to >> weight;
    edges.push_back({--from, --to, weight});
  }
  auto mst = MSTKruscal(n, edges);
  std::cout << std::accumulate(
      mst.begin(), mst.end(), 0ull,
      [](long long acc, const Edge& edge) { return acc + edge.weight; });
}
