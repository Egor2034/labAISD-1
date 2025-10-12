#ifndef SET_H
#define SET_H

#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <random>
/*
ДОБАВИТЬ ФУНКЦИЮ SWAP
*/
template<typename T> requires std::equality_comparable<T>
class Set {
public:
    Set() {
        _data(nullptr); 
        _count = 0; 
        _capacity = 0;
    }

    Set(size_t capacity) {
        _count = 0;
        _capacity = capacity;
        _data = new T[_capacity];
    }

    Set(const T* arr, size_t size) {
        _capacity = size;
        _data = new T[size];

        for (size_t i = 0; i < size; i++) {
            if (!contains(arr[i])) { 
                _count++;
                _data[i] = arr[i]; 
            }
        }
    }

    Set(size_t count, T min, T max) requires std::integral<T> {
        if (min > max) std::swap(min, max);

        if (max - min + 1 < count) {
            throw std::invalid_argument("The number of unique elements is less than the required set size");
        }

        if (count == 0) {
            _count = 0;
            _capacity = 0;
            _data = nullptr;
            return;
        }

        std::random_device seed;
        std::mt19937 generator(seed());
        std::uniform_int_distribution distribution(min, max);

        _count = count;
        _capacity = count;
        _data = new T[count];
        
        bool* used = new bool[max - min + 1]();

        for (size_t i = 0; i < count; i++) {
            T number;

            do {
                number = distribution(generator);
            } while (used[number - min]);

            used[number - min] = true;
            _data[i] = number;
        }

        delete[] used;
    }

    Set(size_t count, T min, T max) requires std::floating_point<T> {
        if (min > max) std::swap(min, max);

        if (count == 0) {
            _count = 0;
            _capacity = 0;
            _data = nullptr;
            return;
        }
       
        std::random_device seed;
        std::mt19937 generator(seed());
        std::uniform_real_distribution distribution(min, max);

        _count = count;
        _capacity = count;
        _data = new T[count];
        
        for (size_t i = 0; i < count; i++) {
            _data[i] = distribution(generator);
        }
    }

    Set(const Set<T>& other);
    Set(const Set<T>&& other);
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

    bool contains(const T& el) const {
        for (size_t i = 0; i < _count; i++) {
            if (_data[i] == el) return true;
        }

        return false;
    }

    void add(const T& el);
    void clear();
    size_t get_size() const;
    size_t get_capacity() const;

    //T* begin();
    //const T* begin() const;
    //T* end() const;
    //const T* end() const;
private:
    size_t _count;
    size_t _capacity;
    T* _data;

    inline static const double EPSILON = 1e-6  ;

    friend std::ostream& operator<<(std::ostream& os, const Set<T>& set) {
        for (size_t i = 0; i < set._count; i++) {
            os << set._data[i] << "\n";
        }
        return os;
    }

    friend Set<T> intersection(const Set<T>& first, const Set<T>& second);
};

template <typename T>
void swap(Set<T>& first, Set<T>& second) {}

template <typename T>
void swap(T& first, T& second) {
    T temp = first;
    first = second;
    second = temp;
}

#endif