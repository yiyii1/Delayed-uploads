#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

// 棋盘大小
const int SIZE = 3;
char board[SIZE][SIZE];

// 初始化棋盘
void initBoard() {
  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++)
      board[i][j] = ' ';
}

// 显示棋盘
void displayBoard() {
  cout << "\n";
  for (int i = 0; i < SIZE; i++) {
    cout << " ";
    for (int j = 0; j < SIZE; j++) {
      cout << board[i][j];
      if (j < SIZE - 1)
        cout << " | ";
    }
    cout << "\n";
    if (i < SIZE - 1)
      cout << "---+---+---\n";
  }
  cout << "\n";
}

// 检查当前棋盘状态
// 返回：'X' 玩家赢，'O' AI赢，'T' 平局，' ' 游戏继续
char checkWinner() {
  // 检查行和列
  for (int i = 0; i < SIZE; i++) {
    if (board[i][0] != ' ' && board[i][0] == board[i][1] &&
        board[i][1] == board[i][2])
      return board[i][0];
    if (board[0][i] != ' ' && board[0][i] == board[1][i] &&
        board[1][i] == board[2][i])
      return board[0][i];
  }
  // 检查对角线
  if (board[0][0] != ' ' && board[0][0] == board[1][1] &&
      board[1][1] == board[2][2])
    return board[0][0];
  if (board[0][2] != ' ' && board[0][2] == board[1][1] &&
      board[1][1] == board[2][0])
    return board[0][2];

  // 检查是否平局（棋盘满）
  bool full = true;
  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++)
      if (board[i][j] == ' ')
        full = false;
  if (full)
    return 'T';

  return ' '; // 游戏继续
}

// 玩家移动
void playerMove() {
  int row, col;
  while (true) {
    cout << "请输入行和列 (1-3，用空格分隔): ";
    cin >> row >> col;
    row--;
    col--;
    if (row >= 0 && row < SIZE && col >= 0 && col < SIZE &&
        board[row][col] == ' ') {
      board[row][col] = 'X';
      break;
    } else {
      cout << "无效位置，请重新输入！\n";
    }
  }
}

// AI 智能移动（简单规则）
void aiMove() {
  // 1. 尝试自己获胜
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      if (board[i][j] == ' ') {
        board[i][j] = 'O';
        if (checkWinner() == 'O') {
          return; // 获胜，直接返回
        }
        board[i][j] = ' '; // 撤销
      }
    }
  }
  // 2. 阻挡玩家获胜
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      if (board[i][j] == ' ') {
        board[i][j] = 'X';
        if (checkWinner() == 'X') {
          board[i][j] = 'O'; // 下在这里阻挡
          return;
        }
        board[i][j] = ' ';
      }
    }
  }
  // 3. 优先占中心
  if (board[1][1] == ' ') {
    board[1][1] = 'O';
    return;
  }
  // 4. 随机选择空位
  vector<pair<int, int>> empty;
  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++)
      if (board[i][j] == ' ')
        empty.push_back({i, j});
  if (!empty.empty()) {
    int idx = rand() % empty.size();
    board[empty[idx].first][empty[idx].second] = 'O';
  }
}

int main() {
  system("chcp 65001 > nul"); // 设置控制台编码为 UTF-8，支持中文显示
  srand(static_cast<unsigned>(time(0))); // 随机种子
  initBoard();
  char winner = ' ';
  bool playerTurn = true; // 玩家先手

  cout << "井字棋 - 人机对战\n";
  cout << "玩家: X, 电脑: O\n";
  displayBoard();

  while (winner == ' ') {
    if (playerTurn) {
      playerMove();
    } else {
      cout << "电脑思考中...\n";
      aiMove();
    }
    displayBoard();
    winner = checkWinner();

    if (winner == 'X')
      cout << "恭喜！你赢了！\n";
    else if (winner == 'O')
      cout << "电脑赢了，再来一局？\n";
    else if (winner == 'T')
      cout << "平局！\n";

    playerTurn = !playerTurn; // 切换回合
  }

  return 0;
}