#pragma once

#include <iostream>
#include <fstream>
#include <set>
#include <optional>
#include "json.hpp"

class MyRectangle {
private:
	static int curr_id;
	const int id;
	int x;
	int y;
	int width;
	int height;

public:
	MyRectangle();
	MyRectangle(int, int, int, int);

	int get_x() const;
	int get_y() const;
	int get_width() const;
	int get_height() const;
	int get_id() const;

	void set_x(int new_x);
	void set_y(int new_y);
	void set_width(int w);
	void set_height(int h);

	int get_area() const;

	void print();

	MyRectangle& operator = (MyRectangle other);

	std::optional<MyRectangle> is_intersecting(MyRectangle &other);
};

void from_json(const nlohmann::json& j, ::MyRectangle& r);

bool open_json(char* file, nlohmann::json& j);