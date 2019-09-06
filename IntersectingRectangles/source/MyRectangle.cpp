#include "MyRectangle.h"

MyRectangle::MyRectangle() : x(0), y(0), width(0), height(0), id(++curr_id) {}
MyRectangle::MyRectangle(int x, int y, int w, int h)
	: x(x), y(y), width(w), height(h), id(++curr_id) {}
int MyRectangle::curr_id = 0;

int MyRectangle::get_x() const { return x; }
int MyRectangle::get_y() const { return y; }
int MyRectangle::get_width() const { return width; }
int MyRectangle::get_height() const { return height; }
int MyRectangle::get_id() const { return id; }

void MyRectangle::set_x(int new_x) { x = new_x; }
void MyRectangle::set_y(int new_y) { y = new_y; }

void MyRectangle::set_width(int w) { 
	width = (w > 0) ? w : 0;
	if (w < 0) {
		std::cerr << "Width must be a positive integer" << std::endl;
	}
}
void MyRectangle::set_height(int h) { 
	height = (h > 0) ? h : 0;
	if (h < 0) {
		std::cerr << "Height must be a positive integer" << std::endl;
	}
}

int MyRectangle::get_area() const {
	return width * height;
}

void MyRectangle::print() {
	std::cout << "\t" << id << ": Rectangle at (" << x << "," << y
		<< "), w=" << width << ", h=" << height << std::endl;
}

MyRectangle& MyRectangle::operator = (MyRectangle other) {
	std::swap(x, other.x);
	std::swap(y, other.y);
	std::swap(width, other.width);
	std::swap(height, other.height);
	return *this;
}

std::optional<MyRectangle> MyRectangle::is_intersecting(MyRectangle& other) {
	MyRectangle intersect;
	intersect.x = std::max(x, other.x);
	intersect.y = std::max(y, other.y);
	intersect.width = std::min((x + width), (other.x + other.width));
	intersect.height = std::min((y + height), (other.y + other.height));

	if (!(intersect.width > intersect.x && intersect.height > intersect.y)) {
		return std::nullopt;
	}

	intersect.width = abs(intersect.width - intersect.x);
	intersect.height = abs(intersect.height - intersect.y);

	return intersect;
}

void from_json(const nlohmann::json& json, MyRectangle& rectangle) {
	try {
		rectangle.set_x((json.at("x").get<int>()));
		rectangle.set_y((json.at("y").get<int>()));
		rectangle.set_width((json.at("w").get<int>()));
		rectangle.set_height((json.at("h").get<int>()));
	}
	catch (std::exception e) {
		std::cerr << "Incorrect Structure for Rectangle " << rectangle.get_id() << std::endl;
		throw e;
	}
}

bool open_json(char* file, nlohmann::json& json) {
	std::ifstream filestream(file);
	if (!filestream) {
		std::cerr << "Input file error" << std::endl;
		return false;
	}

	try {
		filestream >> json;
	}
	catch (std::exception e) {
		std::cerr << "Invalid JSON file" << std::endl;
		return false;
	}
	return true;
}