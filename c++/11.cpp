// zadanie na zaliczenie

// Implement Matrix<N, M, T> (order is random here!)
//     N - number of rows
//     M - number of columns
//     has templated copy ctor ( const Matrix<N1, M1, T1>& )
//         ​N1 < N
//         M1 < M
//         T1 convertible to T 
//     has operators:
//         ​operator<<
//         operator[]
//         template operator+ (const Matrix<N1, M1, T1>)
//     is specialized for N = 0 && M = 0 (cannot be created)
//     is specialized for bools!! (std::vector<bool> is pure evil!)

#include <iostream>

template<int x, int y, typename T>
class matrix
{
    private:
        std::vector<std::vector<T>> _vector;
        std::vector<T> _vector_y { 0 };

    public:
        matrix()
        {
            for(int i=0; i<x; i++)
            {

            }
        }
};

int main()
{

}