#include "Context.h"

QMap<QString, QList<float>> Context::dirSize(ICalculateSize *calc){
    QMap<QString, QList<float>> map;
    if(calc != NULL){
        map = calc->dirSize();
    }
    return map;
}

void Context::changeStrat(Strategies strategy, QString path){


    switch (strategy) {
        case Folder_CalculateSize:
            strat = Strategies::Folder_CalculateSize;
            map = dirSize(new class Folder_CalculateSize(path));
            break;
        case Type_CalculateSize:
            strat = Strategies::Type_CalculateSize;
            map = dirSize(new class Type_CalculateSize(path));
            break;
    }
}





