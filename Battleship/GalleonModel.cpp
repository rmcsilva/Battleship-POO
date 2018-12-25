#include "stdafx.h"
#include "GalleonModel.h"

const int GalleonModel::MAX_SOLDIERS = 40;
const int GalleonModel::MAX_CAPACITY = 70;
const int GalleonModel::MAX_WATER = 400;
const int GalleonModel::MAX_MOVES = 1;
const int GalleonModel::STORM_SOLDIERS_AFFECTED_PERCENTAGE = 10;
const int GalleonModel::STORM_SINK_PROB = 40;

GalleonModel::GalleonModel(CellModel* position) : ShipModel(MAX_CAPACITY, MAX_SOLDIERS, MAX_WATER, MAX_MOVES, Owner::PLAYER, position)
{
}


GalleonModel::~GalleonModel()
{
}

ShipModel::Type GalleonModel::getType() const {return ShipModel::Type::GALLEON;}

bool GalleonModel::stormAttack()
{
	int soldiersLost = (soldiers * STORM_SOLDIERS_AFFECTED_PERCENTAGE) / 100;
	soldiers -= soldiersLost;

	//TODO: Sink probability
	int random = rand() % 100;

	if (random < 40) return false;

	return true;
}

std::string GalleonModel::getAsString() const {return "G";}

GalleonModel* GalleonModel::clone() {
	return new GalleonModel(*this);
}
