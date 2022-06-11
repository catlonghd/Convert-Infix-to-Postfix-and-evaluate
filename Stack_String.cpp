#include "Stack_String.h"

Node_String* createNode(string data) {
	return new (std::nothrow) Node_String{ data, nullptr };
}

void init(Stack_String& s) {
	s.top = nullptr;
}



bool isEmpty(const Stack_String& s) {
	return s.top == nullptr;
}


void push(Stack_String& s, string data) {
	Node_String* p = createNode(data);
	if (isEmpty(s)) {
		s.top = p;
		return;
	}
	p->next = s.top;
	s.top = p;
}


string top(const Stack_String& s) {
	return s.top->data;
}


void pop(Stack_String& s) {
	if (isEmpty(s)) {
		return;
	}

	Node_String* del = s.top;
	s.top = s.top->next;
	delete del;
	del = nullptr;
}

void deleteStack(Stack_String& s) {
	if (isEmpty(s))
		return;
	Node_String* cur = nullptr;
	while (s.top) {
		cur = s.top->next;
		delete s.top;
		s.top = cur;
	}
}
