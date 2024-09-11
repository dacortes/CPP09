# include <RPN.hpp>

RPN &RPN::operator=(const RPN &obj)
{
	this->operandStack = obj.operandStack;
	return (*this);
}

RPN::RPN(const RPN &obj)
{
	*this = obj;
}

void RPN::cleanBlank(std::string &str)
{
	for (std::string::iterator c = str.begin(); c != str.end();)
	{
		if (*c == ' ' || *c == '\t')
			c = str.erase(c);
		else
			++c;
	}
}

 float RPN::calculate(std::string input) 
 {
	cleanBlank(input);
	for (std::string::iterator currOperand = input.begin(); currOperand != input.end(); ++currOperand)
	{
		if (*currOperand >= '0' && *currOperand <= '9')
			operandStack.push(*currOperand - '0');
		else if (doOperation(*currOperand))
                continue;
		else
            throw RPN::RPNException(error_msg(1, "Invalid character encountered in expression.", ""));
	}
    if (operandStack.size() != 1)
            throw RPN::RPNException(error_msg(1, "The stack should contain exactly one element at the end.", ""));
	return operandStack.top();
}

 bool RPN::doOperation(char op)
 {
	if (operandStack.size() < 2)
		throw RPNException(error_msg(1,"Not enough operands for operation.", ""));

	float operand0 = operandStack.top();
    operandStack.pop();
	float operand1 = operandStack.top();
	operandStack.pop();

	switch(op)
	{
		case '+':
			operandStack.push(operand1 + operand0);
			return true;
		case '-':
			operandStack.push(operand1 - operand0);
			return true;
		case '*':
			operandStack.push(operand1 * operand0);
			return true;
		case '/':
			operandStack.push(operand1 / operand0);
			return true;
		default:
			return false;
    }
}