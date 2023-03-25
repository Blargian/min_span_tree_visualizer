#include "app.h"
#include "draw.h"
#include <memory>

void MyApp::StartUp()
{
    g = Graph();
    d = Draw();

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

    g.AddObserver(Graph::DRAWEDGE, this);
    //create the nodes
    for (vector<int> node_properties : tinyEWGnodes) {
        Node n = Node(to_string(node_properties[0]), static_cast<int>(node_properties[1]), static_cast<int>(node_properties[2]));
        g.insertNode(n);
        addMarkerToDraw(Marker(n),d.markers());
    };
    //connect the nodes
    for (vector<double> node_data : tinyEWG) {
        Edge e = g.connectNodes(g.getNodeByName(to_string((int)node_data[0])), g.getNodeByName(to_string((int)node_data[1])), node_data[2]);
        addLineToDraw(Line(e),d.lines());
    };
}

void MyApp::Update()
{
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoInputs;
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(window_width, window_height));
    ImGui::Begin("Minimum Spanning Tree Visualizer", NULL, flags);
    ImPlot::CreateContext();
    createPlot(d, window_width, window_height);
    ImGui::End();
}

void MyApp::OnNotify(Line l)
{
    //
}
