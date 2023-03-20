#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

#include "string"

class DSU {
 public:
  DSU(long long n) : parent_(n), sum_(n, 0), rank_(n, 0) {
    for (long long i = 0; i < n; ++i) {
      parent_[i] = i;
    }
  }

  bool IsSame(long long u, long long v) { return Find(u) == Find(v); }

  long long Sum(long long v) { return sum_[Find(v)]; }

  long long Find(long long v) {
    if (parent_[v] == v) return v;
    parent_[v] = Find(parent_[v]);
    return parent_[v];
  }

  void Union(long long u, long long v, long long weight) {
    long long root_u = Find(u);
    long long root_v = Find(v);
    if (root_u != root_v) {
      if (rank_[root_u] < rank_[root_v]) {
        std::swap(root_v, root_u);
      }
      parent_[root_v] = root_u;
      sum_[root_u] += sum_[root_v];
      if (rank_[root_u] == rank_[root_v]) {
        ++rank_[root_u];
      }
    }
    sum_[root_u] += weight;
  }

 private:
  std::vector<long long> parent_;
  std::vector<long long> sum_;
  std::vector<long long> rank_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n, m;
  int a, b, c, d;
  std::cin >> n >> m;
  DSU ds = DSU(n);
  for (int i = 0; i < m; ++i) {
    std::cin >> a >> b;
    --b;
    if (a == 1) {
      std::cin >> c >> d;
      --c;
      ds.Union(b, c, d);
    } else {
      std::cout << ds.Sum(b) << '\n';
    }
  }
}
