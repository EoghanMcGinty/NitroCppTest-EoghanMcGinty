#pragma once

#include "MyRectangle.h"

class MyIntersection{
private:
	std::set<int> intersecting_rect_ids;
	MyRectangle rectangle;
public:
	MyIntersection(int x, int y, int w, int h);
	MyIntersection();
	MyIntersection(MyRectangle new_rectangle);

	std::set<int> get_ids() const;
	void set_ids(std::set<int> intersections);
	void insert_id(int id);
	void insert_ids(std::set<int> ids);

	int get_area() const;
	int number_of_intersections() const;

	void print() const;

	MyIntersection& operator = (MyIntersection other);

	bool operator< (const MyIntersection& intersect) const;

	std::optional<MyIntersection> is_intersecting(MyIntersection &other);
};