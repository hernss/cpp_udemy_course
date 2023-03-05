#include <iostream>
#include <memory>
#include <vector>
#include <random>


class A {
public:
	A() {std::cout << "A()" << std::endl;}
	~A() { std::cout << "~A()" << std::endl; }

};


class B {
public:
	B() {std::cout << "B()" << std::endl;}
	~B() { std::cout << "~B()" << std::endl; }

};


class Test {
	//A* pA{};
	std::unique_ptr<A> pA{};
	B b{};
	//int* pInt{};
	std::unique_ptr<int> pInt{};

	//char* pStr{};
	std::string pStr{};
	
	//int* pArr{};
	std::vector<int> pArr{};

public:
	Test() { 
		std::cout << "Test()" << std::endl; 
		//pA = new A{};
		pA.reset(new A{});
		//pInt = new int{};

		throw std::runtime_error("Failed to initialize");
		
		//pStr = new char[1000];
		//pArr = new int[50000];
	}
	~Test() { 
		std::cout << "~Test()" << std::endl; 
		//delete pA;
		//delete pInt;
		//delete[] pStr;
		//delete[] pArr;
	}

};

int Sum(int x, int y) noexcept(true) { //Para marcar no exception a funciones que sabemos que no va a tirar excepcion, optimiza el codigo si esta funcion se llamara desde un try
	return x + y;
}

void ProcessRecords(int count) {

	if (count < 10)
		throw std::out_of_range("Count should be greater than 10");

	/*
	int* pArray = (int*)malloc(count * sizeof(int));

	if (pArray == nullptr) {
		throw std::runtime_error("Failed to allocate memory");
	}
	for (int i = 0; i < count; i++) {
		pArray[i] = i;
	}

	
	free(pArray);
	*/
	std::vector<int> p;
	p.reserve(count);

	for (int i = 0; i < count; i++) {
		p.push_back(i);
	}

	std::default_random_engine eng;
	std::bernoulli_distribution dist;

	int errors{};
	for (int i = 0; i < count; i++) {
		try {
			std::cout << "Processing record #:" << i << " ";
			if (!dist(eng)) {
				++errors;
				throw std::runtime_error("Could not procces the record");
			}
		}
		catch (std::runtime_error& ex) {
			std::cout << "[ERROR " << ex.what() << "]";
			if (errors > 4) {
				std::runtime_error err("Too many errors");
				ex = err;
				throw;	
			}
		}
		std::cout << std::endl;
	}

	return;
}

int main() {
	/*
	try {
		//ProcessRecords(std::numeric_limits<long long>::max());
		ProcessRecords(15);
	}
	catch (std::runtime_error &ex) {
		std::cout << ex.what() << std::endl;
	}
	catch (std::out_of_range& ex) {
		std::cout << ex.what() << std::endl;
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
	*/
	try {
		Test t;
	}
	catch (std::runtime_error& ex) {
		std::cout << ex.what() << std::endl;
	}

	return 0;

}