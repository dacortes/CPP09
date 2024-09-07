/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:48:10 by dacortes          #+#    #+#             */
/*   Updated: 2024/09/07 14:46:19 by codespace        ###   ########.fr       */
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
# include <stdexcept>


/******************************************************************************/
/*                            MACROS                                          */
/******************************************************************************/


# define DAYTS_IN_1_YEAR 365
# define DAYTS_IN_4_YEAR 1461
# define DAYTS_IN_400_YEAR 146099

/*	Erros	*/
# define ERROR_INVALID_ARGUMENTS "Invalid arguments: the number of arguments\
must be two: num: "
# define ERROR_TOO_MANY_ARG "too many arguments: the number of arguments\
must be two: num: " 
# define ERROR_OPEN_FILE "open file: "
# define ERROR_PRICE_DATA "invalid price on data "
# define ERROR_INVALID_DATE "invalid date"

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

typedef struct s_date{
	unsigned int year;
	unsigned int month;
	unsigned int day;
} t_date;

class  BitcoinExchange
{
	private:

		BitcoinExchange(void);
		/*
			Attributes
		*/

		std::string						_inFileName;
		std::ifstream 					_fileDataBase;
		std::map<unsigned int, float>	_dataBase;


		static const int	DAYS_IN_1_YEARS = 365;
		static const int	DAYS_IN_4_YEARS = 1461;
		static const int	DAYS_IN_100_YEARS = 36524;
		static const int	DAYS_IN_400_YEARS = 146097;
		const static std::map<unsigned int, unsigned int> DAYS_IN_A_MONTH;

		/*
			Methods
		*/
		static void		parsingFile();

		/* Utils */
		static std::map<unsigned int, unsigned int> INITIALIZE_DAYS_IN_A_MONTH();
		static void		cleanBlank(std::string &inpStr);
		static void		skipUntil(std::ifstream &file, char end);
		static bool 	loadPrices(std::ifstream &fileDataBase, std::map<unsigned int, float> &dataBase);
		static bool 	loadLinePrices(std::ifstream &fileDataBase, std::map<unsigned, float> &dataBase);
		static int		parseDataKeyFromDataBase(std::ifstream &fileDataBase, char separator);
		static float	parseDataValueFromDataBase(std::ifstream &fileDataBase);

		static t_date parseDate(std::string date_str);
		static std::string	getDateStrFromFile(std::ifstream &fileDataBase, char separator);
		static int			dateStrToInt(std::string date_str);

		static bool			isLeap(unsigned int year);
		static unsigned int			monthToDay(unsigned int month);
		static unsigned int			monthAcumulatedDays(unsigned int month);
		
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
