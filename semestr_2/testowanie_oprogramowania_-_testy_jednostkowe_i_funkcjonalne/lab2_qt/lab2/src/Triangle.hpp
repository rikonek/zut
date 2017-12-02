#ifndef __TRIANGEL_HPP__
#define __TRIANGEL_HPP__

#include "IShape.hpp"

class Triangle : public IShape 
{
	public:
		Triangle(int a, int h);
		~Triangle();

		double getArea() override;
	
	private:
		int _a, _h;
};

#endif
