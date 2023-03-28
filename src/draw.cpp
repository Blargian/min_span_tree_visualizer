#include "draw.h"
#include "marker.h"
#include<utility>

vector<Line>& Draw::lines() {
    return lines_;
}

vector<Marker>& Draw::markers() {
    return markers_;
}

Marker* Draw::findMarker(ImPlotPoint p, bool& found) {

    auto predicate = [p](Marker& marker) {
        return ((marker.coordinates().x == p.x) && (marker.coordinates().y == p.y));
    };

    auto it = find_if(markers_.begin(), markers_.end(), predicate);
    if (it != markers_.end()) {
        found = true;
    };

    if (found) {
        return &markers_[std::distance(markers_.begin(), it)];
    } else {
        return NULL;
    };
};

Line* Draw::findLine(Line l, bool& found) {

    auto predicate = [&l](Line& line) {
        return ((line.getPointA() == l.getPointA()) && (line.getPointB() == l.getPointB()));
    };

    auto it = find_if(lines_.begin(), lines_.end(), predicate);
    if (it != lines_.end()) {
        found = true;
    };

    if (found) {
        return &lines_[std::distance(lines_.begin(), it)];
    }
    else {
        return NULL;
    };
};

void Draw::setSelectedMarker(Marker* m) {
    selectedMarker_ = m;
}

void Draw::changeMarkerColour(Marker* m, MarkerColours c) {
    bool foundMarker = false;
    Marker* marker = findMarker(m->coordinates(), foundMarker);
    if (foundMarker) {
        marker->setMarkerColour(c);
    }
}

void Draw::changeLineColour(Line* l, LineColours c) {
    bool foundLine = false;
    Line* line = findLine(*l,foundLine);
    if (foundLine) {
        line->setLineColour(c);
    }
}

Marker* Draw::selectedMarker() {
    return selectedMarker_;
}

void addMarkerToDraw(Marker m, vector<Marker>& markers) {
    markers.push_back(m);
}

void addLineToDraw(Line l, vector<Line>& lines) {
    lines.push_back(l);
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

void createPlot(Draw &d,int window_width, int window_height) {
    ImPlot::BeginPlot("Spanning Tree", ImVec2(window_width * 0.8, window_height * 0.95), ImPlotFlags_NoLegend);
    ImPlot::SetupAxesLimits(-100, 100, -100, 100);
    if (d.hasMarkersToDraw()) { drawNodes(d.markers()); };
    if (d.hasLinesToDraw()) { drawLines(d.lines()); };
    checkPlotClicked(d);
    ImPlot::EndPlot();
}

void drawLines(vector<Line> lines) {
    for (auto& l : lines) {
        ImPlot::SetNextLineStyle(l.lineColour(), l.lineThickness());
        ImPlot::PlotLine("1", l.getPointA(), l.getPointB(), 2, ImPlotLineFlags_Segments);
    }
}

void drawNodes(vector<Marker> markers) {
    for (Marker marker : markers) {
        double xs[1] = {marker.coordinates().x};
        double ys[1] = {marker.coordinates().y};
        ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle, 8, marker.markerColour(), IMPLOT_AUTO, marker.markerColour());
        ImPlot::PlotScatter(marker.id(), xs, ys, 2, ImPlotScatterFlags_None);
    };
}

void checkPlotClicked(Draw &d) {

    if (ImPlot::IsPlotHovered() && ImGui::IsMouseClicked(0)) {
        Marker* previously_selected = d.selectedMarker();
        ImPlotPoint pt = ImPlot::GetPlotMousePos();
        ImPlotPoint nearest = ImPlotPoint(round(pt.x), round(pt.y));
        bool found = false;
        Marker* found_marker = d.findMarker(nearest, found);
        if(found) {
            // select the marker if none is selected 
            if (previously_selected == NULL) {
                d.setSelectedMarker(found_marker);
                d.changeMarkerColour(found_marker, MarkerColours::WHITE);
            }
            else if (previously_selected != NULL && previously_selected != found_marker) {
                d.changeMarkerColour(previously_selected, MarkerColours::GREY);
                d.setSelectedMarker(found_marker);
                d.changeMarkerColour(found_marker, MarkerColours::WHITE);
            }
            else {
                //deselect the currently selected marker
                d.changeMarkerColour(previously_selected, MarkerColours::GREY);
                d.setSelectedMarker(nullptr);
            }
            
            
            //else deselect the currently selected marker and select a new one
            return;
        }
        else {
            //do nothing
            return;
        }
    }
}