#include "stdafx.h"
#include "SeaModel.h"


CellModel::Type SeaModel::getType() {
    return Type::SEA;
}

SeaModel::SeaModel(int x, int y) : CellModel(x, y) {}
