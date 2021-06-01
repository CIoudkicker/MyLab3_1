#include "Context.h"

QMap<QString, QList<float>> Context::dirSize(ICalculateSize *calc){
    QMap<QString, QList<float>> map;
    map = calc->dirSize();
    if(calc != NULL){
        return map;
    }
}
