#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

class SearchQuery {
	//dummy class
};

class DirectorySearchResult {
	static int counter;
public:
	DirectorySearchResult() : attributes(0), query(nullptr), instance_num(counter++)
	{
		std::cout << "Default constructor, instance " << instance_num << std::endl;
	}
	//DirectorySearchResult() = default;

	DirectorySearchResult(
		std::vector<std::string> const& files,
		size_t attributes,
		SearchQuery const* query
	) : files(files),
		attributes(attributes),
		query(new SearchQuery(*query)),
		instance_num(counter++)
	{
		std::cout << "Default constructor with params, instance " << instance_num << std::endl;
	}

	//Copy constructor
	DirectorySearchResult(DirectorySearchResult const &other) :
		files(other.files),
		attributes(other.attributes),
		query(other.query ? new SearchQuery(*other.query) : nullptr),
		instance_num(counter++)
	{
		std::cout << "copy constructor, instance " << instance_num << std::endl;
	}

	//Move constructor
	DirectorySearchResult(DirectorySearchResult &&other) :
		files((std::vector<std::string>&&)other.files),
		//files(std::move(other.files)),
		attributes(other.attributes),
		query(other.query),
		instance_num(counter++)
	{
		std::cout << "move constructor, instance " << instance_num << std::endl;

		other.attributes = 0;
		other.query = nullptr;
	}

	//this operators copies and object upon the existing object
	DirectorySearchResult& operator=(DirectorySearchResult const& other)
	{
		std::cout << "Assignment operator, instance " << instance_num << std::endl;

		//if it's the same object...
		if(this == &other){
			return *this; //we just return this one
		}

		//we copy the members
		files = other.files;
		attributes = other.attributes;
		delete query; //we delete whatever was here
		query = other.query ? new SearchQuery(*other.query) : nullptr;

		return *this; //now we return the present object
	}

	//assignment with move semantics
	DirectorySearchResult& operator=(DirectorySearchResult&& other)
	{
		std::cout << "Move assignment operator, instance " << instance_num << std::endl;

		//files = (std::vector<std::string>&&)other.files;
		files = std::move(other.files);
		attributes = other.attributes;
		other.attributes = 0;

		std::swap(query, other.query);

		return *this;
	}

	friend std::ostream& operator << (std::ostream &os, const DirectorySearchResult &dsr);

	~DirectorySearchResult()
	{
		std::cout << "destructor, instance " << instance_num << std::endl;
		delete query;
	}
private:
	std::vector<std::string> files;
	size_t attributes;
	SearchQuery* query;
	int instance_num;
};

int DirectorySearchResult::counter = 0;

std::ostream& operator << (std::ostream &os, const DirectorySearchResult &dsr)
{
	os << "<< instance " << dsr.instance_num << std::endl;
	for(std::string file : dsr.files){
		os << file << " " << std::endl;
	}

	os << "attributes: " << dsr.attributes << std::endl;

	return os;
}

int main(int argc, char *argv[])
{
	//list of files
	std::vector<std::string> files = {"file1", "file2", "file3"};

	std::cout << std::endl << "test 0: create an object with params" << std::endl;
	DirectorySearchResult dsr0(files, 3, new SearchQuery());
	std::cout << dsr0;

	std::cout << std::endl << "test 1: create an object by copying another" << std::endl;
	DirectorySearchResult dsr1(dsr0);
	std::cout << dsr1;

	std::cout << std::endl << "test 2: create an object by copying another with assignment" << std::endl;
	DirectorySearchResult dsr2 = dsr1;
	std::cout << dsr2;

	std::cout << std::endl << "test 3: assign and object on top on an existing object" << std::endl;
	DirectorySearchResult dsr3;
	std::cout << dsr3;

	dsr3 = dsr2;
	std::cout << dsr3;

	std::cout << std::endl << "test 4: move constructor" << std::endl;
	DirectorySearchResult dsr4((DirectorySearchResult &&) dsr3);
	std::cout << dsr3;
	std::cout << dsr4;

	std::cout << std::endl << "test 5: move constructor with assignment" << std::endl;
	DirectorySearchResult dsr5 = (DirectorySearchResult &&) dsr4;
	std::cout << dsr4;
	std::cout << dsr5;

	std::cout << std::endl << "test 5: assignment with move semantics" << std::endl;
	DirectorySearchResult dsr6;
	dsr6 = (DirectorySearchResult &&) dsr5;
	std::cout << dsr5;
	std::cout << dsr6;
}
