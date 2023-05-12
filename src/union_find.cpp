#include "union_find.h";

UnionFind::UnionFind() {};

UnionFind::UnionFind(int n) {
	count_ = n;
	for (int i = 0; i < n; i++) {
		id_.emplace_back(i);
		sz_.emplace_back(1);
	};
}

UnionFind::~UnionFind() {
}

int UnionFind::Count() {
	return count_;
}

bool UnionFind::Connected(int p, int q)
{
	return Find(p) == Find(q);
}

int UnionFind::Find(int p) {
	//follow the links until you reach an element refering to itself (the root)
	while (p != id_[p])
		p = id_[p];
	return p;
}

void UnionFind::Union(int p, int q) {
	int i = Find(p);
	int j = Find(q);
	if (i == j) return;

	if (sz_[i] < sz_[j]) { id_[i] = j; sz_[j] += sz_[i]; }
	else { id_[j] = i; sz_[i] += sz_[j]; }
	count_--;
};