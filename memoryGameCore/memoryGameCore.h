#include <vector>

class MemoryGame {
private:
	std::vector<int> pattern = {};
	int compareIndex = 0;
	enum State { Starting, Displaying, Listening, Ending };
	int gameState = State::Starting;

	int* getNextPattern();
	void processNextInput(int input);
	void end();

	template <typename T>
	class GameEvent {
	private:
		std::vector<void (*)(T)> observers;
	public:
		void registerObserver(void (*func)(T));
		void detachObserver(void (*func)(T));
		void notifyAllObservers(T data);
	};

	GameEvent<State> changedState;
	GameEvent<int*> newPattern;
public:
	void start();
	void input(int value);
};