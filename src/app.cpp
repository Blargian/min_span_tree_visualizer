#include "app.h"
#include "draw.h"
#include <memory>
#include <thread>
#include <chrono>
#include "node_generator_bestcandidate.h"
#include "node_generator_uniform.h"
#include "edge_generator_delaunay.h"

void MyApp::StartUp()
{

    // mock data graph representation for a small test graph 

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

    g->AddObserver(Graph::DRAWEDGE, this);

    createNodes(g.get(), d.get(), tinyEWGnodes);
    connectNodes(g.get(),d.get(),tinyEWG);

    const float spacing = 15;
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(spacing, spacing));
}

//GUI components are defined here 
void MyApp::Update()
{

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse + ImGuiWindowFlags_NoMove;

    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(window_width*0.8, window_height));
    ImGui::Begin("Minimum Spanning Tree Visualizer", NULL, flags);
    ImPlot::CreateContext();
    createPlot(*d, window_width, window_height);
    if (checkPlotClicked(*d)) {
        d->resetLinesToDefault();
        current_snapshot = 0; 
        max_snapshots = 0;
    };
    ImPlot::EndPlot();
    ImGui::End();

    ImGui::SetNextWindowSize(ImVec2(window_width*0.2, window_height));
    ImGui::SetNextWindowPos(ImVec2(1000, 0), ImGuiCond_FirstUseEver);
    ImGui::Begin("Controls", NULL, flags);
    ImPlot::CreateContext();

    if (ImGui::Button("Generate random tree")) 
    {
        clearGraph(g.get(), d.get());
        //auto node_generator = std::make_unique<BestCandidateGenerator>(20);
        auto node_generator = std::make_unique<UniformGenerator>();
        auto points = node_generator->generatePoints(1000, 200, 200);

        auto edge_generator = std::make_unique<DelaunayEdgeGenerator>();
        createNodes(g.get(), d.get(), points);
        auto triangles = edge_generator->generateEdges(points);
        
        for (auto triangle : triangles) {
            for (auto edge : triangle.edges) {
                addLineToDraw(std::make_unique<Line>(edge.first, edge.second), d->getLines());
            }
        }
    }

    ImGui::RadioButton("Prim's algorithm", &algorithm_choice, 0);
    ImGui::RadioButton("Kruskal's algorithm", &algorithm_choice, 1); 

    float spacing = ImGui::GetStyle().ItemInnerSpacing.x;

    ImGui::PushID(0);
    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0 / 7.0f, 0.6f, 0.6f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0 / 7.0f, 0.7f, 0.7f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0 / 7.0f, 0.8f, 0.8f));
    if (ImGui::Button("STOP")) { stop_playback = true; };
    ImGui::PopStyleColor(3);
    ImGui::PopID();

    ImGui::SameLine(0.0f, spacing);

    ImGui::PushID(1);
    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(2 / 7.0f, 0.6f, 0.6f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(2 / 7.0f, 0.7f, 0.7f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(2 / 7.0f, 0.8f, 0.8f));
    if(ImGui::Button("START"))
    {
        thread draw_multiple_thread([this] {this->drawMultipleThread(); });
        draw_multiple_thread.detach();
    };
    ImGui::PopStyleColor(3);
    ImGui::PopID();

    ImGui::SameLine(0.0f, spacing);

    if (ImGui::ArrowButton("##left", ImGuiDir_Left)) {
        auto temp = current_snapshot;
        if (!(temp-- <= 0) && max_snapshots != 0) {
            current_snapshot--;
            thread draw_thread([this] {this->drawOnceThread(); });
            draw_thread.join();
        }
    }
    ImGui::SameLine(0.0f, spacing);
    if (ImGui::ArrowButton("##right", ImGuiDir_Right)) {
        auto temp = current_snapshot;
        if (!(temp++ >= max_snapshots-1) && max_snapshots != 0) {
            current_snapshot++;
            thread draw_thread([this] {this->drawOnceThread(); });
            draw_thread.detach();
        }
            
        
    }
    if (max_snapshots == 0) {
        ImGui::Text("Step: - / -", current_snapshot, max_snapshots);
    }
    else {
        ImGui::Text("Step: %d / %d", current_snapshot+1, max_snapshots+1);
    }
    

    ImGui::SliderFloat("speed", &selected_playback_speed, 0.0f, 1.0f, "speed = %.2f x");

    if (ImGui::Button("Solve")) {
        auto selectedNode = d->selectedMarker()->getNodePtr();

        if (algorithm_choice == 0) {
            prims->clearAll();
            prims->resetIterationCount();
            g->resetVisitedState(); 
            auto MST = prims->findMST(*selectedNode);
            prims->AddSnapshot(Snapshot(MST));
            max_snapshots = prims->getSnapshotLength();
            thread draw_thread([this] {this->drawOnceThread();});
            draw_thread.detach();
        }
        
        if (algorithm_choice == 1) {
            //auto MST = kruskals->findMST(*selectedNode);
            //kruskals->AddSnapshot(Snapshot(MST));
            //max_snapshots = kruskals->getSnapshotLength();
        }
        
    }
    float solving_time = 0.245;
    ImGui::Text("Solving time: %3f ms", solving_time);
    ImGui::End();
}

void MyApp::OnNotify(Line l)
{
    //
}

void MyApp::drawOnceThread()
{
    drawFromSnapshots(current_snapshot, prims->getSnapshots(), *d);
};

void MyApp::drawMultipleThread() {
    while (current_snapshot != max_snapshots) {

        //If the stop button was pressed, exit the while loop stopping playback 
        if (stop_playback) {
            stop_playback = false;
            break;
        }

        drawFromSnapshots(current_snapshot, prims->getSnapshots(), *d);
        current_snapshot++;
        int time_in_ms = (int)((base_playback_speed_seconds * (1.0/(selected_playback_speed+0.1)))*1000.0);
        std::this_thread::sleep_for(std::chrono::milliseconds(time_in_ms));
    }
}

//creates nodes from a vector consisting of {nodeName,x-coordinate,y-coordinate}
void createNodes(Graph* g, Draw* d, vector<vector<int>> nodes) {
    for (vector<int> node_properties : nodes) {
        auto nodePtr = g->insertNode(std::make_shared<Node>(to_string(node_properties[0]), static_cast<int>(node_properties[1]), static_cast<int>(node_properties[2])));
        auto markerPtrr = std::make_shared<Marker>(*nodePtr);
        auto markerPtr = addMarkerToDraw(markerPtrr, d->getMarkers());
        nodePtr->setMarkerPtr(markerPtr);
        markerPtr->setNodePtr(nodePtr);
    };
}

//creates nodes from std::pair<int,int> of x and y coordinates, no name is provided for a node so the function generates it itself
void createNodes(Graph* g, Draw* d, vector<std::pair<int,int>> nodes) {
    int nodeName = 0;
    for (auto& node_properties : nodes) {
        auto nodePtr = g->insertNode(std::make_shared<Node>(to_string(nodeName), node_properties.first, node_properties.second));
        auto markerPtrr = std::make_shared<Marker>(*nodePtr);
        auto markerPtr = addMarkerToDraw(markerPtrr, d->getMarkers());
        nodePtr->setMarkerPtr(markerPtr);
        markerPtr->setNodePtr(nodePtr);
        nodeName++;
    };
}

void connectNodes(Graph* g, Draw* d, vector<vector<double>> edgeWeightGraph) {
    for (vector<double> node_data : edgeWeightGraph) {
        auto edgePtr = g->connectNodes(g->getNodeByName(to_string((int)node_data[0])).get(), g->getNodeByName(to_string((int)node_data[1])).get(), node_data[2]);
        auto l = std::make_shared<Line>(Line(*edgePtr));
        auto linePtr = addLineToDraw(l, d->getLines());
        linePtr->setEdgePtr(edgePtr);
        edgePtr->setLinePtr(linePtr);
        auto edgeInversePtr = getInverseEdge(*g, *edgePtr);
        edgeInversePtr->setLinePtr(linePtr); //two edges reference one line on the graph due to bidirectional nature 
    };
}

void clearGraph(Graph* g, Draw* d) {
    g->clearAll();
    d->clearAll();
}
