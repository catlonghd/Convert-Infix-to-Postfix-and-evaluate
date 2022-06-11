#pragma once
#include <string>

using namespace std;

struct Node_String {
	string data;
	Node_String* next;
};



struct Stack_String {
	Node_String* top;
};

Node_String* createNode(string data);
void init(Stack_String& s);
bool isEmpty(const Stack_String& s);
void push(Stack_String& s, string data);
string top(const Stack_String& s);
void pop(Stack_String& s);
void deleteStack(Stack_String& s);