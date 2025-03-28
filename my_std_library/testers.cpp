#include "testers.h"

std::ifstream fin("data.in");

template<typename Args> /// universal reference
void print(Args&& arg) {
    std::cout << "universal " << arg << "\n";
}

template<typename Args> /// lvalue reference
void print(Args& arg) {
    std::cout << "lvalue " << arg << "\n";
}

template<typename...Args>
void print_tuple(Args&&...args) {
    //(...,(cout<<args<<" "));
    (..., print(std::forward<Args>(args)));
    std::cout << "\nsize: ";
    std::cout << sizeof...(Args);
}

void testTupleMethods() {

    int a = 0;
    print_tuple(1, 2, std::string("aaa"), false, a);
    //auto tuple = std::make_tuple(1, 1, 1, 1);
    //cout<<std::tuple_size<decltype(tuple)>::value;
}

/////////////////////////////////////

void testSingleton() {
    using Singleton::MySingleton;

    MySingleton::init();
    MySingleton::init();
    MySingleton::init();
    MySingleton::init();
    auto& instance1 = MySingleton::get();
    instance1.display();
    MySingleton::destroy(); /// no instance exists

    auto& instance2 = MySingleton::get();
    instance2.get().get().display();
    MySingleton::get().get().display();
    MySingleton::destroy();

    std::cout << "aaa\n";
}

/////////////////////////////////////

template<typename T> /// normal definition
void mySTL::Dummy<T>::show() {
    std::cout << data;
}

template<> ///class template full-specialization for class method
void mySTL::Dummy<double>::show() {
    std::cout << data << " is a double";
}

template<> /// for class template
template<> /// for func template
void mySTL::Dummy<int>::showSum(int other) {
    std::cout << data <<" " << other << " all are int";
}

void testPair() {

    std::string line;
    while (getline(fin, line)) {
        std::cout << line << "\n";
    }
    const char* aux = line.c_str();
    std::cout << aux;

    mySTL::Pair<int, int> pair1(1, 2);
    mySTL::Pair<double, int> pair2(2.3, 1);

    pair1 = pair2;

    std::cout << pair1.first << " " << pair1.second;
    std::cout << "\n";

    mySTL::Dummy<double> dummy(11.4);
    dummy.showSum(22);

}