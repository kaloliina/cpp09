#include "../include/RPN.hpp"

int main(int argc, char *argv[])
{
	(void)argc;
	RPN rpn;
	std::istringstream iss(argv[1]);
	std::string token;
	std::regex pattern(R"(^[0-9+\-/*]$)");
	std::regex operatorpattern(R"(^[+\-/*]$)");
	int number1, number2, result;
	while (getline(iss, token, ' '))
	{
		if (std::regex_match(token, pattern) == false)
		{
			std::cerr << "Error" << std::endl;
			return 1;
		}
		if (std::regex_match(token, operatorpattern) == true)
		{
			//what if no more numbers, error???
			number2 = rpn.stack.top();
			rpn.stack.pop();
			number1 = rpn.stack.top();
			rpn.stack.pop();
			if (token == "+")
				result = number1 + number2;
			else if (token == "-")
				result = number1 - number2;
			else if (token == "/")
				result = number1 / number2;
			else if (token == "*")
				result = number1 * number2;
			rpn.stack.push(result);
		}
		else
			rpn.stack.push(std::stoi(token));
	}
	if (rpn.stack.size() != 1)
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}
	std::cout << rpn.stack.top() << std::endl;
	return 0;
}
