#include "Context_CalculateSize.h"

DataForTable Context_CalculateSize::dirSize(ICalculateSize *calc)
{
    DataForTable map;
    if (calc != NULL) {
        map = calc->dirSize();
        delete calc;
    }

    return map;
}

void Context_CalculateSize::changeStrat(ICalculateSize *strategy, QString path)
{
    strat = strategy;
    map = dirSize(strategy);
}
