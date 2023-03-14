#include "app_design.h"

class MyApp : public App
{
private:
public:
    MyApp() = default;
    ~MyApp() = default;

    virtual void StartUp() final
    {
    }

    //GUI declarations go here
    virtual void Update() final
    {
        Graph g = Graph();
        std::vector<Node> nodes = {
            Node("Johannesburg", 5, 10),
            Node("Cape Town", 26, 10),
            Node("Durban", -24, 78),
            Node("Richards Bay", 60, 60)
        };
        for (Node node : nodes) {
            g.insertNode(node);
        }
        pair<float*, float*> coordinates = g.getCoordsForPlot();
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoInputs;
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(window_width, window_height));
        ImGui::Begin("Minimum Spanning Tree Visualizer", NULL, flags);
        ImPlot::CreateContext();
        ImPlot::BeginPlot("Spanning Tree", ImVec2(window_width*0.9, window_height*0.9));
        ImPlot::SetupAxesLimits(-100, 100, -100, 100);
        ImPlot::PlotScatter("Tree Node", coordinates.first, coordinates.second, g.getNodeCount());
        ImPlot::EndPlot();
        ImGui::End();
    }
};