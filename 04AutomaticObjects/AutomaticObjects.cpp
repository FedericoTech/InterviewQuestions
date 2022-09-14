#include <memory>
#include <vector>
#include <iostream>

int main()
{
	/*
	 * an automatic object is that that gets initialised by only declaring it in the stack
	 * we don't need to use the new operator and it lasts as long as the scope.
	 * at the end of the scope we don't need to manually delete it, C++ will do it for us by running their destructors.
	 */
	{
		std::vector<int> automatic_object;
	} //the above object is automatically destroyed by now as the scope is ended.

	/**
	 * An object with dynamic storage duration or heap object has to be first declared as a pointer and then created with the new operator.
	 *
	 */
	{
		std::vector<int> *dynamic_object = new std::vector<int>();

		//do something with it

		delete dynamic_object;	//we need to deallocate it manually if we don't need it anymore before we leave the scope
								//otherwise it becomes an unaccessible chunk of memory. memory leak
	}

	/**
	 * if we need to initialise and object to big to fit in the stack or we want to move it around beyond the scope by passing it
	 * to functions and with it the ownership and the responsibility of its deallocation we can use smart pointers
	 */
	auto dynamic_smart_object = std::make_unique<std::vector<int>>(5);

	{
		/**
		 * now dynamic_smart_object is null as it's content has been transferred to dynamic_smart_object_inside_this_scope
		 * and now is its responsability to deallocate the pointer
		 */
		auto dynamic_smart_object_inside_this_scope = std::move(dynamic_smart_object);

		std::cout << "is dynamic_smart_object released? " << (dynamic_smart_object == nullptr) << std::endl;

		//to do something with dynamic_smart_object_inside_this_scope
		std::cout << "is dynamic_smart_object_inside_this_scope active? " << (dynamic_smart_object_inside_this_scope->size() > 0) << std::endl;

	} //the object dynamic_smart_object_inside_this_scope is automatically deallocated by now as the scope is ended.

	/**
	 * the above examples are done with unique smart pointer which only allow one reference to exist at the same time as
	 * the copy constructor and the copy assignment have been deleted and it can only be moved
	 */

	std::cout << std::endl << std::endl;

	/**
	 * there are another two types of smart pointers which are interrelated, the shared_ptr and the weak_ptr which allow copies of the same reference.
	 * shared_ptr tracks the number of copies so that when a pointer is not longer references it deletes it.
	 * weak_ptr can also copy the reference but without tracking it. we can always query whether the reference is still alive.
	 */

	//outside of any scope we have the weak pointer
	std::weak_ptr<std::vector<int>> weak_object;

	{
		//inside this scope we create pointer to a 5 element vector
		auto dynamic_shared_object0 = std::make_shared<std::vector<int>>(5); //it is always better to do this way
		//auto dynamic_shared_object0 = std::shared_ptr<std::vector<int>>(new std::vector<int>(5)); //than this way because it's un-optimized
		{
			//and another smart pointer to relate to.
			std::shared_ptr<std::vector<int>> dynamic_shared_object1;
			{
				//inside this other scope another pointer to the vector.
				std::shared_ptr<std::vector<int>> dynamic_shared_object2 = dynamic_shared_object0;

				//now we assign the weak object we declared outside all of the scopes
				weak_object = dynamic_shared_object0;

				{
					dynamic_shared_object1 = dynamic_shared_object2;

					dynamic_shared_object0.reset(); //this is like doing = nullptr to a row pointer.

					std::cout << "has dynamic_shared_object2 disappeared? " << (dynamic_shared_object2 == nullptr) << std::endl;
					std::cout << "has dynamic_shared_object0 disappeared? " << (dynamic_shared_object0 == nullptr) << std::endl;
					std::cout << "is dynamic_shared_object1 active? " << (dynamic_shared_object1->size() > 0) << std::endl;
					std::cout << "has weak_object expired? " << weak_object.expired() << std::endl;

				}
				//at this point dynamic_shared_object2 is destroyed
			}
			std::cout << "has weak_object now expired? " << weak_object.expired() << std::endl;
			//at this point dynamic_shared_object1 is destroyed
		}

		//here weak_object has expired already because dynamic_shared_object0 was set to nullptr in an inner scope.
		std::cout << "is weak_object now expire? " << weak_object.expired() << std::endl;
		//at this point dynamic_shared_object0 is destroyed
	}

	std::cout << "has weak_object finally expired? " << weak_object.expired() << std::endl;
}
