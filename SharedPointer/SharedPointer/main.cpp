
#include <string>
#include <iostream>

class Project {
	std::string m_Name;
public:
	void SetName(std::string name) {
		m_Name = name;
	}
	void ShowProjectDetails() const {
		std::cout << "[Project Name] " << m_Name << std::endl;
	}
};

class Employee {
	//Project* m_pProject{};
	std::shared_ptr<Project> m_pProject{};
public:
	void SetProject(std::shared_ptr<Project> &prj) {
		m_pProject = prj;
	}

	const std::shared_ptr<Project>& GetProject() const {
		return m_pProject;
	}
};

void ShowInfo(const std::shared_ptr < Employee> &emp) {
	std::cout << "Employee project detail: ";
	emp->GetProject()->ShowProjectDetails();
}

class Printer {
	std::weak_ptr<int> m_pValue{};
public:
	void SetValue(std::weak_ptr<int> p) {
		m_pValue = p;
	}
	void Print() {
		std::cout << "Reference count " << m_pValue.use_count() << std::endl;
		if (m_pValue.expired()) {
			std::cout << "Resource is no longer available" << std::endl;
			return;
		}
		auto sp = m_pValue.lock();
		std::cout << "Value is " << *sp << std::endl;
		
	}
};



int main() {

	// SHARED POINTER
	std::shared_ptr<Project> prj{ new Project{} };
	prj->SetName("Video Decoder");

	std::shared_ptr < Employee> e1{ new Employee{} };
	e1->SetProject(prj);
	std::shared_ptr < Employee> e2{ new Employee{} };
	e2->SetProject(prj);
	std::shared_ptr < Employee> e3{ new Employee{} };
	e3->SetProject(prj);

	ShowInfo(e1);
	ShowInfo(e2);

	if (e2) {
		//Valid
	}
	else {
		//not valid
	}

	std::cout << "Reference count " << prj.use_count() << std::endl;

	e3.reset(new Employee{});

	std::cout << "Reference count " << prj.use_count() << std::endl;


	prj->ShowProjectDetails();


	// WEAK POINTER


	Printer prn;

	int num{};
	std::cin >> num;
	std::shared_ptr<int> p{ new int{ num } };
	prn.SetValue(p);

	if (*p > 10) {
		p = nullptr;
	}

	prn.Print();
}