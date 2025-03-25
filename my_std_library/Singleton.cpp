#include "Singleton.h"

namespace Singleton {

	MySingleton::MySingleton() :a{ 0 }, b{ 0 }, vec{ new int{0} } {
		std::cout << "Constructed\n";
	}
	
	/// for lazy instantiation : static instance or static ptr to 1 instance (requires explicit destructor , instance wont be freed
	// after the static ptr terminates with the program => memoey leak from instance+it`s members)
	/*
	MySingleton& MySingleton::get() { 
		//static MySingleton instance;
		static MySingleton* instance=new MySingleton; /// as static , specific for this function
		return *instance;
	}
	MySingleton& MySingleton::get() {
	    static std::unique_ptr<MySingleton> instance = std::make_unique<MySingleton>(); //same as static MySingleton instance
		return *instance;
	}
	void MySingleton::destroy() {
	   delete &get(); /// delete instance
	}
	*/
	MySingleton& MySingleton::get() {
		if (s_Instance == nullptr) {
			init();
		}
		return *s_Instance;
	}

	void MySingleton::init() {
		if (s_Instance == nullptr)
			s_Instance = new MySingleton;
	}
	void  MySingleton::display() {
		std::cout << a << " " << b << " " << *vec << "\n";
	}
	void MySingleton::destroy() {
		delete s_Instance; 
		s_Instance = nullptr;
	}

	MySingleton::~MySingleton() {
		delete vec;
		vec = nullptr;
		std::cout << "Destroied\n";
	}
}