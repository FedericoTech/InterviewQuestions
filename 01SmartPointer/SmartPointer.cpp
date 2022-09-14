#include <iostream>
#include <memory>

//this function accepts smart pointers by value but they have to be moved first
auto f(std::unique_ptr<int> ptr) {
	*ptr = 42;

	//it can be transferred by value
	return ptr;
}

//this function accepts the smart pointer by reference
void g(std::unique_ptr<int> &ptr) {
	*ptr = 43;
}

template<typename T>
std::unique_ptr<T> createSPointer(){
	std::unique_ptr<T> p = std::make_unique<T>();
	*p = 44;

	//it is transferred by value by being move
	return p;
}

int main() {

	//se create some unique smart pointer
	auto ptr = std::make_unique<int>();

	//then we pass it by value but with move semantics
	auto ptr2 = f(std::move(ptr));

	//now ptr2 has the pointer whereas ptr has been reset and it's null
	std::cout << "Is ptr null? " << (ptr == nullptr) << std::endl;

	std::cout << *ptr2 << std::endl;

	//we can't pass ptr by reference as it points to null and the program breaks at runtime
	//g(ptr);

	//we can pass ptr2  by reference
	g(ptr2);

	std::cout << *ptr2 << std::endl;

	//we reuse ptr by creating a new smart pointer.
	ptr = createSPointer<int>();

	std::cout << *ptr << std::endl;
}
