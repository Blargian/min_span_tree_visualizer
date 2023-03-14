#include "iObserver.h"
#include<forward_list>
#include<map>

//Interface class for a subject of the observable pattern 
class ISubject {
public:

	typedef std::forward_list<IObserver*> ObserversList;
	typedef std::map<int, ObserversList> ObserversMap;
	ISubject() {};
	virtual ~ISubject() {};

	virtual void AddObserver(int message, IObserver* observer) {
		
		auto it = mObservers.find(message);
		if (it == mObservers.end()) {
			//since message was not found
			mObservers[message] = ObserversList();
		}
		mObservers[message].push_front(observer);
	}

	virtual void RemoveObserver(int message,IObserver* observer) {
		auto it = mObservers.find(message);
		if (it != mObservers.end()) {
			mObservers[message].remove(observer);
		}
	}

	virtual void NotifyAll() {
		for (ObserversMap::iterator it = mObservers.begin(); it != mObservers.end(); ++it) {
			for (auto& o : mObservers[it->first]) {
				o->OnNotify();
			}
		}
	}

	virtual void Notify(int message) {
		for (auto& o : mObservers[message]) {
			o->OnNotify();
		}
	}

	virtual bool hasObservers() {
		int size = distance(this->mObservers.begin(),
			this->mObservers.end());
		if (size != 0) {
			return true;
		}
		else {
			return false;
		}
	}

	//used to expose the mObservers map for testing
	virtual ObserversMap getObserverMap() {
		return this->mObservers;
	}

private:
	ObserversMap mObservers;
};