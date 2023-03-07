#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unordered_set>
#include <algorithm>

class Employee {
	std::string m_name;
	int m_id;
	std::string m_proglang;
public:
	Employee(const std::string& n, int id, const std::string& pl) : m_name(n), m_id(id), m_proglang(pl) {

	}

	const std::string& GetName()const {
		return m_name;
	}

	int GetId() const{
		return m_id;
	}

	const std::string& GetProgrammingLanguage() const {
		return m_proglang;
	}

	// Cosas necesarias para ordenar (sort, set , etc)
	//bool operator <(const Employee& e) const {
	//	return m_id < e.m_id;
	//}

};

struct EmpCompare {
	bool operator()(const Employee& e1, const Employee& e2) const {
		return e1.GetId() < e2.GetId();
	}
};

struct EmpIds {
	std::vector<int> m_Ids;
	void operator()(const Employee& e) {
		if (e.GetProgrammingLanguage() == "C++") {
			m_Ids.push_back(e.GetId());
		}
	}
};

int main() {
	std::vector<Employee> v{
		Employee{"Umar", 101, "C++"},
		Employee{"Bob", 202, "Java"},
		Employee{"Joey", 200, "C++"}
	};

	std::sort(v.begin(), v.end(), [](const auto& e1, const auto& e2) {	//Lambda expression cumple la funcion de callback de orden (predicate)
		return e1.GetName() < e2.GetName();
		//return e1.GetId() < e2.GetId();
	});

	std::cout << "VECTOR: \n";
	for (auto& x : v) {
		std::cout << x.GetId() << ":" << x.GetName() << std::endl;
	}
	std::cout << "\n";

	std::set<Employee,EmpCompare> s{	//Si no quiero sobrecargar el operador < o > puedo pasarle un function object para ordenar, es mas flexible de esta forma ya que puedo cambiar el criterio de orden
		Employee{"Umar", 101, "C++"},
		Employee{"Bob", 202, "Java"},
		Employee{"Joey", 200, "C++"}
	};

	std::cout << "SET: \n";
	for (auto& x : s) {
		std::cout << x.GetId() << ":" << x.GetName() << std::endl;
	}
	std::cout << "\n";

	// auto cppCount = std::count_if(v.begin(), v.end(), Employee{"", 0, "C++"}) //SI quiero implementar esto hay que sobrecargar el operador == de la clase employee
	auto cppCount = std::count_if(v.begin(), v.end(), [](const auto& e) { 
		return e.GetProgrammingLanguage() == "C++"; 
	});

	std::cout << "C++ Count: " << cppCount << std::endl;

	auto itr = std::find_if(v.begin(), v.end(), [](auto const& e) {
		return e.GetProgrammingLanguage() == "Java";
	});

	if (itr != v.end()) {
		std::cout << "Found: " << itr->GetName() << " is a Java programmer." << std::endl;
	}
	else {
		std::cout << "No Java programmer found." << std::endl;
	}

	std::for_each(v.begin(), v.end(), [](const auto& e) {
		std::cout << e.GetName() << std::endl;
	});

	std::cout << std::endl << "C++ programmer: " << std::endl;
	auto foundIds = std::for_each(v.begin(), v.end(), EmpIds());
	for (int id : foundIds.m_Ids) {
		std::cout << "ID: " << id << std::endl;
	}


	return 0;
}