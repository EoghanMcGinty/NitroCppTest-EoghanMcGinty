#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../source/MyRectangle.h"
#include "../source/MyIntersection.h"

TEST_CASE("Create Rectangle", "[rectangle]") {
	MyRectangle rectangle(100, 50, 90, 580);
	rectangle.print();
	REQUIRE(rectangle.getX() == 100);
	REQUIRE(rectangle.getY() == 50);
	REQUIRE(rectangle.getWidth() == 90);
	REQUIRE(rectangle.getHeight() == 580);
}

TEST_CASE("Overlap Test", "[rectangle]") {
	MyRectangle rectangle1(100, 100, 250, 80);
	MyRectangle rectangle2(140, 160, 250, 100);
	auto intersection = rectangle1.is_intersecting(rectangle2);
	intersection->print();
	REQUIRE(intersection != std::nullopt);
	REQUIRE(intersection->getX() == 140);
	REQUIRE(intersection->getY() == 160);
	REQUIRE(intersection->getWidth() == 210);
	REQUIRE(intersection->getHeight() == 20);
}

TEST_CASE("Not Overlap Test", "[rectangle]") {
	MyRectangle rectangle1(100, 100, 250, 80);
	MyRectangle rectangle2(120, 200, 250, 150);
	auto intersection = rectangle1.is_intersecting(rectangle2);
	REQUIRE(intersection == std::nullopt);
}

TEST_CASE("Overlap Blank Rectangles Test", "[rectangle]") {
	MyRectangle rectangle1;
	MyRectangle rectangle2;
	auto intersection = rectangle1.is_intersecting(rectangle2);
	REQUIRE(intersection == std::nullopt);
}

TEST_CASE("Overlap One Blank Rectangle Test", "[rectangle]") {
	MyRectangle rectangle1;
	MyRectangle rectangle2(120, 200, 250, 150);
	auto intersection = rectangle1.is_intersecting(rectangle2);
	REQUIRE(intersection == std::nullopt);
}

TEST_CASE("Overlap Two Null Rectangle Test", "[rectangle]") {
	MyRectangle rectangle1(0,0,0,0);
	MyRectangle rectangle2(0,0,0,0);
	auto intersection = rectangle1.is_intersecting(rectangle2);
	REQUIRE(intersection == std::nullopt);
}

TEST_CASE("Overlap Intersections Test", "[intersection]") {
	MyIntersection intersection1(120, 200, 250, 150);
	intersection1.setIntersections({1,2,3,4});
	MyIntersection intersection2(120, 200, 250, 150);
	intersection2.setIntersections({3,4,5,6});
	auto new_intersection = intersection1.is_intersecting(intersection2);
	std::set<int> testset{1, 2, 3, 4, 5, 6};
	new_intersection->print();
	REQUIRE(new_intersection != std::nullopt);
	REQUIRE(new_intersection->getIntersections() == testset);
}


TEST_CASE("Not Overlap Intersections Test", "[intersection]") {
	MyIntersection intersection1(100, 100, 250, 80);
	MyIntersection intersection2(120, 200, 250, 150);
	auto intersection = intersection1.is_intersecting(intersection2);
	REQUIRE(intersection == std::nullopt);
}

TEST_CASE("Overlap Blank Intersections Test", "[intersection]") {
	MyIntersection intersection1;
	MyIntersection intersection2;
	auto intersection = intersection1.is_intersecting(intersection2);
	REQUIRE(intersection == std::nullopt);
}

TEST_CASE("Overlap One Blank Intersections Test", "[intersection]") {
	MyIntersection intersection1;
	MyIntersection intersection2(120, 200, 250, 150);
	auto intersection = intersection1.is_intersecting(intersection2);
	REQUIRE(intersection == std::nullopt);
}

TEST_CASE("Overlap Two Null Intersections Test", "[intersection]") {
	MyIntersection intersection1(0, 0, 0, 0);
	MyIntersection intersection2(0, 0, 0, 0);
	auto intersection = intersection1.is_intersecting(intersection2);
	REQUIRE(intersection == std::nullopt);
}

TEST_CASE("Max Int On Rectangle", "[rectangle]") {
	MyRectangle intersection1(0, 0, 0, 0);
	
	REQUIRE(1 == 0);
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
	rectangle.print();
	REQUIRE(yes == true);
	REQUIRE(rectangle.getX() == 100);
	REQUIRE(rectangle.getY() == 100);
	REQUIRE(rectangle.getWidth() == 250);
	REQUIRE(rectangle.getHeight() == 80);
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
	REQUIRE(rect_vec[4].getX() == 80);
	REQUIRE(rect_vec[2].getY() == -30);
	REQUIRE(rect_vec[7].getWidth() == 500);
	REQUIRE(rect_vec[9].getHeight() == 70);
}
