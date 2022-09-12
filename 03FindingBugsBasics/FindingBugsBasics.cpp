#include <vector.h> //wrong name

void main(int argc, char** argv) //wrong return type. it should be int
{
	int n;

	if(argc > 1)
		n = argv[0];	//argv[0] is the program name
						//it won't compile because we are assigning the pointer to the first array of the bidimensional array
					 	 //we can add another index or we can set an asterisk to get the first letter of the first word

	int *stuff = new int[n]; //n is uninitialised if we run the program without params

	vector<int> v(100000); //we didnt' use the std namspace
							//still it might throw a std::bad_alloc exception

	delete stuff; //we are deleting an array we should use delete[], we could also use a smart pointer instead

	return 0; //if the function is void we shouldn't return a value.
}
