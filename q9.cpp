#include <iostream>
#include <conio.h> // 用于检测键盘输入
#include <windows.h> // 用于清屏
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <shellapi.h> // 用于启动独立终端

using namespace std;

// 游戏地图大小
const int WIDTH = 60;
const int HEIGHT = 30;

// 方向枚举
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

// 全局变量
bool gameOver;
int x, y, foodX, foodY, score;
vector<pair<int, int>> snake; // 蛇的身体
Direction dir;

// 初始化游戏
void Setup() {
    gameOver = false;
    dir = STOP;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    snake.clear();
    snake.push_back({x, y});
    foodX = rand() % WIDTH;
    foodY = rand() % HEIGHT;
    score = 0;
}

// 替换清屏方式，避免闪烁
void ClearScreen() {
    COORD topLeft = {0, 0};
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;
    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    FillConsoleOutputAttribute(console, screen.wAttributes, screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    SetConsoleCursorPosition(console, topLeft);
}

// 设置光标位置
void SetCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// 绘制固定边框
void DrawBorder() {
    SetCursorPosition(0, 0);
    for (int i = 0; i < WIDTH + 2; i++) {
        cout << "#"; // 上边框
    }
    cout << endl;

    for (int i = 0; i < HEIGHT; i++) {
        cout << "#"; // 左边框
        SetCursorPosition(WIDTH + 1, i + 1);
        cout << "#"; // 右边框
    }

    SetCursorPosition(0, HEIGHT + 1);
    for (int i = 0; i < WIDTH + 2; i++) {
        cout << "#"; // 下边框
    }
}

// 绘制动态内容
void Draw() {
    // 清除整个地图的动态内容（蛇和食物）
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            SetCursorPosition(j + 1, i + 1);
            cout << " ";
        }
    }

    // 绘制蛇头
    SetCursorPosition(x + 1, y + 1);
    cout << "O";

    // 绘制蛇身
    for (size_t i = 1; i < snake.size(); i++) {
        SetCursorPosition(snake[i].first + 1, snake[i].second + 1);
        cout << "o";
    }

    // 绘制食物
    SetCursorPosition(foodX + 1, foodY + 1);
    cout << "F";

    // 输出分数
    SetCursorPosition(0, HEIGHT + 2);
    cout << "Score: " << score << "    "; // 清除多余内容
}

// 处理输入
void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

// 更新游戏逻辑
void Logic() {
    pair<int, int> prev = snake[0];
    pair<int, int> prev2;
    snake[0].first = x;
    snake[0].second = y;

    // 更新蛇身位置，从尾到头依次更新
    for (int i = snake.size() - 1; i > 0; i--) {
        snake[i] = snake[i - 1];
    }

    // 根据方向更新蛇头位置
    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    // 更新蛇头位置
    snake[0] = {x, y};

    // 撞墙检测
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        gameOver = true;

    // 撞自己检测
    for (int i = 1; i < snake.size(); i++) {
        if (snake[i].first == x && snake[i].second == y)
            gameOver = true;
    }

    // 吃食物
    if (x == foodX && y == foodY) {
        score += 10;
        foodX = rand() % WIDTH;
        foodY = rand() % HEIGHT;

        // 增加蛇身长度，新增部分与尾部位置相同
        snake.push_back(snake.back());
    }
}

int main() {
    // 启动独立终端
    if (__argc > 1 && std::string(__argv[1]) == "run") {
        srand(time(0));
        Setup();

        // 绘制边框（只绘制一次）
        DrawBorder();

        while (!gameOver) {
            Draw();
            Input();
            Logic();
            Sleep(150); // 降低蛇的速度
        }
        SetCursorPosition(0, HEIGHT + 3);
        cout << "Game Over!" << endl;
    } else {
        // 启动独立终端运行游戏
        std::string command = "start cmd /k \"";
        command += __argv[0]; // 当前程序路径
        command += " run\"";
        system(command.c_str());
    }

    return 0;
}