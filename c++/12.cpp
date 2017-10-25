// implement a find min function that: 

// is a template function ! :)
// accepts arguments as an array (pointer, array)
// returns smallest element

// ------------------------------------------------------------------------------

// Implement min() function that:

// accepts two args: array, function pointer
// works on C-style array (arr, ptr) (yes, template)
// returns void
// when min element is found function pointer is invoked
// function pointer has signature: void ()(const TYPE &t)


#include <iostream>
#include <algorithm>

// template <typename T>
// using fun_ptr = void (*)(T);

template<typename T>
T minimum(T* arr, std::size_t size, fun_ptr<T> fn)
{
    auto out = *(std::min_element(arr, arr+size));
    fn(out);
    // return 4;
}

int main()
{
    int x[5]={1,2,3,4,5};
    std::cout << minimum(x,5) << std::endl;
    return 0;
}