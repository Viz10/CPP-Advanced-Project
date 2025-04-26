#pragma once
#include <iostream>

namespace myStd {

    template<typename T>
    class Dummy {
    public:
        Dummy() { data = 0; }
        Dummy(T data) : data{ data } {}

        void show();

        template<typename U>
        void showSum(U other) {
            std::cout << (data + other);
        }

        T data;
    };

    /// full specializations aren`t inline by default
    template<typename T>
    inline void Dummy<T>::show() {
        std::cout << data;
    }

    template<>
    inline void Dummy<double>::show() {
        std::cout << data << " is a double";
    }

    template<>
    template<>
    inline void Dummy<int>::showSum(int other) {
        std::cout << data << " " << other << " all are int";
    }
    /// ^^ inexistent in Java
    /// however not a good idea to specialize templated methods in C++ rather overload them
}
