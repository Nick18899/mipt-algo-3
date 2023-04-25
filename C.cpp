#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

#include "map"

static constexpr int kInfinity = std::numeric_limits<int>::max();

void PrintOfAns(std::vector<std::pair<int, int>>& result,
                std::map<std::pair<int, int>, int>& edg, long long cut_val) {
  std::cout << result.size() << ' ' << cut_val << '\n';
  for (auto [from, to] : result) {
    std::cout << (edg[{from, to}]) + 1 << ' ';
  }
}

bool BFS(std::vector<std::vector<int>>& graph, int start, int top,
         std::vector<int>& parent) {
  std::vector<bool> visited(graph.size(), false);
  std::queue<int> queue;
  queue.push(start);
  visited[start] = true;
  parent[start] = -1;
  while (!queue.empty()) {
    int from = queue.front();
    queue.pop();
    for (int to = 0; to < static_cast<int>(graph.size()); ++to) {
      if (!visited[to] && graph[from][to] > 0) {
        queue.push(to);
        parent[to] = from;
        visited[to] = true;
      }
    }
  }
  return visited[top];
}

void DFS(std::vector<std::vector<int>>& graph, std::vector<bool>& visited,
         int top) {
  visited[top] = true;
  for (int i = 0; i < static_cast<int>(graph[top].size()); ++i) {
    if (!visited[i] && graph[top][i] > 0) {
      DFS(graph, visited, i);
    }
  }
}

void MinCut(int num, int edges) {
  int start = 0;
  int finish = num - 1;
  std::vector<std::vector<int>> graph;
  graph.assign(num, std::vector<int>(num, 0));
  std::map<std::pair<int, int>, int> edg;
  for (long long i = 0; i < edges; ++i) {
    long long from;
    long long to;
    int weight;
    std::cin >> from >> to >> weight;
    --from;
    --to;
    edg.insert({{from, to}, static_cast<int>(i)});
    edg.insert({{to, from}, static_cast<int>(i)});
    graph[from][to] = weight;
    graph[to][from] = weight;
  }
  std::vector<std::vector<int>> cp_graph = graph;
  std::vector<int> parent(num);
  while (BFS(graph, start, finish, parent)) {
    int flow = kInfinity;
    for (int from = finish; from != start; from = parent[from]) {
      int to = parent[from];
      flow = std::min(flow, graph[to][from]);
    }
    for (int from = finish; from != start; from = parent[from]) {
      int to = parent[from];
      graph[to][from] -= flow;
      graph[from][to] += flow;
    }
  }
  std::vector<bool> visited(num, false);
  std::vector<std::pair<int, int>> result;
  long long min_cut = 0;
  DFS(graph, visited, start);
  for (int i = 0; i < num; ++i) {
    for (int j = 0; j < num; ++j) {
      if (visited[i] && !visited[j] && cp_graph[i][j] != 0) {
        min_cut += cp_graph[i][j];
        result.emplace_back(i, j);
      }
    }
  }
  PrintOfAns(result, edg, min_cut);
}

int main() {
  int num;
  int edges;
  std::cin >> num >> edges;
  MinCut(num, edges);
  return 0;
}
