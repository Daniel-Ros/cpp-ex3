#include "Matrix.hpp"
#include <exception>
#include <algorithm>
#include <sstream>


namespace zich
{    
    std::ostream& operator<<(std::ostream& stream,const Matrix& matrix)
    {

        return stream;
    }

    std::istream& operator>>(std::istream& stream,const Matrix& matrix)
    {

        return stream;
    }

    Matrix::Matrix(std::vector<double> data,unsigned int rows, unsigned int columns)
        : m_Data(data), m_Rows(rows), m_Columns(columns)
    {

    }

    Matrix::Matrix()
        : m_Data({}), m_Rows(0), m_Columns(0)
    {
        // nothing to do here
    }

    Matrix Matrix::operator+() const 
    {
        return Matrix(m_Data,m_Rows,m_Columns);
    }

    Matrix Matrix::operator+(const Matrix& matrix) const 
    {

        return Matrix(m_Data,m_Rows,m_Columns);
    }

    Matrix& Matrix::operator+=(const Matrix& matrix)
    {
        return *this;
    }

    Matrix Matrix::operator-() const
    {
        return Matrix(m_Data,m_Rows,m_Columns);
    }

    Matrix Matrix::operator-(const Matrix& matrix) const
    {
        return Matrix(m_Data,m_Rows,m_Columns);
    }

    Matrix& Matrix::operator-=(const Matrix& matrix)
    {
        return *this;
    }

    Matrix& Matrix::operator++()
    {
        return *this;
    } 

    Matrix& Matrix::operator++(int)
    {
        return *this;
    } 

    Matrix& Matrix::operator--()
    {
        return *this;
    }

    Matrix& Matrix::operator--(int)
    {
        return *this;
    }

    bool Matrix::operator==(const Matrix& matrix) const
    {
        return true;
    }

    bool Matrix::operator!=(const Matrix& matrix) const
    {
        return true;
    }

    bool Matrix::operator>(const Matrix& matrix)  const
    {
        return true;
    }

    bool Matrix::operator>=(const Matrix& matrix) const
    {
        return true;
    }

    bool Matrix::operator<(const Matrix& matrix)  const
    {
        return true;
    }

    bool Matrix::operator<=(const Matrix& matrix) const
    {
        return true;
    }

    Matrix operator*(const double d,const Matrix& matrix) // not a member function, but it's the place for it now
    {
        return Matrix(m_Data,m_Rows,m_Columns);;
    }

    Matrix Matrix::operator*(double scalar) const
    {
        return Matrix(m_Data,m_Rows,m_Columns);;
    }   

    Matrix& Matrix::operator*=(double scalar)
    {
        return *this;
    }

    Matrix Matrix::operator*(const Matrix& matrix) const
    {
        return Matrix(m_Data,m_Rows,m_Columns);;
    }

    Matrix& Matrix::operator*=(const Matrix& matrix)
    {
        return *this;
    }

} // namespace zich