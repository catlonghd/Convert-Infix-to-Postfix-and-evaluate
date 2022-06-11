#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include "Stack_String.h"
#include "Stack_Char.h"


using namespace std;


string readFile(const char* filename);
string convertInfix2Postfix(string infix);
string evaluatePostfix(string postfix);
void writeFile(const char* filename, char c, string res);