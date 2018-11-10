#pragma once
#include <string>

class PlayerModel {
    std::string name = "Guest";
    int coins;

public:
    PlayerModel(const std::string &name, int coins);
    PlayerModel(int coins);

    const std::string &getName() const;
    int getCoins() const;

    void addCoins(int amount);
    bool removeCoins(int amount);

    bool canRemoveCoins(int amount) const;


};