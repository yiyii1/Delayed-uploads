//迷宫
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <stack>
#include <algorithm>
#include <conio.h>  

using namespace std;

// 迷宫尺寸（奇数，保证边界为墙）
const int WIDTH = 63;
const int HEIGHT = 21;

// 方向数组
const int dx[] = {0, 1, 0, -1};
const int dy[] = {-1, 0, 1, 0};

// 迷宫单元格类型
enum CellType {
    WALL = '#',
    ROAD = ' ',
    PLAYER = 'P',
    END = 'E',
    PATH = '.'   // 求解时标记路径
};

// 迷宫类
class Maze {
private:
    vector<vector<char>> grid;   // 存储地图字符
    int playerX, playerY;        // 玩家位置
    int endX, endY;              // 终点位置
    vector<pair<int, int>> path; // BFS 找到的路径（用于显示）

public:
    Maze() {
        grid.resize(HEIGHT, vector<char>(WIDTH, WALL));
        playerX = playerY = 1;
        endX = HEIGHT - 2;
        endY = WIDTH - 2;
        generateMaze();
        grid[playerX][playerY] = PLAYER;
        grid[endX][endY] = END;
    }

    // 递归回溯生成迷宫
    void generateMaze() {
        // 初始化：所有单元格都是墙
        for (int i = 0; i < HEIGHT; ++i)
            for (int j = 0; j < WIDTH; ++j)
                grid[i][j] = WALL;

        // 从 (1,1) 开始挖路
        stack<pair<int, int>> st;
        st.push({1, 1});
        grid[1][1] = ROAD;

        while (!st.empty()) {
            auto [x, y] = st.top();
            // 随机打乱方向
            vector<int> dirs = {0, 1, 2, 3};
            random_shuffle(dirs.begin(), dirs.end());

            bool found = false;
            for (int d : dirs) {
                int nx = x + dx[d] * 2;
                int ny = y + dy[d] * 2;
                if (nx > 0 && nx < HEIGHT-1 && ny > 0 && ny < WIDTH-1 && grid[nx][ny] == WALL) {
                    // 打通当前格和中间格
                    grid[nx][ny] = ROAD;
                    grid[x + dx[d]][y + dy[d]] = ROAD;
                    st.push({nx, ny});
                    found = true;
                    break;
                }
            }
            if (!found) st.pop();
        }
        // 确保起点和终点连通
        grid[1][1] = ROAD;
        grid[HEIGHT-2][WIDTH-2] = ROAD;
    }

    // 绘制迷宫（不清屏，光标归零后重绘）
    void draw() {
        // 光标移动到左上角
        cout << "\033[H";
        for (int i = 0; i < HEIGHT; ++i) {
            for (int j = 0; j < WIDTH; ++j) {
                cout << grid[i][j];
            }
            cout << endl;
        }
        cout << "WASD 移动，S 显示路径，Q 退出" << endl;
    }

    // 移动玩家
    bool movePlayer(int dx, int dy) {
        int nx = playerX + dx;
        int ny = playerY + dy;
        if (nx < 0 || nx >= HEIGHT || ny < 0 || ny >= WIDTH) return false;
        if (grid[nx][ny] == WALL) return false;

        // 清除旧位置
        if (grid[playerX][playerY] != END)  // 起点和终点位置特殊保留
            grid[playerX][playerY] = ROAD;
        else
            grid[playerX][playerY] = END;

        playerX = nx;
        playerY = ny;

        // 到达终点？
        if (grid[playerX][playerY] == END) {
            grid[playerX][playerY] = PLAYER;
            draw();
            cout << "恭喜！你到达了终点！按任意键退出..." << endl;
            _getch();
            return true;
        }

        grid[playerX][playerY] = PLAYER;
        draw();
        return false;
    }

    // BFS 寻找从玩家到终点的路径，并保存到 path
    bool findPath() {
        // 清空旧路径标记
        for (int i = 0; i < HEIGHT; ++i)
            for (int j = 0; j < WIDTH; ++j)
                if (grid[i][j] == PATH)
                    grid[i][j] = ROAD;

        vector<vector<bool>> visited(HEIGHT, vector<bool>(WIDTH, false));
        vector<vector<pair<int, int>>> parent(HEIGHT, vector<pair<int, int>>(WIDTH, {-1, -1}));
        queue<pair<int, int>> q;
        q.push({playerX, playerY});
        visited[playerX][playerY] = true;

        while (!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            if (x == endX && y == endY) {
                // 重建路径
                path.clear();
                int cx = endX, cy = endY;
                while (!(cx == playerX && cy == playerY)) {
                    path.push_back({cx, cy});
                    auto [px, py] = parent[cx][cy];
                    cx = px; cy = py;
                }
                reverse(path.begin(), path.end());
                // 标记路径
                for (auto [px, py] : path) {
                    if (grid[px][py] != PLAYER && grid[px][py] != END)
                        grid[px][py] = PATH;
                }
                draw();
                return true;
            }
            for (int d = 0; d < 4; ++d) {
                int nx = x + dx[d];
                int ny = y + dy[d];
                if (nx >= 0 && nx < HEIGHT && ny >= 0 && ny < WIDTH && !visited[nx][ny]) {
                    if (grid[nx][ny] != WALL) {
                        visited[nx][ny] = true;
                        parent[nx][ny] = {x, y};
                        q.push({nx, ny});
                    }
                }
            }
        }
        return false; // 无路径（迷宫设计保证有路径）
    }

    // 清除路径标记
    void clearPath() {
        for (int i = 0; i < HEIGHT; ++i)
            for (int j = 0; j < WIDTH; ++j)
                if (grid[i][j] == PATH)
                    grid[i][j] = ROAD;
        draw();
    }
};

int main() {
  system("chcp:65001 > nul"); // 设置控制台编码为 UTF-8，支持中文显示
    srand(static_cast<unsigned>(time(nullptr)));
    Maze maze;
    maze.draw();

    bool exitGame = false;
    while (!exitGame) {
        char ch = _getch();  // 获取单字符，无需回车
        switch (ch) {
            case 'w': case 'W': exitGame = maze.movePlayer(-1, 0); break;
            case 's': case 'S': exitGame = maze.movePlayer(1, 0); break;
            case 'a': case 'A': exitGame = maze.movePlayer(0, -1); break;
            case 'd': case 'D': exitGame = maze.movePlayer(0, 1); break;
            case 'q': case 'Q': exitGame = true; break;
            case 'p': case 'P': maze.findPath(); break;   // 显示路径
            case 'c': case 'C': maze.clearPath(); break;  // 清除路径
        }
    }
    return 0;
}