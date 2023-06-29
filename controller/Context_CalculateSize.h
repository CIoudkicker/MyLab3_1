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
    DataForTable dirSize(ICalculateSize *calc);
    void changeStrat(ICalculateSize *strategy, QString path);
    DataForTable getMap() { return map; }
    ICalculateSize *getStrat() { return strat; }

private:
    DataForTable map;
    ICalculateSize *strat;
};

#endif // CONTEXT_CALCULATESIZE_H
