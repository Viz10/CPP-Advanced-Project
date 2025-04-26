#pragma once
#include <iostream>
#include <memory>

namespace Singleton{

	class MySingleton {

	public:

		void display();

		static MySingleton& get(); /// one single get() through the execution , we dont have constructor
		static void destroy();
		static void init();

		MySingleton(const MySingleton& other) = delete;
		MySingleton(MySingleton&& other) = delete;
		MySingleton& operator=(const MySingleton& other) = delete;
		MySingleton& operator=(MySingleton&& other) = delete;

	private:
		MySingleton();
		~MySingleton();

		static inline MySingleton* s_Instance=nullptr; /// has the lifetime of the program as other static stuff
		                                              /// singleton design due to the static class instance and static methods
		int a,b;
		int* vec;
	};
}


