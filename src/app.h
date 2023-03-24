#pragma once
#include "app_design.h"
#include "line.h"

class Line;

class MyApp : public App, public IObserver
{
private:
    std::vector<Line> lines;
    Graph g; 
public:
    MyApp() = default;
    ~MyApp() = default;

    virtual void StartUp() final;

    //GUI declarations go here
    virtual void Update() final;
    void OnNotify(Line l);

};
