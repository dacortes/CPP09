#ifndef RPN_HPP
# define RPN_HPP
/******************************************************************************/
/*                            INCLUDES                                        */
/******************************************************************************/

# include <cstdlib>
# include <string>
# include <iostream>
# include <stdexcept>
# include <stack>

/******************************************************************************/
/*                            MACROS                                          */
/******************************************************************************/

/*	Erros	*/
# define ERROR_INVALID_ARGUMENTS "Invalid arguments: the number of arguments\
must be two: num: "
# define ERROR_TOO_MANY_ARG "too many arguments: the number of arguments\
must be two: num: " 

/******************************************************************************/
/*                            COLORS                                          */
/******************************************************************************/

# define END "\033[m"             
# define RED "\033[1m\033[1;31m"
# define GREEN "\033[1m\033[1;32m"
# define YELLOW "\033[1m\033[1;33m"
# define BLUE "\033[1;34m"
# define TUR "\033[1m\033[1;35m"
# define CYAN "\033[1;36m"
# define ORANGE "\033[1m\033[38;5;208m"
# define PURPLE "\033[1m\033[38;5;128m"


class RPN
{
	private:
		std::stack<float> operandStack;
		bool doOperation(char op);
	public:

		RPN(void) {};
		RPN &operator=(const RPN &obj);
		RPN(const RPN &obj);
		~RPN(void) {};

		void	cleanBlank(std::string &str);
		float	calculate(std::string input);

		class RPNException: public std::exception
		{
			private:
				std::string	_msgError;
			public:
				RPNException(int msgCode):_msgError(""){(void)msgCode;}
				RPNException(std::string msgError): _msgError(msgError){}
				virtual const char *what() const throw()
				{
					return (_msgError.c_str());
				}
				~RPNException(void) throw(){}
		};
};

template <typename PrintT>
int	error_msg(int	exitCode, std::string error, PrintT foo)
{
	std::cout << RED << "Error: " << END << error << foo << std::endl;
	return (exitCode);
}

#endif