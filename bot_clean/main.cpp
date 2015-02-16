#include <iostream>
#include <vector>
#include <functional>
#include <math.h>
#include <map>

using namespace std;

/**
* Point structure to represent a location in the environment
*/
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

char getGridItem(int x, int y, vector<string> grid) {
  return grid[x][y];
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

double getDistance(Point source, Point dest) {
  auto x = pow(dest.x - source.x, 2);
  auto y = pow(dest.y - source.y, 2);
  return sqrt(x + y);
}

map<double, Point> getDirtLocations(Point botLocation, vector<string> grid) {
  map<double, Point> dirtLocations;
  iterateGrid(5, grid, [&](Point aPoint) {
      if (aPoint.content == 'd') {
        auto distance = getDistance(aPoint, botLocation);
        if (dirtLocations.find(distance) == dirtLocations.end())
          dirtLocations[distance] = aPoint;
      }
      return false;
  });
  return dirtLocations;
}

void calculateMoveOption(int n, map<double, string> &moveOptions, string move, Point currentPosition, Point targetPosition) {
  Point checkPoint;
  if (move == "LEFT" && currentPosition.y > 0)
    checkPoint = Point(currentPosition.x, currentPosition.y - 1, '\0');
  else if (move == "RIGHT" && currentPosition.y < n - 1)
    checkPoint = Point(currentPosition.x, currentPosition.y + 1, '\0');
  else if (move == "UP" && currentPosition.x > 0)
    checkPoint = Point(currentPosition.x - 1, currentPosition.y, '\0');
  else if (move == "DOWN" && currentPosition.x < n - 1)
    checkPoint = Point(currentPosition.x + 1, currentPosition.y, '\0');
  if (checkPoint.valid) {
    auto distance = getDistance(targetPosition, checkPoint);
    if (moveOptions.find(distance) == moveOptions.end())
    moveOptions[distance] = move;
  }
}

void nextMove(int posr, int posc, vector<string> board) {
  auto botLocation = Point(posr, posc, 'b');
  // Dirt can be found in multiple locations, build a list of the known dirt locations, ordered by distance to the bot
  auto dirtLocations = getDirtLocations(botLocation, board);
  auto closestDirtLocation = dirtLocations.begin();
  // First check the distance, if 0 then just clean the current location
  auto distance = closestDirtLocation->first;
  if (distance == 0) {
    cout << "CLEAN" << endl;
    // Nothing else to do, just exit the function then
    return;
  }
  else {
    map<double, string> moveOptions;
    // Test each surrounding point as the movement direction
    calculateMoveOption(5, moveOptions, "LEFT", botLocation, closestDirtLocation->second);
    calculateMoveOption(5, moveOptions, "RIGHT", botLocation, closestDirtLocation->second);
    calculateMoveOption(5, moveOptions, "UP", botLocation, closestDirtLocation->second);
    calculateMoveOption(5, moveOptions, "DOWN", botLocation, closestDirtLocation->second);
    auto bestMove = moveOptions.begin();
    cout << bestMove->second << endl;
  }
}

int main(void) {
  int pos[2];
  vector<string> board;
  cin >> pos[0] >> pos[1];
  for (int i = 0; i < 5; i++) {
    string s;
    cin >> s;
    board.push_back(s);
  }
  nextMove(pos[0], pos[1], board);
  return 0;
}
