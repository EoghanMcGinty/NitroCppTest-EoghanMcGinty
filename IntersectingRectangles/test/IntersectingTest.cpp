#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../source/Rectangle.h"

TEST_CASE("Create Rectangle", "[rectangle]") {
	MyRectangle rectangle(100, 50, 90, 580);
	rectangle.print_rectangle();
	REQUIRE(rectangle.x == 100);
	REQUIRE(rectangle.y == 50);
	REQUIRE(rectangle.width == 90);
	REQUIRE(rectangle.height == 580);
}

TEST_CASE("Overlap Test", "[rectangle]") {
	MyRectangle rectangle1(100, 100, 250, 80);
	MyRectangle rectangle2(140, 160, 250, 100);
	MyRectangle intersection;
	bool yes = is_intersecting_rectangles(rectangle1, rectangle2, intersection);
	intersection.print_intersection();
	REQUIRE(yes == true);
	REQUIRE(intersection.x == 140);
	REQUIRE(intersection.y == 160);
	REQUIRE(intersection.width == 210);
	REQUIRE(intersection.height == 20);
}

TEST_CASE("Not Overlap Test", "[rectangle]") {
	MyRectangle rectangle1(100, 100, 250, 80);
	MyRectangle rectangle2(120, 200, 250, 150);
	MyRectangle intersection;
	bool yes = is_intersecting_rectangles(rectangle1, rectangle2, intersection);
	intersection.print_intersection();
	REQUIRE(yes == false);
}

TEST_CASE("Overlap Blank Rectangles Test", "[rectangle]") {
	MyRectangle rectangle1;
	MyRectangle rectangle2;
	MyRectangle intersection;
	bool yes = is_intersecting_rectangles(rectangle1, rectangle2, intersection);
	intersection.print_intersection();
	REQUIRE(yes == false);
}

TEST_CASE("Overlap One Blank Rectangle Test", "[rectangle]") {
	MyRectangle rectangle1;
	MyRectangle rectangle2(120, 200, 250, 150);
	MyRectangle intersection;
	bool yes = is_intersecting_rectangles(rectangle1, rectangle2, intersection);
	intersection.print_intersection();
	REQUIRE(yes == false);
}

TEST_CASE("Overlap Intersctions Test", "[rectangle]") {
	MyRectangle rectangle1(120, 200, 250, 150);
	rectangle1.intersecting_rects = {1,2,3,4};
	MyRectangle rectangle2(120, 200, 250, 150);
	rectangle2.intersecting_rects = {3,4,5,6};
	MyRectangle intersection;
	bool yes = is_intersecting_intersections(rectangle1, rectangle2, intersection);
	std::set<int> testset{1, 2, 3, 4, 5, 6};
	intersection.print_intersection();
	REQUIRE(yes == true);
	REQUIRE(intersection.intersecting_rects == testset);
}


TEST_CASE("Open JSON file", "[json]") {
	nlohmann::json j;
	bool yes = open_json("../../test/json/1rect.json", j);	
	REQUIRE(yes == true);
}

TEST_CASE("Open Bad JSON file", "[json]") {
	nlohmann::json j;
	bool yes = open_json("../../test/json/badjson.json", j);
	REQUIRE(yes == false);
}

TEST_CASE("Open JSON file convert to Rectangle", "[json]") {
	nlohmann::json j;
	bool yes = open_json("../../test/json/1rect.json", j);
	MyRectangle rectangle = j.get<MyRectangle>();
	rectangle.print_rectangle();
	REQUIRE(yes == true);
	REQUIRE(rectangle.x == 100);
	REQUIRE(rectangle.y == 100);
	REQUIRE(rectangle.width == 250);
	REQUIRE(rectangle.height == 80);
}

TEST_CASE("Open Incorrect JSON file try convert to Rectangle", "[json]") {
	nlohmann::json j;
	bool yes = open_json("../../test/json/badrect.json", j);
	try {
		MyRectangle rectangle = j.get<MyRectangle>();
	}
	catch (std::exception e) {		
		yes = false;		
	}
	REQUIRE(yes == false);
}

TEST_CASE("Open JSON file convert 10 Rectangles", "[json]") {
	nlohmann::json j;
	bool yes;
	yes = open_json("../../test/json/rectarray.json", j);
	if (j["rects"].empty()) {
		yes = false;
	}
	std::vector<MyRectangle> rect_vec;
	for (auto& rect : j["rects"]) {
		try {
			rect_vec.push_back(rect.get<MyRectangle>());
			if (rect_vec.size() == 10) {
				std::cout << "10 Rectangles read" << std::endl;
				break;
			}
		}
		catch (std::exception e) {
			yes = false;
			break;
		}
	}
	REQUIRE(yes == true);
	REQUIRE(rect_vec[4].x == 80);
	REQUIRE(rect_vec[2].y == -30);
	REQUIRE(rect_vec[7].width == 500);
	REQUIRE(rect_vec[9].height == 70);
}

TEST_CASE("Multiple Intersections", "[intersection]") {
	
	std::vector<MyRectangle> rect_vec;
	rect_vec.push_back(MyRectangle(110, 150, 200, 50));
	rect_vec.push_back(MyRectangle(100, 160, 180, 45));
	rect_vec.push_back(MyRectangle(90, 140, 210, 60));
	rect_vec.push_back(MyRectangle(100, 160, 185, 45));
	rect_vec.push_back(MyRectangle(70, 170, 300, 100));

	std::vector<MyRectangle> inter_vector;
	for (auto& rect_iterator = rect_vec.begin(); rect_iterator != rect_vec.end(); ++rect_iterator) {
		auto next_iter = std::next(rect_iterator, 1);
		std::find_if(next_iter, rect_vec.end(),
			[&](MyRectangle rect2) {
			MyRectangle intersect;
			bool yes = is_intersecting_rectangles(*rect_iterator, rect2, intersect);
			if (!yes) {
				return false;
			}
			inter_vector.push_back(intersect);
			return false;
		}
		);
	}

	std::set<MyRectangle> inter_set;
	for (auto& inter_iterator = inter_vector.begin(); inter_iterator != inter_vector.end(); ++inter_iterator) {
		auto next_iter = std::next(inter_iterator, 1);
		std::find_if(next_iter, inter_vector.end(),
			[&](MyRectangle intersect2) {
			MyRectangle new_intersect;
			bool yes = is_intersecting_intersections(*inter_iterator, intersect2, new_intersect);
			if (!yes) {
				return false;
			}
			inter_set.insert(new_intersect);
			return false;
		}
		);
	}
	MyRectangle rectangle = *(inter_set.begin());
	REQUIRE(inter_set.size() == 20);
	REQUIRE(rect_vec.size() == 5);
	REQUIRE(rectangle.intersecting_rects.size() == 3);
}