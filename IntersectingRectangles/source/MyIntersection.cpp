#include "MyIntersection.h"

MyIntersection::MyIntersection(int x, int y, int w, int h) {
	rectangle.set_x(x);
	rectangle.set_y(y);
	rectangle.set_width(w);
	rectangle.set_height(h);
}
MyIntersection::MyIntersection() {}
MyIntersection::MyIntersection(MyRectangle new_rectangle) {
	rectangle = new_rectangle;
}

std::set<int> MyIntersection::get_ids() const { return intersecting_rect_ids; }
void MyIntersection::set_ids(std::set<int> intersections) { intersecting_rect_ids = intersections; }
void MyIntersection::insert_id(int id) { intersecting_rect_ids.insert(id); }
void MyIntersection::insert_ids(std::set<int> ids) { intersecting_rect_ids.insert(ids.begin(), ids.end()); }

int MyIntersection::get_area() const {
	return rectangle.get_area();
}

int MyIntersection::number_of_intersections() const {
	return (int)intersecting_rect_ids.size();
}

void MyIntersection::print() const {
	std::cout << "\tBetween rectangle ";
	for (auto iter = intersecting_rect_ids.begin(); iter != intersecting_rect_ids.end(); ++iter) {
		std::cout << *iter;
		if (iter == std::prev(intersecting_rect_ids.end()))
			std::cout << " ";
		else std::cout << ", ";

	}
	std::cout << "at (" << rectangle.get_x() << ", " << rectangle.get_y()
		<< "), w=" << rectangle.get_width() << ", h=" << rectangle.get_height() << std::endl;
}

MyIntersection& MyIntersection::operator = (MyIntersection other) {
	std::swap(rectangle, other.rectangle);
	std::swap(intersecting_rect_ids, other.intersecting_rect_ids);
	return *this;
}

bool MyIntersection::operator< (const MyIntersection& intersect) const {
	return intersecting_rect_ids < intersect.intersecting_rect_ids;
}


std::optional<MyIntersection> MyIntersection::is_intersecting(MyIntersection& other) {
	auto intersect = rectangle.is_intersecting(other.rectangle);
	if (!intersect) {
		return std::nullopt;
	}
	MyIntersection new_intersect(*intersect);
	new_intersect.insert_ids(intersecting_rect_ids);
	new_intersect.insert_ids(other.intersecting_rect_ids);

	return new_intersect;
}