#include <iostream>
#include <initializer_list>
#include <cassert>
#include <vector>

class Bag {
	int arr[10];
	int m_size{};
public:
	void Add(int value) {
		assert(m_size < 10);
		arr[m_size++] = value;
	}
	void Remove() {
		--m_size;
	}
	int operator [](int index) {
		return arr[index];
	}
	int GetSize() {
		return m_size;
	}
	Bag(std::initializer_list<int> values) {
		auto it = values.begin();
		while (it != values.end()) {
			Add(*it);
			++it;
		}
	}
};

void Print(std::initializer_list<int> values) {
	/*	
	auto it = values.begin();
	while (it != values.end()) {
		std::cout << *it << " ";
		++it;
	}
	*/
	for (auto it : values) {
		std::cout << it << " ";
	}
}
int main() {

	//Bag b{ 3,1,8 };
	//b.Add(3);
	//b.Add(1);
	//b.Add(8);
	//for (int i = 0; i < b.GetSize(); i++) {
	//	std::cout << b[i] << std::endl;
	//}

	//Print({ 1,4,6 });


	std::vector<int> data{ 1,4,5,8,9,12};

	data.push_back(8);

	//Access
	int element = data[3];
	for (int i = 0; i < data.size(); i++) {
		std::cout << data[i] << " ";
	}
	std::cout << std::endl;

	for (auto elem : data) {
		std::cout << elem <<  " ";
	}
	std::cout << std::endl;

	// Delete
	auto it = data.begin();
	data.erase(it);
	for (auto elem : data) {
		std::cout << elem << " ";
	}
	std::cout << std::endl;


	//Insert
	it = data.begin() + 5;
	data.insert(it, 500);
	for (auto elem : data) {
		std::cout << elem << " ";
	}
	std::cout << std::endl;


	return 0;
}