#pragma once

#include <utility>
#include <iostream>
#include <fstream>
#include <string>
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

namespace mySTL {

	template<typename First, typename Second>
	class Pair {

	public:

		Pair() = default;	

		template<typename T, typename U> /// universal reference constructor
		Pair(T&& first, U&& second) :first{ static_cast<First>(std::forward<T>(first)) }, second{ static_cast<Second>(std::forward<U>(second)) } {}

		template<typename T, typename U> 
		Pair& operator=(const Pair<T,U>& other) {
		
			if constexpr (std::is_same_v<First, T> && std::is_same_v<Second, U>) { /// compile time template check
				if (this == &other) { /// makes sense only when T and U match First and Second
					return *this;  
				}
			}

			first = static_cast<First>(other.first);
			second = static_cast<Second>(other.second);
			return *this;
		} /// non templated copy asg op may be used if the 2 Pairs must have exactly the same tamplates

		First first;
		Second second;
	};

	//////////////////////////

	template<typename T>
	class Dummy {

	public:

		Dummy() = default;
		void display(T data);
		
	};

	template<typename T> /// normal definition
	void mySTL::Dummy<T>::display(T data) {
		std::cout << data;
	}

	template<> ///class template full-specialization for class method
	void Dummy<int>::display(int data) {
		std::cout << data << " is an int";
	}

	///////////////////////////

}