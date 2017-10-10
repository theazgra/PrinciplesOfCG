#pragma once
#include "Observer.h"
#include <vector>
class Subject
{
private:
    std::vector<Observer*> observers;
public:
    Subject();
    ~Subject();

    void registerObserver(Observer*);
    void notifyObservers();
    
};

