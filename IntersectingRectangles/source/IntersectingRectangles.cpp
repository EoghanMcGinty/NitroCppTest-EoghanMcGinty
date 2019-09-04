
#include "IntersectingRectangles.h"
#include <set>
#include <cmath>
#include <algorithm>

int main(int argc, char* argv[])
{
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " <file>.json" << std::endl;
		return 1;
	}

	std::cout << "Name of file " << argv[1] << std::endl;
	nlohmann::json j;
	if (!open_json(argv[1], j)) {
		return 1;
	}	

	if (j["rects"].empty()) {
		std::cerr << "Invalid JSON rects structure" << std::endl;
		return 1;
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
			return 1;
		}
	}

	std::cout << "Input: " << std::endl;
	for (auto& rect : rect_vec) {
		rect.print_rectangle();
	}

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

	std::vector<MyRectangle> orig_inter_vector = inter_vector;
	
	std::set<MyRectangle> inter_set;
	while (!inter_vector.empty()) {
		std::vector<MyRectangle> new_inter_vector;
		for (auto& inter_iterator = inter_vector.begin(); inter_iterator != inter_vector.end(); ++inter_iterator) {
			auto next_iter = std::next(inter_iterator, 1);
			std::find_if(next_iter, inter_vector.end(),
				[&](MyRectangle intersect2) {
				MyRectangle new_intersect;
				bool yes = is_intersecting_intersections(*inter_iterator, intersect2, new_intersect);
				if (!yes) {
					return false;
				}
				auto result = inter_set.insert(new_intersect);
				if (result.second) {
					new_inter_vector.push_back(new_intersect);
				}
				return false;
			}
			);
		}
		inter_vector = new_inter_vector;
	}

	std::cout << "\nIntersections:" << std::endl;
	for (auto& inter : orig_inter_vector) {
		inter.print_intersection();
	}
	for (auto inter : inter_set) {
		inter.print_intersection();
	}

	return 0;
}

