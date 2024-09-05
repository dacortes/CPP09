/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:48:10 by dacortes          #+#    #+#             */
/*   Updated: 2024/09/05 15:29:01 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

/******************************************************************************/
/*                            INCLUDES                                        */
/******************************************************************************/

# include <map>
# include <cstdlib>
# include <string>
# include <ostream>
# include <iostream>
# include <sstream>
# include <fstream>
# include <float.h>

/******************************************************************************/
/*                            MACROS                                          */
/******************************************************************************/

/*	Erros	*/
# define ERROR_INVALID_ARGUMENTS "Invalid arguments: the number of arguments\
must be two: num: "
# define ERROR_TOO_MANY_ARG "too many arguments: the number of arguments\
must be two: num: " 
# define ERROR_OPEN_FILE "open file: "

/*	Utils	*/
# define PATH_DATA_BASE "data.csv"

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

/******************************************************************************/
/*                            CLASS                                           */
/******************************************************************************/

class  BitcoinExchange
{
	private:

		BitcoinExchange(void);
		/*
			Attributes
		*/

		std::string	_inFileName;
		std::map<std::string, float> _dataBase;
		std::ifstream _fileDataBase;

		/*
			Methods
		*/
		static void	parsingFile();
		static void	checkIfstream(std::ifstream &file, char end);
		
	public:
		/*
		 * Orthodox Canonical Form
		*/
		BitcoinExchange(const BitcoinExchange &obj);
		BitcoinExchange(std::string inFileName);
		BitcoinExchange	&operator=(const BitcoinExchange &obj);
		~ BitcoinExchange(void);
		class BitcoinExchangeException: public std::exception
		{
			private:
				std::string	_msgError;
			public:
				BitcoinExchangeException(int msgCode):_msgError(""){(void)msgCode;}
				BitcoinExchangeException(std::string msgError): _msgError(msgError){}
				virtual const char *what() const throw()
				{
					return (_msgError.c_str());
				}
				~BitcoinExchangeException(void) throw(){}
		};
};

template <typename PrintT>
int	error_msg(int	exitCode, std::string error, PrintT foo)
{
	std::cerr << RED << "Error: " << END << error << foo << std::endl;
	return (exitCode);
}

#endif
