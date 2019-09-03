#pragma once

#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
#include "json.hpp"

class MyRectangle {
private:
	static int curr_id;
public:
	const int id;
	std::set<int> intersecting_rects;
	int x;
	int y;
	int width;
	int height;

	MyRectangle();
	MyRectangle(int, int, int, int);

	void print_rectangle() {
		std::cout << "\t" << id << ": Rectangle at (" << x << "," << y
			<< "), w=" << width << ", h=" << height << std::endl;
	}

	void print_intersection() {
		if (intersecting_rects.empty()) {
			std::cout << "No Intersects" << std::endl;
			print_rectangle();
		} else {			
			std::cout << "\tBetween rectangle ";
			for (auto iter = intersecting_rects.begin(); iter != intersecting_rects.end(); ++iter) {
				std::cout << *iter;
				if (iter == std::prev(intersecting_rects.end()))
					std::cout << " ";
				else std::cout << ", ";

			}
			std::cout << "at (" << x << ", " << y
				<< "), w=" << width << ", h=" << height << std::endl;
		}
	}

	MyRectangle& operator = (MyRectangle other) {
		std::swap(x, other.x);
		std::swap(y, other.y);
		std::swap(width, other.width);
		std::swap(height, other.height);
		std::swap(intersecting_rects, other.intersecting_rects);
		return *this;
	}
	
	bool operator< (const MyRectangle& i) const {
		return (x < i.x || y < i.y || width < i.width || height < i.height || intersecting_rects < i.intersecting_rects);
	}

};

void from_json(const nlohmann::json& j, ::MyRectangle& r);

bool is_intersecting_rectangles(const ::MyRectangle &r1, const ::MyRectangle &r2, MyRectangle &i);
bool is_intersecting_intersections(const ::MyRectangle& r1, const ::MyRectangle& r2, ::MyRectangle& i);

bool open_json(char* file, nlohmann::json& j);