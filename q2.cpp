#include <iostream>
#include <vector>
using namespace std;

void deel(vector<vector<char>> &grid, int i, int j) {
  grid[i][j] = 0;
  if (i - 1 < 0 || i + 1 >= grid.size() || j - 1 < 0 ||
      j + 1 >= grid[0].size()) {
    return;
  }
  if (grid[i - 1][j] == '1')
    deel(grid, i - 1, j);
  if (grid[i + 1][j] == '1')
    deel(grid, i + 1, j);
  if (grid[i][j - 1] == '1')
    deel(grid, i, j - 1);
  if (grid[i][j + 1] == '1')
    deel(grid, i + 1, j - 1);
}

int numIslands(vector<vector<char>> &grid) {
  int m = grid.size();
  int n = grid[0].size();
  int ans = 0;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (grid[i][j] == '1') {
        deel(grid, i, j);
        ans++;
      }
    }
  }
  return ans;
}
int main() {
  vector<vector<char>> grid(4, vector<char>(5));
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 5; j++) {
      char c;
      cin >> c;
    }
  }

  cout << numIslands(grid);
  return 0;
}