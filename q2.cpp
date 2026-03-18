// 岛屿数量
// 给你一个由 '1'（陆地）和
// '0'（水）组成的二维网格，请你计算网格中岛屿的数量。岛屿总是被水包围，
// 并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。此外，你可以假设该网格的四条边均被水包围。
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