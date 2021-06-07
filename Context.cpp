#include "Context.h"

QMap<QString, QList<float>> Context::dirSize(ICalculateSize *calc){
    QMap<QString, QList<float>> map;
    if(calc != NULL){
        map = calc->dirSize();
    }
    return map;
}
