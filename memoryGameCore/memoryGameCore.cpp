#include "memoryGameCore.h"

int* MemoryGame::getNextPattern() {
	int nextValue = rand() * 4 / RAND_MAX;
	pattern.push_back(nextValue);

	int* patternArray = new int[pattern.size()];
	for (int i = 0; i < pattern.size(); i++) {
		patternArray[i] = pattern.at(i);
	}
}
