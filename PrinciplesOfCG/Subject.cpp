#include "stdafx.h"
#include "Subject.h"


Subject::Subject()
{
}


Subject::~Subject()
{
}

void Subject::registerObserver(Observer & observer)
{
    observers.push_back(observer);
}

void Subject::clearObservers()
{
    observers.clear();
}

void Subject::notifyObservers()
{
    for (Observer & observer : observers)
    {
        observer.notify();
    }
}


