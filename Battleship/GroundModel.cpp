#include "stdafx.h"
#include "GroundModel.h"

GroundModel::GroundModel(int x, int y) : CellModel(x, y) {}

CellModel::Type GroundModel::getType() {return Type::GROUND;}
