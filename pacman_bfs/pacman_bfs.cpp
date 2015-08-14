#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <map>

using namespace std;

map<int, map<int, bool>> visited_nodes;
vector<string> explored_nodes;

struct Node {
  Node() {
    previous = nullptr;
  }

  Node(int x, int y, char value) : x_(x), y_(y), value_(value) {
    previous = nullptr;
  }

  void set_previous(Node *a_node) {
    if (previous == nullptr) {
      previous = a_node;
    }
  }

  Node *get_previous() { return previous; }

  int x_, y_;
  char value_;

private:
  Node *previous;
};

map<int, map<int, Node>> build_graph(int r, int c, vector<string> grid) {
  map<int, map<int, Node>> nodes;
  for (auto i = 0; i < r; ++i) {
    for (auto j = 0; j < c; ++j) {
      nodes[i][j] = Node(i, j, grid[i][j]);
      visited_nodes[i][j] = false;
    }
  }
  return nodes;
}

void nextMove(int r, int c, int pacman_r, int pacman_c, int food_r, int food_c, vector <string> grid) {
  auto nodes = build_graph(r, c, grid);
  deque<Node*> node_queue;
  node_queue.push_front(&nodes[pacman_r][pacman_c]);
  vector<string> explored_nodes;
  while (!node_queue.empty()) {
    auto current_node = *node_queue.begin();
    node_queue.pop_front();    
    if (!visited_nodes[current_node->x_][current_node->y_]) {
      visited_nodes[current_node->x_][current_node->y_] = true;
      explored_nodes.push_back(to_string(current_node->x_) + " " + to_string(current_node->y_) + "\n");

      if (current_node->x_ == food_r && current_node->y_ == food_c)
        break;

      // Check the Up Direction
      if (current_node->x_ > 0 && !visited_nodes[current_node->x_ - 1][current_node->y_] && nodes[current_node->x_ - 1][current_node->y_].value_ != '%') {
        nodes[current_node->x_ - 1][current_node->y_].set_previous(current_node);
        node_queue.push_back(&nodes[current_node->x_ - 1][current_node->y_]);
      }

      // Check the Left Direction
      if (current_node->y_ > 0 && !visited_nodes[current_node->x_][current_node->y_ - 1] && nodes[current_node->x_][current_node->y_ - 1].value_ != '%') {
        nodes[current_node->x_][current_node->y_ - 1].set_previous(current_node);
        node_queue.push_back(&nodes[current_node->x_][current_node->y_ - 1]);
      }

      // Check the Right Direction
      if (current_node->y_ < c && !visited_nodes[current_node->x_][current_node->y_ + 1] && nodes[current_node->x_][current_node->y_ + 1].value_ != '%') {
        nodes[current_node->x_][current_node->y_ + 1].set_previous(current_node);
        node_queue.push_back(&nodes[current_node->x_][current_node->y_ + 1]);
      }

      // Check the Down Direction
      if (current_node->x_ < r && !visited_nodes[current_node->x_ + 1][current_node->y_] && nodes[current_node->x_ + 1][current_node->y_].value_ != '%') {
        nodes[current_node->x_ + 1][current_node->y_].set_previous(current_node);
        node_queue.push_back(&nodes[current_node->x_ + 1][current_node->y_]);
      }
    }
  }
  // Calculate shortest path
  vector<string> shortest_path;
  auto current_node = &nodes[food_r][food_c];
  while (current_node->x_ != pacman_r || current_node->y_ != pacman_c) {
    shortest_path.push_back(to_string(current_node->x_) + " " + to_string(current_node->y_) + "\n");
    current_node = current_node->get_previous();
  }
  // Print explored set
  cout << explored_nodes.size() << "\n";
  for (auto i : explored_nodes)
    cout << i;
  // Print shortest path
  cout << shortest_path.size() << "\n";
  for (auto i = shortest_path.rbegin(); i != shortest_path.rend(); ++i)
    cout << *i;
}

int main(void) {
  int r, c, pacman_r, pacman_c, food_r, food_c;
  cin >> pacman_r >> pacman_c;
  cin >> food_r >> food_c;
  cin >> r >> c;
  vector <string> grid;
  for (auto i = 0; i < r; i++) {
    string s; cin >> s;
    grid.push_back(s);
  }
  nextMove(r, c, pacman_r, pacman_c, food_r, food_c, grid);
  return 0;
}