#include <iostream>
#include "MemoryGame.h"

using namespace std;

State currentState;

void displayPattern(NewPatternEventArgs event) {
    for (int i = 0; i < event.pattern->length; i++) {
        cout << event.pattern->values[i] << endl;
    }
}

void changeState(ChangedStateEventArgs event) {
    currentState = event.state;
}

void gameOver(GameEndedEventArgs event) {
    cout << "Game over, your score: " << event.score << endl;
}

int main() {
    srand(time(nullptr));
    MemoryGame game;

    game.registerNewPatternObserver(&displayPattern);
    game.registerChangedStateObserver(&changeState);
    game.registerGameEndedObserver(&gameOver);

    cout << "Let's play a game!" << endl;
    cout << "Start? ";

    char response;
    cin >> response;

    if (response != 'y') return 0;
    game.start();

    while (currentState == Active) {
        char nextInput;
        cin >> nextInput;

        game.input(nextInput - '0');
    }

    return 0;
}