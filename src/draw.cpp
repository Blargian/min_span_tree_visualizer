#include "draw.h"
#include "marker.h"
#include<utility>
#include <functional>

vector<Line>& Draw::lines() {
    return lines_;
}

vector<Marker>& Draw::markers() {
    return markers_;
}

std::optional<Marker> Draw::findMarker(ImPlotPoint p) {

    bool found = false;
    auto it = find(markers_.begin(), markers_.end(), p);
    if (it != markers_.end()) {
        found = true;
    };

    if (found) {
        return std::reference_wrapper<Marker>{markers_[std::distance(markers_.begin(), it)]};
    } else {
        return std::nullopt;
    };
};

void addMarkerToDraw(Marker m, vector<Marker>& markers) {
    markers.push_back(m);
}

void addLineToDraw(Line l, vector<Line>& lines) {
    lines.push_back(l);
}

void createPlot(Draw &d,int window_width, int window_height) {
    ImPlot::BeginPlot("Spanning Tree", ImVec2(window_width * 0.8, window_height * 0.95), ImPlotFlags_NoLegend);
    ImPlot::SetupAxesLimits(-100, 100, -100, 100);
    drawNodes(d.markers());
    drawLines(d.lines());
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
    vector<string> label_ids;
    vector<double> xs_vector, ys_vector;
    vector<ImVec4> colours_vector;
    for (Marker marker : markers) {
        xs_vector.push_back(marker.coordinates().x);
        ys_vector.push_back(marker.coordinates().y);
        colours_vector.push_back(marker.markerColour());
    };
    //char* labels = &label_ids[0];

    //convert vector to array 
    if (xs_vector.size() != 0 && ys_vector.size() != 0) {
       double* xs = &xs_vector[0];
       double* ys = &ys_vector[0];
       ImVec4* cs = &colours_vector[0];
       ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle, 8, *cs, IMPLOT_AUTO, *cs);
       ImPlot::PlotScatter("1", xs, ys, markers.size(), ImPlotScatterFlags_None);
    }
   
}

void checkPlotClicked(Draw &d) {
    if (ImPlot::IsPlotHovered() && ImGui::IsMouseClicked(0)) {
        ImPlotPoint pt = ImPlot::GetPlotMousePos();
        ImPlotPoint nearest = ImPlotPoint(round(pt.x), round(pt.y));
        if (d.findMarker(nearest).has_value()) {
            // select the marker 
        }
        else {
            //do nothing
        }
    }
}