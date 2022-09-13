#include <iostream>
#include <type_traits>

//template base
template<class>
struct is_pointer {
	enum { value = false };
};

//template overload
template<class T>
struct is_pointer<T*>{
	enum { value = true };
};

//template base
template<class>
struct is_const {
	enum { value = false };
};
//template overload
template<class T>
struct is_const<T const>{
	enum { value = true };
};

//template base
template<class>
struct is_volatile {
	enum { value = false };
};

//template overload
template<class T>
struct is_volatile<T volatile>{
	enum { value = true };
};

//we make up these types somewhere
typedef int* int_p;
typedef int int_s;

typedef  int * const c_int_p;
typedef const int c_int_s;

typedef  int * volatile v_int_p;
typedef volatile int v_int_s;

typedef  int * const volatile cv_int_p;
typedef const volatile int cv_int_s;

int main()
{
	//now we don't know which type is a pointer and which isn't, so we need to test them
	std::cout << "is int_p a pointer? " << (is_pointer<int_p>::value) << std::endl;
	std::cout << "is int_s a pointer? " << (is_pointer<int_s>::value) << std::endl;

	std::cout << "is c_int_p a constant pointer? " << (is_const<c_int_p>::value) << std::endl;
	std::cout << "is c_int_s a constant? " << (is_const<c_int_s>::value) << std::endl;

	std::cout << "is v_int_p a volatile pointer? " << (is_volatile<v_int_p>::value) << std::endl;
	std::cout << "is v_int_s a volatile? " << (is_volatile<v_int_s>::value) << std::endl;

	std::cout << "is cv_int_p a constant pointer? " << (is_const<cv_int_p>::value) << std::endl;
	std::cout << "is cv_int_s a constant? " << (is_const<cv_int_s>::value) << std::endl;

	std::cout << "is cv_int_p a volatile pointer? " << (is_volatile<cv_int_p>::value) << std::endl;
	std::cout << "is cv_int_s a volatile? " << (is_volatile<cv_int_s>::value) << std::endl;

	std::cout << std::endl;
	//there is this library type_traits that does the same

	std::cout << "is int_p a pointer? " << (std::is_pointer<int_p>::value) << std::endl;
	std::cout << "is int_s a pointer? " << (std::is_pointer<int_s>::value) << std::endl;

	std::cout << "is c_int_p a constant pointer? " << (std::is_const<c_int_p>::value) << std::endl;
	std::cout << "is c_int_s a constant? " << (std::is_const<c_int_s>::value) << std::endl;

	std::cout << "is v_int_p a volatile pointer? " << (std::is_volatile<v_int_p>::value) << std::endl;
	std::cout << "is v_int_s a volatile? " << (std::is_volatile<v_int_s>::value) << std::endl;

	std::cout << "is cv_int_p a constant pointer? " << (std::is_const<cv_int_p>::value) << std::endl;
	std::cout << "is cv_int_s a constant? " << (std::is_const<cv_int_s>::value) << std::endl;

	std::cout << "is cv_int_p a volatile pointer? " << (std::is_volatile<cv_int_p>::value) << std::endl;
	std::cout << "is cv_int_s a volatile? " << (std::is_volatile<cv_int_s>::value) << std::endl;

	return 0;
}
