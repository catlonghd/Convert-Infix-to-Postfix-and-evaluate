#include "Stack_Char.h"


Node_Char* createNode(char data) {
	return new (std::nothrow) Node_Char{ data, nullptr };
}

void init(Stack_Char& s) {
	s.top = nullptr;
}



bool isEmpty(const Stack_Char& s) {
	return s.top == nullptr;
}


void push(Stack_Char& s, char data) {
	Node_Char* p = createNode(data);
	if (isEmpty(s)) {
		s.top = p;
		return;
	}
	p->next = s.top;
	s.top = p;
}


char top(const Stack_Char& s) {
	return s.top->data;
}


void pop(Stack_Char& s) {
	if (isEmpty(s)) {
		return;
	}

	Node_Char* del = s.top;
	s.top = s.top->next;
	delete del;
	del = nullptr;
}


void deleteStack(Stack_Char& s) {
	if (isEmpty(s))
		return;
	Node_Char* cur = nullptr;
	while (s.top) {
		cur = s.top->next;
		delete s.top;
		s.top = cur;
	}
}