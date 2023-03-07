#include <iostream>
#include <string>
#include <fstream>

template<typename T>
struct Unnamed {
	T operator()(T x, T y) const {
		return x + y;
	}
};

/*
struct Unnamed {
	int operator()(int x, int y) const {
		return x + y;
	}
};
*/


template<typename T, int size, typename Comparator>
void Sort(T(&arr)[size], Comparator comp) {
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - 1; j++) {
			if (comp(arr[j], arr[j + 1])) {
				T temp = std::move(arr[j]);
				arr[j] = std::move(arr[j + 1]);
				arr[j + 1] = std::move(temp);
			}

		}
	}
}

template<typename T, int size, typename Callback>
void ForEach(T(&arr)[size], Callback operation) {
	for (int i = 0; i < size; ++i) {
		operation(arr[i]);
	}
}


bool Comp(int x, int y) {
	return x > y;
}

struct Comp2 {
	bool operator() (int x, int y) {
		return x > y;
	}
};


class Product {
	std::string name;
	float price;
public:
	Product(const std::string& n, float p) : name(n), price(p) {

	}
	void AssignFinalPrice() {
		float taxes[]{ 12, 5, 5 };
		float base_price{ price };

		ForEach(taxes, [base_price, this](float tax) {
			float taxedPrice = base_price * tax / 100;
			price += taxedPrice;
		});
	}
	float GetPrice()const {
		return price;
	}
};

int main() {
	auto fn = []() {
		std::cout << "Lambda expression\n";
	};

	fn();

	std::cout << typeid(fn).name() << std::endl;


	//auto sum = [](int x, int y) -> int {
	//	return x + y;
	//};
	auto sum = [](auto x, auto y) -> int {
		return x + y;
	};

	Unnamed<int> n;

	std::cout << "Sum is: " << sum(5, 2) << std::endl;
	std::cout << "Sum is: " << n(5, 2) << std::endl;

	int arr[]{ 1,6,8,4,0 };

	std::cout << "Unsorted: ";
	for (auto x : arr) {
		std::cout << x << " ";
	}
	std::cout << std::endl;

	//Sort(arr, Comp);	//Puntero a funcion
	Comp2 comp;
	//Sort(arr, comp);	// Objeto con operacion funcion sobrecargada ( mas eficiente que puntero a funcion )
	Sort(arr, [](auto x, auto y) {return x > y; });	//Lambda expression ( Mas eficiente todavia )

	std::cout << "Sorted:   ";
	for (auto x : arr) {
		std::cout << x << " ";
	}
	std::cout << std::endl;

	int offset = 5;
	//ForEach(arr, [offset](auto& x) { x += offset; });
	
	//ForEach(arr, [offset](auto& x) mutable { x += offset; ++offset; });

	int acc{};
	ForEach(arr, [&acc](auto x) {acc += x; });

	std::cout << "La suma es:" << acc << std::endl;

	// [=](auto x) {}; // Captura todas las variables del scope como valor (declaradas antes de la lambda expression)
	// [&](auto x) {}, // Captura todas las variable del scope como referencia
	// [=, &acc](auto x) {}, // Captura todas las variable del scope como valor pero acc la captura como referencia
	// [&, acc](auto x) {}, // Captura todas las variable del scope como referencia pero acc la captura como valor


	//ForEach(arr, [](auto x) { std::cout << x << " "; });

	Product p{ "Watch", 500 };
	p.AssignFinalPrice();
	std::cout << "Final price: " << p.GetPrice() << std::endl;

	[](int x) {
		x *= 2;
		[](int x) {
			std::cout << x << std::endl;
		}(x);
	}(5);

	atexit([]() {std::cout << "Final del programa\n"; }); //Si no tiene capture list se puede usar una lambda expression como puntero a funcion

	int x{ 5 };
	auto f = [y = x](int arg) {		// se crea una variable local a la expresion lambda y se le asigna el valor de x. Las variable locales siempre tienen que estar inicializadas
		return y + arg;
	};

	std::cout << f(5) << std::endl;



	std::ofstream outfile{ "file.txt" };

	auto write = [localoutfile = std::move(outfile)](int x) mutable {
		localoutfile << x;
	};
 
	write(200);

	return 0;
}