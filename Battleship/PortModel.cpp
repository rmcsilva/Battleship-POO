#include "stdafx.h"
#include "PortModel.h"

PortModel::PortModel(int x, int y) : CellModel(x, y) {}

CellModel::Type PortModel::getType() {
    return Type::PORT;
}

