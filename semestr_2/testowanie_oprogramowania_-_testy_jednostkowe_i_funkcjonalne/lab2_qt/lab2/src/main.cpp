#include <iostream>
#include "Picture.hpp"
#include "Rectangle.hpp"
#include "Triangle.hpp"

int main(int , char **)
{
    Picture myPicture;
    myPicture.addShape(new Rectangle(2,4));
    myPicture.addShape(new Rectangle(4,4));
    myPicture.addShape(new Triangle(2,4));
    myPicture.addShape(new Triangle(4,4));

    std::cout << "Total area size = " << myPicture.getTotalArea() << std::endl;
}
