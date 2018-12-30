#pragma once
#include "SeaModel.h"

enum class GameState { SETUP, GAME, END };

class GameModel
{
	int eventProb, stormProb, mermaidProb, lullProb, riotProb;

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
	GameModel(const GameModel &game);

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
	double getPlayerScore() const;

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
	void setScore(int score);

	void addFriendlyShip(ShipModel* ship);
	void addPirateShip(ShipModel* ship);

	bool removeFriendlyShip(ShipModel* ship);
	bool removeEnemyShip(ShipModel* ship);

	void changeShipOwner(ShipModel* ship, Navigation navigation);

	void addCoins(double amount);
	bool removeCoins(int amount);

	bool canRemoveCoins(int amount);
};

