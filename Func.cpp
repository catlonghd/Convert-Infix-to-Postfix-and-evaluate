#include "Header.h"


//read expression from file
string readFile(const char* filename) {
	FILE* f = fopen(filename, "r");
	if (!f) {
		throw invalid_argument("Cannot open file!");
	}

	char c;
	string infix;

	while ((c = fgetc(f)) != '\n') {
		infix += c;
	}
	
	fclose(f);
	return infix;
}


int32_t getPrecedence(char op) {
	int32_t weight = 0;
	if (op == '+' || op == '-')
		weight = 1;
	else if (op == '*' || op == '/' || op == '%')
		weight = 2;
	else if (op == '^')
		weight = 3;
	return weight;
}


bool higherPrecedenceValidate(char operator1, char operator2) {
	int32_t op1 = getPrecedence(operator1);
	int32_t op2 = getPrecedence(operator2);
	return op1 >= op2 ? true : false;
}


bool isOperator(char c) {
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^')
		return true;
	return false;
}


bool isNumberSign(char c) {
	if (c == '+' || c == '-')
		return true;
	return false;
}



//check if character is digit or not
bool isDigit(char c) {
	if (c >= '0' && c <= '9')
		return true;
	return false;
}



/*
I don't split a separate function to check if the expression is valid because 
when converting the infix to the postfix, it will go through each character, 
from which it is easy to determine if the character is valid or not and save memory
*/
string convertInfix2Postfix(string infix) {
	//Check if expression is null or not
	if (infix.length() == 0)
		throw invalid_argument("Expression is null!");


	string postfix;//to store the posfix expresstion
	bool isOperatorRepeated = false;//flag to check if operators are consecutive or not
	bool isOperandRepeared = false;//flag to check if operands are consecutive or not
	bool isSpacedApart = true;//flag to check if numbers and operators are separated by space
	

	Stack_Char operators;//used to store operators in infix
	init(operators);

	Stack_Char negPosChar;//used to store negative or positive sign of a number
	init(negPosChar);


	//loop to the last character of the expression
	for (string::size_type i = 0; i < infix.length(); i++) {
		//Check space
		if (infix[i] == ' ') {
			isSpacedApart = true;
		}

		//if current character is operator
		else if(isOperator(infix[i])) {
			if (!isSpacedApart) {
				deleteStack(operators);
				deleteStack(negPosChar);
				throw invalid_argument("Numbers and operators must be separated by space!");
			}
			
			//if operator repeated
			if (isOperatorRepeated && infix[i + 1] == ' ') {
				deleteStack(operators);
				deleteStack(negPosChar);
				throw invalid_argument("Repeated operator!");
			}

			//if character is sign of a number
			else if (isNumberSign(infix[i]) && isDigit(infix[i + 1])) {
				push(negPosChar, infix[i]);
				continue;
			}
			

			while (!isEmpty(operators) && higherPrecedenceValidate(top(operators), infix[i])) {
				postfix += top(operators);
				postfix += ' ';
				pop(operators);
			}

			push(operators, infix[i]);
			isOperatorRepeated = true;
			isOperandRepeared = false;
			isSpacedApart = false;
		}

		//if current character is number
		else if(isDigit(infix[i])) {
			if (!isSpacedApart) {
				deleteStack(operators);
				deleteStack(negPosChar);
				throw invalid_argument("Numbers and operators must be separated by space!");
			}

			if (isOperandRepeared) {
				deleteStack(operators);
				deleteStack(negPosChar);
				throw invalid_argument("Repeated operand!");
			}


			string temp;//used to store the final number if the number has more than one digit
			int32_t sign = 1;//sign of number

			//get the final sign of the number
			while (!isEmpty(negPosChar)) {
				sign *= (top(negPosChar) == '-') ? -1 : 1;
				pop(negPosChar);
			}
			if (sign < 0)
				temp += '-';
			

			int countDot = 0;//count dot of decimal number
			//Maybe a number has more than one digit
			while ((i < infix.length()) && (isDigit(infix[i]) || infix[i] == '.')){//if '.' in the number, it is decimal number
				temp += infix[i];
				countDot += (infix[i] == '.') ? 1 : 0;
				i++;
			}
			i--;//back to 1 step unless we will skip one character in the next loop 

			//if a number end with '.', it is not a correct structure of decimal number. Ex: 2. or 4.
			if (!isDigit(infix[i])) {
				deleteStack(operators);
				deleteStack(negPosChar);
				throw invalid_argument("Wrong structure of decimal number!");
			}

			//if a number has too many '.'
			if (countDot >= 2) {
				deleteStack(operators);
				deleteStack(negPosChar);
				throw invalid_argument("Wrong structure of decimal number!");
			}
			

			postfix += temp;
			postfix += ' ';
			isOperatorRepeated = false;
			isOperandRepeared = true;
			isSpacedApart = false;
		}

		//if current character is '('
		else if (infix[i] == '(') {
			if (!isSpacedApart) {
				deleteStack(operators);
				deleteStack(negPosChar);
				throw invalid_argument("Numbers and operators must be separated by space!");
			}

			push(operators, infix[i]);
			isOperatorRepeated = false;
			isOperandRepeared = false;
			isSpacedApart = false;
		}
			
		//if current character is ')'
		else if (infix[i] == ')') {
			if (!isSpacedApart) {
				deleteStack(operators);
				deleteStack(negPosChar);
				throw invalid_argument("Numbers and operators must be separated by space!");
			}

			while (!isEmpty(operators) && top(operators) != '(') {
				postfix += top(operators);
				postfix += ' ';
				pop(operators);
			}

			//after meet and pop close bracket, if stack is empty, then it's false
			if (isEmpty(operators)) {
				deleteStack(operators);
				deleteStack(negPosChar);
				throw invalid_argument("Missing opening bracket!");
			}
			//pop ')' from stack
			pop(operators);
			isOperatorRepeated = false;
			isOperandRepeared = false;
			isSpacedApart = false;
		}

		//check invalid character
		else {
			deleteStack(operators);
			deleteStack(negPosChar);
			throw invalid_argument("Invalid character in expression!");
		}
	}

	//pop the remaining operators
	while (!isEmpty(operators)) {

		//If the missing close bracket, throw exception
		if (top(operators) == '(') {
			deleteStack(operators);
			deleteStack(negPosChar);
			throw invalid_argument("Missing closing bracket!");
		}
		postfix += top(operators);
		postfix += ' ';
		pop(operators);
	}

	deleteStack(operators);
	deleteStack(negPosChar);
	
	return postfix;
}


//check if a float value is equivalent to an integer value
bool isInterger(float n) {
	int32_t a = n;
	if (n - a > 0)
		return false;
	return true;
}

//Ex: 1.3400 -> 1.32
void removeTrailingZerosAfterDecimalPoint(string& str) {
	bool isInt = isInterger(stof(str));

	string::size_type s = str.length() - 1;
	for (s; s != '.'; --s)
	{
		if (str[s] == '0') 
			str.erase(s, 1);
		else 
			break;
	}
	if (isInt == true)
		str.erase(s, 1);
}



//check if the '.' character is in the number
bool isDecimalPointInNumber(string s) {
	for (string::size_type i = 0; i < s.length(); i++) {
		if (s[i] == '.')
			return true;
	}
	return false;
}

//function to evaluate postfix expresstion
string evaluatePostfix(string postfix) {
	Stack_String res;
	init(res);

	//loop to the last charater of expression
	for (string::size_type i = 0; i < postfix.length(); i++) {
		if (postfix[i] == ' ')
			continue;
		//if current character is operator
		else if (isOperator(postfix[i]) && postfix[i + 1] == ' ') {
			float result2Nums = 0;

			if (isEmpty(res)) {
				deleteStack(res);
				throw invalid_argument("Operator must be between 2 numbers!");
			}
			string num2 = top(res);

			pop(res);
			if (isEmpty(res)) {
				deleteStack(res);
				throw invalid_argument("Operator must be between 2 numbers!");
			}
			string num1 = top(res);

			pop(res);
			switch (postfix[i])
			{
			case '+':
				result2Nums = stof(num1) + stof(num2);
				break;
			case '-':
				result2Nums = stof(num1) - stof(num2);
				break;
			case '*':
				result2Nums = stof(num1) * stof(num2);
				break;
			case '/':
				//Cannot divide a number by 0
				if (stof(num2) == 0) {
					deleteStack(res);
					throw invalid_argument("Cannot divide a number by 0!");
				}
				result2Nums = stof(num1) / stof(num2);
				break;
			case '^':
				result2Nums = pow(stof(num1), stof(num2));
				break;
			case '%':
				if (isDecimalPointInNumber(num1) || isDecimalPointInNumber(num2)) {
					deleteStack(res);
					throw invalid_argument("Modulus operator cannot be applied on float value!");
				}
				result2Nums = stoi(num1) % stoi(num2);
				break;
			default:
				break;
			}

			string temp = to_string(result2Nums);
			removeTrailingZerosAfterDecimalPoint(temp);
			push(res, temp);
		}
		//if current character is number
		else {
			string temp;
			while (postfix[i] != ' ' && postfix[i] != '\0') {
				temp += postfix[i];
				i++;
			}
			i--;//back to 1 step unless we will skip one character in the next loop 
			push(res, temp);
		}
	}

	string result = top(res);
	deleteStack(res);
	return result;
}



//write result to file
void writeFile(const char* filename, char c, string result) {
	FILE* f = fopen(filename, "w");
	if (!f) {
		throw invalid_argument("Cannot open file!");
	}

	fputc(c, f);//write 1 if the expression is correct and can be calculated, 0 if opposite
	fputc('\n', f);

	for (string::size_type i = 0; i < result.length(); i++) {
		fputc(result[i], f);
	}
	fclose(f);
}




