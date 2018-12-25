#pragma once
#include "PortModel.h"
#include "SeaModel.h"

enum class GameState { SETUP, GAME, END };

class GameModel
{
	static const int COINS_EASY;

	static const int EVENT_PROB_EASY;
	static const int STORM_EVENT_PROB_EASY;
	static const int MERMAID_EVENT_PROB_EASY;
	static const int LULL_EVENT_PROB_EASY;
	static const int RIOT_EVENT_PROB_EASY;

	int eventProb, stormProb, mermaidProb, lullProb, riotProb;
	//TODO: Change consts of the prices according to game difficulty
	int shipPrice, soldierPrice;
	int fishSellPrice, merchSellPrice;
	int merchBuyPrice;
	double coins;
	double score=0;

	std::vector<ShipModel*> friendlyShips;
	std::vector<ShipModel*> enemyShips;

	GameState state;

public:
	GameModel();
	~GameModel();

	GameState getGameState() const;
	double getPlayerCoins() const;
	int getShipPrice() const;
	int getSoldierPrice() const;
	int getFishSellPrice() const;
	int getMerchSellPrice() const;
	int getMerchBuyPrice() const;
	std::vector<ShipModel*> getFriendlyShips() const;
	std::vector<ShipModel*> getEnemyShips() const;
	int getEventProbability() const;
	int getStormEventProbability() const;
	int getMermaidEventProbability() const;
	int getLullEventProbability() const;
	int getRiotEventProbability() const;

	void setGameState(GameState state);
	void setPlayerCoins(int amount);
	void setShipPrice(int amount);
	void setSoldierPrice(int amount);
	void setFishSellPrice(int amount);
	void setMerchSellPrice(int amount);
	void setMerchBuyPrice(int amount);
	void setEventProbability(int prob);
	void setStormEventProbability(int prob);
	void setMermaidEventProbability(int prob);
	void setCalmEventProbability(int prob);
	void setRiotEventProbability(int prob);

	void addFriendlyShip(ShipModel* ship);
	void addPirateShip(ShipModel* ship);

	bool removeFriendlyShip(ShipModel* ship);
	bool removeEnemyShip(ShipModel* ship);

	void changeShipOwner(ShipModel* ship, Navigation navigation);

	void addCoins(double amount);
	bool removeCoins(int amount);

	bool canRemoveCoins(int amount);
};

