#pragma once
#include "CellModel.h"

class GroundModel : public CellModel{
public:
    GroundModel(int x, int y);

    Type getType() override;

	GroundModel* clone() override;
};
