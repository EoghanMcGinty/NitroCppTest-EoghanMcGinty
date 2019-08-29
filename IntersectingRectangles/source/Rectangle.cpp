#include "Rectangle.h"

MyRectangle::MyRectangle() : id(++curr_id) {}
MyRectangle::MyRectangle(int x, int y, int w, int h)
	: x(x), y(y), width(w), height(h), id(++curr_id) {}
int MyRectangle::curr_id = 0;

void from_json(const nlohmann::json& j, MyRectangle& r) {
	try {
		j.at("x").get_to(r.x);
		j.at("y").get_to(r.y);
		j.at("w").get_to(r.width);
		j.at("h").get_to(r.height);
	}
	catch (std::exception e) {
		std::cerr << "Incorrect Structure for Rectangle " << r.id << std::endl;
		throw e;
	}
}

bool is_intersecting(const MyRectangle& r1, const MyRectangle& r2, MyRectangle& i) {
	i.x = std::max(r1.x, r2.x);
	i.y = std::max(r1.y, r2.y);
	i.width = std::min((r1.x + r1.width), (r2.x + r2.width));
	i.height = std::min((r1.y + r1.height), (r2.y + r2.height));
	if (!(i.width >= i.x && i.height >= i.y)) {
		return false;
	}
	i.width = abs(i.width - i.x);
	i.height = abs(i.height - i.y);
	return true;
}

bool is_intersecting_rectangles(const MyRectangle& r1, const MyRectangle& r2, MyRectangle& i) {

	if (is_intersecting(r1, r2, i)) {
		i.intersecting_rects.insert(r1.id);
		i.intersecting_rects.insert(r2.id);
		return true;
	}
	return false;
}

bool is_intersecting_intersections(const MyRectangle& r1, const MyRectangle& r2, MyRectangle& i) {

	if (is_intersecting(r1, r2, i)) {
		i.intersecting_rects.insert(r1.intersecting_rects.begin(), r1.intersecting_rects.end());
		i.intersecting_rects.insert(r2.intersecting_rects.begin(), r2.intersecting_rects.end());
		return true;
	}
	return false;
}

bool open_json(char* file, nlohmann::json& j) {
	std::ifstream i(file);
	if (!i) {
		std::cerr << "Input file error" << std::endl;
		return false;
	}

	try {
		i >> j;
	}
	catch (std::exception e) {
		std::cerr << "Invalid JSON file" << std::endl;
		return false;
	}
	return true;
}