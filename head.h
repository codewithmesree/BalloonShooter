#ifndef HEAD_H
#define HEAD_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

// Constants
const int WIDTH = 50;
const int HEIGHT = 20;
const int BALLOON_SPAWN_RATE = 3;

// Class declarations
class Balloon {
private:
    int x, y;
    bool active;
    char symbol;

public:
    Balloon();
    Balloon(int startX, int startY);
    void move();
    void deactivate();
    bool isActive() const;
    int getX() const;
    int getY() const;
    char getSymbol() const;
};

class Arrow {
private:
    int x, y;
    bool active;

public:
    Arrow();
    Arrow(int startX, int startY);
    void move();
    void deactivate();
    bool isActive() const;
    int getX() const;
    int getY() const;
};

class Bow {
private:
    int x, y;

public:
    Bow();
    void moveLeft();
    void moveRight();
    int getX() const;
    int getY() const;
    Arrow shoot();
};

class Game {
private:
    Bow bow;
    vector<Balloon> balloons;
    vector<Arrow> arrows;
    int score;
    int totalBalloons;
    int balloonsShot;
    int arrowsUsed;
    int arrowLimit;
    bool isHardMode;
    int frameCount;
    char gameBoard[HEIGHT][WIDTH];

    void initializeBoard();
    void updateBoard();
    void displayBoard();
    void spawnBalloon();
    void updateBalloons();
    void updateArrows();
    void checkCollisions();
    bool isGameOver();

public:
    Game(bool hardMode, int balloonCount, int arrowLimitCount = -1);
    void run();
    void handleInput();
    int getScore() const;
    bool hasWon() const;
};

// Utility functions
void clearScreen();
void setCursorPosition(int x, int y);
void displayMenu();
int getMenuChoice();

#endif
