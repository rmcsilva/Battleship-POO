#pragma once
#include "CellModel.h"
#include "ShipModel.h"
#include "SeaModel.h"
#include "PortModel.h"

class MapModel {
	static const int MIN_LINES = 10, MIN_COLUMNS = 20;
    int numLines, numColumns;
	int pirateProb;
	std::vector<CellModel*> map;

	//Main port is the first one
	std::vector<PortModel*> friendlyPorts;
	std::vector<PortModel*> enemyPorts;

	std::vector<SeaModel*> seaCells;

public:
    MapModel(const int numLines, const int numColumns);
	~MapModel();
	MapModel(const MapModel &map);

	int getNumLines() const;
	int getNumColumns() const;
	int getPirateProb() const;
	std::vector<PortModel*> getFriendlyPorts() const;
	std::vector<PortModel*> getEnemyPorts() const;

	void setPirateProb(int prob);

	CellModel* getCellAt(int x, int y) const;
	std::vector<SeaModel*> getSeaCells() const;

	void addCellAt(int x, int y,CellModel::Type type);
	void addPortCellAt(int x, int y, char id, Owner owner);
	void addSeaCell(SeaModel * cell);

	void addFriendlyPort(PortModel *port);
	void addPiratePort(PortModel *port);

	void changePortOwner(PortModel* port);

	std::vector<SeaModel*> getRandom2x2ContinuousSeaCells() const;
	std::vector<SeaModel*> get2x2ContinuousSeaCells(CellModel* startingCell) const;
	std::vector<SeaModel*> getSurroundingSeaCells(const CellModel* currentCell) const;
	std::vector<SeaModel*> getSurroundingSeaCellsInRange2(const CellModel* currentCell) const;

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
