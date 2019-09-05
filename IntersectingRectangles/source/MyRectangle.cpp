#include "MyRectangle.h"

MyRectangle::MyRectangle() : id(++curr_id) {}
MyRectangle::MyRectangle(int x, int y, int w, int h)
	: x(x), y(y), width(w), height(h), id(++curr_id) {}
int MyRectangle::curr_id = 0;

int MyRectangle::getX() const { return x; }
int MyRectangle::getY() const { return y; }
int MyRectangle::getWidth() const { return width; }
int MyRectangle::getHeight() const { return height; }
int MyRectangle::getId() const { return id; }

void MyRectangle::setX(int newX) { x = newX; }
void MyRectangle::setY(int newY) { y = newY; }
void MyRectangle::setWidth(int w) { width = w; }
void MyRectangle::setHeight(int h) { height = h; }

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
		rectangle.setX((json.at("x").get<int>()));
		rectangle.setY((json.at("y").get<int>()));
		rectangle.setWidth((json.at("w").get<int>()));
		rectangle.setHeight((json.at("h").get<int>()));
	}
	catch (std::exception e) {
		std::cerr << "Incorrect Structure for Rectangle " << rectangle.getId() << std::endl;
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