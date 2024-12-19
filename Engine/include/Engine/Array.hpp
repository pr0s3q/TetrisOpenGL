#pragma once

template <typename T, unsigned int N>
class Array
{
public:

    //---------------------------------------------------------------

    Array() = default;
    ~Array() = default;

    //---------------------------------------------------------------

    T* begin();
    const T& begin() const;

    //---------------------------------------------------------------

    T* end();
    const T& end() const;

    //---------------------------------------------------------------

    T operator[](unsigned int index) const;
    T& operator[](unsigned int index);

    //---------------------------------------------------------------

    [[nodiscard]] unsigned int Size() const;

    //---------------------------------------------------------------

private:

    //---------------------------------------------------------------

    T m_internalArray[N];

    //---------------------------------------------------------------
};

//---------------------------------------------------------------

template <typename T, unsigned int N>
T* Array<T, N>::begin()
{
    return &m_internalArray[0];
}

//---------------------------------------------------------------

template <typename T, unsigned int N>
const T& Array<T, N>::begin() const
{
    return m_internalArray[0];
}

//---------------------------------------------------------------

template <typename T, unsigned int N>
T* Array<T, N>::end()
{
    return &m_internalArray[N];
}

//---------------------------------------------------------------

template <typename T, unsigned int N>
const T& Array<T, N>::end() const
{
    return m_internalArray[N];
}

//---------------------------------------------------------------

template <typename T, unsigned int N>
T Array<T, N>::operator[](unsigned int index) const
{
    if (index < N)
        return m_internalArray[index];

    return T();
}

//---------------------------------------------------------------

template <typename T, unsigned int N>
T& Array<T, N>::operator[](unsigned int index)
{
    if (index < N)
        return m_internalArray[index];

    return m_internalArray[0];
}

//---------------------------------------------------------------

template <typename T, unsigned int N>
unsigned int Array<T, N>::Size() const
{
    return N;
}

//---------------------------------------------------------------
