#include "../include/PmergeMe.hpp"

int main(int argc, char *argv[])
{
	(void)argc;
	PmergeMe meme;
	std::istringstream iss(argv[1]);
	std::string token;
	std::vector<int> litania; //still unclear whether this should be in the class itself but for now lets keep it here
	while (getline(iss, token, ' '))
	{
		litania.push_back(std::stoi(token));
		//all sorts of error checks 
	}
	meme.doMagic(litania);
}
