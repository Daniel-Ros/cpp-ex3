#pragma once
#include <iostream>
#include <vector>
namespace zich
{
    class Matrix
    {
    public:
        Matrix();
        Matrix(const std::vector<double>&, int, int);
        Matrix(const std::vector<double>&, unsigned int, unsigned int);
        ~Matrix() = default;

        Matrix operator+() const ;
        Matrix operator+(const Matrix&) const;
        Matrix& operator+=(const Matrix&);
        Matrix operator-() const;
        Matrix operator-(const Matrix&) const;
        Matrix& operator-=(const Matrix&);

        Matrix& operator++();// prefix
        Matrix operator++(int); // postfix
        Matrix& operator--(); // prefix
        Matrix operator--(int); // postfix

        bool operator==(const Matrix&) const;
        bool operator!=(const Matrix&) const;
        bool operator>(const Matrix&)  const;
        bool operator>=(const Matrix&) const;
        bool operator<(const Matrix&)  const;
        bool operator<=(const Matrix&) const;

        friend  Matrix operator*(const double,const Matrix&);
        Matrix operator*(double) const;
        Matrix& operator*=(double);
        Matrix operator*(const Matrix&) const;
        Matrix& operator*=(const Matrix&);

        friend std::ostream& operator<<(std::ostream&,const Matrix&);
        friend std::istream& operator>>(std::istream&,Matrix&);
    private:
        std::vector<double> m_Data;
        unsigned int m_Rows;
        unsigned int m_Columns; 
    };
} // namespace zich
