#include<iostream>
#include<type_traits>
#include<array>

/**
 * This exercise is to make a template available only if it fulfils certain conditions.
 */

//template that accepts a type and a number of elements
template<typename T, std::size_t N>
//if the type is integral and the number of elements less than 128
typename std::enable_if<std::is_integral<T>::value && N < 128, void>::type
//then we can make the template enable
insertion_sort(std::array<T, N>& array) {
	//here the algorithm for insertion short
	for (std::size_t i = 0; i < N; i++) {
		for (std::size_t j = i; j > 0 && array[j] < array[j-1]; j--) {
			std::swap(array[j], array[j - 1]);
		}
	}
}

int main()
{
	//std::array<float, 5> a1 {1, 8, -4, 9, 7}; //this won't compile as float isn't integral

	//std::array<int, 128> a1 {1, 8, -4, 9, 7}; // this won't compile as the array is set to have 128 and only less than 128 is allowed

	std::array<long long, 5> a1 {1, 8, -4, 9, 7}; //it compiles because 'long long' is integral and the array has less than 128 elements

	insertion_sort(a1); //we sort the elements of the array

	//we can show then and check that it works
	for(int i : a1){
		std::cout << i << " ";
	}

	std::cout << std::endl;

	return 0;
}
