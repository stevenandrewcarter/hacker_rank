#include <functional>
#include <iostream>
#include <math.h>
#include <map>
#include <vector>

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
  Point location;
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
    moveOption.location = checkPoint;
    moveOption.moveName = move;
    moveOptions[distance] = moveOption;
  }
}

/**
* Grid is a vector of strings that represents a NxN grid.
* Find the grid location of the bot and the princess
* Perform dijkstra search to for shortest path
* Can only move in cardinal directions
*/
void displayPathtoPrincess(int n, vector<string> grid) {
  // Find the position of the bot
  auto botPosition = getActorPosition(n, grid, 'm');
  // Find the position of the the princess
  auto princessPosition = getActorPosition(n, grid, 'p');
  auto distance = getDistance(princessPosition, botPosition);
  auto currentPosition = botPosition;
  vector<string> moves;
  while (distance > 0) {
    map<double, MoveOption> moveOptions;
    // Test each surrounding point as the movement direction
    calculateMoveOption(n, grid, moveOptions, "LEFT", currentPosition, princessPosition);
    calculateMoveOption(n, grid, moveOptions, "RIGHT", currentPosition, princessPosition);
    calculateMoveOption(n, grid, moveOptions, "UP", currentPosition, princessPosition);
    calculateMoveOption(n, grid, moveOptions, "DOWN", currentPosition, princessPosition);
    auto bestMove = moveOptions.begin();
    distance = bestMove->first;
    moves.push_back(bestMove->second.moveName);
    currentPosition = bestMove->second.location;
  }
  for (auto i : moves) {
    cout << i << endl;
  }
}

int main(void) {
  int m;
  vector<string> grid;

  cin >> m;

  for (int i = 0; i < m; i++) {
    string s;
    cin >> s;
    grid.push_back(s);
  }

  displayPathtoPrincess(m, grid);

  return 0;
}