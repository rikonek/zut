#include "Triangle.hpp"

Triangle::Triangle(int a, int h)
	: _a(a), _h(h) {} 

Triangle::~Triangle() {}

double Triangle::getArea()
{
	return 0.5 * _a * _h;
}
