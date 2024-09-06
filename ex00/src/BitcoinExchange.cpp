#include <BitcoinExchange.hpp>

BitcoinExchange::BitcoinExchange(std::string inFileName)
{
	this->_fileDataBase.open(PATH_DATA_BASE);
	if (!this->_fileDataBase.is_open())
		throw BitcoinExchangeException(ERROR_OPEN_FILE);
	this->_inFileName = inFileName;
	skipUntil(this->_fileDataBase, '\n');
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &obj)
{
	*this = obj;
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

void	BitcoinExchange::skipUntil(std::ifstream &file, char end)
{
	std::ostringstream os;
	while(file.good() and (file.peek() != end))
	{
		//file.get();
		char c = file.get();
		os << c;
	}
	std::cout << "Stream content: " << os.str() << std::endl;
	if (file.peek() == end)
		file.get();
}

bool BitcoinExchange::loadPrices(std::ifstream &fileDataBase, std::map<int, int> &dataBase)
{
	skipUntil(fileDataBase, '\n');
	while (fileDataBase.good())
	{
		if (!BitcoinExchange::loadLinePrices(fileDataBase, dataBase))
			skipUntil(fileDataBase, '\n');
	}
	return (true);
}

int	BitcoinExchange::parseDataKeyFromDataBase(std::ifstream &fileDataBase, char separator)
{

}

float BitcoinExchange::parseDataValueFromDataBase(std::ifstream &fileDataBase)
{
	float		price;
	std::string price_str;
	char		insert;

	fileDataBase.get(insert);
	while (fileDataBase.good() and insert != '\n')
	{
		price_str.append(1, insert);
		fileDataBase.get(insert);
	}
	
	try
	{
		price = std::atof(price_str.c_str());
	}
	catch (std::invalid_argument& e)
	{
		error_msg(1, ERROR_PRICE_DATA, price_str); 
		throw (e);
	}
	catch ( std::out_of_range& e)
	{
		error_msg(1, ERROR_PRICE_DATA, price_str);
		throw (e);
	}
	
	return (price);
}

bool BitcoinExchange::loadLinePrices(std::ifstream &fileDataBase, std::map<int, int> &dataBase)
{
	int		date;
	float	price;

	date = BitcoinExchange::parseDataKeyFromDataBase(fileDataBase, ',');
	if (!date or !fileDataBase.good())
		return (false);
	try
	{
		price = BitcoinExchange::parseDataValueFromDataBase(fileDataBase);
	}
	catch(const std::exception& e)
	{
		return (false);
	}
	dataBase[date] = price;
	return (true);
}


