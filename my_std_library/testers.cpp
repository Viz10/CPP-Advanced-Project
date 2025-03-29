#include "testers.h"
#include <functional>
std::ifstream fin("data.in");

namespace MyTupleFunctions {

    template<typename Args> /// universal reference
    void print(Args&& arg) {
        std::cout << "universal " << arg << "\n";
    }

    template<typename Args> /// lvalue reference
    void print(Args& arg) {
        std::cout << "lvalue " << arg << "\n";
    }

    template<typename...Args>
    void print_data(Args&&...args) {
        //(...,(cout<<args<<" "));
        (..., print(std::forward<Args>(args)));
        std::cout << "\nsize: ";
        std::cout << sizeof...(Args);
    }
    
    ////////////////////////////////////////////////////////////////////////////
   
    template<typename Tuple,size_t... Ind>
    void printTupleHelper(Tuple&&tuple,std::index_sequence<Ind...> index) {
        (..., (std::cout << std::get<Ind>(std::forward<Tuple>(tuple)) << " "));
    }


    template<typename...Args>
    void printTuple(const std::tuple<Args...>&tuple) {
        constexpr size_t size = sizeof...(Args);
         auto index_list = std::make_index_sequence<size>();
        printTupleHelper(tuple,index_list);
    }

    ////////////////////////////////////////////////////////////////////////////

    /* this passes the tuple as an lvalue and will make copies along the way , ...Args are needed for calc the size
    template<typename Function,typename...Args>
    void myApply(Function f, const std::tuple<Args...>& tuple) {
        constexpr size_t size = sizeof...(Args);
        auto index_list = std::make_index_sequence<size>();
        myApplyHelper(f,tuple, index_list);
    }
    */

    template<typename Function, typename Tuple, size_t... Ind>
    void myApplyHelper(Function&& f, Tuple&& tuple, std::index_sequence<Ind...>) {
        std::forward<Function>(f)(std::get<Ind>( std::forward<Tuple>(tuple))... );
    }

   // this passes the tuple as forwarded, ...Args is not needed as we can deduce the size by tuple_size
    template<typename Function, typename Tuple>
    void myApply(Function&& f, Tuple&& tuple) {
        constexpr size_t size = std::tuple_size_v<std::remove_reference_t<Tuple>>; /// tuple_size_v works with base types like std::tuple<int,int>, not references => must strip the reference
        auto index_list = std::make_index_sequence<size>{};
        myApplyHelper(std::forward<Function>(f), std::forward<Tuple>(tuple), index_list);
    }

    /// usind forward to avoid coppies especially for the tuple
}

    void testTupleMethods() {

        using namespace MyTupleFunctions;

        int a = 101;

        auto lambda = [](auto&&... args) {  (..., print(std::forward<decltype(args)>(args))); }; ///as using a generic lambda here doesnt allow in this scope templating , auto must be used
        auto tuple = std::make_tuple(1, 2, std::string("aaa"), false, a);                        ///and as for forward to know the type , decltype fetches the underlying type of the current element
        
        myApply(lambda, std::move(tuple));
        //myApply(lambda, std::move(tuple)); /// will use the lvalue as std get extracts them from a lvalue tuple , must use std move for rvalue
        

        //printTuple<int,bool,const char*,int>(tuple);
        //printTuple(tuple);
        //print_data(1, 2, std::string("aaa"), false, a);
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

    mySTL::Dummy dummy(11);
    dummy.show();

}