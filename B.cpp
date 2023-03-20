#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

#include "string"

class DSU {
 public:
  DSU(long long n) : parent_(n), rank_(n, 0) {
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
        ++rank_[root_u];
      }
    }
  }

 private:
  std::vector<long long> parent_;
  std::vector<long long> rank_;
};

struct Operarion {
  short type;
  int u;
  int v;
};

int main() {
  int n, m, k;
  int a, b;
  std::cin >> n >> m >> k;
  std::vector<std::vector<int>> graph(n);
  for (int i = 0; i < m; ++i) {
    std::cin >> a >> b;
    --a;
    --b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }
  std::vector<Operarion> op;
  DSU ds = DSU(n);
  char str[7];
  for (int i = 0; i < k; ++i) {
    std::cin >> str >> a >> b;
    --a;
    --b;
    if (str[0] == 'a') {
      op.push_back({0, a, b});
    } else {
      op.push_back({1, a, b});
    }
  }
  std::reverse(op.begin(), op.end());
  std::vector<std::string> result;
  for (int i = 0; i < k; ++i) {
    if (op[i].type == 1) {
      ds.Union(op[i].u, op[i].v);
    } else {
      if (ds.IsSame(op[i].u, op[i].v)) {
        result.emplace_back("YES");
      } else {
        result.emplace_back("NO");
      }
    }
  }
  std::reverse(result.begin(), result.end());
  for (const auto& i : result) {
    std::cout << i << '\n';
  }
}
