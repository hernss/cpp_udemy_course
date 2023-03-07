#include <cstdlib>
#include <iostream>
#include <memory>


struct Free {
	void operator()(int *p) {
		free(p);
		std::cout << "pointer freed\n";
	}
};

void MallocFree(int* p) {
	free(p);
	std::cout << "pointer freed\n";
}
void UniquePtrDeleter() {
	
	std::unique_ptr<int, void(*)(int*)> p{(int*)malloc(4), MallocFree}; // USando puntero a funcion
	
	//std::unique_ptr<int, Free> p{ (int*)malloc(4), Free{} }; //With object or struct
	*p = 100;

	std::cout << *p << std::endl;
}

void SharedPtrDeleter() {

	//std::shared_ptr<int> p{ (int*)malloc(4), MallocFree }; // USando puntero a funcion

	std::shared_ptr<int> p{ (int*)malloc(4), Free{} }; //With object or struct
	*p = 100;

	std::cout << *p << std::endl;
}

class Point {
public:
	Point(int x, int y) {

	}
};

int main() {
	//UniquePtrDeleter();
	//SharedPtrDeleter();
	{
		auto p = std::make_unique<int>(5);
		auto pt = std::make_unique<Point>(6, 7);

		auto pArr = std::make_unique<int[]>(5);
		pArr[0] = 0;
	}

	{
		auto p = std::make_shared<int>(5);
		auto pt = std::make_shared<Point>(6, 7);

		auto pArr = std::make_shared<int[]>(5);
		pArr[0] = 0;
	}
}