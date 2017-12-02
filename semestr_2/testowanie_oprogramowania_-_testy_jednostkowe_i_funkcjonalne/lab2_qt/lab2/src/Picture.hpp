#ifndef __PICTURE_HPP__
#define __PICTURE_HPP__

#include "IShape.hpp"
#include <vector>

class Picture
{
	public:
		Picture();
		~Picture();
		void addShape(IShape* shape);
		double getTotalArea();

	private:
		std::vector<IShape*> _vec_shapes;
};

#endif
