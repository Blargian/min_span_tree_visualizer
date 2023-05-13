#pragma once
#include "app_design.h"
#include "line.h"
#include "graph.h"
#include "draw.h"
#include "prims_algo.h"
#include "kruskals_algo.h"
#include <atomic>

class Line;

class MyApp : public App, public IObserver
{

private:
    int current_snapshot_ = 0;
    int max_snapshots_ = 0;
protected:
    std::unique_ptr<Graph> g = std::make_unique<Graph>();
    std::unique_ptr<Draw> d = std::make_unique<Draw>();
    std::unique_ptr<PrimsAlgorithm> prims = std::make_unique<PrimsAlgorithm>();
    std::unique_ptr<KruskalsAlgorithm> kruskals;
    int algorithm_choice = 0;
    float base_playback_speed_seconds = 0.1;
    float selected_playback_speed = 1.0f, max_playback_speed = 1.0f;
    std::atomic<bool> stop_playback = false; 
    bool show_random_generation_dialogue = false;

public:
    MyApp() = default;
    ~MyApp() = default;
    int getCurrentSnapshot();
    int getMaxSnapshots();
    void setCurrentSnapshot(int current_snapshot);
    void setMaxSnapshots(int max_snapshot);

    virtual void StartUp() final;

    //GUI declarations go here
    virtual void Update() final;
    void OnNotify(Line l);
    void drawOnceThread();
    void drawMultipleThread();
};

void createNodes(Graph* g, Draw* d, vector<vector<int>> nodes);
void createNodes(Graph* g, Draw* d, vector<std::pair<int,int>> nodes);
void connectNodes(Graph* g, Draw* d, vector<vector<double>> ewg);
void connectNodes(Graph* g, Draw* d, vector<std::pair<std::pair<int, int>, std::pair<int, int>>> edges, vector<double> weights);
void clearGraph(Graph* g, Draw* d);
void resetDrawState(Draw& d, MyApp* a);



