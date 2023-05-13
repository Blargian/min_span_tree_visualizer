#pragma once
#include <vector>

class UnionFind {
private:
	std::vector<int> id_;
	int count_;
	std::vector<int> sz_;
public:
	UnionFind();
	UnionFind (int n);
	~UnionFind();
	void Union(int p, int q);
	int Find (int p);
	bool Connected (int p, int q);
	int Count ();
};