#include "doctest.h"
#include "Matrix.hpp"
using namespace zich;

#include <sstream>
#include <regex>

std::string removeNewLines(std::string input){
    std::regex_replace(input,std::regex("\n"),", ");
    return input;
}

TEST_CASE("test streams")
{
    std::stringstream isstream("[1 0 0], [0 1 0], [0 0 1]");
    std::stringstream osstream;
    Matrix m;
    isstream >> m;
    osstream << m;
    CHECK_EQ(osstream.str(), isstream.str());
}

TEST_CASE("PLUS/MINUS TEST")
{
    std::stringstream osstream;
    std::vector<double> identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    Matrix id1{identity, 3, 3};  // constructor taking a vector and a matrix size
    Matrix id2{identity, 3, 3};  // constructor taking a vector and a matrix size

    auto res = +id1;
    osstream << res;
    CHECK_EQ(osstream.str(), "[1 0 0], [0 1 0], [0 0 1]");

    res = id1+id2;
    osstream << res;
    CHECK_EQ(osstream.str(), "[2 0 0], [0 2 0], [0 0 2]");

    res += id1;
    osstream << res;
    CHECK_EQ(osstream.str(), "[3 0 0], [0 3 0], [0 0 3]");

    res = -id1;
    osstream << res;
    CHECK_EQ(osstream.str(), "[-1 0 0], [0 -1 0], [0 0 -1]");

    res = id1-id2;
    osstream << res;
    CHECK_EQ(osstream.str(), "[0 0 0], [0 0 0], [0 0 0]");

    res -= id1;
    osstream << res;
    CHECK_EQ(osstream.str(), "[-1 0 0], [0 -1 0], [0 0 -1]");

    ++res;
    osstream << res;
    CHECK_EQ(osstream.str(), "[0 1 1], [1 0 1], [1 1 0]");

    --res;
    osstream << res;
    CHECK_EQ(osstream.str(), "[-1 0 0], [0 -1 0], [0 0 -1]");

    res++;
    osstream << res;
    CHECK_EQ(osstream.str(), "[0 1 1], [1 0 1], [1 1 0]");

    res--;
    osstream << res;
    CHECK_EQ(osstream.str(), "[-1 0 0], [0 -1 0], [0 0 -1]");
}


TEST_CASE("Equallity test")
{
    std::vector<double> identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    Matrix id1{identity, 3, 3};  // constructor taking a vector and a matrix size
    Matrix id2{identity, 3, 3};  // constructor taking a vector and a matrix size

    CHECK(id1 == id2);
    id1++;
    CHECK(id1 != id2);
    CHECK(id1 > id2);
    CHECK(id2 < id1);
    id2 *= 4;
    CHECK(id1 >= id2);
    CHECK(id2 <= id1);
}

TEST_CASE("MULTIPLICATION TEST")
{
    std::stringstream osstream;
    std::vector<double> identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    Matrix id1{identity, 3, 3};  // constructor taking a vector and a matrix size
    Matrix id2{identity, 3, 3};  // constructor taking a vector and a matrix size

    auto res = id1 * 3;
    osstream << res;
    CHECK_EQ(osstream.str(), "[3 0 0], [0 3 0], [0 0 3]");

    res = 3*id2;
    osstream << res;
    CHECK_EQ(osstream.str(), "[3 0 0], [0 3 0], [0 0 3]");

    res *= 3;
    osstream << res;
    CHECK_EQ(osstream.str(), "[9 0 0], [0 9 0], [0 0 9]");

    res *= id1;
    osstream << res;
    CHECK_EQ(osstream.str(), "[9 0 0], [0 9 0], [0 0 9]");

    res = id1 * id2;
    osstream << res;
    CHECK_EQ(osstream.str(), "[1 0 0], [0 1 0], [0 0 1]");
}