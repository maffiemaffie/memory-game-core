#include "memoryGameCore.h"

void MemoryGame::start() {
	state = MemoryGame::State::Starting;
	changedState.notifyAllObservers(state);
	compareIndex = 0;
	pattern = {};

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

int* MemoryGame::getNextPattern() {
	int nextValue = rand() * 4 / RAND_MAX;
	pattern.push_back(nextValue);

	int* patternArray = new int[pattern.size()];
	for (int i = 0; i < pattern.size(); i++) {
		patternArray[i] = pattern.at(i);
	}

	return patternArray;
}

bool MemoryGame::input(int value) {
	if (gameState != MemoryGame::State::Active) return false; // not ready for input
	if (input < 0 || input > 3) return false; // out of range

	processNextInput(value);
	return true;
}

void MemoryGame::processNextInput(int input) {
	// check that pattern is correct
	if (pattern.at(compareIndex) == input) compareIndex++;
	else return end();

	// continue game
	if (compareIndex == pattern.size()) {
		compareIndex = 0;
		newPattern.notifyAllObservers(getNextPattern());
	}
}

void MemoryGame::end() {
	state = MemoryGame::State::Ending;
	changedState.notifyAllObservers(state);
	gameEnded.notifyAllObservers(pattern.size());
}