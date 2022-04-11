#include "Matrix.hpp"
#include <exception>
#include <algorithm>
#include <sstream>


namespace zich
{    
    std::ostream& operator<<(std::ostream& stream,const Matrix& matrix)
    {
        for (size_t i = 0; i < matrix.m_Rows; i++)
        {
            bool firstPrint = true;
            stream << "[";
            for (size_t j = 0; j < matrix.m_Columns; j++)
            {
                if(!firstPrint)
                {
                    stream << " ";
                }
                stream << matrix.m_Data.at(i*matrix.m_Columns+j);
                firstPrint = false;
            }
            stream << "]";
            if(i != matrix.m_Rows - 1) //not the last run
            {
                stream << "\n";
            }
        }
        return stream;
    }

    std::vector<double> parseStringStream(std::stringstream& sstream)
    {
        int columns = 0;

        std::vector<double> ret;
        while(sstream.rdbuf()->in_avail() > 0) // runs as long as we have data in the stream
        {
            std::string d;
            sstream >> d;
            if(d == " " || d.empty())
            {
                continue;
            }
            ret.push_back(std::stod(d));
            columns++;
        }

        ret.push_back(columns); // will be used to checks and see if all the columns are the same
        return ret;
    }

    std::istream& operator>>(std::istream& stream,Matrix& matrix)
    {
        int rows = 0;
        int column = -1;
        std::vector<double> dataVector;
        std::string str;
        std::getline(stream, str);
        std::string firstHalf;
        std::string secondHalf;
        do{
            firstHalf = str.substr(0,str.find_first_of(']')+1);
            secondHalf = str.substr(str.find_first_of(']')+1,str.size());

            if(!firstHalf.starts_with('[') && !firstHalf.starts_with(", ["))
            {
                throw std::invalid_argument("input format not right");
            }


            std::stringstream sstream(firstHalf.substr(firstHalf.find_last_of('[') + 1, firstHalf.find_first_of(']') - firstHalf.find_last_of('[') - 1));
                                                                          //last - first -  1 = the n elements we want
            std::vector<double> vec = parseStringStream(sstream);

            if(column == -1)
            {
                column = vec.at(vec.size() -1);
                
            }
            else if(column != vec.at(vec.size() -1))
            {
                throw std::invalid_argument("input format not right");
            }
            vec.pop_back(); // we can discard the column data now

            dataVector.insert(dataVector.end(),vec.begin(),vec.end());
            str = secondHalf;
            rows++;
        }while((!secondHalf.empty()));

        matrix = Matrix(dataVector,rows,column);

        return stream;
    }

    Matrix::Matrix(const std::vector<double>& data, int rows,  int columns)
        : m_Data(data)
    {
        if(rows <= 0 || columns <= 0)
        {
            throw std::invalid_argument("size of matrix should be more then 1");
        }

        m_Rows = static_cast<unsigned int>(rows);
        m_Columns = static_cast<unsigned int>(columns);

        if(data.size() != rows * columns)
        {
            throw std::invalid_argument("matirx data not corllate to size");
        }
    }

    Matrix::Matrix(const std::vector<double>& data, unsigned int rows,  unsigned int  columns)
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
        if(m_Columns != matrix.m_Columns || m_Rows != matrix.m_Rows)
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
        if(m_Columns != matrix.m_Columns || m_Rows != matrix.m_Rows)
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
        std::for_each(dataVector.begin(),dataVector.end(),[](double& d){d = 0 -d;});
        return Matrix(dataVector,m_Rows,m_Columns);
    }

    Matrix Matrix::operator-(const Matrix& matrix) const
    {
        if(m_Columns != matrix.m_Columns || m_Rows != matrix.m_Rows)
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
        if(m_Columns != matrix.m_Columns || m_Rows != matrix.m_Rows)
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

    Matrix Matrix::operator++(int)
    {
        auto dataVector = m_Data; 
        std::for_each(m_Data.begin(),m_Data.end(),[](double& d){d++;});
        return Matrix(dataVector,m_Rows,m_Columns);
    } 

    Matrix& Matrix::operator--()
    {
        std::for_each(m_Data.begin(),m_Data.end(),[](double& d){d--;});
        return *this;
    }

    Matrix Matrix::operator--(int)
    {
        auto dataVector = m_Data; 
        std::for_each(m_Data.begin(),m_Data.end(),[](double& d){d--;});
        return Matrix(dataVector,m_Rows,m_Columns);
    }

    bool Matrix::operator==(const Matrix& matrix) const
    {
        if(m_Columns != matrix.m_Columns || m_Rows != matrix.m_Rows)
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
        if(m_Columns != matrix.m_Columns || m_Rows != matrix.m_Rows)
        {
            throw std::invalid_argument("Matrix sizes should be the same");
        }
        double sum1 = 0;
        double sum2 = 0;
        std::for_each(m_Data.begin(),m_Data.end(),[&](double d){sum1+=d;});
        std::for_each(matrix.m_Data.begin(),matrix.m_Data.end(),[&](double d){sum2+=d;});

        return sum1 > sum2;
    }

    bool Matrix::operator>=(const Matrix& matrix) const
    {
        if(m_Columns != matrix.m_Columns || m_Rows != matrix.m_Rows)
        {
            throw std::invalid_argument("Matrix sizes should be the same");
        }
        double sum1 = 0;
        double sum2 = 0;
        std::for_each(m_Data.begin(),m_Data.end(),[&](double d){sum1+=d;});
        std::for_each(matrix.m_Data.begin(),matrix.m_Data.end(),[&](double d){sum2+=d;});

        return (*this == matrix) || (sum1 > sum2);
    }

    bool Matrix::operator<(const Matrix& matrix)  const
    {
        if(m_Columns != matrix.m_Columns || m_Rows != matrix.m_Rows)
        {
            throw std::invalid_argument("Matrix sizes should be the same");
        }
        double sum1 = 0;
        double sum2 = 0;
        std::for_each(m_Data.begin(),m_Data.end(),[&](double d){sum1+=d;});
        std::for_each(matrix.m_Data.begin(),matrix.m_Data.end(),[&](double d){sum2+=d;});

        return sum1 < sum2;
    }

    bool Matrix::operator<=(const Matrix& matrix) const
    {
        if(m_Columns != matrix.m_Columns || m_Rows != matrix.m_Rows)
        {
            throw std::invalid_argument("Matrix sizes should be the same");
        }
        double sum1 = 0;
        double sum2 = 0;
        std::for_each(m_Data.begin(),m_Data.end(),[&](double d){sum1+=d;});
        std::for_each(matrix.m_Data.begin(),matrix.m_Data.end(),[&](double d){sum2+=d;});

        return (*this == matrix) || (sum1 <= sum2);
    }

    Matrix operator*(const double scalar,const Matrix& matrix) // not a member function, but it's the place for it now
    {
        return matrix * scalar;
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
                   tempVal += m_Data.at(i * m_Columns + k) * matrix.m_Data.at(k * matrix.m_Columns + j);
               }
               dataVector.push_back(tempVal);
           }
        }
        return Matrix(dataVector,m_Rows,matrix.m_Columns);
    }

    Matrix& Matrix::operator*=(const Matrix& matrix)
    {
        *this = *this * matrix;
        return *this;
    }

} // namespace zich