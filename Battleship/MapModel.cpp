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
std::vector<SeaModel*> MapModel::getSeaCells() const {return seaCells;}

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

void MapModel::addPortCellAt(int x, int y, char id,Owner owner)
{
	switch (owner)
	{
	case Owner::PLAYER:
		map.push_back(new PortModel(x, y, id, Owner::PLAYER));
		break;
	case Owner::ENEMY:
		map.push_back(new PortModel(x, y, id, Owner::ENEMY));
		break;
	}
}

void MapModel::addSeaCell(SeaModel* cell) {seaCells.push_back(cell);}

std::vector<SeaModel*> MapModel::getRandom2x2ContinuousSeaCells() const
{
	std::vector<SeaModel*> continuousCells;

	int randomCell = rand() % seaCells.size();
	bool isValid = false;


	do
	{
		SeaModel* startingCell = seaCells.at(randomCell);
		continuousCells.push_back(startingCell);

		CellModel* tmp = getCellBelow(startingCell);

		if (tmp->getType() == CellModel::Type::SEA) {
			continuousCells.push_back((SeaModel*)tmp);
		}
		else {
			continuousCells.clear();
			continue;
		}

		tmp = getCellRight(startingCell);

		if (tmp->getType() == CellModel::Type::SEA)
		{
			continuousCells.push_back((SeaModel*)tmp);

			tmp = getCellBelowRight(startingCell);
			if (tmp->getType() == CellModel::Type::SEA) {
				continuousCells.push_back((SeaModel*)tmp);
			}
			else {
				continuousCells.clear();
				continue;
			}

			isValid = true;

		}
		else
		{
			tmp = getCellLeft(startingCell);

			if (tmp->getType() == CellModel::Type::SEA) {
				continuousCells.push_back((SeaModel*)tmp);
			}
			else {
				continuousCells.clear();
				continue;
			}

			tmp = getCellBelowLeft(startingCell);
			if (tmp->getType() == CellModel::Type::SEA) {
				continuousCells.push_back((SeaModel*)tmp);
			}
			else {
				continuousCells.clear();
				continue;
			}

			isValid = true;
		}

	} while (!isValid);

	return continuousCells;
}

std::vector<SeaModel*> MapModel::get2x2ContinuousSeaCells(CellModel* startingCell) const
{
	std::vector<SeaModel*> continuousCells;

	if (startingCell->getType() == CellModel::Type::SEA) {
		continuousCells.push_back((SeaModel*)startingCell);
	}
	else {
		continuousCells.clear();
		return continuousCells;
	}


	CellModel* tmp = getCellBelow(startingCell);

	if (tmp->getType() == CellModel::Type::SEA) {
		continuousCells.push_back((SeaModel*)tmp);
	}
	else {
		continuousCells.clear();
		return continuousCells;
	}

	tmp = getCellRight(startingCell);

	if (tmp->getType() == CellModel::Type::SEA)
	{
		continuousCells.push_back((SeaModel*)tmp);

		tmp = getCellBelowRight(startingCell);
		if (tmp->getType() == CellModel::Type::SEA) {
			continuousCells.push_back((SeaModel*)tmp);
		}
		else {
			continuousCells.clear();
			return continuousCells;
		}

		return continuousCells;

	}
	else
	{
		tmp = getCellLeft(startingCell);

		if (tmp->getType() == CellModel::Type::SEA) {
			continuousCells.push_back((SeaModel*)tmp);
		}
		else {
			continuousCells.clear();
			return continuousCells;
		}

		tmp = getCellBelowLeft(startingCell);
		if (tmp->getType() == CellModel::Type::SEA) {
			continuousCells.push_back((SeaModel*)tmp);
		}
		else {
			continuousCells.clear();
			return continuousCells;
		}

		return continuousCells;
	}
}

std::vector<SeaModel*> MapModel::getSurroundingSeaCells(const CellModel* currentCell) const
{
	std::vector<SeaModel*> seaCells;

	CellModel* cellTmp;

	cellTmp = getCellAbove(currentCell);
	if (cellTmp->getType() == CellModel::Type::SEA) seaCells.push_back((SeaModel*)cellTmp);

	cellTmp = getCellBelow(currentCell);
	if (cellTmp->getType() == CellModel::Type::SEA) seaCells.push_back((SeaModel*)cellTmp);

	cellTmp = getCellRight(currentCell);
	if (cellTmp->getType() == CellModel::Type::SEA) seaCells.push_back((SeaModel*)cellTmp);

	cellTmp = getCellLeft(currentCell);
	if (cellTmp->getType() == CellModel::Type::SEA) seaCells.push_back((SeaModel*)cellTmp);

	cellTmp = getCellAboveRight(currentCell);
	if (cellTmp->getType() == CellModel::Type::SEA) seaCells.push_back((SeaModel*)cellTmp);

	cellTmp = getCellAboveLeft(currentCell);
	if (cellTmp->getType() == CellModel::Type::SEA) seaCells.push_back((SeaModel*)cellTmp);

	cellTmp = getCellBelowRight(currentCell);
	if (cellTmp->getType() == CellModel::Type::SEA) seaCells.push_back((SeaModel*)cellTmp);

	cellTmp = getCellBelowLeft(currentCell);
	if (cellTmp->getType() == CellModel::Type::SEA) seaCells.push_back((SeaModel*)cellTmp);

	return seaCells;
}

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