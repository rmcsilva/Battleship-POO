#pragma once
#include "CellModel.h"

class PortModel : public CellModel{
	char id;
	CellModel::Owner owner;
	int numSoldiers = 100;
public:
    PortModel(int x, int y, char id,CellModel::Owner owner);

    Type getType() override;
	Owner getOwner() const;
	char getID() const;
};