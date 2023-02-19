#include <iostream>
#include <limits>
#include <vector>

#include "algorithm"

void DFS(std::pair<std::pair<int, int>,
                   std::pair<std::vector<std::vector<int>>&, std::vector<int>&>>
             p1,
         int& time, std::vector<int>& time_in, std::vector<int>& time_out,
         std::vector<bool>& used) {
  int top = p1.first.first;
  int prev = p1.first.second;
  std::vector<std::vector<int>>& graph = p1.second.first;
  std::vector<int>& points = p1.second.second;
  used[top] = true;
  time_in[top] = time_out[top] = ++time;
  int num_of_children = 0;
  for (size_t i = 0; i < graph[top].size(); ++i) {
    int to = graph[top][i];
    if (to == top) {
      continue;
    }
    if (used[to]) {
      time_out[top] = std::min(time_out[top], time_in[to]);
    } else {
      ++num_of_children;
      DFS({{to, top}, {graph, points}}, time, time_in, time_out, used);
      time_out[top] = std::min(time_out[to], time_out[top]);
      if ((prev != -1) && (time_out[to] >= time_in[top]) &&
          (std::count(points.begin(), points.end(), top) == 0)) {
        points.push_back(top);
      }
    }
  }
  if ((prev == -1) && (num_of_children > 1) &&
      (std::count(points.begin(), points.end(), top) == 0)) {
    points.push_back(top);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> graph(n);
  for (int id = 0; id < m; ++id) {
    int from;
    int to;
    std::cin >> from >> to;
    --to;
    --from;
    graph[from].push_back(to);
    graph[to].push_back(from);
  }
  std::vector<int> points;
  std::vector<int> time_in(n);
  std::vector<int> time_out(n);
  std::vector<bool> used;
  used.assign(n, false);
  int time = 0;
  for (int i = 0; i < n; ++i) {
    if (!used[i]) {
      DFS({{i, -1}, {graph, points}}, time, time_in, time_out, used);
    }
  }
  std::cout << points.size() << '\n';
  std::sort(points.begin(), points.end());
  for (int point : points) {
    std::cout << point + 1 << '\n';
  }
  return 0;
}
