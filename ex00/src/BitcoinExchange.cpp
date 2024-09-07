#include <BitcoinExchange.hpp>

const	std::map<unsigned int, unsigned int> BitcoinExchange::DAYS_IN_A_MONTH = BitcoinExchange::INITIALIZE_DAYS_IN_A_MONTH();

std::map<unsigned int, unsigned int> BitcoinExchange::INITIALIZE_DAYS_IN_A_MONTH()
{
	std::map<unsigned int, unsigned int> new_map;
	new_map[1] = 31;
	new_map[2] = 28;
	new_map[3] = 31;
	new_map[4] = 30;
	new_map[5] = 31;
	new_map[6] = 30;
	new_map[7] = 31;
	new_map[8] = 31;
	new_map[9] = 30;
	new_map[10] = 31;
	new_map[11] = 30;
	new_map[12] = 31;
	return (new_map);
}

bool customAtoi(std::string::const_iterator& c, std::string::const_iterator end, unsigned int& dest)
{
	dest = 0;
	while (c != end && *c != '-')
	{
		if ( *c < '0' || *c > '9')
			return (false);
		dest *= 10; 
		dest += *c - '0'; 
		c++;
	}
	return (dest != 0);
}

BitcoinExchange::BitcoinExchange(std::string inFileName)
{
	this->_fileDataBase.open(PATH_DATA_BASE);
	if (!this->_fileDataBase.is_open())
		throw BitcoinExchangeException(ERROR_OPEN_FILE);
	this->_inFileName = inFileName;
	BitcoinExchange::loadPrices(this->_fileDataBase, this->_dataBase);
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

void BitcoinExchange::cleanBlank(std::string &inpStr)
{
	while(inpStr.size() > 0 && inpStr[0] == ' ')
	{
		inpStr.erase(0, 1);
	}
	while(inpStr.size() > 0 && inpStr[inpStr.size()-1] == ' ')
		inpStr.erase(inpStr.size()-1, 1);
}

void	BitcoinExchange::skipUntil(std::ifstream &file, char end)
{
	while(file.good() and (file.peek() != end))
	{
		file.get();
	}
	if (file.peek() == end)
		file.get();
}

bool BitcoinExchange::loadPrices(std::ifstream &fileDataBase, std::map<unsigned int, float> &dataBase)
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
	std::string date_str;
	int			date;

	date_str = BitcoinExchange::getDateStrFromFile(fileDataBase, separator);
	if (!date_str.size() and !fileDataBase.good())
		return (0);
	date = BitcoinExchange::dateStrToInt(date_str);
	if (!date)
	{
		error_msg(1, ERROR_INVALID_DATE, date_str);
		return (0);
	}

	return (date);
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

bool BitcoinExchange::loadLinePrices(std::ifstream &fileDataBase, std::map<unsigned int, float> &dataBase)
{
	unsigned int		date;
	float	price;

	date = BitcoinExchange::parseDataKeyFromDataBase(fileDataBase, ',');
	if (!date or !fileDataBase.good())
		return (false);

	try
	{
		price = BitcoinExchange::parseDataValueFromDataBase(fileDataBase);
	}
	catch(const std::invalid_argument &e)
	{
		return (false);
	}
	catch(const std::out_of_range &e)
	{
		return (false);
	}

	dataBase[date] = price;
	return (true);
}

std::string BitcoinExchange::getDateStrFromFile(std::ifstream &fileDataBase, char separator)
{
	std::string	date_str;
	char	c;

	fileDataBase.get(c);
	while (fileDataBase.good() and c != separator and c != '\n')
	{
		date_str.append(1, c);
		fileDataBase.get(c);
	}

	if (c == '\n')
		fileDataBase.putback('\n');

	BitcoinExchange::cleanBlank(date_str);
	return (date_str);
}

bool BitcoinExchange::isLeap(unsigned int year)
{
	if ( year % 400 == 0)
		return (1);
	if (year % 100 == 0)
		return (0);
	return (year % 4 == 0);
}

unsigned int BitcoinExchange::monthToDay(unsigned int month)
{
	try
	{
		return BitcoinExchange::DAYS_IN_A_MONTH.at(month);
	}
	catch (std::out_of_range& exc)
	{
		return (0);
	}
}

unsigned int BitcoinExchange::monthAcumulatedDays(unsigned int month)
{
	int acumulated = 0;
	for(unsigned int i = 1; i < month; i++)
	{
		acumulated +=  BitcoinExchange::monthToDay(i);
	}
	return(acumulated);
}

t_date BitcoinExchange::parseDate(std::string date_str)
{
	std::string::const_iterator	c, end;
	t_date					date;
	
	c = date_str.begin();
	end = date_str.end();

	if (c != end and customAtoi(  c, end, date.year) and
		c != end && customAtoi(++c, end, date.month) and
		c != end && customAtoi(++c, end, date.day) and
		c == end)
		return (date);
	else
	{
		date.year = 0; date.month = 0; date.day = 0;
		return (date);
	}
}

int	BitcoinExchange::dateStrToInt(std::string date_str)
{
	int		result = 0;
	t_date	date = BitcoinExchange::parseDate(date_str);

	if (!date.year or !date.month or !date.day)
		return (0);
	if (date.month < 1 or date.month > 12)
		return (0);
	if (date.day > BitcoinExchange::monthToDay(date.month))
	{
		if (!(BitcoinExchange::isLeap(date.year) and date.day == 29 && date.month == 2))
			return (0);
	}

	if (BitcoinExchange::isLeap(date.year) && date.month > 2)
		result += 1;

	date.year -= 1;
	result +=  ((date.year) / 400) * BitcoinExchange::DAYS_IN_400_YEARS;
	date.year %= 400;
	result +=  ((date.year) / 100) * BitcoinExchange::DAYS_IN_100_YEARS;
	date.year %= 100;
	result +=  ((date.year) / 4) * BitcoinExchange::DAYS_IN_4_YEARS;
	date.year %= 4;
	result +=  ((date.year)) * BitcoinExchange::DAYS_IN_1_YEARS;

	result += BitcoinExchange::monthAcumulatedDays(date.month);
	result += + date.day;
	return (result);
}
