# include <iostream>
# include <stack>

using namespace std;

template <class T>
class StackExt {

private:
	stack<T> main_stack;
	stack<T> min_stack;

public:
	StackExt() {};
	bool empty() const;
	T& top();
	void pop();
	void push(const T& val);
	T& findMin();
};

template <class T>
bool StackExt<T>::empty() const {
	return main_stack.empty();
}

template <class T>
T& StackExt<T>::top() {

	return main_stack.top();
}

template <class T>
void StackExt<T>::pop() {

	if (main_stack.top() == min_stack.top())
		min_stack.pop();

	main_stack.pop();
}

template <class T>
void StackExt<T>::push(const T& val) {
	main_stack.push(val);
	if (min_stack.empty() || val < min_stack.top() || val == min_stack.top())
		min_stack.push(val);
}

template <class T>
T& StackExt<T>::findMin() {

	return min_stack.top();
}
