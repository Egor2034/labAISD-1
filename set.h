#ifndef SET_H
#define SET_H

#include <iostream>
/*
ДОБАВИТЬ ФУНКЦИЮ SWAP
*/
template<typename T> requires std::equality_comparable<T>
class Set {
public:
    Set();
    Set(size_t size);
    Set(const T* el);
    Set(int count, int min, int max) requires std::integral<T> || std::floating_point<T>;

    Set(const Set& other);
    Set(const Set&& other);
    ~Set() { delete[] _data; }

    Set<T>& operator=(const Set<T>& other);

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    Set<T> operator+(const Set<T>& other) const;
    Set<T>& operator+=(const Set<T>& other);
    Set<T> operator-(const Set<T>& other) const;
    Set<T>& operator-=(const Set<T>& other);
    
    /*Операторы для работы с элементом типа T*/
    Set<T> operator+(const T& el) const;
    Set<T>& operator+=(const T& el);
    Set<T> operator-(const T& el) const;
    Set<T>& operator-=(const T& el);

    bool operator==(const Set<T>& other) const;
    bool operator!=(const Set<T>& other) const;

    bool contains(const T& el) const;
    void add(const T& el);
    void clear();
    //void sort();
    size_t get_size() const;
    size_t get_capacity() const;
    
    T* begin();
    const T* begin() const;
    T* end() const;
    const T* end() const;
private:
    size_t _size;
    size_t _capacity;
    T* _data;

    const float EPSILON = 1e-6f;
    friend std::ostream& operator<<(std::ostream& os, const Set<T>& set);
    friend Set<T> intersection(const Set<T> first, const Set<T> second);
};

template<typename T>
void swap(Set<T> first, Set<T> second) {}

#endif