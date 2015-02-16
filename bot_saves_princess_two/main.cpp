#include <iostream>
#include <vector>
#include <functional>
#include <math.h>
#include <map>

using namespace std;

struct Point {
  Point() {
    x = y = 0;
    content = '\0';
    valid = false;
  }

  Point(int aX, int aY, char aContent) {
    x = aX;
    y = aY;
    content = aContent;
    valid = true;
  }

  int x, y;
  char content;
  bool valid;
};

struct MoveOption {
  string moveName;
};

char getGridItem(int x, int y, vector<string> grid) {
  return grid[y][x];
}

void iterateGrid(int n, vector<string> grid, function<bool(Point)> func) {
  for (auto i = 0; i < n; ++i) {
    for (auto j = 0; j < n; ++j) {
      auto gridItem = getGridItem(i, j, grid);
      Point aPoint(i, j, gridItem);
      if (func(aPoint)) break;
    }
  }
}

Point getActorPosition(int n, vector<string> grid, char actor) {
  Point foundActor;
  iterateGrid(n, grid, [&](Point aPoint) {
      if (aPoint.content == actor) {
        foundActor = aPoint;
        return true;
      }
      return false;
  });
  return foundActor;
}

double getDistance(Point source, Point dest) {
  auto x = pow(dest.x - source.x, 2);
  auto y = pow(dest.y - source.y, 2);
  return sqrt(x + y);
}

void calculateMoveOption(int n, vector<string> grid, map<double, MoveOption> &moveOptions, string move, Point currentPosition, Point princessPosition) {
  Point checkPoint;
  if (move == "LEFT" && currentPosition.x > 0)
    checkPoint = Point(currentPosition.x - 1, currentPosition.y, '\0');
  else if (move == "RIGHT" && currentPosition.x < n - 1)
    checkPoint = Point(currentPosition.x + 1, currentPosition.y, '\0');
  else if (move == "UP" && currentPosition.y > 0)
    checkPoint = Point(currentPosition.x, currentPosition.y - 1, '\0');
  else if (move == "DOWN" && currentPosition.y < n - 1)
    checkPoint = Point(currentPosition.x, currentPosition.y + 1, '\0');
  if (checkPoint.valid) {
    auto actor = getGridItem(checkPoint.x, checkPoint.y, grid);
    checkPoint.content = actor;
    auto distance = getDistance(princessPosition, checkPoint);
    MoveOption moveOption;
    moveOption.moveName = move;
    moveOptions[distance] = moveOption;
  }
}

/**
*  Calculate the next best move, the bot position is provided by the params r and c
*/
void nextMove(int n, int r, int c, vector<string> grid) {
  // Find the position of the bot (r and c don't seem to work as intended?)
  auto botPosition = getActorPosition(n, grid, 'm');
  // Find the position of the the princess
  auto princessPosition = getActorPosition(n, grid, 'p');
  auto currentPosition = botPosition;
  // Only calculate one move
  map<double, MoveOption> moveOptions;
  // Test each surrounding point as the movement direction
  calculateMoveOption(n, grid, moveOptions, "LEFT", currentPosition, princessPosition);
  calculateMoveOption(n, grid, moveOptions, "RIGHT", currentPosition, princessPosition);
  calculateMoveOption(n, grid, moveOptions, "UP", currentPosition, princessPosition);
  calculateMoveOption(n, grid, moveOptions, "DOWN", currentPosition, princessPosition);
  auto bestMove = moveOptions.begin();
  cout << bestMove->second.moveName << endl;
}

int main(void) {
  int n, r, c;
  vector<string> grid;
  cin >> n;
  cin >> r;
  cin >> c;
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    grid.push_back(s);
  }
  nextMove(n, r, c, grid);
  return 0;
}
