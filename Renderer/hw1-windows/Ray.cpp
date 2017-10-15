#include "Ray.h"

void Ray::setTime() {
	std::random_device rand_dev;
	std::mt19937 generator(rand_dev());
	std::uniform_real_distribution<double> distribution(0.0f, 1.0f);
	time = distribution(generator);
}