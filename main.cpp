#include "Matrix.hpp"

#include <sstream>

int main()
{
    zich::Matrix m1({1,3,4,5},2,2);
    zich::Matrix m2({1,2,3,4},2,2);

    std::stringstream ss;
    ss.str("[1.11 1 1], [1 1 1]");

    ss >> m1;

    std::cout << "about to print m" << std::endl;
    m1 += m2;
    std::cout << m1;
}