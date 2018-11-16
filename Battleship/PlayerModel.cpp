#include "stdafx.h"
#include "PlayerModel.h"

PlayerModel::PlayerModel(const std::string &name, int coins) : name(name), coins(coins) {}

PlayerModel::PlayerModel(int coins) : coins(coins) {}

PlayerModel::PlayerModel() : PlayerModel(COINS_EASY)
{
	
}

const std::string &PlayerModel::getName() const {return name;}
int PlayerModel::getCoins() const {return coins;}

void PlayerModel::setCoins(int coins) {this->coins = coins;}

void PlayerModel::addCoins(double amount) {coins += amount;}

bool PlayerModel::removeCoins(int amount) {
    if (canRemoveCoins(amount)){
        coins -= amount;
        return true;
    }else{
        return false;
    }
}

bool PlayerModel::canRemoveCoins(int amount) const {return coins > amount;}
