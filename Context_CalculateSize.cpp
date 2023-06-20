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
    map = dirSize(strategy);

    //    switch (strategy) {
    //    case Folder_CalculateSize:
    //        strat = Strategies::Folder_CalculateSize;
    //        map = dirSize(new class Folder_CalculateSize(path));
    //        break;
    //    case Type_CalculateSize:
    //        strat = Strategies::Type_CalculateSize;
    //        map = dirSize(new class Type_CalculateSize(path));
    //        break;
    //    }
}
