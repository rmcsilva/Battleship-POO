#pragma once

class EventModel
{
	int currentTurn;
	const int turnDuration;

protected:
	void incrementTurn();

public:
	EventModel(int max_turns);

	enum class Type {LULL, MERMAID, RIOT, STORM};

	virtual Type getType() = 0;

	bool isOver();

	virtual bool executeEvent() = 0;
};

