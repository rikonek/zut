// implement a program that:

// has a Shape interface with Rect, Circle and triangle implementations
// have a function that accepts Shape pointer
// calculates Shape area
// shape is created based command line input
// shape parameters are random (0, 100)

#include <iostream>

class shape
{
    public:
        void rect();
        void circle();
        void triangle();
};

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int a=rand() % 100; // a or r
    int b=rand() % 100;
    int c=rand() % 100;

    // std::cout << ""

    std::string in_shape=argv[1];
    switch(in_shape)
    {
        case "rect":
            break;

        // case "circle":
        //     break;
        
        // case "triangle":
        //     break;
    }

    return 0;
}