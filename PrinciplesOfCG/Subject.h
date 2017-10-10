#pragma once
#include "Observer.h"
#include <vector>
class Subject
{
private:
    std::vector<std::reference_wrapper<Observer>> observers;
public:
    Subject();
    ~Subject();

    void registerObserver(Observer&);
    void clearObservers();
protected:
    void notifyObservers();
    
};

