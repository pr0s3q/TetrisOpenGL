#pragma once

template <typename T, unsigned int N>
class Stack
{
public:

    //---------------------------------------------------------------

    Stack() = default;
    ~Stack() = default;

    //---------------------------------------------------------------

    [[nodiscard]] unsigned int ElementCount() const;

    //---------------------------------------------------------------

    void Push(const T& item);

    //---------------------------------------------------------------

    T Peek() const;

    //---------------------------------------------------------------

    T& Pop();

    //---------------------------------------------------------------

private:

    //---------------------------------------------------------------

    unsigned int m_elementCount = 0;
    T m_internalStack[N];

    //---------------------------------------------------------------
};

//---------------------------------------------------------------

template <typename T, unsigned int N>
unsigned int Stack<T, N>::ElementCount() const
{
    return m_elementCount;
}

//---------------------------------------------------------------

template <typename T, unsigned int N>
void Stack<T, N>::Push(const T& item)
{
    if (m_elementCount == N)
        return;

    m_internalStack[m_elementCount] = item;
    m_elementCount++;
}

//---------------------------------------------------------------

template <typename T, unsigned int N>
T Stack<T, N>::Peek() const
{
    if (m_elementCount == 0)
        return m_internalStack[0];

    return m_internalStack[m_elementCount - 1];
}

//---------------------------------------------------------------

template <typename T, unsigned int N>
T& Stack<T, N>::Pop()
{
    if (m_elementCount == 0)
        return m_internalStack[0];

    m_elementCount--;
    return m_internalStack[m_elementCount];
}

//---------------------------------------------------------------