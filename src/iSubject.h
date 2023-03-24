#pragma once
#include "iObserver.h"
#include<forward_list>
#include<map>
#include "line.h"

class Line; 
//Interface class for a subject of the observable pattern 
class ISubject {
public:

	typedef std::forward_list<IObserver*> ObserversList;
	typedef std::map<int, ObserversList> ObserversMap;
	ISubject() {};
	virtual ~ISubject() {};
	virtual void AddObserver(int message, IObserver* observer);
	virtual void RemoveObserver(int message, IObserver* observer);
	void Notify(int message, Line l);
	bool hasObservers();

	//used to expose the mObservers map for testing
	virtual ObserversMap ISubject::getObserverMap() {
		return this->mObservers;
	}

private:
	ObserversMap mObservers;
};
