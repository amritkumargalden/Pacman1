#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <conio.h>
#include <windows.h>
#include <limits>
#include <sstream> // Add this header for stringstream

// Maze dimensions
const int ROWS = 11;
const int COLS = 11;
const int MAX_GHOSTS = 10; // Maximum number of ghosts

// Maze definition
int maze[ROWS][COLS];

// Levels
int level1[ROWS][COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1},
    {1, 3, 1, 2, 1, 2, 1, 1, 1, 2, 1},
    {1, 2, 1, 2, 2, 2, 2, 2, 1, 2, 1},
    {1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1},
    {1, 2, 1, 2, 2, 2, 2, 2, 1, 2, 1},
    {1, 2, 1, 2, 1, 1, 1, 2, 1, 2, 1},
    {1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

int level2[ROWS][COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 4, 1, 2, 2, 2, 2, 1, 2, 2, 1},
    {1, 2, 1, 1, 1, 1, 2, 1, 1, 2, 1},
    {1, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1},
    {1, 3, 1, 1, 2, 1, 1, 1, 1, 2, 1},
    {1, 2, 2, 2, 2, 3, 2, 2, 2, 2, 1},
    {1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1},
    {1, 2, 1, 2, 2, 2, 2, 2, 1, 2, 1},
    {1, 2, 1, 2, 1, 1, 1, 2, 1, 2, 1},
    {1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

// Add more levels here
int level3[ROWS][COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1},
    {1, 2, 1, 2, 1, 2, 1, 1, 1, 2, 1},
    {1, 2, 1, 2, 2, 2, 2, 2, 1, 2, 1},
    {1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1},
    {1, 2, 2, 2, 2, 3, 2, 2, 2, 2, 1},
    {1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1},
    {1, 2, 1, 2, 2, 2, 2, 2, 1, 2, 1},
    {1, 2, 1, 2, 1, 1, 1, 2, 1, 2, 1},
    {1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
int level4[ROWS][COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1},
    {1, 2, 1, 2, 1, 2, 1, 1, 1, 2, 1},
    {1, 2, 1, 2, 2, 2, 2, 2, 1, 2, 1},
    {1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1},
    {1, 2, 1, 2, 2, 2, 2, 2, 1, 2, 1},
    {1, 2, 1, 2, 1, 1, 1, 2, 1, 2, 1},
    {1, 2, 1, 2, 1, 2, 2, 2, 2, 2, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
int level5[ROWS][COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1},
    {1, 2, 1, 2, 1, 2, 1, 1, 1, 2, 1},
    {1, 2, 1, 2, 2, 2, 2, 2, 1, 2, 1},
    {1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1},
    {1, 2, 2, 2, 2, 3, 2, 2, 2, 2, 1},
    {1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1},
    {1, 2, 1, 2, 2, 2, 2, 2, 1, 2, 1},
    {1, 2, 1, 2, 1, 1, 1, 2, 1, 2, 1},
    {1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
int level6[ROWS][COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 2, 1, 1, 1, 2, 2, 1, 1, 2, 1},
    {1, 2, 1, 2, 2, 2, 2, 2, 1, 2, 1},
    {1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1},
    {1, 2, 1, 2, 2, 2, 2, 2, 1, 2, 1},
    {1, 2, 1, 2, 1, 1, 1, 2, 1, 2, 1},
    {1, 3, 2, 2, 1, 2, 2, 2, 1, 2, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

// Function to convert int to string
std::string intToString(int num) {
    std::stringstream ss;
    ss << num;
    return ss.str();
}

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
    bool stunned;
    int stunEndTime; // Time when stun effect ends

    Enemy() : x(0), y(0), stunned(false), stunEndTime(0) {} // Default constructor
    Enemy(int startX, int startY) : x(startX), y(startY), stunned(false), stunEndTime(0) {}

    void moveRandomly() {
        if (!stunned) {
            int directions[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
            int randomDir = rand() % 4;
            int newX = x + directions[randomDir][0];
            int newY = y + directions[randomDir][1];
            if (maze[newY][newX] != 1) {
                x = newX;
                y = newY;
            }
        }
    }

    void stun(int currentTime) {
        stunned = true;
        stunEndTime = currentTime + 100; // 10 seconds (100 * 100ms)
    }

    void checkStun(int currentTime) {
        if (stunned && currentTime >= stunEndTime) {
            stunned = false;
        }
    }
};

// Main game class
class Game {
public:
    Player player;
    Enemy enemies[MAX_GHOSTS]; // Array to handle multiple enemies
    int numEnemies; // Number of active enemies
    int score;
    int lives;
    int totalCollectibles;
    int currentLevel;
    int currentTime; // Game time in 100ms units

    Game() : player(5, 5), score(0), lives(3), currentLevel(1), numEnemies(1), currentTime(0) {
        srand(time(0));
        loadLevel(1);
    }

    void loadLevel(int level) {
        if (level == 1) memcpy(maze, level1, sizeof(maze));
        else if (level == 2) memcpy(maze, level2, sizeof(maze));
        else if (level == 3) memcpy(maze, level3, sizeof(maze));

        totalCollectibles = 0;
        for (int i = 0; i < ROWS; ++i)
            for (int j = 0; j < COLS; ++j)
                if (maze[i][j] == 2) totalCollectibles++;

        player.x = 5; player.y = 5;
        numEnemies = currentLevel; // Increase the number of enemies with each level
        for (int i = 0; i < numEnemies; ++i) {
            enemies[i] = Enemy(6, 7); // Initialize enemies
        }
    }

    void resetPositions() {
        player.x = 5;
        player.y = 5;
        for (int i = 0; i < numEnemies; ++i) {
            enemies[i].x = 6;
            enemies[i].y = 7;
        }
    }

    void render() {
    std::ostringstream buffer; // Use an off-screen buffer
    buffer << "\033[2J\033[1;1H"; // Clear the screen and move the cursor to top-left

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (player.x == j && player.y == i) {
                buffer << "\033[1;33mP \033[0m"; // Pac-Man
            } else {
                bool enemyPrinted = false;
                for (int k = 0; k < numEnemies; ++k) {
                    if (enemies[k].x == j && enemies[k].y == i) {
                        buffer << (enemies[k].stunned ? "\033[1;35mS \033[0m" : "\033[1;31mE \033[0m");
                        enemyPrinted = true;
                        break;
                    }
                }
                if (!enemyPrinted) {
                    if (maze[i][j] == 1) buffer << "\033[1;34m# \033[0m"; // Wall
                    else if (maze[i][j] == 2) buffer << "\033[1;32m. \033[0m"; // Dot
                    else if (maze[i][j] == 3) buffer << "\033[1;36mB \033[0m"; // Boost
                    else buffer << "  "; // Empty space
                }
            }
        }
        buffer << "\n";
    }
    buffer << "Score: " << score << " | Lives: " << lives << "\n";

    std::cout << buffer.str(); // Output everything at once
}


    void showEndMessage(const std::string& message) {
        std::cout << message << "\n";
        std::cout << "Press any key to return to the main menu...\n";
        _getch();
    }

    void update() {
        currentTime++; // Increment game time in 100ms units

        if (maze[player.y][player.x] == 2) {
            maze[player.y][player.x] = 0;
            score++;
            totalCollectibles--;
        }

        // Check for boost item
        if (maze[player.y][player.x] == 3) {
            maze[player.y][player.x] = 0;
            for (int i = 0; i < numEnemies; ++i) {
                enemies[i].stun(currentTime); // Stun all enemies
            }
        }

        for (int i = 0; i < numEnemies; ++i) {
            enemies[i].checkStun(currentTime); // Check and update stun status
            enemies[i].moveRandomly();
            if (player.x == enemies[i].x && player.y == enemies[i].y && !enemies[i].stunned) {
                lives--;
                if (lives == 0) {
                    showEndMessage("Game Over! Final Score: " + intToString(score));
                    return;
                }
                resetPositions(); // Reset positions instead of reloading the level
                break;
            }
        }

        if (totalCollectibles == 0) {
            currentLevel++;
            if (currentLevel > 3) { // Update this if more levels are added
                showEndMessage("Congratulations! You won with a score of " + intToString(score) + "!");
                return;
            }
            loadLevel(currentLevel);
        }
    }

    void play() {
        char direction = ' ';  // Initialize with a dummy direction
        while (lives > 0) {
            render();
            if (_kbhit()) {
                direction = _getch();  // Update direction on key press
            }
            player.move(direction);
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
    system("cls");
    std::cout << "--- How to Play ---\n";
    std::cout << "- Use W/A/S/D to move Pacman\n";
    std::cout << "- Avoid the Ghosts\n";
    std::cout << "- Collect all dots to progress levels\n";
    std::cout << "- Collect boost items (B) to stun ghosts for 10 seconds\n";
    std::cout << "- You have 3 lives\n";
    std::cout << "Press Enter to continue...\n";
    std::cin.ignore();
    std::cin.get();
}

void tryagain() {
    char a;
    std::cout << "Invalid choice. Try again.\n";
    a = getch();
}

int main() {
    while (true) {
        system("cls");
        showMenu();
        char choice;
        choice = getch();
        switch (choice) {
            case '1': {
                Game game;
                game.play();
                system("cls");
                break;
            }
            case '2':
                showInstructions();
                break;
            case '3':
                std::cout << "Thanks for playing!\n";
                return 0;
            default:
                tryagain();
                break;
        }
    }
}
