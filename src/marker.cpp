#include "marker.h"

Marker::Marker(Node n) {
	auto coordinate_pair = n.getXY();
    coordinates_ = ImPlotPoint(coordinate_pair.first, coordinate_pair.second);
	id_ = generateSimpleUuid();
    markerColour_ = MarkerColours::GREY;
}

const ImPlotPoint Marker::coordinates() {
    return coordinates_;
}

ImVec4 Marker::markerColour() {
    ImVec4 line_colour;
    switch (markerColour_) {
    case MarkerColours::GREY:
        line_colour = ImColor(125,124,124);
        break;
    case MarkerColours::WHITE: 
        line_colour = ImColor(255,255,255);
        break;
    default: 
        line_colour = ImColor(125,124,124);
        break;
    }
    return line_colour;
}

/* This code is not mine, credit to happy_sisyphus on stackoverflow.com
   I'd use a uuid function from boost library ordinary, just don't feel
   like including it in this project.
   Slightly modified to return const char* instead of string
*/
const char* generateSimpleUuid() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 15);
    std::uniform_int_distribution<> dis2(8, 11);

    std::stringstream ss;
    int i;
    ss << std::hex;
    for (i = 0; i < 8; i++) {
        ss << dis(gen);
    }
    ss << "-";
    for (i = 0; i < 4; i++) {
        ss << dis(gen);
    }
    ss << "-4";
    for (i = 0; i < 3; i++) {
        ss << dis(gen);
    }
    ss << "-";
    ss << dis2(gen);
    for (i = 0; i < 3; i++) {
        ss << dis(gen);
    }
    ss << "-";
    for (i = 0; i < 12; i++) {
        ss << dis(gen);
    };

    return ss.str().c_str();
}

bool operator==(Marker a, const Marker b) {
    if (
        a.coordinates().x == b.coordinates().x
        && a.coordinates().y == b.coordinates().y
    ){
        return true;
    } else {
        return false;
    }
};