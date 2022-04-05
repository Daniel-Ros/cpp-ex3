#include "Matrix.hpp"
#include <exception>
#include <algorithm>
#include <sstream>


namespace zich
{    
    std::ostream& operator<<(std::ostream& stream,const Matrix& matrix)
    {
        for (size_t i = 0; i < matrix.m_Columns; i++)
        {
            bool firstPrint = true;
            stream << '[';
            for (size_t j = 0; j < matrix.m_Rows; j++)
            {
                if(!firstPrint)
                {
                    stream << " ";
                }
                stream << matrix.m_Data.at(i*matrix.m_Columns+j);
                firstPrint = false;
            }
            stream << ']' << '\n';
        }
        stream << std::endl;
        return stream;
    }

    std::istream& operator>>(std::istream& stream,const Matrix& matrix)
    {
        std::string ss;
        std::getline(stream, ss);
        std::string fh = ss.substr(0,ss.find_first_of(']')+1);
        std::string sh = ss.substr(ss.find_first_of(']')+1,ss.size());
        std::cout << fh << "\n" << sh;
        return stream;
    }

    Matrix::Matrix(std::vector<double> data,unsigned int rows, unsigned int columns)
        : m_Data(data), m_Rows(rows), m_Columns(columns)
    {
        if(data.size() != rows * columns)
        {
            throw std::invalid_argument("matirx data not corllate to size");
        }
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
        if(m_Columns != matrix.m_Columns && m_Rows != matrix.m_Rows)
        {
            throw std::invalid_argument("Matrix sizes should be the same");
        }
        std::vector<double> dataVector;
        for (size_t i = 0; i < m_Data.size(); i++)
        {
            double data = m_Data.at(i) 
                        + matrix.m_Data.at(i);
            dataVector.push_back(data);
        }

        return Matrix(dataVector,m_Rows,m_Columns);
    }

    Matrix& Matrix::operator+=(const Matrix& matrix)
    {
        if(m_Columns != matrix.m_Columns && m_Rows != matrix.m_Rows)
        {
            throw std::invalid_argument("Matrix sizes should be the same");
        }
        for (size_t i = 0; i < m_Data.size(); i++)
        {
            m_Data.at(i) += matrix.m_Data.at(i);
        }
        return *this;
    }

    Matrix Matrix::operator-() const
    {
        auto dataVector = m_Data;
        for(double& d:dataVector)
        {
            d = 0 - d;
        }
        return Matrix(dataVector,m_Rows,m_Columns);
    }

    Matrix Matrix::operator-(const Matrix& matrix) const
    {
        if(m_Columns != matrix.m_Columns && m_Rows != matrix.m_Rows)
        {
            throw std::invalid_argument("Matrix sizes should be the same");
        }
        std::vector<double> dataVector;
        for (size_t i = 0; i < m_Data.size(); i++)
        {
            double data = m_Data.at(i) 
                        - matrix.m_Data.at(i);
            dataVector.push_back(data);
        }

        return Matrix(dataVector,m_Rows,m_Columns);
    }

    Matrix& Matrix::operator-=(const Matrix& matrix)
    {
        if(m_Columns != matrix.m_Columns && m_Rows != matrix.m_Rows)
        {
            throw std::invalid_argument("Matrix sizes should be the same");
        }
        for (size_t i = 0; i < m_Data.size(); i++)
        {
            m_Data.at(i) -= matrix.m_Data.at(i);
        }
        return *this;
    }

    Matrix& Matrix::operator++()
    {
        std::for_each(m_Data.begin(),m_Data.end(),[](double& d){d++;});
        return *this;
    } 

    Matrix& Matrix::operator++(int)
    {
        std::for_each(m_Data.begin(),m_Data.end(),[](double& d){d++;});
        return *this;
    } 

    Matrix& Matrix::operator--()
    {
        std::for_each(m_Data.begin(),m_Data.end(),[](double& d){d--;});
        return *this;
    }

    Matrix& Matrix::operator--(int)
    {
        std::for_each(m_Data.begin(),m_Data.end(),[](double& d){d--;});
        return *this;
    }

    bool Matrix::operator==(const Matrix& matrix) const
    {
        if(m_Columns != matrix.m_Columns && m_Rows != matrix.m_Rows)
        {
            throw std::invalid_argument("Matrix sizes should be the same");
        }
        for (size_t i = 0; i < m_Data.size(); i++)
        {   
            if(m_Data.at(i) != matrix.m_Data.at(i))
            {
              return false;
            }
        }
        return true;
    }

    bool Matrix::operator!=(const Matrix& matrix) const
    {
        return !(*this == matrix);
    }

    bool Matrix::operator>(const Matrix& matrix)  const
    {
        double sum1;
        double sum2;
        std::for_each(m_Data.begin(),m_Data.end(),[&](double d){sum1+=d;});
        std::for_each(matrix.m_Data.begin(),matrix.m_Data.end(),[&](double d){sum2+=d;});

        return sum1 > sum2;
    }

    bool Matrix::operator>=(const Matrix& matrix) const
    {
        double sum1;
        double sum2;
        std::for_each(m_Data.begin(),m_Data.end(),[&](double d){sum1+=d;});
        std::for_each(matrix.m_Data.begin(),matrix.m_Data.end(),[&](double d){sum2+=d;});

        return sum1 > sum2;
    }

    bool Matrix::operator<(const Matrix& matrix)  const
    {
        double sum1;
        double sum2;
        std::for_each(m_Data.begin(),m_Data.end(),[&](double d){sum1+=d;});
        std::for_each(matrix.m_Data.begin(),matrix.m_Data.end(),[&](double d){sum2+=d;});

        return sum1 < sum2;
    }

    bool Matrix::operator<=(const Matrix& matrix) const
    {
        double sum1;
        double sum2;
        std::for_each(m_Data.begin(),m_Data.end(),[&](double d){sum1+=d;});
        std::for_each(matrix.m_Data.begin(),matrix.m_Data.end(),[&](double d){sum2+=d;});

        return sum1 <= sum2;
    }

    Matrix operator*(const double d,const Matrix& matrix) // not a member function, but it's the place for it now
    {
        return matrix * d;
    }

    Matrix Matrix::operator*(double scalar) const
    {
        auto dataVector = m_Data;
        std::for_each(dataVector.begin(),dataVector.end(),[=](double& d){d*=scalar;});
        return Matrix(dataVector,m_Rows,m_Columns);
    }   

    Matrix& Matrix::operator*=(double scalar)
    {
        std::for_each(m_Data.begin(),m_Data.end(),[=](double& d){d*=scalar;}); //could use [&] doesn't really matter as we only copying 8 byte double the same as a pointer 
        return *this;
    }

    Matrix Matrix::operator*(const Matrix& matrix) const
    {
        if(m_Columns != matrix.m_Rows)
        {
            throw std::invalid_argument("matrix multiplaction is not right");
        }
        std::vector<double> dataVector;
        for (size_t i = 0; i < m_Rows; i++)
        {
           for (size_t j = 0; j < matrix.m_Columns; j++)
           {
               double tempVal = 0;
               for (size_t k = 0; k < matrix.m_Rows; k++)
               {
                   tempVal += m_Data.at(i * m_Rows + k) * matrix.m_Data.at(k * matrix.m_Rows + j);
               }
               dataVector.push_back(tempVal);
           }
        }
        return Matrix(dataVector,m_Rows,matrix.m_Columns);
    }

    Matrix& Matrix::operator*=(const Matrix& matrix)
    {
        if(m_Columns != matrix.m_Rows)
        {
            throw std::invalid_argument("matrix multiplaction is not right");
        }
        std::vector<double> dataVector;
        for (size_t i = 0; i < m_Rows; i++)
        {
           for (size_t j = 0; j < matrix.m_Columns; j++)
           {
               double tempVal = 0;
               for (size_t k = 0; k < matrix.m_Rows; k++)
               {
                   tempVal += m_Data.at(i * m_Rows + k) * matrix.m_Data.at(k * matrix.m_Rows + j);
               }
               m_Data.at(i*m_Columns + j);
           }
        }
        return *this;
    }

} // namespace zich