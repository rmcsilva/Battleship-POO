#include "stdafx.h"
#include "MapModel.h"
#include "SeaModel.h"
#include "PortModel.h"
#include "GroundModel.h"

MapModel::MapModel(const int numLines, const int numColumns) : numLines(numLines), numColumns(numColumns) {
	map = new CellModel*[numLines * numColumns];
}

CellModel* MapModel::getCellAt(int x, int y) const
{
	return map[x + numLines * y];
}

void MapModel::setCellAt(int x, int y, CellModel::Type type) const
{
	CellModel* cell = getCellAt(x, y);

	//TODO:Verify if cells can be of the specific type
	switch (type)
	{
		case CellModel::Type::SEA:
			cell = new SeaModel(x, y);
			break;
		case CellModel::Type::PORT:
			cell = new PortModel(x, y);
			break;
		case CellModel::Type::GROUND:
			cell = new GroundModel(x, y);
	}
}


int MapModel::getNumLines() const
{
	return numLines;
}

int MapModel::getNumColumns() const
{
	return numColumns;
}