#include "../include/BitcoinExchange.hpp"

static void validateLine(std::string line)
{
	std::istringstream iss(line);
	int year, month, day, value;
	char separator1, separator2, separator3;
	iss >> year >> separator1 >> month >> separator2 >> day >> separator3 >> value;
	// std::cout << "Year: " << year << std::endl;
	// std::cout << "Sep1: " << separator1 << std::endl;
	// std::cout << "Month: " << month << std::endl;
	// std::cout << "Sep2: " << separator2 << std::endl;
	// std::cout << "Day: " << day << std::endl;
	// std::cout << "Pipesep: " << separator3 << std::endl;
	// std::cout << "value: " << value << std::endl;
	if (separator1 != '-' || separator2 != '-' || separator3 != '|') // check valid separators
		throw std::runtime_error("bad input => " + line);
	if (std::count(line.begin(), line.end(), ' ') != 2) // check that only 2 spaces
		throw std::runtime_error("bad input => " + line);
	if (line.find(" | ") == std::string::npos)
		throw std::runtime_error("bad input => " + line);
	//do I need to check for tabs etc..? //now it allows if there is 2 spaces AND tabs in addition
	if (!std::chrono::year_month_day{ std::chrono::year{year}, std::chrono::month{static_cast<unsigned int>(month)}, std::chrono::day{static_cast<unsigned int>(day)}}.ok())
		throw std::runtime_error("invalid date => " + line);
}

static void extractInfo(BitcoinExchange& database, std::string line) //rename this function..?
{
	std::pair<std::string, float> pair;
	int separator_pos = line.find("|");
	pair.first = line.substr(0, separator_pos - 1);
	std::string number = line.substr(separator_pos + 2);
	if (std::count(line.begin(), line.end(), '+') > 0)
		throw std::runtime_error("bad input => " + line);	
	if (pair.first < database.data.begin()->first)
	{
		throw std::runtime_error("date out of database scope.");
	}
	if (pair.first > (--database.data.end())->first)
	{
		throw std::runtime_error("date out of database scope.");
	}
	size_t pos;
	try
	{
		pair.second = std::stof(number, &pos);
	}
	catch(const std::exception& e)
	{
		throw std::runtime_error("invalid number.");
	}
	if (number.length() != pos)
	{
		throw std::runtime_error("invalid number.");		
	}
	if (pair.second < 0)
		throw std::runtime_error("not a positive number.");
	if (pair.second > 1000)
		throw std::runtime_error("too large a number.");
	// std::cout << "First: " << pair.first << std::endl;
	// std::cout << "Second: " << pair.second << std::endl;
	auto it = database.data.find(pair.first);
	if (it == database.data.end())
	{
		// std::cout << "No direct match found, finding the closest smaller" << std::endl;
		it = database.data.upper_bound(pair.first);
		--it;
	}
	std::cout << pair.first << " => " << pair.second << " = " << pair.second * it->second << std::endl; //double check this
}

int main(int argc, char *argv[])
{
	(void)argc;
	BitcoinExchange hello;
	std::ifstream MyFile(argv[1]);
	if (MyFile.is_open() == false)
	{
		std::cerr << "Error: failed to open file" << std::endl;
		return 1;
	}
	std::string line;
	std::getline(MyFile, line);
	if (line.empty())
		std::cerr << "Error: input file is empty" << std::endl;
	if (line != "date | value")
		std::cerr << "Error: format example is wrong" << std::endl;
	while (std::getline(MyFile, line))
	{
		try
		{
			validateLine(line);
			extractInfo(hello, line);
		}
		catch(const std::exception& e)
		{
			std::cerr << "Error: " << e.what() << '\n';
		}
	}
}
//dates of database in the future, past
//2011- 01-03 |3
//2011-02+29 | 3
//A valid value must be either a float or a positive integer, between 0 and 1000.
