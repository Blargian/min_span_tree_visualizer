#include "ISubject.h"

void ISubject::AddObserver(int message, IObserver* observer) {

	auto it = mObservers.find(message);
	if (it == mObservers.end()) {
		//since message was not found
		mObservers[message] = ObserversList();
	}
	mObservers[message].push_front(observer);
}

void ISubject::RemoveObserver(int message, IObserver* observer) {
	auto it = mObservers.find(message);
	if (it != mObservers.end()) {
		mObservers[message].remove(observer);
	}
}

void ISubject::Notify(int message, Line l) {
	for (auto& o : mObservers[message]) {
		//should pass back data
		o->OnNotify(l);
	}
}

bool ISubject::hasObservers() {
	int size = distance(this->mObservers.begin(),
		this->mObservers.end());
	if (size != 0) {
		return true;
	}
	else {
		return false;
	}
}