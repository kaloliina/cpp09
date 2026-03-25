#include "../include/PmergeMe.hpp"

int main(int argc, char *argv[])
{
	PmergeMe meme;
	std::stringstream ss;
	size_t num_of_elements = 0;
	if (argc < 2)
		std::cerr << "Expected Input: ./PmergeMe <Numbers to Sort>" << std::endl;
	for (int i = 1; i < argc; i++)
	{
		ss << argv[i] << ' ';
		num_of_elements++;
	}
	std::cout << "Number of Elements: " << num_of_elements << std::endl;
	std::string token;
	std::vector<int> litania; //still unclear whether this should be in the class itself but for now lets keep it here
	size_t pos;

	while (getline(ss, token, ' '))
	{
		try
		{
			litania.push_back(std::stoi(token, &pos));
			if (token.length() != pos)
				throw std::runtime_error("Problemos mi amiga");
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
			return 1;
		}
	}
	//Before and afters
	std::cout << "Before: " << ss.str() << std::endl;
	//Time
	auto start = std::chrono::high_resolution_clock::now();
	litania = meme.doMagic(litania);
	//Stop time
	auto stop = std::chrono::high_resolution_clock::now();
	std::cout << "After:";
	for (size_t i = 0; i < litania.size(); i++)
	{
		std::cout << " ";
		std::cout << litania[i];
	}
	std::cout << std::endl;
	//Time to process (add other container as well)
	auto duration = std::chrono::duration<double, std::micro>(stop - start).count(); //I guess we can ignore the "time taken for parsing as brief requests specifically for the sorting"
	//But then there is another line that says Of course you have to indicate the time used to perform all your
	//operations, both the sorting part and the data management part. ..?
	std::cout << "Time to process a range of " << num_of_elements << " elements with std::vector : " << duration << " us" << std::endl;
}

//Need to look if there is a specific reason why we should block person from inputting duplicates.
