#ifndef CONTEXT_CALCULATESIZE_H
#define CONTEXT_CALCULATESIZE_H
#include "ICalculateSize.h"
#include "Folder_CalculateSize.h"
#include "Type_CalculateSize.h"
#include <QMap>
#include <QString>

class Context_CalculateSize
{

public:
    enum Strategies { Folder_CalculateSize = 1, Type_CalculateSize };

    DataForTable dirSize(ICalculateSize *calc);
    void changeStrat(Strategies strategy, QString path);
    DataForTable getMap() { return map; };
    Strategies getStrat() { return strat; }

private:
    DataForTable map;
    Strategies strat;
};

#endif // CONTEXT_CALCULATESIZE_H
