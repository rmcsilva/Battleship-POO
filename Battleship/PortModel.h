#include "CellModel.h"

class PortModel : public CellModel{
public:
    PortModel(int x, int y);

    Type getType() override;
};