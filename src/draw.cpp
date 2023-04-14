#include "draw.h"
#include "line.h"
#include "marker.h"
#include<utility>

vector<SharedLinePtr>& Draw::getLines() {
    return lines_;
}

vector<SharedMarkerPtr>& Draw::getMarkers() {
    return markers_;
}

SharedMarkerPtr Draw::findMarker(ImPlotPoint p, bool& found) {

    auto predicate = [p](SharedMarkerPtr& marker) {
        return ((marker->coordinates().x == p.x) && (marker->coordinates().y == p.y));
    };

    auto it = find_if(markers_.begin(), markers_.end(), predicate);
    if (it != markers_.end()) {
        found = true;
    };

    if (found) {
        return SharedMarkerPtr(markers_[std::distance(markers_.begin(), it)]);
    } else {
        return NULL;
    };
};

SharedLinePtr Draw::findLine(Line& l, bool& found) {

    auto predicate = [&l](SharedLinePtr& line) {
        return (*line.get() == l);
    };

    auto it = find_if(lines_.begin(), lines_.end(), predicate);
    if (it != lines_.end()) {
        found = true;
    };

    if (found) {
        return SharedLinePtr(lines_[std::distance(lines_.begin(), it)]);
    }
    else {
        return NULL;
    };
};

void Draw::setSelectedMarker(SharedMarkerPtr m) {
    selectedMarker_ = m;
}

void Draw::changeMarkerColour(SharedMarkerPtr m, MarkerColours c) {
    bool foundMarker = false;
    auto marker = findMarker(m->coordinates(), foundMarker);
    if (foundMarker) {
        marker->setMarkerColour(c);
    }
}

void Draw::changeLineColour(Line* l, LineColours c) {
    bool foundLine = false;
    auto line = findLine(*l,foundLine);
    if (foundLine) {
        line->setLineColour(c);
    }
}

void Draw::changeLineThickness(Line* l, float thickness) {
    bool foundLine = false;
    auto& line = findLine(*l, foundLine);
    if (foundLine) {
        line->setLineThickness(thickness);
    }
}

SharedMarkerPtr Draw::selectedMarker() {
    return selectedMarker_;
}

SharedMarkerPtr addMarkerToDraw(SharedMarkerPtr m, vector<SharedMarkerPtr>& markers) {
    return SharedMarkerPtr(markers.emplace_back(m));
}

SharedLinePtr addLineToDraw(SharedLinePtr l, vector<SharedLinePtr>& lines) {
    return SharedLinePtr(lines.emplace_back(l));
}

bool Draw::hasMarkersToDraw() {
    if(markers_.size()>0){
        return true;
    }
    else {
        return false;
    }
};

bool Draw::hasLinesToDraw() {
    if (lines_.size() > 0) {
        return true;
    }
    else {
        return false;
    }
}

void Draw::resetLinesToDefault() {
    for (auto& line : lines_) {
        line->resetLineToDefault();
    }
}

void createPlot(Draw &d,int window_width, int window_height) {
    ImPlot::BeginPlot("Spanning Tree", ImVec2(window_width * 0.8, window_height * 0.95), ImPlotFlags_NoLegend);
    ImPlot::SetupAxesLimits(-100, 100, -100, 100);
    if (d.hasMarkersToDraw()) { drawNodes(d.getMarkers()); };
    if (d.hasLinesToDraw()) { drawLines(d.getLines()); };
}

void drawLines(vector<SharedLinePtr> lines) {
    for (auto const& l : lines) {
        ImPlot::SetNextLineStyle(l->lineColour(), l->lineThickness());
        ImPlot::PlotLine("1", l->getPointA(), l->getPointB(), 2, ImPlotLineFlags_Segments);
    }
}

void drawNodes(vector<SharedMarkerPtr> markers) {
    for (auto const& marker : markers) {
        double xs[1] = {marker->coordinates().x};
        double ys[1] = {marker->coordinates().y};
        ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle, 8, marker->markerColour(), IMPLOT_AUTO, marker->markerColour());
        ImPlot::PlotScatter(marker->id(), xs, ys, 2, ImPlotScatterFlags_None);
    };
}

bool checkPlotClicked(Draw &d) {

    if (ImPlot::IsPlotHovered() && ImGui::IsMouseClicked(0)) {
        auto previously_selected = d.selectedMarker();
        ImPlotPoint pt = ImPlot::GetPlotMousePos();
        ImPlotPoint nearest = ImPlotPoint(round(pt.x), round(pt.y));
        bool found = false;
        auto found_marker = d.findMarker(nearest, found);
        if(found) {
            // select the marker if none is selected 
            if (previously_selected == NULL) {
                d.setSelectedMarker(found_marker);
                d.changeMarkerColour(found_marker, MarkerColours::WHITE);
            }
            else if (previously_selected != NULL && previously_selected != found_marker) {
                d.resetLinesToDefault();
                d.changeMarkerColour(previously_selected, MarkerColours::GREY);
                d.setSelectedMarker(found_marker);
                d.changeMarkerColour(found_marker, MarkerColours::WHITE);
            }
            else {
                //deselect the currently selected marker
                d.resetLinesToDefault();
                d.changeMarkerColour(previously_selected, MarkerColours::GREY);
                d.setSelectedMarker(nullptr);
            }
            
            
            //else deselect the currently selected marker and select a new one
            return true;
        }
        else {
            //do nothing
            return false;
        }
    }
}

void drawFromSnapshots(int iteration, vector<Snapshot> snapshots, Draw& d) {
    auto snapshot = snapshots[iteration];
        d.resetLinesToDefault();
        auto pq = snapshot.getPQ();
        while (!pq.empty()) {
            auto edge = pq.top();
            pq.pop();
            if (edge.getLinePtr().get() != nullptr) {
                d.changeLineColour(edge.getLinePtr().get(), LineColours::RED);
            }
        }
        auto MST = snapshot.getMST();
        while (!MST.empty()) {
            auto edge = MST.front();
            MST.pop();
            if (edge.getLinePtr().get() != nullptr) {
                d.changeLineColour(edge.getLinePtr().get(), LineColours::BLACK);
                d.changeLineThickness(edge.getLinePtr().get(), 6.0);
            }
        }

        if(snapshot.getEdgeLeastWeight().getLinePtr()!=nullptr){
            auto line = snapshot.getEdgeLeastWeight().getLinePtr().get();
            d.changeLineColour(line, LineColours::RED);
            d.changeLineThickness(line, 6.0);
        }
        return;
}