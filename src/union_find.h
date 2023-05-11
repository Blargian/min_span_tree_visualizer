#pragma once

class UnionFind {
private:
	int* id_;
	int count_;
	int* sz_;
public:
	UnionFind (int n);
	~UnionFind();
	void Union(int p, int q);
	int Find (int p);
	bool Connected (int p, int q);
	int Count ();
};