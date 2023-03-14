class IObserver {
public:
	virtual ~IObserver() {};
	virtual void OnNotify() = 0;
};