#ifndef IOBSERVER_H
#define IOBSERVER_H

#include <QString>

class IObserver
{
public:
    IObserver();
    virtual void Update(QMap<QString, QList<float>> map) = 0;
};

#endif // IOBSERVER_H
