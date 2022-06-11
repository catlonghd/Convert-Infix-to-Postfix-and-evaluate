#include "Header.h"


int32_t main() {
	try {
		string infix = readFile("infix.txt");
		cout << infix << endl;
		string postfix = convertInfix2Postfix(infix);
		cout << postfix << endl;
		string res = evaluatePostfix(postfix);
		cout << res;
		writeFile("result.txt", '1', res);
	}
	catch (invalid_argument msg) {
		cout << msg.what();
		writeFile("result.txt", '0', msg.what());
	}
	return 0;
}

