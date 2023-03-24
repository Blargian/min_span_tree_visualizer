#include "app.h"
#include "draw.h"

void MyApp::StartUp()
{

    vector<vector<double>> tinyEWG =
    {
        {4, 5, 0.35},
        {4, 7, 0.37},
        {5, 7, 0.28},
        {0, 7, 0.16},
        {1, 5, 0.32},
        {0, 4, 0.38},
        {2, 3, 0.17},
        {1, 7, 0.19},
        {0, 2, 0.26},
        {1, 2, 0.36},
        {1, 3, 0.29},
        {2, 7, 0.34},
        {6, 2, 0.40},
        {3, 6, 0.52},
        {6, 0, 0.58},
        {6, 4, 0.93}
    };

    //mock data for nodes of a small test graph:

    vector<vector<int>> tinyEWGnodes =
    {
        {0, 4, 2},
        {1, 3, 7},
        {2, 6, 4},
        {3, 8, 7},
        {4, 0, 0},
        {5, 0, 4},
        {6, 8, 0},
        {7, 3, 4},

    };

    g = Graph();
    g.AddObserver(Graph::DRAWEDGE, this);
    //create the nodes
    for (vector<int> node : tinyEWGnodes) {
        g.insertNode(Node(to_string(node[0]), static_cast<int>(node[1]), static_cast<int>(node[2])));
    };
    //connect the nodes
    for (vector<double> node_data : tinyEWG) {
        g.connectNodes(g.getNodeByName(to_string((int)node_data[0])), g.getNodeByName(to_string((int)node_data[1])), node_data[2]);
    };
}

void MyApp::Update()
{
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoInputs;
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(window_width, window_height));
    ImGui::Begin("Minimum Spanning Tree Visualizer", NULL, flags);
    ImPlot::CreateContext();
    ImPlot::BeginPlot("Spanning Tree", ImVec2(window_width * 0.8, window_height * 0.95), ImPlotFlags_NoLegend);
    ImPlot::SetupAxesLimits(-100, 100, -100, 100);
    Draw::drawNodes(g);
    Draw::drawLines(lines);
    ImPlot::EndPlot();
    ImGui::End();
}

void MyApp::OnNotify(Line l)
{
    this->lines.push_back(l);
}
