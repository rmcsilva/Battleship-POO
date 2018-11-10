#include "stdafx.h"
#include "MapModel.h"
#include "SeaModel.h"
#include "PortModel.h"
#include "GroundModel.h"

MapModel::MapModel(const int numLines, const int numColumns) : numLines(numLines), numColumns(numColumns) {
	if (numLines < MIN_LINES || numColumns < MIN_COLUMNS)
		throw 10;
}


CellModel* MapModel::getCellAt(int x, int y) const
{
	return map.at(x + (numColumns * y));
}

void MapModel::addCellAt(int x, int y, CellModel::Type type)
{
	switch (type)
	{
	case CellModel::Type::SEA:
		map.push_back(new SeaModel(x, y));
		break;
	case CellModel::Type::GROUND:
		map.push_back(new GroundModel(x, y));
		break;
	}
}

void MapModel::addPortCellAt(int x, int y, CellModel::Owner owner)
{
	switch (owner)
	{
	case CellModel::Owner::PLAYER:
		map.push_back(new PortModel(x, y, CellModel::Owner::PLAYER));
		break;
	case CellModel::Owner::PIRATE:
		map.push_back(new PortModel(x, y, CellModel::Owner::PIRATE));
		break;
	}
}



//void MapModel::setCellAt(int x, int y, CellModel::Type type)
//{
//	CellModel* cell = getCellAt(x,y);
//
//	//TODO:Verify if cells can be of the specific type
//	switch (type)
//	{
//		case CellModel::Type::SEA:
//			cell = new SeaModel(x, y);
//			break;
//		case CellModel::Type::PORT:
//			cell = new PortModel(x, y);
//			break;
//		case CellModel::Type::GROUND:
//			cell = new GroundModel(x, y);
//			break;
//	}
//}

int MapModel::getNumLines() const
{
	return numLines;
}

int MapModel::getNumColumns() const
{
	return numColumns;
}
