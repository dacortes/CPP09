#include <BitcoinExchange.hpp>

BitcoinExchange::BitcoinExchange(void){}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &obj)
{
	(void)obj;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &obj)
{
	(void)obj;
	return (*this);
}

void	BitcoinExchange::parsing_file()
