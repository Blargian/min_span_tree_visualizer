#pragma once
#include "app_design.h"
#include "line.h"
#include "graph.h"
#include "draw.h"

class Line;

class MyApp : public App, public IObserver
{
protected:
    Graph g;
    Draw d;
public:
    MyApp() = default;
    ~MyApp() = default;

    virtual void StartUp() final;

    //GUI declarations go here
    virtual void Update() final;
    void OnNotify(Line l);

};
