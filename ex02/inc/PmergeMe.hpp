#ifndef SORTER_HPP
# define SORTER_HPP

/******************************************************************************/
/*                            INCLUDES                                        */
/******************************************************************************/

#include <iostream>
#include <sstream>
#include <deque>
#include <vector>
#include <cstdlib>

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

template <typename PrintT>
int	error_msg(int	exitCode, std::string error, PrintT foo)
{
	std::cout << RED << "Error: " << END << error << foo << std::endl;
	return (exitCode);
}

template <typename contType>
void printContainer(contType cont)
{
	typename contType::iterator number;
	for(number = cont.begin(); number != cont.end(); number++)
		std::cout << *number << " ";
}

template <typename T > 
class sorter
{
	private:

		T						initialNumbers;
		T						numbers;
		T						subset0;
		T						subset1;
		typename T::size_type	subsetSize;

	public:
		sorter<T>(){} ;
		sorter(T numbers) : numbers(numbers), initialNumbers(numbers) {};

		sorter(sorter& orig)
		{
			this->subsetSize = orig.subsetSize();
			this->initialNumbers = orig.initialNumbers;
			this->numbers = orig.numbers;
			this->subset0 = orig.subset0;
			this->subset1 = orig.subset1;
		};
		sorter& operator=(const sorter& orig)
		{
			this->subsetSize = orig.subsetSize();
			this->initialNumbers = orig.initialNumbers;
			this->numbers = orig.numbers;
			this->subset0 = orig.subset0;
			this->subset1 = orig.subset1;
			return *this;
		};

		~sorter() {};

		void print(void) { printContainer(this->numbers); };
		void printInitial(void) { printContainer(this->initialNumbers); };

		void push(const std::string& number)
		{
			std::string::const_iterator c = number.begin(), end = number.end();

			if (*c == '+')
				c++;
			for (; c != end; c++)
			{
				if (*c < '0' || *c > '9')
					throw sorterException(error_msg(1, "Invalid input - the string contains non-numeric characters", *c));
			}
			this->push(atoi(number.c_str()));
		};
		void push(unsigned int num) { this->numbers.push_back(num); this->initialNumbers.push_back(num); };

		void sort(void)
		{	
			this->subsetSize = 1;
			while (subsetSize < numbers.size())
			{
				this->doIteration();
				this->subsetSize *= 2;
			}
		}

		void doIteration(void)
		{
			typename T::iterator number = numbers.begin();
			typename T::iterator end = numbers.end();
			typename T::iterator beginSet;

			while (number != end)
			{
				beginSet = number;	
				this->subset0.clear();
				this->subset1.clear();
				for (typename T::size_type i = 0; i < this->subsetSize && number != end; i++)
					this->subset0.push_back(*number++);
				for (typename T::size_type i = 0; i < this->subsetSize && number != end; i++)
					this->subset1.push_back(*number++);
				this->sortSet(beginSet);
			}
		}

		void sortSet(typename T::iterator& beginSet)
		{
			typename T::iterator num0 = this->subset0.begin();
			typename T::iterator end0 = this->subset0.end();
			typename T::iterator num1 = this->subset1.begin();
			typename T::iterator end1 = this->subset1.end();

			while (num0 != end0 || num1 != end1)
			{
				if (num1 == end1)
					*beginSet = *num0++;
				else if (num0 != end0 && *num0 < *num1)
					*beginSet = *num0++;
				else
					*beginSet = *num1++;
				beginSet++;
			}
		}
		class sorterException: public std::exception
		{
			private:
				std::string	_msgError;
			public:
				sorterException(int msgCode):_msgError(""){(void)msgCode;}
				sorterException(std::string msgError): _msgError(msgError){}
				virtual const char *what() const throw()
				{
					return (_msgError.c_str());
				}
				~sorterException(void) throw(){}
		};
};

#endif