#include <BitcoinExchange.hpp>

BitcoinExchange::BitcoinExchange(std::string inFileName)
{
	this->_fileDataBase.open(PATH_DATA_BASE);
	if (!this->_fileDataBase.is_open())
		throw BitcoinExchangeException(ERROR_OPEN_FILE);
	this->_inFileName = inFileName;
	checkIfstream(this->_fileDataBase, ' ');
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &obj)
{
	(void)obj;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &obj)
{
	this->_inFileName = obj._inFileName;
	return (*this);
}

BitcoinExchange::~BitcoinExchange(void)
{
	this->_fileDataBase.close();
}


// void	BitcoinExchange::parsingFile(std::string inFileName)
// {
	
// }

void	BitcoinExchange::checkIfstream(std::ifstream &file, char end)
{
	while(file.good() and (file.peek() != end))
		file.get();
	if (file.peek() == end)
		file.get();
	else
		throw BitcoinExchangeException(error_msg(1, ERROR_OPEN_FILE, PATH_DATA_BASE));
}
