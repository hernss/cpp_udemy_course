#include <iostream>
/*
class Stack {
	int m_Buffer[512];
	int m_top{ -1 };

public:
	void Push(int elem) {
		m_Buffer[++m_top] = elem;
	}

	int Pop(void) {
		if (m_top >= 0)
			return m_Buffer[m_top--];
		else
			return 0;
	}

	int Top() const {
		return m_Buffer[m_top];
	}

	bool IsEmpty() {
		return m_top == -1;
	}

};
*/

template<typename T, int size>
class Stack {
	T m_Buffer[size]{ 0 };
	int m_top{ -1 };

public:
	void Push(const T &elem) {
		m_Buffer[++m_top] = elem;
	}

	const T& Pop(void);

	const T& Top() const {
		return m_Buffer[m_top];
	}

	bool IsEmpty() {
		return m_top == -1;
	}

};

template<typename T, int size>
const T& Stack<T,size>::Pop(void) {
	if (m_top >= 0)
		return m_Buffer[m_top--];
	else
		return 0;
}

int main() {
	Stack<float, 10> s;
	s.Push(3);
	s.Push(1);
	s.Push(6);
	s.Push(9);

	while (!s.IsEmpty()) {
		std::cout << s.Pop() << " ";
	}
}