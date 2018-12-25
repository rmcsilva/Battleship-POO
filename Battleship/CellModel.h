#pragma once
class CellModel {
    int x, y;

public:
    CellModel(int x, int y);
	CellModel(const CellModel &cell);
	virtual ~CellModel();

    enum class Type {GROUND, SEA, PORT};

    virtual Type getType() = 0;

	int getX() const;
	int getY() const;

	virtual CellModel* clone() = 0;

	bool operator==(CellModel const &cell) const;
};

