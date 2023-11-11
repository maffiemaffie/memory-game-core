#include <iostream>
#include "memoryGameCore.h"

using namespace std;

State currentState;

void displayPattern(Pattern* pattern) {
	for (int i = 0; i < pattern->length; i++) {
		cout << pattern->values[i] << endl;
	}
}

void changeState(State state) {
	currentState = state;
}

void gameOver(int score) {
	cout << "Game over, your score: " << score << endl;
}

int main() {
	MemoryGame game;

	game.registerObserver(onNewPattern, &displayPattern);
	game.registerObserver(onChangedState, &changeState);
	game.registerObserver(onGameEnded, &gameOver);

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