#include "head.h"

int main() {
    int choice;
    
    while (true) {
        displayMenu();
        choice = getMenuChoice();
        
        switch (choice) {
            case 1: {
                // Easy Mode - Unlimited arrows, 20 balloons
                Game easyGame(false, 20);
                easyGame.run();
                
                cout << "\nPress any key to return to menu...";
                _getch();
                break;
            }
            case 2: {
                // Hard Mode - Limited arrows (15 arrows for 10 balloons)
                Game hardGame(true, 10, 15);
                hardGame.run();
                
                cout << "\nPress any key to return to menu...";
                _getch();
                break;
            }
            case 3: {
                cout << "\nThank you for playing! Goodbye!\n";
                return 0;
            }
            default: {
                cout << "\nInvalid choice! Please try again.\n";
                Sleep(1500);
                break;
            }
        }
    }
    
    return 0;
}
