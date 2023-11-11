#include "memoryGame.h"

template <typename T> void MemoryGame::GameEvent<T>::registerObserver(void (*onEvent)(T)) {
	observer = onEvent;
}

template <typename T> void MemoryGame::GameEvent<T>::notifyObserver(T data) {
	observer(data);
}

void MemoryGame::start() {
	state = Starting;
	changedState.notifyObserver(state);
	compareIndex = 0;
	pattern.length = 0;

	state = Active;
	changedState.notifyObserver(state);
	getNextPattern();
}

template <typename T> bool MemoryGame::registerObserver(Event event, void (*onEvent)(T)) {
	switch (event) {
	case onChangedState:
		changedState.registerObserver(onEvent);
		break;
	case onGameEnded:
		gameEnded.registerObserver(onEvent);
		break;
	case onNewPattern:
		newPattern.registerObserver(onEvent);
		break;
	default:
		return false;
	}
	return true;
}

template bool MemoryGame::registerObserver<Pattern*>(Event, void (*)(Pattern*));
template bool MemoryGame::registerObserver<State>(Event, void (*)(State));
template bool MemoryGame::registerObserver<int>(Event, void (*)(int));

void MemoryGame::getNextPattern() {
	int nextValue = rand() * 4 / RAND_MAX;
	pattern.values[pattern.length++] = nextValue;

	newPattern.notifyObserver(&pattern);
}

bool MemoryGame::input(int value) {
	if (state != Active) return false; // not ready for input
	if (value < 0 || value > 3) return false; // out of range

	processNextInput(value);
	return true;
}

void MemoryGame::processNextInput(int input) {
	// check that pattern is correct
	if (pattern.values[compareIndex] == input) compareIndex++;
	else return end();

	// continue game
	if (compareIndex == pattern.length) {
		compareIndex = 0;
		getNextPattern();
	}
}

void MemoryGame::end() {
	state = Ending;
	changedState.notifyObserver(state);
	gameEnded.notifyObserver(pattern.length);
}
