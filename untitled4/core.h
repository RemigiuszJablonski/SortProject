// core.h - Zastępuje podstawowe komponenty STL
#ifndef CORE_H
#define CORE_H

#define MAX_INT 2147483647

// Zastępuje std::pair
template<typename T1, typename T2>
struct Pair {
    T1 first;
    T2 second;
    Pair(T1 f, T2 s) : first(f), second(s) {}
};

// Prosta dynamiczna tablica (zastępuje std::vector)
template<typename T>
class Vector {
    T* data;
    int _size;
    int _capacity;

    void resize() {
        _capacity = _capacity ? _capacity * 2 : 1;
        T* new_data = new T[_capacity];
        for (int i = 0; i < _size; ++i) new_data[i] = data[i];
        delete[] data;
        data = new_data;
    }

public:
    Vector() : data(nullptr), _size(0), _capacity(0) {}
    ~Vector() { delete[] data; }

    void push_back(const T& value) {
        if (_size >= _capacity) resize();
        data[_size++] = value;
    }

    T& operator[](int index) { return data[index]; }
    int size() const { return _size; }
    bool empty() const { return _size == 0; }
};

#endif