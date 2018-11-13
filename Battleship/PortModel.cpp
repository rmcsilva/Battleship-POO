#include "stdafx.h"
#include "PortModel.h"

PortModel::PortModel(int x, int y, char id,CellModel::Owner owner) : CellModel(x, y), id(id), owner(owner) {}

CellModel::Type PortModel::getType() {
    return Type::PORT;
}

CellModel::Owner PortModel::getOwner() const
{
	return owner;
}

char PortModel::getID() const
{
	return id;
}

