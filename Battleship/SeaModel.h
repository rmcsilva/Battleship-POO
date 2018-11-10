#pragma once
#include "CellModel.h"

class SeaModel : public CellModel{

public:
    SeaModel(int x, int y);

    Type getType() override;

};