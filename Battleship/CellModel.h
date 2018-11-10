#pragma once
class CellModel {
    int x, y;

public:
    CellModel(int x, int y);

    enum class Type {GROUND, SEA, PORT};
    virtual Type getType() = 0;

	int getX() const;
	int getY() const;
};

