#include "my_container.hpp"

#include <iostream>

template<typename T, std::size_t N>
My_container<T, N>::My_container() :
    _data(nullptr),
    _size(0),
    _capacity(0)
{
}

template<typename T, std::size_t N>
My_container<T, N>::~My_container()
{
    _deallocate();
}

template<typename T, std::size_t N>
typename My_container<T, N>::size_type size()
{
    return N;
}

template<typename T, std::size_t N>
constexpr bool My_container<T, N>::empty()
{
    return size() == 0;
}

template<typename T, std::size_t N>
typename My_container<T, N>::reference My_container<T, N>::at(size_type i)
{
    if(i > _size)
    {
        throw std::out_of_range();
    }
    return _data[i];
}

template<typename T, std::size_t N>
typename My_container<T, N>::reference My_container<T, N>::operator[](size_type i)
{
    return _data[i];
}

template<typename T, std::size_t N>
typename My_container<T, N>::const_reference My_container<T, N>::operator[](size_type i) const
{
    return _data[i];
}

template<typename T, std::size_t N>
typename My_container<T, N>::iterator My_container<T, N>::begin()
{
    return (_size == 0 ? end() : &_data[0]);
}

template<typename T, std::size_t N>
typename My_container<T, N>::iterator My_container<T, N>::end()
{
    return (_sizeBuf == 0 ? nullptr : &_data[_size]);
}

template<typename T, std::size_t N>
void My_container<T, N>::push_back(const value_type& value)
{
    if (_size == 0)
    {
        _allocate(1);
        _sizeBuf = 1;
    }
    else if (_size == _sizeBuf)
    {
        _allocate(_sizeBuf * 2);
        _sizeBuf *= 2;
    }

    _data[_size++] = value;
}

template<typename T, std::size_t N>
void My_container<T, N>::_allocate(size_type count)
{
    std::size_t allocSize = count * sizeof(value_type);
    _data = (value_type*)realloc(_data, allocSize);

    if(!_data) 
    {
        throw std::bad_alloc();
    }
}

template<typename T, std::size_t N>
void My_container<T, N>::_deallocate()
{
    free(_data);
}

int main()
{
    int count = 10;
    My_container<int, 10> ok;

    for (size_t i = 0; i < count; ++i)
    {
        ok.push_back(i);
    }

    ok.push_back(1337);

    for (int& it : ok)
    {
        std::cout << it << std::endl;
    }

    std::cout << ok[4] << std::endl;

}