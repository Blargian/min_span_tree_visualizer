#include "draw.h"

void Draw::drawLines(vector<Line> lines) {
    for (auto& l : lines) {
        ImPlot::SetNextLineStyle(l.lineColour(), l.lineThickness());
        ImPlot::PlotLine("1", l.getPointA(), l.getPointB(), 2, ImPlotLineFlags_Segments);
    }
}

void Draw::drawNodes(Graph& g) {
    vector<string> label_ids;
    vector<double> xs_vector, ys_vector;
    for (auto&& node : g.getNodes()) {
        //label_ids.push_back(node->getNodeName());
        xs_vector.push_back(node->getXY().first);
        ys_vector.push_back(node->getXY().second);
    };
    //char* labels = &label_ids[0];
    double* xs = &xs_vector[0];
    double* ys = &ys_vector[0];
    ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle, 8, ImPlot::GetColormapColor(1), IMPLOT_AUTO, ImPlot::GetColormapColor(1));
    ImPlot::PlotScatter("1", xs, ys, g.getNodeCount(), ImPlotScatterFlags_None);
}