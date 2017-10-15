#include "Intersection.h"

Intersection::Intersection() {
	HitDistance = 1e10; Mtl = 0; hitIndex = -1; skipLight = std::vector<int>(0);
}