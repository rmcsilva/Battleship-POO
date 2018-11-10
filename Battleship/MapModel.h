#include "CellModel.h"

class MapModel {
    const int numLines, numColumns;
	CellModel** map;

public:
    MapModel(const int numLines, const int numColumns);
	
	int getNumLines() const;
	int getNumColumns() const;

	CellModel* getCellAt(int x, int y) const;
	void setCellAt(int x, int y, CellModel::Type type) const;
	
};