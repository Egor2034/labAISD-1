#ifndef SET_H
#define SET_H

#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <random>

template<typename T> requires std::equality_comparable<T>
class Set {
public:
    Set() : _data(nullptr), _count(0), _capacity(0) {}

    Set(size_t capacity) {
        _count = 0;
        _capacity = capacity;
        _data = new T[_capacity];
    }

    Set(const T* arr, size_t size) : _capacity(size), _data(new T[size]) {
        for (size_t i = 0; i < size; i++) {
            add(arr[i]);
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

    Set(const Set<T>& other) {
        _count = other._count;
        _capacity = other._capacity;
        _data = new T[_capacity];

        for (size_t i = 0; i < _count; i++) {
            _data[i] = other._data[i];
        }
    }

    ~Set() { clear(); }

    const T& operator[](size_t index) const {
        if (index >= _count) { throw std::out_of_range("Out of range"); }
        return _data[index];
    }

    Set<T>& operator=(const Set<T>& other) {
        if (*this != other) {
            delete[] _data;
            _data = new T[other._count];
            _count = other._count;
            _capacity = other._capacity;

            for (size_t i = 0; i < _count; i++) {
                _data[i] = other._data[i];
            }
        }

        return *this;
    }

    Set<T> operator+(const Set<T>& other) const { 
        Set<T> temp(*this);

        for (const T& el : other) { temp.add(el); }

        return temp;
    }

    Set<T>& operator+=(const Set<T>& other) {   
        for (const T& el : other) { add(el); }

        return *this;
    }

    Set<T> operator-(const Set<T>& other) const {
        Set<T> temp(*this);

        for (const T& el : other) { 
            if (temp._count == 0) { break; }
            temp.remove(el); 
        }

        return temp;
    }

    Set<T>& operator-=(const Set<T>& other) {
        for (const T& el : other) {
            if (_count == 0) { break; }
            remove(el);
        }

        return *this;
    }

    bool operator==(const Set<T>& other) const {
        if (_count != other.get_count()) { return false; }
        
        for (const T& el : *this) {
            if (!other.contains(el)) { return false; }
        }

        return true;
    }

    bool operator!=(const Set<T>& other) const {
        return !(*this == other);
    }

    /*Операторы для работы с элементом типа T*/
    Set<T> operator+(const T& el) const {
        Set<T> temp(*this);
        temp.add(el);
        return temp;
    }

    Set<T>& operator+=(const T& el) {
        add(el);
        return *this;
    }

    Set<T> operator-(const T& el) const {
        Set<T> temp(*this);
        temp.remove(el);
        return temp;
    }

    Set<T>& operator-=(const T& el) {
        remove(el);
        return *this;
    }

    bool contains(const T& el) const {
        for (size_t i = 0; i < _count; i++) {
            if (_data[i] == el) { return true; }
        }

        return false;
    }

    bool contains(const T& el) const requires std::floating_point<T> {
        for (size_t i = 0; i < _count; i++) {
            if ((_data[i] - el) <= EPSILON) { return true; }
        }

        return false;
    }

    void add(const T& el) {
        if (contains(el)) { return; }

        if (_count + 1 > _capacity) {
            reserve(_capacity * 2 + 1);
        }

        _data[_count++] = el;
    }

    void remove(const T& el) {
        if (!contains(el)) { return; }

        for (size_t i = 0; i < _count; i++) {
            if (_data[i] == el) {
                for (size_t j = i; j < _count - 1; j++) {
                    _data[j] = _data[j + 1];
                }
                _count--;
                break;
            }
        }
    }

    void reserve(size_t new_capacity) {
        if (new_capacity <= _capacity) return;

        T* new_data = new T[new_capacity];

        for (size_t i = 0; i < _count; i++) {
            new_data[i] = _data[i];
        }

        delete[] _data;
        _capacity = new_capacity;
        _data = new_data;
    }

    void clear() {
        delete[] _data;
        _data = nullptr;
        _count = 0;
    }

    size_t get_count() const { return _count; }
    size_t get_capacity() const { return _capacity; }

    T* begin() { return _data; }
    T* end() { return (_data + _count); }
    const T* begin() const { return _data; }
    const T* end() const { return (_data + _count); }
private:
    size_t _count;
    size_t _capacity;
    T* _data;

    inline static const double EPSILON = 1e-6;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Set<T>& set) {
    for (const T& val : set) {
        os << val << "\n";
    }
    return os;
}

template <typename T>
Set<T> intersection(const Set<T>& first, const Set<T>& second) {
    if (first.get_count() == 0 || second.get_count() == 0) { return Set<T>(); }

    Set<T> result;

    for (const T& el : first) {
        if (second.contains(el)) { result.add(el); }
    }

    return result;
}

template <typename T>
void swap(Set<T>& first, Set<T>& second) {
    Set<T> temp(first);
    first = second;
    second = temp;
}

template <typename T>
void swap(T& first, T& second) {
    T temp = first;
    first = second;
    second = temp;
}

#endif