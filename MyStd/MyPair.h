#pragma once
#include <utility>
#include <iostream>

namespace myStd {

	template<typename First, typename Second>
	class Pair {

	public:

		Pair() = default;
		Pair(const Pair&) = default; /// pairwise

		//template<typename T, typename U, typename = std::enable_if_t<std::is_constructible_v<First, T&&> && std::is_constructible_v<Second, U&&>>>
		/// check if the type can be constructed using Args... ,here the types are T&&,U&& ,also allows casts
		
		template<typename T, typename U> requires (std::is_constructible_v<First, T&&> && std::is_constructible_v<Second, U&&>)
		Pair(T&& first, U&& second) : first{ static_cast<First>(std::forward<T>(first)) }, second{ static_cast<Second>(std::forward<U>(second)) } {}
		
		
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
			
	template <typename T, typename U> /// type deduction guide
	Pair(T, U) -> Pair<T, U>;

}

namespace std {

	template<typename First, typename Second>
	struct tuple_size<myStd::Pair<First, Second>> {
		static constexpr size_t value = 2; /// size of tuple
		using type = integral_constant<size_t, value>; 
	};

	template<size_t I, typename First, typename Second>
	struct tuple_element<I, myStd::Pair<First, Second>> {
		using type = typename conditional<I == 0, First, Second>::type; /// :: type returns First or Second
	};
		
	template<size_t N, typename First, typename Second>
	constexpr auto& get(myStd::Pair<First, Second>& pair) { /// overloads
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