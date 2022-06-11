//#include <iostream>
//#include <fstream>
//#include <string>
//#include <exception>
//#include <math.h>
//
//#define _CRT_SECURE_NO_WARNINGS
//
//using namespace std;
//
//struct SNode {
//	string key;
//	SNode* next;
//};
//
//struct Stack
//{
//	SNode* Head;
//	SNode* Tail;
//};
//
////prototype
//void initStack(Stack& s);
//SNode* createNode(const string& data);
//bool isEmpty(const Stack& q);
//SNode* push(Stack& s, const string& data);
//string pop(Stack& s);
//string top(const Stack& s);
//bool printStack(const Stack& s);
//void deleteStack(Stack& s);
//string readFile(const char* filename);
//string* StringToInfix(const string& data, int& size);
//void preliminaryCheck(const string* Infix, int size);
//int32_t Precedence(string x);
//int IsAMathElement(const string& x);
//bool HigherPriority(const string& a, const string& b);
//string* InfixToPostfix(const string* Infix, int32_t& size);
//
//
//void initStack(Stack& s) {
//	s.Head = nullptr;
//	s.Tail = nullptr;
//}
//
//SNode* createNode(const string& data) {
//	return new (std::nothrow) SNode{ data, nullptr };
//}
//
//bool isEmpty(const Stack& q) {
//	return (q.Head==nullptr && q.Tail==nullptr);
//}
//
//SNode* push(Stack& s, const string& data) {
//	SNode* node = createNode(data);
//	if (!node) {
//		return nullptr;
//	}
//	if (isEmpty(s))
//	{
//		s.Head = node;
//		s.Tail = node;
//		return node;
//	}
//	node->next = s.Head;
//	s.Head = node;
//	return node;
//}
//
//string pop(Stack& s) {
//	if (isEmpty(s))
//	{
//		throw "Stack empty, cannot pop!";
//	}
//	if (s.Head == s.Tail)
//	{
//		string x = s.Head->key;
//		delete s.Head;
//		s.Head = nullptr;
//		s.Tail = nullptr;
//		return x;
//	}
//	string x = s.Head->key;
//
//	SNode* node = s.Head;
//	s.Head = s.Head->next;
//	delete node;
//	return x;
//}
//
//string top(const Stack& s) {
//	string top = s.Head->key;
//	return top;
//}
//
//bool printStack(const Stack& s) {
//	if (isEmpty(s))
//	{
//		cout << "Stack is empty!\n";
//		return false;
//	}
//	SNode* node = s.Head;
//	while (node != nullptr)
//	{
//		cout << node->key << " ";
//		node = node->next;
//	}
//	cout << endl;
//	return true;
//}
//
//void deleteStack(Stack& s) {
//	SNode* node = s.Head;
//	while (node != nullptr)
//	{
//		s.Head = s.Head->next;
//		delete node;
//		node = s.Head;
//	}
//	s.Head = nullptr;
//	s.Tail = nullptr;
//}
//
//string readFile(const char* filename) {
//	FILE* fp = nullptr;
//	fopen_s(&fp, filename, "r");
//
//	if (!fp)
//	{
//		throw "Cannot open file!";
//	}
//	int a = 0;
//	string data;
//
//	while (a != '\n')
//	{
//		a = fgetc(fp);
//		data.push_back(char(a));
//	}
//	data.pop_back(); //delete '\n' char from string
//	
//	fclose(fp);
//	return data;
//}
//
//string* StringToInfix(const string& data, int& size) { //separate elements
//	int count = 0;
//	for (int i = 0; i < data.size(); i++)
//	{
//		if (data[i]==' ')
//		{
//			count++;
//		}
//	}
//	size = count + 1;
//	string* Infix = new (std::nothrow) string[size];
//	if (!Infix)
//	{
//		throw invalid_argument("Cannot allocate!");
//	}
//	count = 0;
//	for (int i = 0; i < data.size(); i++)
//	{
//		if (data[i] == ' ')
//		{
//			count++;
//			i++;
//		}
//		Infix[count].push_back(data[i]);
//	}
//	return Infix;
//}
//
//void preliminaryCheck(const string* Infix, int size) {
//	Stack parentheses; //check if amount of "(" == amount of ")"
//	initStack(parentheses);
//	for (int i = 0; i < size; i++)
//	{
//		try {
//			IsAMathElement(Infix[i]);
//		}
//		catch (invalid_argument msg) {
//			throw invalid_argument(msg.what());
//		}
//
//		if (Infix[i] == "(")
//		{
//			push(parentheses, "$");
//		}
//		else if (Infix[i] == ")")
//		{
//			pop(parentheses);
//		}
//		else if (i < (size-1) && Precedence(Infix[i]) == Precedence(Infix[i+1]))
//		{
//			deleteStack(parentheses);
//			throw invalid_argument("Two operands with the same precedence cannot be next to each other.");
//		}
//	}
//	
//	if (!isEmpty(parentheses)) //redundant or missing parentheses
//	{
//		deleteStack(parentheses);
//		throw invalid_argument("Redundant or missing parentheses.");
//	}
//	deleteStack(parentheses);
//
//}
//
//int32_t Precedence(string x)
//{
//	if (x == "(" || x== ")") {
//		return 1;
//	}
//	if (x == "+" || x == "-") {
//		return 2;
//	}
//	if (x == "*" || x == "/" || x == "%" ) {
//		return 3;
//	}
//	if (x == "^")
//	{
//		return 4;
//	}
//	return 0;
//}
//
//int IsAMathElement(const string& x) {
//	if (Precedence(x) != 0)
//	{
//		return 0; //other legit math characters
//	}
//	if (x[0] == '-' || (x[0] > '0' && x[0] < '9')) //check negative number (ex: -7)
//	{
//
//	}
//	else if (x[0] < '0' || x[x.size() - 1] < '0' || x[0] > '9' || x[x.size() - 1] > '9')
//		//check if there is illegal character or dot in wrong place (first or last place)
//	{
//		throw invalid_argument("illegal characters exist.");
//	}
//	int countDot = 0;
//	for (int i = 1; i < x.size(); i++) {
//		if (x[i] == '.')
//		{
//			countDot++;
//		}
//		else if (x[i] < '0' || x[i] > '9') //check if 1 char is number or not
//		{
//			if (Precedence(string(1, x[i]))==0) 
//			{
//				throw invalid_argument("illegal characters exist.");
//			}
//			else
//			{
//				throw invalid_argument("Operands were placed at wrong places.");
//			}
//		}
//	}
//	if (countDot == 0)
//	{
//		return 1; //interger number
//	}
//	if (countDot == 1)
//	{
//		return 2; //real number
//	}
//
//	throw invalid_argument("Too many dot (.) in a number."); //there are >=2 dot in a number
//	
//}
//
//bool HigherPriority(const string& a, const string& b) {
//	int pri_a = Precedence(a);
//	int pri_b = Precedence(b);
//	if (pri_a > pri_b)
//	{
//		return true;
//	}
//	return false;
//}
//
//string* InfixToPostfix(const string* Infix, int32_t& size) {
//	int32_t priority = 0;
//	int i = 0; 
//	int j = 0; //index of Postfix array
//	string* Postfix = new string[size];
//	int num = 0;
//	Stack s;
//	initStack(s);
//	push(s, "$");
//
//	for (; i < size; i++)
//	{
//		try
//		{
//			num = IsAMathElement(Infix[i]);
//
//			if (num == 1 || num == 2)
//			{
//				Postfix[j++] = Infix[i]; //add to Postfix when string is a number
//			}
//			else if (Infix[i] == "(") {
//				push(s, "(");
//			}
//			else if (Infix[i] == "^") {
//				push(s, "^");
//			}
//			else if (Infix[i] == ")") {
//				while (top(s) != "$" && top(s) != "(") {
//					Postfix[j++] = top(s); //store and pop until ( has found
//					pop(s);
//				}
//				pop(s);
//			}
//			else {
//				if (HigherPriority(Infix[i], top(s)))
//					push(s, Infix[i]); //push if precedence is high
//				else {
//					while (top(s) != "$" && !HigherPriority(Infix[i], top(s))) {
//						Postfix[j++] = pop(s); //store and pop until higher precedence is found
//					}
//					push(s, Infix[i]);
//				}
//			}
//		}
//		catch(invalid_argument msg){
//			throw invalid_argument(msg.what());
//		}
//	}
//	while (top(s) != "$") {
//		Postfix[j++] = pop(s);        //store and pop until stack is not empty.
//	}
//	size = j; //update size for Postfix after remove the parentheses
//	return Postfix;
//}
//
//string calculate2Element(const string& a, const string& b, const string& operand) {
//	
//	float a_f = std::stof(a);
//	float b_f = std::stof(b);
//	if (operand == "+")
//	{
//		return to_string(a_f + b_f);
//	}
//	else if (operand == "-")
//	{
//		return to_string(a_f - b_f);
//	}
//	else if (operand == "*")
//	{
//		return to_string(a_f * b_f);
//	}
//	else if (operand == "/")
//	{
//		return to_string(a_f / b_f);
//	}
//	else if (operand == "^")
//	{
//		return to_string(pow(a_f, b_f));
//	}
//	throw invalid_argument("Unknown error.");
//}
//
//string calculatePostfix(string* Postfix, int size) {
//	Stack result;
//	initStack(result);
//
//	int32_t pred = 0;
//
//	string a = " ";
//	string b = " ";
//	
//	int32_t answer_i = 0;
//	float answer_f = 0.0f;
//	for (int i = 0; i < size; i++)
//	{
//		pred = Precedence(Postfix[i]);
//		if (pred==0) //a number
//		{
//			push(result, Postfix[i]);
//		}
//		else if (Postfix[i]=="%")
//		{
//			a = pop(result);
//			b = pop(result);
//			if (IsAMathElement(a) == 2 || IsAMathElement(b) == 2) {
//				throw invalid_argument("Modulo only can be used on 2 integer");
//			}
//			else
//			{
//				answer_i = stoi(b) % stoi(a);
//				push(result, std::to_string(answer_i));
//			}
//		}
//		else {
//			a = pop(result);
//			b = pop(result);
//			push(result, calculate2Element(b, a, Postfix[i]));
//		}
//	}
//	string answer = pop(result);
//	if (!isEmpty(result))
//	{
//		throw "Too much element.";
//	}
//	deleteStack(result);
//	return answer;
//}
//
//
//int main() {
//	FILE* fp = nullptr;
//	fopen_s(&fp, "result.txt", "w");
//
//	if (!fp)
//	{
//		throw "Cannot open file!";
//	}
//	string* Infix = nullptr;
//	string* Postfix = nullptr;
//	string result = " ";
//	try
//	{
//		string data = readFile("infix.txt");
//		int32_t size = 0;
//		Infix = StringToInfix(data, size);
//		preliminaryCheck(Infix, size);
//		Postfix = InfixToPostfix(Infix, size);
//		result = calculatePostfix(Postfix, size);
//		cout << result << endl;
//		delete []Infix;
//		delete[]Postfix;
//		Infix = Postfix = nullptr;
//	}
//	catch (std::exception& msg)
//	{
//		delete[]Infix;
//		delete[]Postfix;
//		Infix = Postfix = nullptr;
//		fputc('0',fp);
//		fputc('\n', fp);
//		fputs(msg.what(), fp);
//		fclose(fp);
//	}
//	
//	fputc('1', fp);
//	fputc('\n', fp);
//	fputs(result.c_str(), fp);
//
//	fclose(fp);
//	return 0;
//}