#pragma once

#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
#include <optional>
#include "json.hpp"

class MyRectangle {
private:
	static int curr_id;
	const int id;
protected:
	int x;
	int y;
	int width;
	int height;

public:
	MyRectangle();
	MyRectangle(int, int, int, int);

	int getX() const;
	int getY() const;
	int getWidth() const;
	int getHeight() const;
	int getId() const;

	void setX(int newX);
	void setY(int newY);
	void setWidth(int w);
	void setHeight(int h);

	void print();

	MyRectangle& operator = (MyRectangle other);

	std::optional<MyRectangle> is_intersecting(MyRectangle &other);
};

void from_json(const nlohmann::json& j, ::MyRectangle& r);

bool open_json(char* file, nlohmann::json& j);