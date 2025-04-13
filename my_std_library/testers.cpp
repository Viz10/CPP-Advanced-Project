#include "testers.h"
#include <functional>
#include <concepts>
#include <array>

std::ifstream fin("data.in");

namespace MyTupleFunctions {

    template<typename... Ts>
    struct my_tuple_size {};

    template<typename... Ts>
    struct my_tuple_size<std::tuple<Ts...>> {
        static constexpr std::size_t value = sizeof...(Ts);
    };


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
        
        (..., print(std::forward<Args>(args)));
        std::cout << "pack size: ";
        std::cout << sizeof...(Args);
        //(...,(cout<<args<<" "));
    }
    
    ////////////////////////////////////////////////////////////////////////////
   
    template<typename Tuple,size_t... Ind>
    void printTupleHelper(const Tuple&tuple,std::index_sequence<Ind...> index) {
        std::cout << "tuple elements: ";
        (..., (std::cout << std::get<Ind>(tuple) << " "));
    }


    template<typename...Args>
    void printTuple(const std::tuple<Args...>&tuple) {
        constexpr size_t size = sizeof...(Args);
         auto index_list = std::make_index_sequence<size>();
        printTupleHelper(tuple,index_list);
    }

    ////////////////////////////////////////////////////////////////////////////

    template<typename Function, typename Tuple, size_t... Ind>
    void myApplyHelper(Function&& f, Tuple&& tuple, std::index_sequence<Ind...>) {
        std::forward<Function>(f)(std::get<Ind>( std::forward<Tuple>(tuple))... );
    }

    // this solution passes the tuple as an lvalue and will make copies along the way , ...Args are needed for calc the size and specify the types for the tuple
    // its safer , no other kind of type can be sent to this function like an int or anything , however it makes it rigid
    template<typename Function, typename...Args>
    void myApply1(Function &&f, const std::tuple<Args...>& tuple) {
        constexpr size_t size = sizeof...(Args);
        auto index_list = std::make_index_sequence<size>(); /// 0 1 2 3 ...
        myApplyHelper(std::forward<Function>(f), tuple, index_list);
    }

   
   // this passes the tuple as it is , it forwards it through , ...Args is not needed as we can deduce the size by tuple_size
   // more generic : allows also pair and Tuple-likes objects to be passed using the concept to the template , not allowing compilation if none of these types passed
    template<typename T>
    concept TupleType = requires { typename std::tuple_size<std::remove_reference_t<T>>::type; };

    template<typename Function, TupleType Tuple>
    void myApply2(Function&& f, Tuple&& tuple) {
        constexpr size_t size = std::tuple_size_v<std::remove_reference_t<Tuple>>; /// tuple_size_v works with base types like std::tuple<int,int>, not references => must strip the reference
        auto index_list = std::make_index_sequence<size>{};
        myApplyHelper(std::forward<Function>(f), std::forward<Tuple>(tuple), index_list);
    } 
    
    
    /// std::remove_reference does not touch the reference added by the parameter itself—it only deals with the deduced type of T like std::tuple<int,int>& (if lval passed to univ ref).
    /// usind forward to avoid coppies especially for the tuple
}

void testTupleMethods() {

        int a = 101;

        auto lambda_for_print = [](auto&&... args) {  (..., MyTupleFunctions::print(std::forward<decltype(args)>(args))); }; ///as using a generic lambda here doesnt allow in this scope templating , auto must be used
                                                                                                ///and as for forward to know the type , decltype fetches the underlying type of the current element
        auto tuple = std::make_tuple(1, 2, std::string("aaa"), false, a);
        auto tuple2 = tuple;
        std::array<int, 5> arr= {1,2,3,4,5} ;
       
        
        MyTupleFunctions::myApply1(lambda_for_print, tuple); // lval
        std::cout << "\n";
        MyTupleFunctions::myApply2(lambda_for_print, std::pair(3,43)); /// doesnt work with apply1
        std::cout << "\n";
        MyTupleFunctions::myApply2(lambda_for_print, arr);
        std::cout << "\n";
        MyTupleFunctions::myApply2(lambda_for_print, std::move(tuple)); /// rval
        std::cout << "\n";
        MyTupleFunctions::printTuple(tuple2);
        std::cout << "\n\n";
        MyTupleFunctions::print_data(1, 2, std::string("aaa"), false, a);
        std::cout << "\n";
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

    /*
    std::string line;
    while (getline(fin, line)) {
        std::cout << line << "\n";
    }
    const char* aux = line.c_str();
    std::cout << aux;

    mySTL::Pair<int, int> a(1, 2);
    mySTL::Pair<int, int> b(3, 4333);
    a = b;
    std::cout << "\n";

    std::cout << a.first << " " << a.second;
    std::cout << "\n";

    mySTL::Dummy dummy(11);
    dummy.showSum(11);
    dummy.show();
    */

    mySTL::Pair<std::string, int*> a("aaaa", new int{2});
    //mySTL::Pair b(std::move(a));
    mySTL::Pair b(a);

    //a = b;

    std::cout << a.first << " " << *a.second << "\n";
    std::cout << b.first << " " << *b.second << " ";

    delete a.second;
  

}