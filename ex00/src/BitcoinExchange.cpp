#include "../include/BitcoinExchange.hpp"

//remember to throw here
BitcoinExchange::BitcoinExchange()
{
	std::ifstream data("data.csv");
	if (data.is_open() == false)
	{
		std::cerr << "Failed to open file" << std::endl;
		//throw!!
	}
	std::string line;
	std::getline(data, line);
	if (line.empty())
		std::cerr << "Database is empty" << std::endl;
	if (line != "date,exchange_rate")
		std::cerr << "Format is wrong" << std::endl;
	while (std::getline(data, line))
	{
		std::pair<std::string, float> pair;
		int separator_pos = line.find(",");
		pair.first = line.substr(0, separator_pos);
		pair.second = std::stof(line.substr(separator_pos + 1));
		// std::cout << "First: " << pair.first << std::endl;
		// std::cout << "Second: " << pair.second << std::endl;
		this->data.insert(pair);
	}
}
