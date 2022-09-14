#include <iostream>
#include <vector>
#include <algorithm>

template <typename T> class Heap {
public:
	void add(T const &value);
	T const &max() const;
	T remove_max();
	size_t size() const;
private:
	std::vector<T> elements;
};

template <typename T> void Heap<T>::add(T const &value)
{
	elements.push_back(value);
}

template <typename T> T const& Heap<T>::max() const
{
	return *std::max_element (elements.begin(), elements.end());
}

template <typename T> T Heap<T>::remove_max()
{
	auto e = std::max_element (elements.begin(), elements.end());
	elements.erase(e);

	return *e;
}

template <typename T> size_t Heap<T>::size() const
{
	return elements.size();
}

int main()
{
	Heap<float> h;

	h.add(0.4);
	h.add(-345);
	h.add(23);

	std::cout << "Heap has " << h.size() << " elements." << std::endl;
	std::cout << "the max element is: " << h.max() << std::endl;
	std::cout << "the erase the max element which is: " << h.remove_max() << std::endl;
	std::cout << "now the max element is: " << h.max() << std::endl;
	std::cout << "now Heap has " << h.size() << " elements." << std::endl;

	return 0;
}
