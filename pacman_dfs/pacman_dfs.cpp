#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>

using namespace std;

struct Node {
  Node(): x_(0), y_(0), value_(0) {
  }

  Node(int x, int y, char value) : x_(x), y_(y), value_(value) {
  }

  int x_, y_;
  char value_;
};

map<int, map<int, bool>> visited_nodes;
vector<string> explored_nodes;

void dfs_recursive(int r, int c, Node *current_node, Node *destination_node, map<int, map<int, Node>> nodes, stack<Node*> &path) {
  path.push(current_node);
  explored_nodes.push_back(to_string(current_node->x_) + " " + to_string(current_node->y_));
  visited_nodes[current_node->x_][current_node->y_] = true;
  if (current_node->x_ == destination_node->x_ && current_node->y_ == destination_node->y_) {
    cout << explored_nodes.size() << "\n";
    for (auto explored : explored_nodes)
      cout << explored << "\n";
    // First node is not a move?
    cout << path.size() - 1 << "\n";
    string path_string = "";
    while (!path.empty()) {
      auto current = path.top();
      path.pop();
      path_string = to_string(current->x_) + " " + to_string(current->y_) + "\n" + path_string;
    }
    cout << path_string;
    exit(0);
  }
  // Check the Down Direction
  if (current_node->x_ < r && !visited_nodes[current_node->x_ + 1][current_node->y_] && nodes[current_node->x_ + 1][current_node->y_].value_ != '%')
    dfs_recursive(r, c, &nodes[current_node->x_ + 1][current_node->y_], destination_node, nodes, path);

  // Check the Right Direction
  if (current_node->y_ < c && !visited_nodes[current_node->x_][current_node->y_ + 1] && nodes[current_node->x_][current_node->y_ + 1].value_ != '%')
    dfs_recursive(r, c, &nodes[current_node->x_][current_node->y_ + 1], destination_node, nodes, path);

  // Check the Left Direction
  if (current_node->y_ > 0 && !visited_nodes[current_node->x_][current_node->y_ - 1] && nodes[current_node->x_][current_node->y_ - 1].value_ != '%')
    dfs_recursive(r, c, &nodes[current_node->x_][current_node->y_ - 1], destination_node, nodes, path);

  if (current_node->x_ > 0 && !visited_nodes[current_node->x_ - 1][current_node->y_] && nodes[current_node->x_ - 1][current_node->y_].value_ != '%')
    dfs_recursive(r, c, &nodes[current_node->x_ - 1][current_node->y_], destination_node, nodes, path);

  visited_nodes[current_node->x_][current_node->y_] = false;
  if (path.size() > 0) path.pop();
}

map<int, map<int, Node>> build_graph(int r, int c, vector<string> grid) {
  map<int, map<int, Node>> nodes;
  for (auto i = 0; i < r; ++i)
    for (auto j = 0; j < c; ++j)
      nodes[i][j] = Node(i, j, grid[i][j]);
  return nodes;
}

void dfs(int r, int c, int pacman_r, int pacman_c, int food_r, int food_c, vector<string> grid) {
  auto nodes = build_graph(r, c, grid);
  stack<Node*> path;
  for (auto i = 0; i < r; ++i)
    for (auto j = 0; j < c; ++j)
      visited_nodes[i][j] = false;
  dfs_recursive(r, c, &nodes[pacman_r][pacman_c], &nodes[food_r][food_c], nodes, path);
}

int main(void) {
  int r, c, pacman_r, pacman_c, food_r, food_c;
  cin >> pacman_r >> pacman_c;
  cin >> food_r >> food_c;
  cin >> r >> c;
  vector<string> grid;
  for (auto i = 0; i < r; i++) {
    string s;
    cin >> s;
    grid.push_back(s);
  }
  dfs(r, c, pacman_r, pacman_c, food_r, food_c, grid);
  return 0;
};