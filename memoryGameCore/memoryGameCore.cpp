#include "memoryGameCore.h"

void MemoryGame::start() {
	state = MemoryGame::State::Starting;
	changedState.notifyAllObservers(state);
	compareIndex = 0;
	pattern = int[256];
  patternLength = 0;

	state = MemoryGame::State::Active;
	changedState.notifyAllObservers(state);
	newPattern.notifyAllObservers(getNextPattern());
}

void MemoryGame::registerObserver(Event event, void (*onEvent)(auto)) {
	switch (event) {
	case MemoryGame::Event::onChangedState:
		changedState.registerObserver(onEvent);
		break;
	case MemoryGame::Event::onGameEnded:
		gameEnded.registerObserver(onEvent);
		break;
	case MemoryGame::Event::onNewPattern:
		newPattern.registerObserver(onEvent);
		break;
	default:
		return false;
	}
	return true;
}

bool MemoryGame::detachObserver(Event event, void (*onEvent)(auto)) {
	switch (event) {
	case MemoryGame::Event::onChangedState:
		changedState.detachObserver(onEvent);
		break;
	case MemoryGame::Event::onGameEnded:
		gameEnded.detachObserver(onEvent);
		break;
	case MemoryGame::Event::onNewPattern:
		newPattern.detachObserver(onEvent);
		break;
	default:
		return false;
	}

	return true;
}

void MemoryGame::getNextPattern() {
	int nextValue = rand() * 4 / RAND_MAX;
	pattern[patternLength++] = nextValue;

  newPattern.notifyAllObservers(pattern, patternLength);
}

bool MemoryGame::input(int value) {
	if (gameState != MemoryGame::State::Active) return false; // not ready for input
	if (input < 0 || input > 3) return false; // out of range

	processNextInput(value);
	return true;
}

void MemoryGame::processNextInput(int input) {
	// check that pattern is correct
	if (pattern[compareIndex] == input) compareIndex++;
	else return end();

	// continue game
	if (compareIndex == patternLength) {
		compareIndex = 0;
		getNextPattern();
	}
}

void MemoryGame::end() {
	state = MemoryGame::State::Ending;
	changedState.notifyAllObservers(state);
	gameEnded.notifyAllObservers(patternLength);
}
