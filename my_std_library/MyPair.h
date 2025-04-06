#pragma once
#include <utility>
#include <iostream>

namespace mySTL {

	template<typename First, typename Second>
	class Pair {

	public:

		Pair() = default;
		Pair(const Pair&) = default; /// pairwise
	
		template<typename T, typename U, typename = std::enable_if_t<std::is_constructible_v<First, T&&> && std::is_constructible_v<Second, U&&>>>
		Pair(T&& first, U&& second): first{ static_cast<First>(std::forward<T>(first)) }, second{ static_cast<Second>(std::forward<U>(second)) } {}
		/// pre " concept " way to check if the type can be constructed using Args... ,here the type(s) are T&&,U&& also allows casts

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

		First first;
		Second second;
	};

	////////////////////////// exactly like std::pair , assigments and constructions are done pairwise on each term hence potential memory leaks 

}