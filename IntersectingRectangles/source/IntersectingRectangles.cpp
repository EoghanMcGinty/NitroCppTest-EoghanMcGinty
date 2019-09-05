
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
		rect.print();
	}

	std::vector<MyIntersection> inter_vector;
	for (auto& rect_iterator = rect_vec.begin(); rect_iterator != rect_vec.end(); ++rect_iterator) {
		auto next_iter = std::next(rect_iterator, 1);
		std::find_if(next_iter, rect_vec.end(),
			[&](MyRectangle rect_other) {
				auto rectangle = rect_iterator->is_intersecting(rect_other);
				if (!rectangle) {
					return false;
				}
				MyIntersection intersection(*rectangle);
				intersection.insert_id(rect_iterator->getId());
				intersection.insert_id(rect_other.getId());
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
			std::find_if(next_iter, inter_vector.end(),
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

	std::cout << "\nIntersections:" << std::endl;
	for (auto& inter : orig_inter_vector) {
		inter.print();
	}
	for (auto& inter : inter_set) {
		inter.print();
	}

	return 0;
}

