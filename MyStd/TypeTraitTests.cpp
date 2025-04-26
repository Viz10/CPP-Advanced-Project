#include "testers.h"

template <typename T>
void func(const T& a) {
	// T is deduced as the base type, like int
}
template <>
void func<int>(const int& a) { // Explicit specialization
	std::cout << "Specialized for int&\n";
}

void func(const int& a) { // prefered
	std::cout << "Overload for int&\n";
}

////////////

template<typename T>
void ptr_print(T ptr) {
	std::cout << *ptr << " ";
}

template<typename T>
void ptr_print(T* ptr) { // chooses this one the compiler expects a pointer to be passed
	std::cout << *ptr << " from * variant\n";
}


///////// 

template<typename T>
void boolean(T&& var) {
	if (std::is_same_v<decltype(var),std::string&&>) {
		std::cout << "decl\n";
	}
	if (std::is_lvalue_reference<T>::value) {
		std::cout << "lval T\n";
	}
	using newtype = std::remove_reference_t<T>;
	if (std::is_lvalue_reference<newtype>::value) {
		std::cout << "lval newtype\n";
	}
	if (std::is_same_v<newtype, std::string>) {
		std::cout << "rval int\n";
	}

}

void aaa(int&) { std::cout << "L"; }
void aaa(int&&){ std::cout << "R"; }

template<typename T>
void boolean2(T&& var) {

	using newtype = std::remove_reference_t<T>;

	if (std::is_lvalue_reference<newtype>::value) {
		std::cout << "removed &/&& T\n";
	}
	if (std::is_rvalue_reference<newtype>::value) {
		std::cout << "removed &/&& T\n";
	}

	if (std::is_lvalue_reference<T>::value) {
		std::cout << "lval T\n";
	}
	
	if (std::is_rvalue_reference<T>::value) {
		std::cout << "rval T\n";
	}
	if (std::is_same_v<decltype(var), int&&>) {
		std::cout << "rval int\n";
	}
	if (std::is_same_v<decltype(var), int&>) {
		std::cout << "lval int\n";
	}
	if (std::is_same_v<decltype(var),const int&>) {
		std::cout << "const lval int\n";
	}
	aaa(var);// Named rvalue references are always lvalues when used in expressions.
}



void testTypeTraits() {
	int a = 325;
	const int b = 5;

	boolean2<int>(10);
	//boolean2(b);
	//std::cout << "\n";
	//boolean2(a);

	//int* aa = new int{ 55 };
	//std::cout << "\n";
	//ptr_print(aa);
	
	//func(b);

	//delete aa;
}