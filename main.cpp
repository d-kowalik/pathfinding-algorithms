#include <cstdio>
#include <cstring>
#include <set>
#include <stack>
#include <utility>

#define SIZE 8

using std::set, std::pair, std::make_pair, std::stack;

struct Point {
  Point() = default;
  Point(int x, int y) : x(x), y(y) {}
  Point(int x, int y, int dist) : x(x), y(y), distance(dist) {}
  int x, y, distance = 0;

  friend bool operator<(const Point &l, const Point &r) {
    if (l.distance < r.distance)
      return true;
    if (l.distance == r.distance)
      if (l.x < r.x)
        return true;
    return l.y < r.y;
  }
};

bool is_in_bounds(int x, int y) {
  return x >= 0 && y >= 0 && x < SIZE && y < SIZE;
}

void print_graph(int graph[SIZE][SIZE], bool visited[SIZE][SIZE], Point dest) {
  for (int x = 0; x < SIZE; x++) {
    for (int y = 0; y < SIZE; y++) {
      if (x == dest.x && y == dest.y)
        putchar('D');
      else if (!graph[x][y])
        putchar('W');
      else if (visited[x][y])
        putchar('#');
      else
        putchar('.');
    }
    putchar('\n');
  }
  putchar('\n');
}

bool visited[SIZE][SIZE];
set<Point> next_points{};
pair<int, int> previous_points[SIZE][SIZE];

void calculate_path(Point dest, int dist) {
  dist += 1;
  stack<pair<int, int>> path{};
  int x = dest.x;
  int y = dest.y;
  while (dist--) {
    path.emplace(x, y);
    auto next_pair = previous_points[x][y];
    x = next_pair.first;
    y = next_pair.second;
  }

  pair<int, int> node = path.top();
  path.pop();
  printf("(%d, %d)", node.first, node.second);

  while (!path.empty()) {
    node = path.top();
    path.pop();
    printf(" -> (%d, %d)", node.first, node.second);
  }
  putchar('\n');
}

bool dijkstra_check(int graph[SIZE][SIZE], int x, int y, int current_x,
                    int current_y, int dist, Point dest) {
  if (is_in_bounds(x, y) && !visited[x][y]) {
    if (x == dest.x && y == dest.y) {
      printf("Found! Distance: %d\n", dist + 1);
      previous_points[x][y] = make_pair(current_x, current_y);
      calculate_path(dest, dist + 1);
      return true;
    }
    if (graph[x][y]) {
      next_points.emplace(x, y, dist + 1);
      previous_points[x][y] = make_pair(current_x, current_y);
    }
  }
  return false;
}

void dijkstra(int graph[SIZE][SIZE], Point src, Point dest) {
  memset(visited, false, sizeof(visited));
  next_points.emplace(src);
  printf("%d\n", previous_points[0][0].first);

  while (!next_points.empty()) {
    Point current_point = *next_points.begin();
    next_points.erase(next_points.begin());
    int x = current_point.x;
    int y = current_point.y;
    int dist = current_point.distance;
    visited[x][y] = true;

    print_graph(graph, visited, dest);

    // Search right
    if (dijkstra_check(graph, x + 1, y, x, y, dist, dest))
      return;
    // Search left
    if (dijkstra_check(graph, x - 1, y, x, y, dist, dest))
      return;
    // Search down
    if (dijkstra_check(graph, x, y + 1, x, y, dist, dest))
      return;
    // Search up
    if (dijkstra_check(graph, x, y - 1, x, y, dist, dest))
      return;
  }
}

int main() {
  int graph[SIZE][SIZE] = {
      {1, 1, 1, 1, 1, 1, 1, 0}, {1, 1, 1, 1, 1, 1, 0, 1},
      {1, 1, 1, 1, 1, 0, 1, 1}, {1, 1, 1, 1, 0, 1, 1, 1},
      {1, 1, 1, 0, 1, 1, 1, 1}, {1, 1, 0, 1, 1, 1, 1, 1},
      {1, 0, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 0, 1, 1, 1, 1},
  };
  dijkstra(graph, {0, 0}, {6, 6});

  return 0;
}