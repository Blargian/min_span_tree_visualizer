#pragma once
#include "app_design.h"
#include "line.h"
#include "graph.h"
#include "draw.h"
#include "prims_algo.h"

class Line;

class MyApp : public App, public IObserver
{
protected:
    Graph g;
    Draw d;
    PrimsAlgorithm prims; 
public:
    MyApp() = default;
    ~MyApp() = default;

    virtual void StartUp() final;

    //GUI declarations go here
    virtual void Update() final;
    void OnNotify(Line l);

};
