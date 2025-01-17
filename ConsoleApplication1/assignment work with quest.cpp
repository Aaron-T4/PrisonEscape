#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>

using namespace std;

void wait(unsigned timeout)
{
    timeout += clock();
    while (clock() < timeout)continue;
}

bool SetConsoleFont(const wchar_t* fontName, SHORT fontSize) {
    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);

    // Get the current console font info
    HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!GetCurrentConsoleFontEx(hConsoleOutput, FALSE, &fontInfo)) {
        return false; // Error getting current font
    }

    // Set the font name and size
    wcscpy_s(fontInfo.FaceName, fontName);
    fontInfo.dwFontSize.Y = fontSize;

    // Set the new font
    if (!SetCurrentConsoleFontEx(hConsoleOutput, FALSE, &fontInfo)) {
        return false; // Error setting font
    }

    return true;
}

bool SetConsoleFont(const wchar_t* fontName, SHORT fontSize) {
    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);

    // Get the current console font info
    HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!GetCurrentConsoleFontEx(hConsoleOutput, FALSE, &fontInfo)) {
        return false; // Error getting current font
    }

    // Set the font name and size
    wcscpy_s(fontInfo.FaceName, fontName);
    fontInfo.dwFontSize.Y = fontSize;

    // Set the new font
    if (!SetCurrentConsoleFontEx(hConsoleOutput, FALSE, &fontInfo)) {
        return false; // Error setting font
    }

    return true;
}



// Constants
const int MAX_INVENTORY_SIZE = 5;

// Player class
class Player {
public:
    int health;
    string inventory[MAX_INVENTORY_SIZE];
    int inventoryCount;

    Player() : health(100), inventoryCount(0) {
        for (int i = 0; i < MAX_INVENTORY_SIZE; ++i) {
            inventory[i] = "";
        }
    }
    //inventory system
    void addItem(const string& item) {
        if (inventoryCount < MAX_INVENTORY_SIZE) {
            inventory[inventoryCount++] = item;
            cout << item << " added to your inventory.\n";
        }
        else {
            cout << "Your inventory is full! Can't carry more items.\n";
        }
    }

    void displayInventory() {
        cout << "Inventory:\n";
        for (int i = 0; i < inventoryCount; ++i) {
            cout << "- " << inventory[i] << "\n";
        }
        if (inventoryCount == 0) {
            cout << "Your inventory is empty.\n";
        }
    }

    bool hasItem(const string& item) {
        for (int i = 0; i < inventoryCount; ++i) {
            if (inventory[i] == item) {
                return true;
            }
        }
        return false;
    }

    void removeItem(const string& item) {
        for (int i = 0; i < inventoryCount; ++i) {
            if (inventory[i] == item) {
                inventory[i] = inventory[--inventoryCount];
                inventory[inventoryCount] = "";
                cout << item << " removed from your inventory.\n";
                return;
            }
        }
        cout << item << " not found in your inventory.\n";
    }
};

// Combat system
bool combat(Player& player) {
    int guardHealth = 50;
    cout << "A guard confronts you! Prepare for battle!\n";

    while (guardHealth > 0 && player.health > 0) {
        int playerDamage = rand() % 20 + 5;
        int guardDamage = rand() % 15 + 5;

        guardHealth -= playerDamage;
        player.health -= guardDamage;

        cout << "You deal " << playerDamage << " damage to the guard.\n";
        if (guardHealth > 0) {
            cout << "The guard deals " << guardDamage << " damage to you.\n";
        }
    }

    if (player.health <= 0) {
        cout << "You have been defeated by the guard...\n";
        return false;
    }
    else {
        cout << "You defeated the guard!\n";
        return true;
    }
}

// Puzzle functions
bool solveRiddle() {
    string answer;
    cout << "Solve this riddle to progress:\n";
    cout << "\"I speak without a mouth and hear without ears. I have no body, but I come alive with wind. What am I?\"\n";
    getline(cin >> ws, answer); // Read full input
    if (answer == "echo" || answer == "Echo") {
        cout << "Correct! The way forward is clear.\n";
        return true;
    }
    cout << "Wrong answer! The guards catch you.\n";
    return false;
}

bool solveMathPuzzle() {
    int answer;
    cout << "Solve this puzzle to unlock the door:\n";
    cout << "What is 12 + 35 * 2?\n";
    cin >> answer;
    if (answer == 82) {
        cout << "Correct! The door unlocks.\n";
        return true;
    }
    cout << "Wrong answer! The alarm goes off.\n";
    return false;
}

bool solveMemoryPuzzle() {
    string color;
    cout << "Solve this memory puzzle to disable the alarm:\n";
    cout << "Remember this sequence: Red, Blue, Green, Yellow. What was the third color?\n";
    getline(cin >> ws, color);
    if (color == "Green" || color == "green") {
        cout << "Correct! The alarm is disabled.\n";
        return true;
    }
    cout << "Wrong answer! The alarm triggers, and guards are alerted.\n";
    return false;
}

// Game progression
void exploreCell(Player& player) {
    cout << "You search your prison cell and find a hidden lockpick.\n";
    player.addItem("Lockpick");
}

void escapeVent(Player& player) {
    if (player.hasItem("Lockpick")) {
        cout << "You use the lockpick to open the vent and crawl through the ducts.\n";
        player.removeItem("Lockpick");

        if (solveRiddle() && combat(player)) {
            cout << "You make it past the guard near the exit.\n";
        }
        else {
            player.health = 0;
        }
    }
    else {
        cout << "You need a lockpick to open the vent.\n";
    }
}

void escapeMainHall(Player& player) {
    cout << "You choose to escape through the main hall.\n";
    if (solveMathPuzzle() && combat(player)) {
        cout << "You defeat the guards in the main hall and escape.\n";
    }
    else {
        player.health = 0;
    }
}

void disableAlarm(Player& player) {
    cout << "You attempt to disable the security alarm.\n";
    if (solveMemoryPuzzle()) {
        cout << "The alarm is disabled, making your escape quieter.\n";
    }
    else {
        player.health = 0;
    }
}

void decideEnding(Player& player) {
    if (player.health > 50) {
        cout << "You successfully escape the prison with minimal injuries. You start a new life as a free person!\n";
    }
    else if (player.health > 0) {
        cout << "You escape the prison but are heavily injured. You barely make it out alive.\n";
    }
    else {
        cout << "Your escape attempt fails as you succumb to your injuries. Game over.\n";
    }
}

int main() {

    if (!SetConsoleFont(L"Pristina", 36))  
    {
        // Handle error if needed
    }

    std::string Name = "Your Name";
    for (int i = 0; i < Name.size(); i++)
    {
        std::cout << Name[i];
        wait(100);
    }

    if (!SetConsoleFont(L"Pristina", 36))
    {
        // Handle error if needed
    }
    srand(static_cast<unsigned>(time(0)));
    Player player;

    cout << "Welcome to the Prison Escape game!\n";
    cout << "Your objective is to escape the prison by solving puzzles, fighting guards, and making strategic choices.\n";

    bool gameRunning = true;

    while (gameRunning) {
        cout << "\n--- Current Health: " << player.health << " ---\n";
        cout << "Choose an action:\n";
        cout << "1. Search your cell\n";
        cout << "2. Escape through the vent\n";
        cout << "3. Fight through the main hall\n";
        cout << "4. Disable the security alarm\n";
        cout << "5. Check inventory\n";
        cout << "6. Quit game\n";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            exploreCell(player);
            break;
        case 2:
            escapeVent(player);
            decideEnding(player);
            gameRunning = false;
            break;
        case 3:
            escapeMainHall(player);
            decideEnding(player);
            gameRunning = false;
            break;
        case 4:
            disableAlarm(player);
            break;
        case 5:
            player.displayInventory();
            break;
        case 6:
            cout << "You decide to stay in your cell. Game over.\n";
            gameRunning = false;
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }

        if (player.health <= 0) {
            cout << "You have died. Game over.\n";
            gameRunning = false;
        }
    }

    return 0;
}
