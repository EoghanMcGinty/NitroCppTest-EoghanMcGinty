#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../source/MyRectangle.h"
#include "../source/MyIntersection.h"

TEST_CASE("Create Rectangle", "[rectangle]") {
	MyRectangle rectangle(100, 50, 90, 580);
	rectangle.print();
	REQUIRE(rectangle.get_x() == 100);
	REQUIRE(rectangle.get_y() == 50);
	REQUIRE(rectangle.get_width() == 90);
	REQUIRE(rectangle.get_height() == 580);
}

TEST_CASE("Overlap Test", "[rectangle]") {
	MyRectangle rectangle1(100, 100, 250, 80);
	MyRectangle rectangle2(140, 160, 250, 100);
	auto intersection = rectangle1.is_intersecting(rectangle2);
	intersection->print();
	REQUIRE(intersection != std::nullopt);
	REQUIRE(intersection->get_x() == 140);
	REQUIRE(intersection->get_y() == 160);
	REQUIRE(intersection->get_width() == 210);
	REQUIRE(intersection->get_height() == 20);
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
	intersection1.set_ids({1,2,3,4});
	MyIntersection intersection2(120, 200, 250, 150);
	intersection2.set_ids({3,4,5,6});
	auto new_intersection = intersection1.is_intersecting(intersection2);
	std::set<int> testset{1, 2, 3, 4, 5, 6};
	new_intersection->print();
	REQUIRE(new_intersection != std::nullopt);
	REQUIRE(new_intersection->get_ids() == testset);
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
	MyRectangle rectangle;
	rectangle.set_height(-50);
	rectangle.set_width(INT_MAX + 1);
	REQUIRE(rectangle.get_height() == 0);
	REQUIRE(rectangle.get_width() == 0);
}

TEST_CASE("10 overlapping intersections", "[intersection]") {
	MyRectangle rectangle1(100, 100, 100, 150);
	MyRectangle rectangle2(105, 105, 150, 100);
	MyRectangle rectangle3(90, 90, 140, 200);
	MyRectangle rectangle4(95, 95, 95, 95);
	MyRectangle rectangle5(110, 110, 150, 200);
	MyRectangle rectangle6(100, 100, 80, 150);
	MyRectangle rectangle7(100, 100, 200, 200);
	MyRectangle rectangle8(90, 90, 90, 150);
	MyRectangle rectangle9(110, 110, 250, 80);
	MyRectangle rectangle10(95, 95, 95, 95);

	std::vector<MyRectangle> rect_vec;
	rect_vec.push_back(rectangle1);
	rect_vec.push_back(rectangle2);
	rect_vec.push_back(rectangle3);
	rect_vec.push_back(rectangle4);
	rect_vec.push_back(rectangle5);
	rect_vec.push_back(rectangle6);
	rect_vec.push_back(rectangle7);
	rect_vec.push_back(rectangle8);
	rect_vec.push_back(rectangle9);
	rect_vec.push_back(rectangle10);

	std::vector<MyIntersection> inter_vector;
	for (auto& rect_iterator = rect_vec.begin(); rect_iterator != rect_vec.end(); ++rect_iterator) {
		auto next_iter = std::next(rect_iterator, 1);
		auto it = std::find_if(next_iter, rect_vec.end(),
			[&](MyRectangle rect_other) {
			auto rectangle = rect_iterator->is_intersecting(rect_other);
			if (!rectangle) {
				return false;
			}
			MyIntersection intersection(*rectangle);
			intersection.insert_id(rect_iterator->get_id());
			intersection.insert_id(rect_other.get_id());
			inter_vector.push_back(intersection);
			return false;
		}
		);
	}

	std::vector<MyIntersection> orig_inter_vector = inter_vector;

	std::set<MyIntersection> inter_set;
	while (!inter_vector.empty()) {
		std::vector<MyIntersection> new_inter_vector;
		for (auto& inter_iterator = inter_vector.begin(); inter_iterator != inter_vector.end(); ++inter_iterator) {
			auto next_iter = std::next(inter_iterator, 1);
			auto it = std::find_if(next_iter, inter_vector.end(),
				[&](MyIntersection intersect_other) {
				auto new_intersect = inter_iterator->is_intersecting(intersect_other);
				if (!new_intersect) {
					return false;
				}
				auto result = inter_set.insert(*new_intersect);
				if (result.second) {
					new_inter_vector.push_back(*new_intersect);
				}
				return false;
			}
			);
		}
		inter_vector = new_inter_vector;
	}
	bool yes = false;
	for (auto& inter : inter_set) {
		if (inter.number_of_intersections() == 10) {
			yes = true;
		}
	}

	REQUIRE(yes == true);
}

TEST_CASE("0 overlapping intersections", "[intersection]") {
	MyRectangle rectangle1(100, 100, 40, 40);
	MyRectangle rectangle2(305, 305, 40, 40);
	MyRectangle rectangle3(-90, -90, 40, 40);
	MyRectangle rectangle4(405, 405, 40, 40);
	MyRectangle rectangle5(510, 510, 40, 40);
	MyRectangle rectangle6(700, 700, 40, 40);
	MyRectangle rectangle7(900, 900, 40, 40);
	MyRectangle rectangle8(-190, -190, 40, 40);
	MyRectangle rectangle9(1110, 1110, 40, 40);
	MyRectangle rectangle10(-295, -295, 45, 45);

	std::vector<MyRectangle> rect_vec;
	rect_vec.push_back(rectangle1);
	rect_vec.push_back(rectangle2);
	rect_vec.push_back(rectangle3);
	rect_vec.push_back(rectangle4);
	rect_vec.push_back(rectangle5);
	rect_vec.push_back(rectangle6);
	rect_vec.push_back(rectangle7);
	rect_vec.push_back(rectangle8);
	rect_vec.push_back(rectangle9);
	rect_vec.push_back(rectangle10);

	std::vector<MyIntersection> inter_vector;
	for (auto& rect_iterator = rect_vec.begin(); rect_iterator != rect_vec.end(); ++rect_iterator) {
		auto next_iter = std::next(rect_iterator, 1);
		auto it = std::find_if(next_iter, rect_vec.end(),
			[&](MyRectangle rect_other) {
			auto rectangle = rect_iterator->is_intersecting(rect_other);
			if (!rectangle) {
				return false;
			}
			MyIntersection intersection(*rectangle);
			intersection.insert_id(rect_iterator->get_id());
			intersection.insert_id(rect_other.get_id());
			inter_vector.push_back(intersection);
			return false;
		}
		);
	}

	std::cout << "\nIntersections:" << std::endl;
	for (auto& inter : inter_vector) {
		inter.print();
	}

	std::vector<MyIntersection> orig_inter_vector = inter_vector;

	std::set<MyIntersection> inter_set;
	while (!inter_vector.empty()) {
		std::vector<MyIntersection> new_inter_vector;
		for (auto& inter_iterator = inter_vector.begin(); inter_iterator != inter_vector.end(); ++inter_iterator) {
			auto next_iter = std::next(inter_iterator, 1);
			auto it = std::find_if(next_iter, inter_vector.end(),
				[&](MyIntersection intersect_other) {
				auto new_intersect = inter_iterator->is_intersecting(intersect_other);
				if (!new_intersect) {
					return false;
				}
				auto result = inter_set.insert(*new_intersect);
				if (result.second) {
					new_inter_vector.push_back(*new_intersect);
				}
				return false;
			}
			);
		}
		inter_vector = new_inter_vector;
	}

	REQUIRE(inter_set.empty() == true);
	REQUIRE(orig_inter_vector.empty() == true);
}

TEST_CASE("5 overlapping intersections", "[intersection]") {
	MyRectangle rectangle1(100, 100, 100, 150);
	MyRectangle rectangle2(105, 105, 150, 100);
	MyRectangle rectangle3(90, 90, 140, 200);
	MyRectangle rectangle4(95, 95, 95, 95);
	MyRectangle rectangle5(110, 110, 150, 200);
	MyRectangle rectangle6(700, 700, 40, 40);
	MyRectangle rectangle7(900, 900, 40, 40);
	MyRectangle rectangle8(-190, -190, 40, 40);
	MyRectangle rectangle9(1110, 1110, 40, 40);
	MyRectangle rectangle10(-295, -295, 45, 45);

	std::vector<MyRectangle> rect_vec;
	rect_vec.push_back(rectangle1);
	rect_vec.push_back(rectangle2);
	rect_vec.push_back(rectangle3);
	rect_vec.push_back(rectangle4);
	rect_vec.push_back(rectangle5);
	rect_vec.push_back(rectangle6);
	rect_vec.push_back(rectangle7);
	rect_vec.push_back(rectangle8);
	rect_vec.push_back(rectangle9);
	rect_vec.push_back(rectangle10);

	std::vector<MyIntersection> inter_vector;
	for (auto& rect_iterator = rect_vec.begin(); rect_iterator != rect_vec.end(); ++rect_iterator) {
		auto next_iter = std::next(rect_iterator, 1);
		auto it = std::find_if(next_iter, rect_vec.end(),
			[&](MyRectangle rect_other) {
			auto rectangle = rect_iterator->is_intersecting(rect_other);
			if (!rectangle) {
				return false;
			}
			MyIntersection intersection(*rectangle);
			intersection.insert_id(rect_iterator->get_id());
			intersection.insert_id(rect_other.get_id());
			inter_vector.push_back(intersection);
			return false;
		}
		);
	}

	std::vector<MyIntersection> orig_inter_vector = inter_vector;

	std::set<MyIntersection> inter_set;
	while (!inter_vector.empty()) {
		std::vector<MyIntersection> new_inter_vector;
		for (auto& inter_iterator = inter_vector.begin(); inter_iterator != inter_vector.end(); ++inter_iterator) {
			auto next_iter = std::next(inter_iterator, 1);
			auto it = std::find_if(next_iter, inter_vector.end(),
				[&](MyIntersection intersect_other) {
				auto new_intersect = inter_iterator->is_intersecting(intersect_other);
				if (!new_intersect) {
					return false;
				}
				auto result = inter_set.insert(*new_intersect);
				if (result.second) {
					new_inter_vector.push_back(*new_intersect);
				}
				return false;
			}
			);
		}
		inter_vector = new_inter_vector;
	}
	bool yes = false;
	for (auto& inter : inter_set) {
		if (inter.number_of_intersections() == 5) {
			yes = true;
		}
	}

	REQUIRE(yes == true);
}


TEST_CASE("Area of 5 overlapping intersections", "[area]") {
	MyRectangle rectangle1(100, 100, 100, 150);
	MyRectangle rectangle2(105, 105, 150, 100);
	MyRectangle rectangle3(90, 90, 140, 200);
	MyRectangle rectangle4(95, 95, 95, 95);
	MyRectangle rectangle5(110, 110, 150, 200);

	std::vector<MyRectangle> rect_vec;
	rect_vec.push_back(rectangle1);
	rect_vec.push_back(rectangle2);
	rect_vec.push_back(rectangle3);
	rect_vec.push_back(rectangle4);
	rect_vec.push_back(rectangle5);

	std::vector<MyIntersection> inter_vector;
	for (auto& rect_iterator = rect_vec.begin(); rect_iterator != rect_vec.end(); ++rect_iterator) {
		auto next_iter = std::next(rect_iterator, 1);
		auto it = std::find_if(next_iter, rect_vec.end(),
			[&](MyRectangle rect_other) {
			auto rectangle = rect_iterator->is_intersecting(rect_other);
			if (!rectangle) {
				return false;
			}
			MyIntersection intersection(*rectangle);
			intersection.insert_id(rect_iterator->get_id());
			intersection.insert_id(rect_other.get_id());
			inter_vector.push_back(intersection);
			return false;
		}
		);
	}

	std::vector<MyIntersection> orig_inter_vector = inter_vector;

	std::set<MyIntersection> inter_set;
	while (!inter_vector.empty()) {
		std::vector<MyIntersection> new_inter_vector;
		for (auto& inter_iterator = inter_vector.begin(); inter_iterator != inter_vector.end(); ++inter_iterator) {
			auto next_iter = std::next(inter_iterator, 1);
			auto it = std::find_if(next_iter, inter_vector.end(),
				[&](MyIntersection intersect_other) {
				auto new_intersect = inter_iterator->is_intersecting(intersect_other);
				if (!new_intersect) {
					return false;
				}
				auto result = inter_set.insert(*new_intersect);
				if (result.second) {
					new_inter_vector.push_back(*new_intersect);
				}
				return false;
			}
			);
		}
		inter_vector = new_inter_vector;
	}

	int area = 0;
	for (auto& rect : rect_vec) {
		area += rect.get_area();
	}
	for (auto& inter : orig_inter_vector) {
		area -= inter.get_area();
	}
	for (auto& inter : inter_set) {
		if (inter.number_of_intersections() % 2 == 0) {
			area -= inter.get_area();
		}
		else {
			area += inter.get_area();
		}
	}

	REQUIRE(area == 36525);
}

TEST_CASE("Area of 0 overlapping intersections", "[area]") {
	MyRectangle rectangle1(100, 100, 40, 40);
	MyRectangle rectangle2(305, 305, 40, 40);
	MyRectangle rectangle3(-90, -90, 40, 40);
	MyRectangle rectangle4(405, 405, 40, 40);
	MyRectangle rectangle5(510, 510, 40, 40);

	std::vector<MyRectangle> rect_vec;
	rect_vec.push_back(rectangle1);
	rect_vec.push_back(rectangle2);
	rect_vec.push_back(rectangle3);
	rect_vec.push_back(rectangle4);
	rect_vec.push_back(rectangle5);

	std::vector<MyIntersection> inter_vector;
	for (auto& rect_iterator = rect_vec.begin(); rect_iterator != rect_vec.end(); ++rect_iterator) {
		auto next_iter = std::next(rect_iterator, 1);
		auto it = std::find_if(next_iter, rect_vec.end(),
			[&](MyRectangle rect_other) {
			auto rectangle = rect_iterator->is_intersecting(rect_other);
			if (!rectangle) {
				return false;
			}
			MyIntersection intersection(*rectangle);
			intersection.insert_id(rect_iterator->get_id());
			intersection.insert_id(rect_other.get_id());
			inter_vector.push_back(intersection);
			return false;
		}
		);
	}

	std::vector<MyIntersection> orig_inter_vector = inter_vector;

	std::set<MyIntersection> inter_set;
	while (!inter_vector.empty()) {
		std::vector<MyIntersection> new_inter_vector;
		for (auto& inter_iterator = inter_vector.begin(); inter_iterator != inter_vector.end(); ++inter_iterator) {
			auto next_iter = std::next(inter_iterator, 1);
			auto it = std::find_if(next_iter, inter_vector.end(),
				[&](MyIntersection intersect_other) {
				auto new_intersect = inter_iterator->is_intersecting(intersect_other);
				if (!new_intersect) {
					return false;
				}
				auto result = inter_set.insert(*new_intersect);
				if (result.second) {
					new_inter_vector.push_back(*new_intersect);
				}
				return false;
			}
			);
		}
		inter_vector = new_inter_vector;
	}

	int area = 0;
	for (auto& rect : rect_vec) {
		area += rect.get_area();
	}
	for (auto& inter : orig_inter_vector) {
		area -= inter.get_area();
	}
	for (auto& inter : inter_set) {
		if (inter.number_of_intersections() % 2 == 0) {
			area -= inter.get_area();
		}
		else {
			area += inter.get_area();
		}
	}

	REQUIRE(area == 8000);
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
	REQUIRE(rectangle.get_x() == 100);
	REQUIRE(rectangle.get_y() == 100);
	REQUIRE(rectangle.get_width() == 250);
	REQUIRE(rectangle.get_height() == 80);
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
	REQUIRE(rect_vec[4].get_x() == 80);
	REQUIRE(rect_vec[2].get_y() == -30);
	REQUIRE(rect_vec[7].get_width() == 500);
	REQUIRE(rect_vec[9].get_height() == 70);
}
