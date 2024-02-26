#pragma once

#include <iostream>
#include <initializer_list>

template <typename T>
class TVector {
public:
    TVector() : Size(0), Capacity(1)
    {
        Data = new T[1];
    }

    TVector(const std::initializer_list<T> & data) noexcept
    {
        Size = data.size();
        Capacity = data.size();
        Data = new T[data.size()];

        size_t i = 0;
        for (auto &el : data) {
            Data[i++] = el;
        }  
    }

    TVector(const TVector<T> & other) noexcept
    {
        Data = new T[other.Capacity];

        for (size_t i = 0; i < other.Size; ++i) {
            Data[i] = other.Data[i];
        }

        Size = other.Size;
        Capacity = other.Capacity;
    }

    TVector(TVector<T> && other) noexcept
    {
        Swap(Size, other.Size);
        Swap(Capacity, other.Capacity);
        Swap(Data, other.Data);
    }

    ~TVector() noexcept
    {
        Size = 0;
        Capacity = 0;
        delete[] Data;
        Data = nullptr;
    }

    T & operator[](size_t index) const
    {
        if (index > Size) {
            throw std::range_error("Error! operator[]: Invalid index");
        }

        return Data[index];
    }

    bool Empty() const 
    {
        return (Size == 0);
    }

    T* begin() 
    {
        return Data;
    }

    T* end()
    {
        return Data + Size;
    }

    const T* begin() const
    {
        return Data;
    }

    const T* end() const
    {
        return Data + Size;
    }

    void PushBack(const T & el)
    {
        const size_t MEMORY_SIZE_MULTIPLIER = 2;
        if (Size >= Capacity) {
            Capacity *= MEMORY_SIZE_MULTIPLIER;

            T* newData = new T[Capacity];

            for (size_t i = 0; i < Size; ++i) {
                newData[i] = Data[i];
            }

            delete[] Data;
            Data = newData;
        }

        Data[Size++] = el;
    }

    TVector<T> & operator=(const TVector<T> & other)
    {
        delete[] Data;
        
        Data = new T[other.Capacity];

        for (size_t i = 0; i < other.Size; ++i) {
            Data[i] = other.Data[i];
        }

        Size = other.Size;
        Capacity = other.Capacity;

        return *this;
    }

    void Clear() noexcept
    {
        delete[] Data;
        Size = 0;
        Data = new T[Capacity];
    }

    size_t GetSize() const
    {
        return Size;
    }

    void ShrinkToFit()
    {
        if (Size < Capacity) {
            Capacity = Size;
            T* newData = new T[Size];
            std::copy(begin(), end(), newData);
            delete[] Data;
            Data = newData;
        }
    }

private:
    void Swap(T & a, T & b) noexcept
    {
        T tmp = std::move(a);
        a = std::move(b);
        b = std::move(tmp);
    }

private:
    size_t Size = 0;
    size_t Capacity = 0;
    T* Data;
};

struct TData {
    TVector<char> Data;
    uint64_t Days;
};  

struct TSortType {
    TData Key;
    uint64_t Value;
};

// TVector<TSortType> RadixSort(TVector<TSortType> vec, TSortType maxKey)
// {

// }