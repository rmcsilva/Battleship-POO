#include "stdafx.h"
#include "CellModel.h"

CellModel::CellModel(int x, int y) : x(x), y(y) {}

int CellModel::getX() const {return x;}
int CellModel::getY() const {return y;}

bool CellModel::operator==(CellModel const& cell) const {return this->x == cell.getX() && this->y == cell.getY();}
