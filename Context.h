#ifndef CONTEXT_H
#define CONTEXT_H
#include "ICalculateSize.h"
#include "Folder_CalculateSize.h"
#include "Type_CalculateSize.h"
#include<QMap>
#include<QString>

class Context{

    public:

        enum Strategies{
            Folder_CalculateSize = 1,
            Type_CalculateSize
        };


        QMap<QString, QList<float>> dirSize(ICalculateSize *calc);
        void changeStrat(Strategies strategy, QString path);
        QMap<QString, QList<float>> getMap(){ return map; };
        Strategies getStrat(){ return strat; }

    private:

        QMap<QString, QList<float>> map;
        Strategies strat;

};

#endif // CONTEXT_H
