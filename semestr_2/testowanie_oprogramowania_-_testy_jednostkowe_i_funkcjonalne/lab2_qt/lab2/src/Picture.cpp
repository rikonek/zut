#include "Picture.hpp"

Picture::Picture() {}

Picture::~Picture() {}

void Picture::addShape(IShape* shape)
{
	_vec_shapes.push_back(shape);
}

double Picture::getTotalArea()
{
	double retVal = 0.0;

	for(auto sh : _vec_shapes) 
	{
		double temp = sh->getArea();
		if(temp > 0)
			retVal += temp;
	}

	return retVal;
}
