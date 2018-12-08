#pragma once
#include "EventModel.h"
#include "SeaModel.h"

class LullModel : public EventModel
{
	static const int TURN_DURATION;
	static const int GOLD_BONUS;
	int *playerCoins;
	std::vector<SeaModel*> affectedPositions;

public:
	LullModel(std::vector<SeaModel*> affectedPositions, int *playerCoins);
	~LullModel();

	std::vector<SeaModel*> getAffectedPositions() const;

	Type getType() override;
	bool executeEvent() override;
};

