#include <bits/stdc++.h>

using namespace std;

struct GasStation {
  int start, end, x, id;
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, x1, y1;
  cin >> n >> y1 >> x1;
  vector<GasStation> gus_stations(n);
  for (int i = 0; i < n; ++i) {
    gus_stations[i].id = i;
    cin >> gus_stations[i].x >> gus_stations[i].start >> gus_stations[i].end;
  }
  multiset<int> locations = {0, x1};
  multiset<int> distances = {x1};
  vector<vector<pair<bool, int>>> events(y1 + 1);
  for (const GasStation& a : gus_stations) {
    events[a.start].push_back({true, a.id});
    events[a.end].push_back({false, a.id});
  }
  for (int height = 0; height <= y1; ++height) {
    vector<int> adding, removing;
    for (int i = 0; i < (long long)events[height].size(); ++i) {
      bool type = events[height][i].first;
      int id = events[height][i].second;
      if (type) {
        int x = gus_stations[id].x;
        int before = *std::prev(locations.lower_bound(x));
        int after = *locations.lower_bound(x + 1);
        distances.erase(distances.lower_bound(after - before));
        distances.insert(x - before);
        distances.insert(after - x);
        locations.insert(x);
      }
    }
    cout << *distances.rbegin() << '\n';
    for (int& x : adding) {
      locations.insert(x);
    }
    for (int i = 0; i < (long long)events[height].size(); ++i) {
      bool type = events[height][i].first;
      int id = events[height][i].second;
      if (!type) {
        int x = gus_stations[id].x;
        int before = *std::prev(locations.lower_bound(x));
        int after = *locations.lower_bound(x + 1);
        distances.erase(distances.lower_bound(after - x));
        distances.erase(distances.lower_bound(x - before));
        distances.insert(after - before);
        locations.erase(locations.lower_bound(x));
      }
    }
    for (int x : removing) {
      locations.erase(locations.lower_bound(x));
    }
  }
  cout.flush();
  return 0;
}
