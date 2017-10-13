#pragma once

#include "glm/glm.hpp"
#include <random>


class Ray {
public:
	glm::vec3 Origin;
	glm::vec3 Direction;
	float time;

	void setTime() {
		std::random_device rand_dev;
		std::mt19937 generator(rand_dev());
		std::uniform_real_distribution<double> distribution(0.0f, 1.0f);
		time = distribution(generator);
	}
};
