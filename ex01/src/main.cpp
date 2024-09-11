#include <RPN.hpp>

void parsing_arguments(int numArguments)
{
	if (numArguments < 2)
		std::exit(error_msg(1, ERROR_INVALID_ARGUMENTS, numArguments));
	if (numArguments > 2)
		std::exit(error_msg(1, ERROR_TOO_MANY_ARG, numArguments));
}

int main(int ac, char **av)
{
	(void)av;
	RPN foo;
	parsing_arguments(ac);
	try
	{
		std::cout << foo.calculate(av[1]) << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what();
	}	
	return (EXIT_SUCCESS);
}