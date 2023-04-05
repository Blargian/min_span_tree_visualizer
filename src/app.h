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
    std::unique_ptr<Graph> g = std::make_unique<Graph>();
    std::unique_ptr<Draw> d = std::make_unique<Draw>();
    std::unique_ptr<PrimsAlgorithm> prims = std::make_unique<PrimsAlgorithm>();
public:
    MyApp() = default;
    ~MyApp() = default;

    virtual void StartUp() final;

    //GUI declarations go here
    virtual void Update() final;
    void OnNotify(Line l);

};
