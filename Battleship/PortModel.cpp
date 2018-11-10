#include "stdafx.h"
#include "PortModel.h"

PortModel::PortModel(int x, int y, CellModel::Owner owner) : CellModel(x, y), owner(owner) {}

CellModel::Type PortModel::getType() {
    return Type::PORT;
}

