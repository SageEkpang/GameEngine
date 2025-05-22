#ifndef OK_MATHS_H
#define OK_MATHS_H

#include <iostream>
#include <random>

namespace OKMaths
{
	constexpr double OK_PI = 3.14159265359f;

	double DegreesToRadians(double degree);

	double RadiansToDegree(double radians);

	float RandomRangeFLOAT(float min, float max);
	int RandomRangeINT(int min, int max);

	template<typename T>
	T Clamp(T value, T min, T max);
};

#endif