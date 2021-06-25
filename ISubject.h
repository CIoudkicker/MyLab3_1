#ifndef ISUBJECT_H
#define ISUBJECT_H

#include "IObserver.h"

class ISubject{

    public:

        ISubject();
        virtual ~ISubject(){};
        virtual void Attach(IObserver *observer) = 0;
        virtual void Detach(IObserver *observer) = 0;
        virtual void Notify() = 0;

};

#endif // ISUBJECT_H
