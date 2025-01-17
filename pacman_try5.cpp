#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <conio.h>
#include <windows.h>
#include <limits>

// Maze dimensions
const int ROWS = 11;
const int COLS = 11;

// Maze definition
int maze[ROWS][COLS];

// Levels
int level1[ROWS][COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1},
    {1, 2, 1, 2, 1, 2, 1, 1, 1, 2, 1},
    {1, 2, 1, 2, 2, 2, 2, 2, 1, 2, 1},
    {1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1},
    {1, 2, 2, 2, 2, 3, 2, 2, 2, 2, 1},
    {1, 2, 1, 1, 1, 1, 1, 4, 1, 2, 1},
    {1, 2, 1, 2, 2, 2, 2, 2, 1, 2, 1},
    {1, 2, 1, 2, 1, 1, 1, 2, 1, 2, 1},
    {1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

int level2[ROWS][COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 2, 2, 2, 2, 1, 2, 2, 1},
    {1, 2, 1, 1, 1, 1, 2, 1, 1, 2, 1},
    {1, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1},
    {1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1},
    {1, 2, 2, 2, 2, 3, 2, 2, 2, 2, 1},
    {1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1},
    {1, 2, 1, 2, 2, 2, 2, 2, 1, 2, 1},
    {1, 2, 1, 2, 1, 1, 1, 2, 1, 2, 1},
    {1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

// Player class
class Player {
public:
    int x, y;

    Player(int startX, int startY) : x(startX), y(startY) {}

    void move(char direction) {
        int newX = x, newY = y;
        if (direction == 'w') newY--;
        if (direction == 's') newY++;
        if (direction == 'a') newX--;
        if (direction == 'd') newX++;
        if (maze[newY][newX] != 1) {
            x = newX;
            y = newY;
        }
    }
};

// Enemy class
class Enemy {
public:
    int x, y;

    Enemy(int startX, int startY) : x(startX), y(startY) {}

    void moveRandomly() {
        int directions[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
        int randomDir = rand() % 4;
        int newX = x + directions[randomDir][0];
        int newY = y + directions[randomDir][1];
        if (maze[newY][newX] != 1) {
            x = newX;
            y = newY;
        }
    }
};

// Main game class
class Game {
public:
    Player player;
    Enemy enemy;
    int score;
    int lives;
    int totalCollectibles;
    int currentLevel;

    Game() : player(5, 5), enemy(6, 7), score(0), lives(3), currentLevel(1) {
        srand(time(0));
        loadLevel(1);
    }

    void loadLevel(int level) {
        if (level == 1) memcpy(maze, level1, sizeof(maze));
        else if (level == 2) memcpy(maze, level2, sizeof(maze));

        totalCollectibles = 0;
        for (int i = 0; i < ROWS; ++i)
            for (int j = 0; j < COLS; ++j)
                if (maze[i][j] == 2) totalCollectibles++;

        player.x = 5; player.y = 5;
        enemy.x = 6; enemy.y = 7;
    }

    void render() {
        system("cls");
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                if (player.x == j && player.y == i) std::cout << "\033[1;33mP \033[0m";
                else if (enemy.x == j && enemy.y == i) std::cout << "\033[1;31mE \033[0m";
                else if (maze[i][j] == 1) std::cout << "\033[1;34m# \033[0m";
                else if (maze[i][j] == 2) std::cout << "\033[1;32m. \033[0m";
                else std::cout << "  ";
            }
            std::cout << "\n";
        }
        std::cout << "Score: " << score << " | Lives: " << lives << "\n";
    }

    void update() {
        if (maze[player.y][player.x] == 2) {
            maze[player.y][player.x] = 0;
            score++;
            totalCollectibles--;
        }

        enemy.moveRandomly();

        if (player.x == enemy.x && player.y == enemy.y) {
            lives--;
            if (lives == 0) {
                std::cout << "Game Over! Final Score: " << score << "\n";
                exit(0);
            }
            loadLevel(currentLevel);
        }

        if (totalCollectibles == 0) {
            currentLevel++;
            if (currentLevel > 2) {
                std::cout << "Congratulations! You won with a score of " << score << "!\n";
                exit(0);
            }
            loadLevel(currentLevel);
        }
    }

    void play() {
        while (lives > 0) {
            render();
            if (_kbhit()) {
                char input = _getch();
                player.move(input);
            }
            update();
            Sleep(100);
        }
    }
};

void showMenu() {
    std::cout << "--- PAC-MAN GAME ---\n";
    std::cout << "1. Start New Game\n";
    std::cout << "2. Instructions\n";
    std::cout << "3. Exit\n";
    std::cout << "Enter your choice: ";
}

void showInstructions() {
    std::cout << "--- How to Play ---\n";
    std::cout << "- Use W/A/S/D to move Pacman\n";
    std::cout << "- Avoid the Ghost\n";
    std::cout << "- Collect all dots to progress levels\n";
    std::cout << "- You have 3 lives\n";
    std::cout << "Press Enter to continue...\n";
    std::cin.ignore();
    std::cin.get();
}

int main() {
    while (true) {
        showMenu();
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                Game game;
                game.play();
                break;
            }
            case 2:
                showInstructions();
                break;
            case 3:
                std::cout << "Thanks for playing!\n";
                return 0;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    }
}

