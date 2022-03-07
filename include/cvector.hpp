#ifndef __CVECTOR_HPP__
#define __CVECTOR_HPP__

#include <vector>
#include <numeric>
#include <iostream>
template <typename T>
class cvector : public std::vector<T>
{
public:
    using std::vector<T>::vector;
    cvector<T> operator+(const cvector<T> &v) const;
    cvector<T> operator+(const T value) const;
    cvector<T> operator-(const cvector<T> &v) const;
    cvector<T> operator-(const T value) const;
    cvector<T> operator*(const cvector<T> &v) const;
    cvector<T> operator*(const T value) const;
    cvector<T> operator/(const cvector<T> &v) const;
    cvector<T> operator/(const T value) const;
    T dot(const cvector<T> &v) const;
    cvector<T> range(const size_t start_row, const size_t end_row, const size_t start_col, const size_t end_col) const;
    int mean(void) const;
    int median(void);

    friend std::ostream &operator<<(std::ostream &os, const cvector<T> &v)
    {
        os << "{ ";
        for (auto itr = v.begin(); itr != v.end(); itr++)
        {
            os << *itr << " ";
        }
        os << "}";
        return os;
    }
};

template <typename T>
cvector<T> cvector<T>::operator+(const cvector<T> &v) const
{
    if (this->size() != v.size())
    {
        throw "Vectors must have the same size";
    }
    cvector<T> vect;
    for (size_t i = 0; i < this->size(); i++)
    {
        vect.push_back(v[i] + this->operator[](i));
    }
    return vect;
}

template <typename T>
cvector<T> cvector<T>::operator+(const T value) const
{
    cvector<T> vect;
    for (auto itr = this->begin(); itr != this->end(); itr++)
    {
        vect.push_back((*itr) + value);
    }
    return vect;
}

template <typename T>
cvector<T> cvector<T>::operator-(const cvector<T> &v) const
{
    if (this->size() != v.size())
    {
        throw "Vectors must have the same size";
    }
    cvector<T> vect;
    for (size_t i = 0; i < this->size(); i++)
    {
        vect.push_back(v[i] - this->operator[](i));
    }
    return vect;
}

template <typename T>
cvector<T> cvector<T>::operator-(const T value) const
{
    return this->operator+(-value);
}

template <typename T>
cvector<T> cvector<T>::operator*(const cvector<T> &v) const
{
    if (this->size() != v.size())
    {
        throw "Vectors must have the same size";
    }
    cvector<T> vect;
    for (size_t i = 0; i < this->size(); i++)
    {
        vect.push_back(v[i] * this->operator[](i));
    }
    return vect;
}

template <typename T>
cvector<T> cvector<T>::operator*(const T value) const
{
    cvector<T> vect;
    for (auto itr = this->begin(); itr != this->end(); itr++)
    {
        vect.push_back((*itr) * value);
    }
    return vect;
}

template <typename T>
cvector<T> cvector<T>::operator/(const cvector<T> &v) const
{
    if (this->size() != v.size())
    {
        throw "Vectors must have the same size";
    }
    cvector<T> vect;
    for (size_t i = 0; i < this->size(); i++)
    {
        vect.push_back(v[i] / this->operator[](i));
    }
    return vect;
}

template <typename T>
cvector<T> cvector<T>::operator/(const T value) const
{
    return this->operator*(1 / value);
}

template <typename T>
T cvector<T>::dot(const cvector<T> &v) const
{
    if (this->size() != v.size())
    {
        throw "Vectors must have the same size";
    }
    T sum = 0;
    for (size_t i = 0; i < this->size(); i++)
    {
        sum += this->operator[](i) * v[i];
    }
    return sum;
}

template <typename T>
cvector<T> cvector<T>::range(const size_t start_row, const size_t end_row, const size_t start_col, const size_t end_col) const
{
    cvector<T> v;
    for (size_t i = start_row; i < end_row; i++)
    {
        T row;
        for (size_t j = start_col; j < end_col; j++)
        {
            row.push_back(this->operator[](i)[j]);
        }
        v.push_back(row);
    }
    return v;
}

template <typename T>
int cvector<T>::mean(void) const
{
    double mean_value = 0 ;
    for (size_t i = 0; i < this->size(); i++)
    {
            mean_value += this->operator[](i);
    }
    mean_value = (mean_value/this->size());
    return (int) mean_value;
}

template <typename T> 
int cvector<T>::median(void)
{   int median;
    size_t n = this->size() / 2;
    std::nth_element(this->begin(), this->begin()+n, this->end());
    median = this->operator[](n);
    return median;
}

#endif