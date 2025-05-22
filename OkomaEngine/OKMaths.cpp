#include "OKMaths.h"

namespace OKMaths
{
	double DegreesToRadians(double degree)
	{
		return (degree * (OK_PI / 180));
	}

	double RadiansToDegree(double radians)
	{
		return (radians * (180 / OK_PI));
	}

	float RandomRangeFLOAT(float min, float max)
	{
		std::random_device rd;
		std::uniform_real_distribution<float> Distance(min, max);
		return Distance(rd);
	}

	int RandomRangeINT(int min, int max)
	{
		std::random_device rd;
		std::uniform_int_distribution<int> Distance(min, max);
		return Distance(rd);
	}

	template<typename T>
	T Clamp(T value, T min, T max)
	{
		T t_tempValue = value;
		t_tempValue = value > max ? max : value;
		t_tempValue = value < min ? min : value;
		return t_tempValue;
	}
};