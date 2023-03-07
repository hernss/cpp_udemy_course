#include "Integer.h"
#include <iostream>
#include <memory>

void Display(Integer* p) {
	if (!p) {
		return;
	}
	std::cout << p->GetValue() << std::endl;
}

Integer* GetPointer(int value) {
	Integer* p = new Integer{};
	return p;
}

void Store(std::unique_ptr<Integer> &p) {
	std::cout << "Storing data into a file:" << p->GetValue() << std::endl;
}

void Operate(int value) {
	/* OLD CODE
	Integer* p = GetPointer(value);
	if (p == nullptr) {
		p = new Integer{value};
	}
	p->SetValue(100);
	Display(p);
	delete p;
	p = nullptr;
	p = new Integer{};
	*p = __LINE__;
	Display(p);
	delete p;
	*/

	// C++ recomended
	std::unique_ptr<Integer> p{ GetPointer(value) };
	if (p == nullptr) {
		p.reset(new Integer{ value });
	}
	p->SetValue(100);
	Display(p.get());		// Si la funcion no puede tomar smart pointer con get obtengo el raw pointer
	p.reset(new Integer{});
	*p = __LINE__;
	Display(p.get());

	Store(p);				// Si lo pasas por referencia se puede seguir usando
	//Store(std::move(p));	// SI lo moves no se puede volver a usar el puntero en la funcion
	// No hay que hacer delete a los smart pointer
}

int main() {
	
	Operate(5);


	return 0;
}