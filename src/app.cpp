#include "app.h"
#include "draw.h"
#include <memory>
#include <thread>
#include <chrono>
#include "node_generator_bestcandidate.h"
#include "node_generator_uniform.h"
#include "edge_generator_delaunay.h"
#include "utility_mstv.h"

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

    //g->AddObserver(Graph::DRAWEDGE, this);

    //createNodes(g.get(), d.get(), tinyEWGnodes);
    //connectNodes(g.get(),d.get(),tinyEWG);

    const float spacing = 15;
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(spacing, spacing));
}

//GUI components are defined here 
void MyApp::Update()
{

    ImGuiWindowFlags graph_area_flags = 0;
    //graph_area_flags |= ImGuiWindowFlags_NoDecoration;
    graph_area_flags |= ImGuiWindowFlags_NoMove;
    graph_area_flags |= ImGuiWindowFlags_NoSavedSettings;
    graph_area_flags |= ImGuiWindowFlags_NoCollapse;
    graph_area_flags |= ImGuiWindowFlags_NoResize;

    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos((viewport->WorkPos));
    ImGui::SetNextWindowSize(ImVec2((viewport->WorkSize.x)*0.8,(viewport->WorkSize.y)));
    ImGui::Begin("Minimum Spanning Tree Visualizer", NULL, graph_area_flags);
    auto win_size = ImGui::GetWindowSize();
    createPlot(*d, (viewport->WorkSize.x) * 0.8, viewport->WorkSize.y);
    if (checkPlotClicked(*d)) {
        resetDrawState(*d, this);
    };
    ImPlot::EndPlot();
    ImGui::End();


    ImGui::SameLine();

    ImGuiWindowFlags control_area_flags = graph_area_flags;
    ImGui::SetNextWindowPos(ImVec2(0.8*(viewport->WorkSize.x),viewport->WorkPos.y));
    ImGui::SetNextWindowSize(ImVec2((viewport->WorkSize.x)*0.20, (viewport->WorkSize.y)));
    ImGui::Begin("Controls", NULL, control_area_flags);

    if (ImGui::Button("Generate random tree"))
    {
        show_random_generation_dialogue = true;
    }
    
    if (show_random_generation_dialogue) {

        ImGuiWindowFlags tree_gen_flags = 0;
        tree_gen_flags |= ImGuiWindowFlags_NoResize;
        tree_gen_flags |= ImGuiWindowFlags_NoMove;
        tree_gen_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
        tree_gen_flags |= ImGuiWindowFlags_NoCollapse;

        ImGui::Begin("Random Tree Generation Dialogue", &show_random_generation_dialogue);

        const char* node_generator_items[] = { "Uniform Random", "Best Fit"};
        const char* edge_generator_items[] = { "Delaunay"};
        const char* weight_generator_items[] = { "Euclidean Distance","Uniform Random (0.0 , 1.0]"};
        const char* nodecombo_preview_value = node_generator_items[nodegen_current_idx_];  // Pass in the preview value visible before opening the combo (it could be anything)
        const char* edgecombo_preview_value = edge_generator_items[edgegen_current_idx_];
        const char* weightcombo_preview_value = weight_generator_items[weightgen_current_idx_];

        if (ImGui::BeginCombo("Node Generator", nodecombo_preview_value,
                              tree_gen_flags))
        {
            for (int n = 0; n < IM_ARRAYSIZE(node_generator_items); n++)
            {
                const bool is_selected = (nodegen_current_idx_ == n);
                if (ImGui::Selectable(node_generator_items[n], is_selected))
                    nodegen_current_idx_ = n;

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }

        if (ImGui::BeginCombo("Edge Generator", edgecombo_preview_value,
                              tree_gen_flags))
        {
            for (int n = 0; n < IM_ARRAYSIZE(edge_generator_items); n++)
            {
                const bool is_selected = (edgegen_current_idx_ == n);
                if (ImGui::Selectable(edge_generator_items[n], is_selected))
                    edgegen_current_idx_ = n;

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }

        if (ImGui::BeginCombo("Weight Generator", weightcombo_preview_value,
                              tree_gen_flags))
        {
            for (int n = 0; n < IM_ARRAYSIZE(weight_generator_items); n++)
            {
                const bool is_selected = (weightgen_current_idx_ == n);
                if (ImGui::Selectable(weight_generator_items[n], is_selected))
                    weightgen_current_idx_ = n;

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }

        ImGui::SliderInt("Nodes", &numberOfNodes_, 3, 1000, "N = %d ");

        if (ImGui::Button("Generate Tree")) {
            clearGraph(g.get(), d.get());

            //Select node generator based on selection
            std::unique_ptr<NodeGenerator> node_generator;
            switch (nodegen_current_idx_) {
            default:
                node_generator = std::make_unique<UniformGenerator>();
                break;
            case 1:
                node_generator = std::make_unique<BestCandidateGenerator>();
                break;
            };
            auto points = node_generator->generatePoints(numberOfNodes_, 200, 200);
            createNodes(g.get(), d.get(), points);

            //Select edge generator based on selection
            std::unique_ptr<EdgeGenerator> edge_generator;
            switch (nodegen_current_idx_) {
            default:
                edge_generator = std::make_unique<DelaunayEdgeGenerator>();
                break;
            };
            auto edges = TrianglesToEdgeList(edge_generator->generateEdges(points));
            edges = removeOneOfDuplicateEdges(edges); //removes one of the edges of any two triangles which share an edge

            //add weights to edges
            std::vector<double> weights;
            switch (nodegen_current_idx_) {
            default:
                weights = edge_generator->generateWeightsEuclidean(edges);
                break;
            case 1:
                //weights = edge_generator->generateWeightsUniformRandom(edges);
                break;
            }

            connectNodes(g.get(), d.get(), edges, weights);
        }
        ImGui::End();
    }

    if(ImGui::RadioButton("Prim's algorithm", &algorithm_choice, 0))
    {
        resetDrawState(*d, this);
    }
    if (ImGui::RadioButton("Kruskal's algorithm", &algorithm_choice, 1)) 
    {
        resetDrawState(*d, this);
    };

    float spacing = ImGui::GetStyle().ItemInnerSpacing.x;

    if (ImGui::ArrowButton("##left", ImGuiDir_Left)) {
        auto temp = getCurrentSnapshot();
        if (!(temp-- <= 0) && getMaxSnapshots() != 0) {
            setCurrentSnapshot(getCurrentSnapshot()-1);
            thread draw_thread([this] {this->drawOnceThread(); });
            draw_thread.join();
        }
    }

    ImGui::SameLine(0.0f, spacing);

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
    if (ImGui::Button("START"))
    {
        thread draw_multiple_thread([this] {this->drawMultipleThread(); });
        draw_multiple_thread.detach();
    };
    ImGui::PopStyleColor(3);
    ImGui::PopID();

    ImGui::SameLine(0.0f, spacing);

    ImGui::SameLine(0.0f, spacing);
    if (ImGui::ArrowButton("##right", ImGuiDir_Right)) {
        auto temp = getCurrentSnapshot();
        auto max = getMaxSnapshots();
        if (!(temp++ >= max -1) && max != 0) {
            setCurrentSnapshot(getCurrentSnapshot()+1);
            thread draw_thread([this] {this->drawOnceThread(); });
            draw_thread.detach();
        }
            
        
    }
    if (getMaxSnapshots() == 0) {
        ImGui::Text("Step: - / -", getCurrentSnapshot(), getMaxSnapshots());
    }
    else {
        ImGui::Text("Step: %d / %d", getCurrentSnapshot()+1, getMaxSnapshots() +1);
    }
    

    ImGui::SliderFloat("Speed", &selected_playback_speed, 0.0f, 1.0f, "speed = %.2f x");

    if (ImGui::Button("Solve")) {

        if (algorithm_choice == 0) {
            auto selectedNode = d->selectedMarker()->getNodePtr();
            prims->clearAll();
            prims->resetIterationCount();
            g->resetVisitedState(); 
            auto MST = prims->findMST(*selectedNode);
            prims->AddSnapshot(Snapshot(MST));
            setMaxSnapshots(prims->getSnapshotLength());
            thread draw_thread([this] {this->drawOnceThread();});
            draw_thread.detach();
        }
        
        if (algorithm_choice == 1) {
            
            kruskals = std::make_unique<KruskalsAlgorithm>(*g);
            auto MST_kruskal = kruskals->findMST();
            kruskals->AddSnapshot(Snapshot(MST_kruskal));
            setMaxSnapshots(kruskals->getSnapshotLength());
            thread draw_thread([this] {this->drawOnceThread(); });
            draw_thread.detach();
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
    if (algorithm_choice == 0) {
        drawFromSnapshots(getCurrentSnapshot(), prims->getSnapshots(), *d);
    }

    if (algorithm_choice == 1) {
        drawFromSnapshots(getCurrentSnapshot(), kruskals->getSnapshots(), *d);
    }
    
};

void MyApp::drawMultipleThread() {
    while (getCurrentSnapshot() != getMaxSnapshots()) {

        //If the stop button was pressed, exit the while loop stopping playback 
        if (stop_playback) {
            stop_playback = false;
            break;
        }

        if (algorithm_choice == 0) {
            drawFromSnapshots(getCurrentSnapshot(), prims->getSnapshots(), *d);
        }

        if (algorithm_choice == 1) {
            drawFromSnapshots(getCurrentSnapshot(), kruskals->getSnapshots(), *d);
        }
        
        setCurrentSnapshot(getCurrentSnapshot()+1);
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


//connect nodes from std::pair<int,int> of A and B coordinates of the edge
void connectNodes(Graph* g, Draw* d, vector<std::pair<std::pair<int,int>,std::pair<int,int>>> edges, vector<double> weights) {

    int i = 0;
    for (auto edge : edges) {
        auto edgePtr = g->connectNodes(g->getNodeByCoord(edge.first).get(), g->getNodeByCoord(edge.second).get(), weights[i]);
        auto l = std::make_shared<Line>(Line(*edgePtr));
        auto linePtr = addLineToDraw(l, d->getLines());
        linePtr->setEdgePtr(edgePtr);
        edgePtr->setLinePtr(linePtr);
        auto edgeInversePtr = getInverseEdge(*g, *edgePtr);
        edgeInversePtr->setLinePtr(linePtr); //two edges reference one line on the graph due to bidirectional nature 
        i++;
    };
}

void clearGraph(Graph* g, Draw* d) {
    g->clearAll();
    d->clearAll();
}

void resetDrawState(Draw& d, MyApp* a) {
    d.resetLinesToDefault();
    a->setMaxSnapshots(0);
    a->setCurrentSnapshot(0);
}

int MyApp::getCurrentSnapshot() { return current_snapshot_; };
int MyApp::getMaxSnapshots() { return max_snapshots_; };
void MyApp::setCurrentSnapshot(int current_snapshot) { current_snapshot_ = current_snapshot; };
void MyApp::setMaxSnapshots(int max_snapshots) { max_snapshots_ = max_snapshots; };