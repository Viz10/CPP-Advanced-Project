#pragma once
#include <utility>
#include <iostream>

namespace myStd {

	template<typename First, typename Second>
	class Pair {

	public:
 
		//template<typename T, typename U, typename = std::enable_if_t<std::is_constructible_v<First, T&&> && std::is_constructible_v<Second, U&&>>>
		/// check if the type can be constructed using Args... ,here the types are T&&,U&& because after reference collapsing T and U can be with
		/// or without & and there must check the constr if accept any of the types ,also allows casts
		
		template<typename T, typename U> requires std::is_constructible_v<First, T&&> && std::is_constructible_v<Second, U&&>
		Pair(T&& first, U&& second) : first{ std::forward<T>(first) }, second{ std::forward<U>(second) } {}
		
		Pair() = default;

		Pair(const Pair&) = default; /// pairwise

		template<typename T, typename U> //different types but can be deduced from 
		Pair(const Pair<T,U>& other) {
			first = other.first;
			second = other.second;
			std::cout << "HERE\n";
		}

		Pair(Pair&& other) noexcept {
			first = std::move(other.first);
			second = std::move(other.second);
		}

		Pair& operator=(const Pair& other) {

			if (this == &other) {
				return *this;
			}

			first = other.first;
			second = other.second;
			return *this;

		} /// copy assigment

		Pair& operator=(Pair&& other) noexcept {

			first = std::move(other.first);
			second = std::move(other.second);

			return *this;

		} /// move assigment

		operator std::pair<First, Second>() const { /// for std::tie type conversion
			return { first, second }; ///RVO
		}

		First first;
		Second second;
	};

	//////////////////////// exactly like std::pair , assigments and constructions are done pairwise on each term hence potential memory leaks 
			
	template <typename T, typename U> 
	Pair(T, U) -> Pair<std::remove_cvref_t<T>, std::remove_cvref_t<U>>;

	/// type deduction guide
	/// if we have an object of type Pair with 2 types T,U let the type be Pair<T, U>
	/// after calling the constr T ,U can be deduced with & hence we dont want the types to be references , just raw types => & remove
}

namespace std {

	template<typename T>
	struct TypeIdentity {
		using type = T;
	};

	/// in order for the structured binding to work with Pair: the compiler must know the size of the Pair class (tuple_size) , its types stored (tuple_element)
	/// and to get the element based on provided index (get)

	/// partial specialization , accepts a Pair which will deduce its temple arguments
	template<typename First, typename Second>
	struct tuple_size<myStd::Pair<First, Second>> : integral_constant<std::size_t,2> {};

	/// returns First if I==0 or Second , inheriting the type 
	template<size_t I, typename First, typename Second>
	struct tuple_element<I, myStd::Pair<First, Second>> : TypeIdentity<typename conditional_t<I == 0, First, Second>> {};
	
	/// overloads
	template<size_t N, typename First, typename Second>
	constexpr auto& get(myStd::Pair<First, Second>& pair) { 
		if constexpr (N == 0) {
			return pair.first;
		}
		else {
			return pair.second;
		}
	}

	template<size_t N, typename First, typename Second>
	constexpr auto&& get(myStd::Pair<First, Second>&& pair) {
		if constexpr (N == 0) {
			return move(pair.first);
		}
		else {
			return move(pair.second);
		}
	}
	
	template<size_t N, typename First, typename Second>
	constexpr const auto& get(const myStd::Pair<First, Second>& pair) {
		if constexpr (N == 0) {
			return pair.first;
		}
		else {
			return pair.second;
		}
	}

	template<size_t N, typename First, typename Second>
	constexpr const auto&& get(const myStd::Pair<First, Second>&& pair) {
		if constexpr (N == 0) {
			return move(pair.first);
		}
		else {
			return move(pair.second);
		}
	}

}