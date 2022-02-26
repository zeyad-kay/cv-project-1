#ifndef __CVECTOR_HPP__
#define __CVECTOR_HPP__

#include <vector>
#include <numeric>

template <typename T>
class cvector : public std::vector<T>
{
public:
    using std::vector<T>::vector;
    cvector<T> operator+(std::vector<T> const v) const;
    cvector<T> operator+(T const value) const;
    cvector<T> operator-(std::vector<T> const v) const;
    cvector<T> operator-(T const value) const;
    cvector<T> operator*(std::vector<T> const v) const;
    cvector<T> operator*(T const value) const;
    cvector<T> operator/(std::vector<T> const v) const;
    cvector<T> operator/(T const value) const;
    T dot(cvector<T> const v) const;
};

template <typename T>
cvector<T> cvector<T>::operator+(std::vector<T> const v) const
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
cvector<T> cvector<T>::operator+(T const value) const
{
    cvector<T> vect;
    for (auto itr = this->begin(); itr != this->end(); itr++)
    {
        vect.push_back((*itr) + value);
    }
    return vect;
}

template <typename T>
cvector<T> cvector<T>::operator-(std::vector<T> const v) const
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
cvector<T> cvector<T>::operator-(T const value) const
{
    return this->operator+(-value);
}

template <typename T>
cvector<T> cvector<T>::operator*(std::vector<T> const v) const
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
cvector<T> cvector<T>::operator*(T const value) const
{
    cvector<T> vect;
    for (auto itr = this->begin(); itr != this->end(); itr++)
    {
        vect.push_back((*itr) * value);
    }
    return vect;
}

template <typename T>
cvector<T> cvector<T>::operator/(std::vector<T> const v) const
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
cvector<T> cvector<T>::operator/(T const value) const
{
    return this->operator*(1 / value);
}

template <typename T>
T cvector<T>::dot(cvector<T> const v) const
{
    T sum = 0;
    auto res = this->operator*(v);
    return std::accumulate(res.begin(), res.end(), sum);
}

#endif