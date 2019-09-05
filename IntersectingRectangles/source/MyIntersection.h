#pragma once

#include "MyRectangle.h"

class MyIntersection{
private:
	std::set<int> intersecting_rects;
	MyRectangle rectangle;
public:
	MyIntersection(int x, int y, int w, int h);
	MyIntersection();
	MyIntersection(MyRectangle new_rectangle);

	std::set<int> getIntersections();
	void setIntersections(std::set<int> intersections);
	void insert_id(int id);
	void insert_ids(std::set<int> ids);

	void print() const;

	MyIntersection& operator = (MyIntersection other);

	bool operator< (const MyIntersection& intersect) const;

	std::optional<MyIntersection> is_intersecting(MyIntersection &other);
};