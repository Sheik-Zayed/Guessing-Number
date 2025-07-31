#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// Player Class
class Player {
public:
    string name;
    char avatar;
    int score;

    void createProfile() {
        cout << "Enter your name: ";
        getline(cin, name);
        cout << "Choose your avatar (single character): ";
        cin >> avatar;
        score = 0;
    }

    void showProfile() const {
        cout << "\nPlayer Profile:\n";
        cout << "Name: " << name << "\n";
        cout << "Avatar: " << avatar << "\n";
        cout << "Score: " << score << "\n";
    }
};

// Game Class
class Game {
private:
    int level;
    int maxRange;
    int maxAttempts;
    int number;
    bool hintUsed;

public:
    Game() : level(1), maxRange(50), maxAttempts(10), hintUsed(false) {}

    void showRules() const {
        cout << "\nGame Rules:\n";
        cout << "1. Guess the secret number between 1 and " << maxRange << ".\n";
        cout << "2. You have " << maxAttempts << " attempts to guess correctly.\n";
        cout << "3. You can use a hint once per game to know if the number is even or odd.\n";
        cout << "4. Your score is based on remaining attempts.\n";
    }

    void setupLevel() {
        maxRange = level * 50;
        maxAttempts = max(10 - level, 3);
        number = rand() % maxRange + 1;
        hintUsed = false;
    }

    void playLevel(Player& player) {
        int guess;
        bool guessedCorrectly = false;

        cout << "\nLevel " << level << ": Guess a number between 1 and " << maxRange << ".\n";
        cout << "You have " << maxAttempts << " attempts.\n";

        for (int i = 0; i < maxAttempts; ++i) {
            cout << "Attempt " << i + 1 << ": Enter your guess: ";
            cin >> guess;

            if (guess == number) {
                cout << "Congratulations! You've guessed the number correctly.\n";
                player.score += (maxAttempts - i) * 10;
                guessedCorrectly = true;
                break;
            } else if (guess < number) {
                cout << "Too low! Try a higher number.\n";
            } else {
                cout << "Too high! Try a lower number.\n";
            }

            if (i == maxAttempts - 1) {
                cout << "Sorry, you've used all attempts. The correct number was " << number << ".\n";
            }
        }

        if (!guessedCorrectly && !hintUsed) {
            char useHint;
            cout << "Would you like to use a hint (Y/N)? ";
            cin >> useHint;

            if (useHint == 'Y' || useHint == 'y') {
                hintUsed = true;
                cout << "The secret number is " << (number % 2 == 0 ? "even" : "odd") << ".\n";
            }
        }
    }

    void start(Player& player) {
        while (true) {
            setupLevel();
            showRules();
            playLevel(player);

            if (level >= 5 || player.score >= 100) {
                cout << "\nGame Over! Final Score: " << player.score << "\n";
                break;
            }

            ++level;
            char continueGame;
            cout << "Do you want to proceed to the next level (Y/N)? ";
            cin >> continueGame;

            if (continueGame != 'Y' && continueGame != 'y') {
                cout << "Thank you for playing! Final Score: " << player.score << "\n";
                break;
            }
        }
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0)));

    Player player;
    player.createProfile();
    player.showProfile();

    Game game;
    game.start(player);

    return 0;
}
