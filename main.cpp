#include <cstdio>
#include <cstring>
#include <set>
#include <utility>

#define SIZE 8

using std::set, std::pair;

struct Point {
  Point() = default;
  Point(int x, int y) : x(x), y(y) {}
  Point(int x, int y, int dist) : x(x), y(y), distance(dist) {}
  int x, y, distance = 0;

  friend bool operator<(const Point &l, const Point &r) {
    if (l.distance < r.distance)
      return true;
    if (l.distance == r.distance) {
      if (l.x < r.x)
        return true;
      if (l.x == r.x) {
        if (l.y < r.y)
          return true;
      }
    }
    return false;
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

void dijkstra(int graph[SIZE][SIZE], Point src, Point dest) {
  bool visited[SIZE][SIZE];
  memset(visited, false, sizeof(visited));
  set<Point> next_points{};
  int sx = src.x;
  int sy = src.y;
  visited[sx][sy] = true;
  next_points.emplace(sx, sy);

  while (!next_points.empty()) {
    Point current_point = *next_points.begin();
    // printf("Checking (%d, %d, %d)\n", current_point.x, current_point.y,
    //        current_point.distance);
    next_points.erase(next_points.begin());
    int x = current_point.x;
    int y = current_point.y;
    int dist = current_point.distance;
    visited[x][y] = true;

    print_graph(graph, visited, dest);

    // Search right
    if (is_in_bounds(x + 1, y) && !visited[x + 1][y]) {
      if (x + 1 == dest.x && y == dest.y) {
        printf("Found! Distance: %d\n", dist + 1);
        return;
      }
      if (graph[x + 1][y]) {
        next_points.emplace(x + 1, y, dist + 1);
      }
    }
    // Search left
    if (is_in_bounds(x - 1, y) && !visited[x - 1][y]) {
      if (x + 1 == dest.x && y == dest.y) {
        printf("Found! Distance: %d\n", dist + 1);
        return;
      }
      if (graph[x - 1][y]) {
        next_points.emplace(x - 1, y, dist + 1);
      }
    }
    // Search up
    if (is_in_bounds(x, y - 1) && !visited[x][y - 1]) {
      if (x == dest.x && y - 1 == dest.y) {
        printf("Found! Distance: %d\n", dist + 1);
        return;
      }
      if (graph[x][y - 1]) {
        next_points.emplace(x, y - 1, dist + 1);
      }
    }
    // Search down
    if (is_in_bounds(x, y + 1) && !visited[x][y + 1]) {
      if (x == dest.x && y + 1 == dest.y) {
        printf("Found! Distance: %d\n", dist + 1);
        return;
      }
      if (graph[x][y + 1]) {
        next_points.emplace(x, y + 1, dist + 1);
      }
    }

    // printf("Currently checking:\n");
    // for (const auto &point : next_points)
    //   printf("(%d, %d, %d) ", point.x, point.y, point.distance);
    // putchar('\n');
  }
}

int main() {
  int graph[SIZE][SIZE] = {
      {1, 1, 1, 1, 1, 1, 1, 0}, {1, 1, 1, 1, 1, 1, 0, 1},
      {1, 1, 1, 1, 1, 0, 1, 1}, {1, 1, 1, 1, 0, 1, 1, 1},
      {1, 1, 1, 0, 1, 1, 1, 1}, {1, 1, 0, 1, 1, 1, 1, 1},
      {1, 0, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 0, 1, 1, 1, 1},
  };
  dijkstra(graph, {4, 0}, {6, 6});

  return 0;
}