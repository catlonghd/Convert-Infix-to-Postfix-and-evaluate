#pragma once
#include <string>


struct Node_Char {
	char data;
	Node_Char* next;
};



struct Stack_Char {
	Node_Char* top;
};

Node_Char* createNode(char data);
void init(Stack_Char& s);
bool isEmpty(const Stack_Char& s);
void push(Stack_Char& s, char data);
char top(const Stack_Char& s);
void pop(Stack_Char& s);
void deleteStack(Stack_Char& s);
