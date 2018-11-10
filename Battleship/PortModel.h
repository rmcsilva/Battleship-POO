#pragma once
#include "CellModel.h"

class PortModel : public CellModel{
	CellModel::Owner owner;
public:
    PortModel(int x, int y, CellModel::Owner owner);

    Type getType() override;
};