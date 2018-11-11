#pragma once

class PlayerModel {
    std::string name = "Guest";
	const int COINS_EASY = 5000;
    int coins;

public:
    PlayerModel(const std::string &name, int coins);
    PlayerModel(int coins);
	PlayerModel();

    const std::string &getName() const;
    int getCoins() const;
	void setCoins(int coins);

    void addCoins(int amount);
    bool removeCoins(int amount);

    bool canRemoveCoins(int amount) const;


};