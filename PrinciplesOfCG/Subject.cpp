#include "stdafx.h"
#include "Subject.h"


Subject::Subject()
{
}


Subject::~Subject()
{
    for (int i = 0; i < observers.size(); i++)
    {
        delete observers.at(i);
    }
}

void Subject::registerObserver(Observer * observer)
{
    observers.push_back(observer);
}

void Subject::notifyObservers()
{
    for (Observer * observer : observers)
    {
        observer->notify();
    }
}
