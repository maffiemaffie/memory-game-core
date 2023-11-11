#include <stdlib.h>

/// <summary>
/// The current state of the game.
/// </summary>
enum State { Starting, Active, Ending };

/// <summary>
/// The game events emitted during gameplay.
/// </summary>
enum Event { onChangedState, onNewPattern, onGameEnded };

struct Pattern {
	int values[200] = {};
	int length = 0;
};

class MemoryGame {
private:
	Pattern pattern;
	int compareIndex = 0;
	State state = Starting;

	/// <summary>
	/// Appends a step to the pattern.
	/// </summary>
	void getNextPattern();

	/// <summary>
	/// Processes an input and progresses the game.
	/// </summary>
	/// <param name="input">The input (between 0 and 3).</param>
	void processNextInput(int input);

	/// <summary>
	/// Ends the game.
	/// </summary>
	void end();

	template <typename T> class GameEvent {
	private:
		void (*observer)(T) = nullptr;
	public:
		/// <summary>
		/// Sets the observer for this game event.
		/// </summary>
		/// <param name="event">The event to set the observer to.</param>
		void registerObserver(void (*onEvent)(T));

		/// <summary>
		/// Notifies the observer that this event has occured.
		/// </summary>
		/// <param name="data">The relevant data to pass to the observer.</param>
		void notifyObserver(T data);
	};

	GameEvent<State> changedState;
	GameEvent<Pattern*> newPattern;
	GameEvent<int> gameEnded;
public:
	/// <summary>
	/// Starts the game.
	/// </summary>
	void start();

	/// <summary>
	/// Notifies the game of a user input.
	/// </summary>
	/// <param name="value">The input.</param>
	/// <returns>True if the input is accepted.</returns>
	bool input(int value);

	/// <summary>
	/// Sets the observer to a specified game event.
	/// </summary>
	/// <param name="event">The event to set the observer to.</param>
	/// <param name="onEvent">The event handler.</param>
	/// <returns>True if successful.</returns>
	template <typename T> bool registerObserver(Event event, void (*onEvent)(T));
};
