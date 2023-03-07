#include <iostream>

/*
int Max(int x, int y) {
	return x > y ? x : y;
}
float Max(float x, float y) {
	return x > y ? x : y;
}
*/

template<typename T>
T Max(T x, T y) {
	return x > y ? x : y;
}

template<typename T>
T ArraySum(T* pArray, int size) {
	T sum{};
	for (int i = 0; i < size; i++) {
		sum += pArray[i];
	}
	return sum;
}

// Variadic templates
void Print() {
	std::cout << std::endl;
}
template<typename T, typename... Params>
void Print(T a, Params... args) {
	
	std::cout << a;
	
	if (sizeof...(args))
		std::cout << ",";
	
	Print(args...);
}

int main() {
	/*
	auto num = Max(3, 8);

	std::cout << num << std::endl;

	auto num2 = Max(3.4, 4.6);

	std::cout << num2 << std::endl;

	int* pA = new int[5] {1, 2, 3, 4, 5};

	auto num3 = ArraySum(pA, 5);

	std::cout << "La suma es:" << num3 << std::endl;

	float* pA2 = new float[5] {1.1, 2.2, 3.3, 4.4, 5.5};

	auto num4 = ArraySum(pA2, 5);

	std::cout << "La suma es:" << num4 << std::endl;

	delete pA;
	delete pA2;
	*/
	Print( 1, 2.5, 3, "4" );
}