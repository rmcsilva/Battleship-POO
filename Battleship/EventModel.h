#pragma once

class EventModel
{
	int currentTurn = 0;
	const int turnDuration;

protected:
	void incrementTurn();

public:
	EventModel(int max_turns);

	virtual ~EventModel();

	enum class Type {LULL, MERMAID, RIOT, STORM};

	virtual Type getType() = 0;

	bool isOver();

	virtual bool executeEvent() = 0;
};