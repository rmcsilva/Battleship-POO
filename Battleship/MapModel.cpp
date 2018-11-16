#include "stdafx.h"
#include "MapModel.h"
#include "SeaModel.h"
#include "PortModel.h"
#include "GroundModel.h"

MapModel::MapModel(const int numLines, const int numColumns) : numLines(numLines), numColumns(numColumns) {
	if (numLines < MIN_LINES || numColumns < MIN_COLUMNS)
		throw 10;
}

MapModel::~MapModel()
{
	for (int i = 0; i<numLines; i++)
		for (int j = 0; j < numColumns; j++)
			delete(getCellAt(j, i));
}

int MapModel::getNumLines() const { return numLines; }
int MapModel::getNumColumns() const { return numColumns; }
int MapModel::getPirateProb() const { return pirateProb; }

void MapModel::setPirateProb(int prob) { pirateProb = prob; }

CellModel* MapModel::getCellAt(int x, int y) const {return map.at(x + (numColumns * y));}

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

void MapModel::addPortCellAt(int x, int y, char id,CellModel::CellOwner owner)
{
	switch (owner)
	{
	case CellModel::CellOwner::PLAYER:
		map.push_back(new PortModel(x, y, id, CellModel::CellOwner::PLAYER));
		break;
	case CellModel::CellOwner::PIRATE:
		map.push_back(new PortModel(x, y, id, CellModel::CellOwner::PIRATE));
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

CellModel* MapModel::getCellAbove(const CellModel* currentCell) const
{
	int x = currentCell->getX();
	int y = currentCell->getY();
	if (y == 0)
		return getCellAt(x, getNumLines() - 1);
	else
		return getCellAt(x, y - 1);
}

CellModel* MapModel::getCellBelow(const CellModel* currentCell) const
{
	int x = currentCell->getX();
	int y = currentCell->getY();
	if (y == (getNumLines() - 1))
		return getCellAt(x, 0);
	else
		return getCellAt(x, y + 1);
}

CellModel* MapModel::getCellRight(const CellModel* currentCell) const
{
	int x = currentCell->getX();
	int y = currentCell->getY();
	if (x == (getNumColumns() - 1))
		return getCellAt(0, y);
	else
		return getCellAt(x + 1, y);
}

CellModel* MapModel::getCellLeft(const CellModel* currentCell) const
{
	int x = currentCell->getX();
	int y = currentCell->getY();
	if (x == 0)
		return getCellAt((getNumColumns() - 1), y);
	else
		return getCellAt(x - 1, y);
}

CellModel* MapModel::getCellAboveRight(const CellModel* currentCell) const
{
	CellModel *temp = getCellAbove(currentCell);
	return getCellRight(temp);
}

CellModel* MapModel::getCellAboveLeft(const CellModel* currentCell) const
{
	CellModel *temp = getCellAbove(currentCell);
	return getCellLeft(temp);
}

CellModel* MapModel::getCellBelowRight(const CellModel* currentCell) const
{
	CellModel *temp = getCellBelow(currentCell);
	return getCellRight(temp);
}

CellModel* MapModel::getCellBelowLeft(const CellModel* currentCell) const
{
	CellModel *temp = getCellBelow(currentCell);
	return getCellLeft(temp);
}