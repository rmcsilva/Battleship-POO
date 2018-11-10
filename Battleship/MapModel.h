#pragma once
#include "CellModel.h"

class MapModel {
	const int MIN_LINES = 10, MIN_COLUMNS = 20;
    int numLines, numColumns;
	std::vector<CellModel*> map;

public:
    MapModel(const int numLines, const int numColumns);
	
	int getNumLines() const;
	int getNumColumns() const;

	CellModel* getCellAt(int x, int y) const;
	void addCellAt(int x, int y,CellModel::Type type);
	void addPortCellAt(int x, int y, CellModel::Owner owner);
	//void setCellAt(int x, int y, CellModel::Type type);
};