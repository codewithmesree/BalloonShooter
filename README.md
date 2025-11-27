# Balloon Shooter Game

A console-based balloon shooting game built with C++ using Object-Oriented Programming principles.

## Game Description

Shoot balloons with your bow and arrow to score points! The game features two difficulty levels:

### Easy Mode
- **Unlimited arrows** - shoot as many times as you need
- **20 balloons** to shoot down
- Game continues until all balloons are shot
- No way to lose, just keep shooting!

### Hard Mode
- **Limited arrows** (15 arrows for 10 balloons)
- **10 balloons** to shoot down
- **Win condition**: Shoot all 10 balloons before running out of arrows
- **Lose condition**: Run out of arrows before shooting all balloons

## Controls

- **A** or **a** - Move bow left
- **D** or **d** - Move bow right
- **SPACE** - Shoot arrow
- **Q** or **q** - Quit game

## How to Compile and Run

### Using g++ (MinGW on Windows)
```bash
g++ main.cpp notmain.cpp -o BalloonShooter.exe
BalloonShooter.exe
```

### Using Visual Studio
1. Create a new C++ Console Application project
2. Add all three files (head.h, main.cpp, notmain.cpp) to the project
3. Build and run (F5)

## Game Features

- **Object-Oriented Design**: Clean separation of concerns with Balloon, Arrow, Bow, and Game classes
- **Dynamic Gameplay**: Balloons spawn continuously and move down the screen
- **Collision Detection**: Arrows destroy balloons on contact
- **Score Tracking**: Earn 10 points for each balloon shot
- **Two Difficulty Levels**: Choose between relaxed unlimited mode or challenging limited mode
- **Console Graphics**: Simple ASCII-based visual representation

## File Structure

- **head.h** - Header file with class declarations and constants
- **main.cpp** - Main game loop and menu system
- **notmain.cpp** - Implementation of all classes and game logic

## Requirements

- Windows OS (uses Windows.h for console manipulation)
- C++ compiler with C++11 or later support
- Console that supports ANSI/Windows console functions

## Game Mechanics

- Balloons spawn from the top and move downward
- Your bow is at the bottom of the screen
- Shoot arrows upward to hit balloons
- Each successful hit awards 10 points
- In Easy mode, keep playing until all balloons are destroyed
- In Hard mode, manage your limited arrows wisely!

Enjoy the game! 🎯🎈
