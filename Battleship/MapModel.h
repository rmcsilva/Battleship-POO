#pragma once
#include "CellModel.h"

class MapModel {
	const int MIN_LINES = 10, MIN_COLUMNS = 20;
    int numLines, numColumns;
	int pirateProb;
	std::vector<CellModel*> map;

public:
    MapModel(const int numLines, const int numColumns);
	~MapModel();

	int getNumLines() const;
	int getNumColumns() const;
	int getPirateProb() const;

	void setPirateProb(int prob);

	CellModel* getCellAt(int x, int y) const;
	void addCellAt(int x, int y,CellModel::Type type);
	void addPortCellAt(int x, int y, char id, CellModel::CellOwner owner);

	CellModel* getCellAbove(const CellModel* currentCell) const;
	CellModel* getCellBelow(const CellModel* currentCell) const;
	CellModel* getCellRight(const CellModel* currentCell) const;
	CellModel* getCellLeft(const CellModel* currentCell) const;
	//Diagonals
	CellModel* getCellAboveRight(const CellModel* currentCell) const;
	CellModel* getCellAboveLeft(const CellModel* currentCell) const;
	CellModel* getCellBelowRight(const CellModel* currentCell) const;
	CellModel* getCellBelowLeft(const CellModel* currentCell) const;
	//void setCellAt(int x, int y, CellModel::Type type);
};