#ifndef CONTEXT_H
#define CONTEXT_H
#include "ICalculateSize.h"
#include<QMap>
#include<QString>

class Context{

    public:

        QMap<QString, QList<float>> dirSize(ICalculateSize *calc);
};

#endif // CONTEXT_H
