#include "head.h"

// Balloon class implementation
Balloon::Balloon() : x(0), y(0), active(false), symbol('O') {}

Balloon::Balloon(int startX, int startY) : x(startX), y(startY), active(true), symbol('O') {}

void Balloon::move() {
    if (active) {
        y++;
        if (y >= HEIGHT - 1) {
            active = false;
        }
    }
}

void Balloon::deactivate() {
    active = false;
}

bool Balloon::isActive() const {
    return active;
}

int Balloon::getX() const {
    return x;
}

int Balloon::getY() const {
    return y;
}

char Balloon::getSymbol() const {
    return symbol;
}

// Arrow class implementation
Arrow::Arrow() : x(0), y(0), active(false) {}

Arrow::Arrow(int startX, int startY) : x(startX), y(startY), active(true) {}

void Arrow::move() {
    if (active) {
        y--;
        if (y < 0) {
            active = false;
        }
    }
}

void Arrow::deactivate() {
    active = false;
}

bool Arrow::isActive() const {
    return active;
}

int Arrow::getX() const {
    return x;
}

int Arrow::getY() const {
    return y;
}

// Bow class implementation
Bow::Bow() : x(WIDTH / 2), y(HEIGHT - 2) {}

void Bow::moveLeft() {
    if (x > 1) {
        x--;
    }
}

void Bow::moveRight() {
    if (x < WIDTH - 2) {
        x++;
    }
}

int Bow::getX() const {
    return x;
}

int Bow::getY() const {
    return y;
}

Arrow Bow::shoot() {
    return Arrow(x, y - 1);
}

// Game class implementation
Game::Game(bool hardMode, int balloonCount, int arrowLimitCount)
    : score(0), totalBalloons(balloonCount), balloonsShot(0), 
      arrowsUsed(0), arrowLimit(arrowLimitCount), isHardMode(hardMode), frameCount(0) {
    srand(time(0));
}

void Game::initializeBoard() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1) {
                gameBoard[i][j] = '#';
            } else {
                gameBoard[i][j] = ' ';
            }
        }
    }
}

void Game::updateBoard() {
    initializeBoard();

    // Place bow
    gameBoard[bow.getY()][bow.getX()] = '^';

    // Place balloons
    for (const auto& balloon : balloons) {
        if (balloon.isActive()) {
            int bx = balloon.getX();
            int by = balloon.getY();
            if (bx >= 0 && bx < WIDTH && by >= 0 && by < HEIGHT) {
                gameBoard[by][bx] = balloon.getSymbol();
            }
        }
    }

    // Place arrows
    for (const auto& arrow : arrows) {
        if (arrow.isActive()) {
            int ax = arrow.getX();
            int ay = arrow.getY();
            if (ax >= 0 && ax < WIDTH && ay >= 0 && ay < HEIGHT) {
                gameBoard[ay][ax] = '|';
            }
        }
    }
}

void Game::displayBoard() {
    setCursorPosition(0, 0);
    
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            cout << gameBoard[i][j];
        }
        cout << endl;
    }

    cout << "\n==============================================\n";
    cout << "Mode: " << (isHardMode ? "HARD" : "EASY") << endl;
    cout << "Score: " << score << " | Balloons Shot: " << balloonsShot 
         << "/" << totalBalloons << endl;
    
    if (isHardMode) {
        cout << "Arrows Used: " << arrowsUsed << "/" << arrowLimit << endl;
    } else {
        cout << "Arrows Used: " << arrowsUsed << " (Unlimited)" << endl;
    }
    
    cout << "==============================================\n";
    cout << "Controls: A/D - Move Left/Right | SPACE - Shoot | Q - Quit\n";
}

void Game::spawnBalloon() {
    if (balloonsShot < totalBalloons) {
        int spawnX = rand() % (WIDTH - 4) + 2;
        balloons.push_back(Balloon(spawnX, 1));
    }
}

void Game::updateBalloons() {
    for (auto& balloon : balloons) {
        if (balloon.isActive()) {
            balloon.move();
        }
    }
}

void Game::updateArrows() {
    for (auto& arrow : arrows) {
        if (arrow.isActive()) {
            arrow.move();
        }
    }
}

void Game::checkCollisions() {
    for (auto& arrow : arrows) {
        if (!arrow.isActive()) continue;
        
        for (auto& balloon : balloons) {
            if (!balloon.isActive()) continue;
            
            if (arrow.getX() == balloon.getX() && arrow.getY() == balloon.getY()) {
                arrow.deactivate();
                balloon.deactivate();
                balloonsShot++;
                score += 10;
                break;
            }
        }
    }
}

bool Game::isGameOver() {
    if (isHardMode) {
        // Hard mode: game over if arrows exhausted or all balloons shot
        if (arrowsUsed >= arrowLimit && arrows.empty()) {
            return balloonsShot >= totalBalloons;
        }
        if (balloonsShot >= totalBalloons) {
            return true;
        }
        // Check if player has lost (no arrows left and can't win)
        bool hasActiveArrows = false;
        for (const auto& arrow : arrows) {
            if (arrow.isActive()) {
                hasActiveArrows = true;
                break;
            }
        }
        if (arrowsUsed >= arrowLimit && !hasActiveArrows && balloonsShot < totalBalloons) {
            return true;
        }
    } else {
        // Easy mode: game over when all balloons are shot
        return balloonsShot >= totalBalloons;
    }
    return false;
}

void Game::handleInput() {
    if (_kbhit()) {
        char key = _getch();
        
        if (key == 'a' || key == 'A') {
            bow.moveLeft();
        } else if (key == 'd' || key == 'D') {
            bow.moveRight();
        } else if (key == ' ') {
            if (!isHardMode || arrowsUsed < arrowLimit) {
                arrows.push_back(bow.shoot());
                arrowsUsed++;
            }
        } else if (key == 'q' || key == 'Q') {
            exit(0);
        }
    }
}

void Game::run() {
    clearScreen();
    
    while (!isGameOver()) {
        handleInput();
        
        frameCount++;
        
        // Spawn balloons periodically
        if (frameCount % BALLOON_SPAWN_RATE == 0 && balloonsShot < totalBalloons) {
            int activeBalloons = 0;
            for (const auto& b : balloons) {
                if (b.isActive()) activeBalloons++;
            }
            if (activeBalloons < 5) {
                spawnBalloon();
            }
        }
        
        updateBalloons();
        updateArrows();
        checkCollisions();
        updateBoard();
        displayBoard();
        
        Sleep(100);
    }
    
    // Game over screen
    clearScreen();
    cout << "\n\n";
    cout << "==============================================\n";
    cout << "              GAME OVER!\n";
    cout << "==============================================\n";
    
    if (hasWon()) {
        cout << "          *** YOU WIN! ***\n";
    } else {
        cout << "          *** YOU LOSE! ***\n";
    }
    
    cout << "\nFinal Score: " << score << endl;
    cout << "Balloons Shot: " << balloonsShot << "/" << totalBalloons << endl;
    cout << "Arrows Used: " << arrowsUsed;
    if (isHardMode) {
        cout << "/" << arrowLimit;
    }
    cout << endl;
    cout << "==============================================\n\n";
}

int Game::getScore() const {
    return score;
}

bool Game::hasWon() const {
    return balloonsShot >= totalBalloons;
}

// Utility functions
void clearScreen() {
    system("cls");
}

void setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void displayMenu() {
    clearScreen();
    cout << "\n\n";
    cout << "==============================================\n";
    cout << "          BALLOON SHOOTER GAME\n";
    cout << "==============================================\n";
    cout << "\n";
    cout << "  1. Easy Mode (Unlimited Arrows)\n";
    cout << "  2. Hard Mode (Limited Arrows)\n";
    cout << "  3. Exit\n";
    cout << "\n";
    cout << "==============================================\n";
    cout << "Enter your choice (1-3): ";
}

int getMenuChoice() {
    int choice;
    cin >> choice;
    return choice;
}
