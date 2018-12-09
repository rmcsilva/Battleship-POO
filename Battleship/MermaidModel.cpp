#include "stdafx.h"
#include "MermaidModel.h"

const int MermaidModel::TURN_DURATION = 1;
const int MermaidModel::SOLDIERS_LOST_PERCENTAGE = 10;

MermaidModel::MermaidModel(ShipModel* affectedShip) : EventModel(TURN_DURATION), affectedShip(affectedShip)
{
	
}


MermaidModel::~MermaidModel()
{
}

EventModel::Type MermaidModel::getType() {return Type::MERMAID;}

bool MermaidModel::executeEvent()
{
	if (isOver()) return false;

	affectedShip->mermaidAttack(SOLDIERS_LOST_PERCENTAGE);
	incrementTurn();
	return true;
}