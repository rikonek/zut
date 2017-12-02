#ifndef __RECTANGLE_HPP__
#define __RECTANGLE_HPP__

#include "IShape.hpp"

class Rectangle : public IShape 
{
	public:
		Rectangle(int a, int b);
		~Rectangle();

		double getArea() override;
	
	private:
		int _a, _b;
};

#endif
