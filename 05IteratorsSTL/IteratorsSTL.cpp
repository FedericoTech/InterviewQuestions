#include<iostream>
#include<list>
#include<vector>
#include<algorithm>

int main(int argc, char *argv[])
{
	std::list<int> lo {1,3,2}; //we declare this list with unordered values

	std::list<int> l(lo); //we make a copy with copy constructor

	//std::sort(l.begin(), l.end()); //it won't work because std::sort requieres a random access iterator.
	l.sort(); //instead we use its own method sort

	for(auto i : l){
		std::cout << i << " ";
	}

	std::cout << std::endl;

	//another way to get those data ordered could be by copying them into a vector

	std::vector<int> v(lo.begin(), lo.end());

	//now we can use std::sort as vector iterators have random access
	std::sort(v.begin(), v.end());

	for(auto i : v){
		std::cout << i << " ";
	}

	std::cout << std::endl;

	return 0;
}


