#ifndef IOBSERVER_H
#define IOBSERVER_H

#include <QString>
#include "ICalculateSize.h"

class IObserver
{
public:
    IObserver();
    virtual void Update(DataForTable map) = 0;
};

class ISubject
{

public:
    ISubject();
    virtual ~ISubject(){};
    virtual void Attach(IObserver *observer) = 0;
    virtual void Detach(IObserver *observer) = 0;
    virtual void Notify() = 0;
};

#endif // IOBSERVER_H
