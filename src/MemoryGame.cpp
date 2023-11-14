/**
 * @file MemoryGame.cpp
 * @author Elia Cohen
 * @brief Source file contains all the core functionality for the memory game.
 * @version 0.1
 * @date 2023-11-11
 */

#include "MemoryGame.h"

template<typename T> void MemoryGame::GameEvent<T>::registerObserver(void (*onEvent)(T)) {
  observer = onEvent;
}

template<typename T> void MemoryGame::GameEvent<T>::notifyObserver(T event) {
  observer(event);
}

void MemoryGame::start() {
  if (state != Starting) return;
  compareIndex = 0;
  pattern.length = 0;

  state = Active;
  ChangedStateEventArgs event;
  event.state = state;
  changedState.notifyObserver(event);
  getNextPattern();
}

void MemoryGame::registerChangedStateObserver(void (*onChangedState)(ChangedStateEventArgs)) {
  changedState.registerObserver(onChangedState);
}

void MemoryGame::registerNewPatternObserver(void (*onNewPattern)(NewPatternEventArgs)) {
  newPattern.registerObserver(onNewPattern);
}

void MemoryGame::registerGameEndedObserver(void (*onGameEnded)(GameEndedEventArgs)) {
  gameEnded.registerObserver(onGameEnded);
}

void MemoryGame::getNextPattern() {
  long random = rand();
  random = rand();
  int nextValue = random * 4 / RAND_MAX;
  pattern.values[pattern.length++] = nextValue;

  NewPatternEventArgs event;
  event.pattern = &pattern;
  newPattern.notifyObserver(event);
}

bool MemoryGame::input(int value) {
  if (state != Active) return false;         // not ready for input
  if (value < 0 || value > 3) return false;  // out of range

  processNextInput(value);
  return true;
}

void MemoryGame::processNextInput(int input) {
  // check that pattern is correct
  if (pattern.values[compareIndex] == input) {
    compareIndex++;
  } else {
    end();
    return;
  }

  // continue game
  if (compareIndex == pattern.length) {
    compareIndex = 0;
    getNextPattern();
  }
}

void MemoryGame::end() {
  state = Ending;

  ChangedStateEventArgs changedStateEventArgs;
  changedStateEventArgs.state = state;
  changedState.notifyObserver(changedStateEventArgs);

  GameEndedEventArgs gameEndedEventArgs;
  gameEndedEventArgs.score = pattern.length - 1;
  gameEnded.notifyObserver(gameEndedEventArgs);
}
