#include "MyIntersection.h"

MyIntersection::MyIntersection(int x, int y, int w, int h) {
	rectangle.setX(x);
	rectangle.setY(y);
	rectangle.setWidth(w);
	rectangle.setHeight(h);
}
MyIntersection::MyIntersection() {}
MyIntersection::MyIntersection(MyRectangle new_rectangle) {
	rectangle = new_rectangle;
}

std::set<int> MyIntersection::getIntersections() { return intersecting_rects; }
void MyIntersection::setIntersections(std::set<int> intersections) { intersecting_rects = intersections; }
void MyIntersection::insert_id(int id) { intersecting_rects.insert(id); }
void MyIntersection::insert_ids(std::set<int> ids) { intersecting_rects.insert(ids.begin(), ids.end()); }

void MyIntersection::print() const {
	std::cout << "\tBetween rectangle ";
	for (auto iter = intersecting_rects.begin(); iter != intersecting_rects.end(); ++iter) {
		std::cout << *iter;
		if (iter == std::prev(intersecting_rects.end()))
			std::cout << " ";
		else std::cout << ", ";

	}
	std::cout << "at (" << rectangle.getX() << ", " << rectangle.getY()
		<< "), w=" << rectangle.getWidth() << ", h=" << rectangle.getHeight() << std::endl;
}

MyIntersection& MyIntersection::operator = (MyIntersection other) {
	std::swap(rectangle, other.rectangle);
	std::swap(intersecting_rects, other.intersecting_rects);
	return *this;
}

bool MyIntersection::operator< (const MyIntersection& intersect) const {
	return intersecting_rects < intersect.intersecting_rects;
}


std::optional<MyIntersection> MyIntersection::is_intersecting(MyIntersection& other) {
	auto intersect = rectangle.is_intersecting(other.rectangle);
	if (!intersect) {
		return std::nullopt;
	}
	MyIntersection new_intersect(*intersect);
	new_intersect.insert_ids(intersecting_rects);
	new_intersect.insert_ids(other.intersecting_rects);

	return new_intersect;
}