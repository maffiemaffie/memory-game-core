/**
 * @file memoryGame.h
 * @author Elia Cohen
 * @brief Header file for all the core functionality for the memory game.
 * @version 0.1
 * @date 2023-11-11
 */

#ifndef MEMORYGAME_H
#define MEMORYGAME_H


#include <stdlib.h>

/**
 * @brief The current state of the game.
 *
 */
enum State { Starting, Active, Ending };

/**
 * @brief Contains values and length of a pattern.
 *
 */
struct Pattern {
    int values[200] = {}; /**< The pattern values.*/
    int length = 0; /**< The length of the pattern.*/
};

/**
 * @brief Contains the necessary data to handle a changed state event.
 *
 */
struct ChangedStateEventArgs {
    State state; /**< The new game state.*/
};

/**
 * @brief Contains the necessary data to handle a new pattern event.
 *
 */
struct NewPatternEventArgs {
    Pattern* pattern; /**< The new pattern.*/
};

/**
 * @brief Contains the necessary data to handle a game ended event.
 *
 */
struct GameEndedEventArgs {
    int score; /**< The final score.*/
};

/**
 * @brief Contains methods for running the memory game
 *
 */
class MemoryGame {
private:
    Pattern pattern; /**< The pattern.*/
    int compareIndex = 0; /**< The index of the next pattern step the user is expected to input.*/
    State state = Starting; /**< The current state of the game.*/

    /**
     * @brief Appends a step to the pattern.
     *
     */
    void getNextPattern();

    /**
     * @brief Processes an input and progresses the game.
     *
     * @param input The input (between 0 and 3)
     */
    void processNextInput(int input);

    /**
     * @brief Ends the game.
     *
     */
    void end();

    /**
     * @brief Contains methods for executing a game event to a single observer.
     *
     * @tparam T The event args parameter type that the event handler should accept.
     */
    template <typename T> class GameEvent {
    private:
        void (*observer)(T) = nullptr; /**< The observer called when the event occurs.*/
    public:
        /**
         * @brief Sets the observer for this game event.
         *
         * @param onEvent The observer.
         */
        void registerObserver(void (*onEvent)(T));

        /**
         * @brief Notifies the observer that this event has occurred.
         *
         * @param event The relevant data to pass to the observer.
         */
        void notifyObserver(T event);
    };

    GameEvent<ChangedStateEventArgs> changedState; /**< Event for when the @ref state changes.*/
    GameEvent<NewPatternEventArgs> newPattern; /**< Event for when the next @ref pattern is generated.*/
    GameEvent<GameEndedEventArgs> gameEnded; /**< Event for when the game ends.*/
public:
    /**
     * @brief Starts the game.
     *
     */
    void start();

    /**
     * @brief Notifies the game of a user input.
     *
     * @param value The input.
     * @return true The input was accepted.
     * @return false The input was rejected (out of range, out of turn)
     */
    bool input(int value);

    /**
     * @brief Sets an observer for the changed state event.
     *
     * @param onChangedState The event handler.
     */
    void registerChangedStateObserver(void (*onChangedState)(ChangedStateEventArgs));

    /**
     * @brief Sets an observer for the new pattern event.
     *
     * @param onNewPattern The event handler.
     */
    void registerNewPatternObserver(void (*onNewPattern)(NewPatternEventArgs));

    /**
     * @brief Sets an observer for the game ended event.
     *
     * @param onGameEnded The event handler.
     */
    void registerGameEndedObserver(void (*onGameEnded)(GameEndedEventArgs));
};

#endif // MEMORYGAME_H
