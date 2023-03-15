#pragma once
#include "line.h"

class Line;

class IObserver {
public:
	virtual ~IObserver() {};
	virtual void OnNotify(Line l) = 0;
};