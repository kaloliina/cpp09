#include "../include/PmergeMe.hpp"

int main(int argc, char *argv[])
{
	PmergeMe PmergeMe;

	try
	{
		PmergeMe.parseAndStore(argc, argv);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}

	PmergeMe.printVector("Before", PmergeMe.chain, 0);
	//Time
	auto start = std::chrono::high_resolution_clock::now();
	PmergeMe.chain = PmergeMe.doMagic(PmergeMe.chain);
	//Stop time
	auto stop = std::chrono::high_resolution_clock::now();
	PmergeMe.printVector("After", PmergeMe.chain, 0);
	auto duration = std::chrono::duration<double, std::micro>(stop - start).count(); //I guess we can ignore the "time taken for parsing as brief requests specifically for the sorting"
	//But then there is another line that says Of course you have to indicate the time used to perform all your
	//operations, both the sorting part and the data management part. ..?
	std::cout << "Time to process a range of " << PmergeMe.numberOfElements << " elements with std::vector : " << duration << " us" << std::endl;
}
