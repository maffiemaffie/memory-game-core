/// <summary>
/// The current state of the game.
/// </summary>
enum State { Starting, Active, Ending };

/// <summary>
/// The game events emitted during gameplay.
/// </summary>
enum Event { onChangedState, onNewPattern, onGameEnded };

class MemoryGame {
private:
	int* pattern = int[200];
  int patternLength = 0;
	int compareIndex = 0;
	State gameState = Starting;

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
		void (*)(T) observers;
	public:
		void registerObserver(void (*func)(T));
		void detachObserver(void (*func)(T));
		void notifyAllObservers(T data);
	};

	GameEvent<State> changedState;
	GameEvent<int*, int> newPattern;
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
	/// Attaches an observer to a specified game event.
	/// </summary>
	/// <param name="event">The event to attach the observer to.</param>
	/// <param name="onEvent">The event handler.</param>
	/// <returns>True if successful.</returns>
	bool registerObserver(Event event, void (*onEvent)(auto));

	/// <summary>
	/// Detaches an observer from a specified game event.
	/// </summary>
	/// <param name="event">The event to detach the observer from.</param>
	/// <param name="onEvent">The event handler.</param>
	/// <returns>True if successful.</returns>
	bool detachObserver(Event event, void (*onEvent)(auto));
};
