#include "../include/PmergeMe.hpp"

void PmergeMe::parseAndStore(int argc, char *argv[])
{
	std::stringstream ss;
	if (argc < 2)
		throw std::runtime_error("Expected Input: ./PmergeMe <Numbers to Sort>");
	for (int i = 1; i < argc; i++)
	{
		ss << argv[i] << ' ';
	}
	std::string token;
	size_t pos;

	while (getline(ss, token, ' '))
	{
		chain.push_back(std::stoi(token, &pos));
		if (token.length() != pos)
			throw std::runtime_error("Problemos mi amiga");
	}
	numberOfElements = chain.size();
	std::cout << "Number of Elements: " << numberOfElements << std::endl;
}

//Might be good to add debug note on number of comparisons etc:D

/*
We use binary search in order to find the correct position for the number in chain.
- We have a parameter called ceiling. This is the max range that we are searching. Every number has it's pair in main chain,
and we know we only need to search in the range that comes before that. However, if we have our unpaired value, the "extra", in the pend
chain, we have to search the entire range in that case.
- We start by getting the mid point of the range, if numberToInsert is bigger than the number in the middle range,
we know we need to search the upper range section. If it's smaller, we search the smaller range section.
We do this as long as "low" and "ceiling" match, meaning we've found the correct position.
*/
int PmergeMe::binarySearch(std::vector<int> &numbers, int numberToInsert, int ceiling)
{
	int low = 0;
	while (low <= ceiling)
	{
		int mid = low + (ceiling - low) / 2;
		if (numbers[mid] < numberToInsert)
			low = mid + 1;
		else
			ceiling = mid - 1;
	}
	return low;
}

/*
We use Jacobsthal sequence together with binary search to alleviate the number of comparisons needed in order to find
the right position in the sorting chain. //Do more research on this one because it's still a bit tricky to grasp
First we generate Jacosthal sequence:
- 0, 1, 3, 5, 11... where 0 and 1 are starting numbers and the calculation goes by: current = previous + 2 * previous of the previous
- We only need to calculate the sequence to the point where the number is smaller or equal to the size of the pend??? chain.

Then we use the Jacobsthal sequence and make the correct insertion order
- For that we use the following formula: insert formula here
- So for example, we start with 1, then the in insertion order will be 3, after this we will insert all the values between 1 and 3, meaning 2.
- So insertion order becomes 1, 3, 2, 5, 4...
- If there are remaining values left (size is bigger than the biggest value we got from Jacobsthal sequence), we insert them in the end.
My initial question was why not to generate one more number to the Jacobsthal sequence, but if we did so, we would be inserting unnecessary/out of bound
values.
*/
std::vector<int> getInsertionOrder(size_t size)
{
	//Generate Jacobsthal Sequence
	std::vector<int> sequence;
	size_t prev = 1;
	size_t prevOfPrev = 0;
	size_t curr = 0;
	while (curr <= size)
	{
		curr = prev + (2 * prevOfPrev);
		if (curr > size)
			break ;
		sequence.push_back(curr);
		prevOfPrev = prev;
		prev = curr;
	}

	//Generate Insertion Order
	std::vector<int> order;
	order.push_back(1);
	for (size_t i = 1; i < sequence.size(); i++)
	{
		order.push_back(sequence[i]);
		for (int y = sequence[i - 1] + 1; y < sequence[i]; y++)
			order.push_back(y);
	}

	//Push the remaining numbers (outside of Jacobsthal sequence) to the order. //Still a bit unclear WHY we would insert them in reverse order
	int last;
	last = sequence.back();
	for (int i = size; i > last; --i)
		order.push_back(i);
	return order;
}

[[maybe_unused]]
void	PmergeMe::printVector(const std::string& message, const std::vector<int> chain, bool newLine)
{
	std::cout << message << ": ";
	for (int x: chain)
	{
		std::cout << x << " ";
	}
	std::cout << std::endl;
	if (newLine == true)
		std::cout << std::endl;
}

[[maybe_unused]]
void	PmergeMe::printPairs(const std::string& message, const std::vector<std::pair<int, int>> pairs, int extra)
{
	std::cout << message << ": ";
	for (auto x: pairs)
	{
		std::cout << "[ " << x.first << ", " << x.second << " ] ";
	}
	std::cout << std::endl;
	if (extra != -1)
		std::cout << "Extra : " << extra << std::endl;
}

/*
And this is where the magic happens! This function accepts the vector of numbers as a parameter and gets called recursively (more on that soon).
This function can be roughly divided into X sections:
1. Splitting the numbers vector into pairs.
- If we receive 30, 49, 60, 1, 31, 29, 46, 13, 8, we will split this into another vector of pairs: [30, 49], [60, 1], [31, 29], [46, 13]. If there is one more element that has no pair, we mark is as extra.

2. Dividing the pairs into winners (bigger) chain and losers (smaller) chain. If there was an extra, unpaired, value, we insert this in the end of losers chain.

3. Repeat the magic! We do steps 1 and 2 as long as we have more than 1 element in the main chain.

4. Now we are at the stage where we go up in the recursion chain, meaning we have a sorted main chain. However, our pend chain is still matcing the old unsorted main. So now we need to match
the pend chain to the new order in main chain.

5. Our main chain and pend chain are now in sync and it's time to find the correct insertion order by using the Jacobsthal sequence.

6. Insert pend chain's elements according to the Jacobsthal's sequence.

7. Now we either proceed going up in the recursion chain and proceed with numbers 4-6. Or if we have completed the recursion, we return the completely sorted main!
*/
std::vector<int> PmergeMe::doMagic(std::vector<int> numbers)
{
	//Handles the recursion, if main chain has only one element left, it's time to start going up the recursion chain.
	if (numbers.size() <= 1)
		return numbers;
	
	//Divide numbers into pairs.
	int extra = -1;
	int a, b; // a larger, b smaller. Expected [b, a]...
	std::vector<std::pair<int, int>> datu;
	for (size_t i = 1; i < numbers.size(); i+=2)
	{
		a = numbers[i - 1];
		b = numbers[i];
		if (a < b)
			datu.push_back(std::make_pair(a, b));
		else
			datu.push_back(std::make_pair(b, a));	
	}
	if (numbers.size() % 2 == 1)
		extra = numbers[numbers.size() - 1];
	DEBUG_PRINT(printPairs, "Pairs", datu, extra);

	//Divide the pairs into winners and losers chain.
	std::vector<int> main;
	std::vector<int> pend;
	for (auto &p: datu)
	{
		main.push_back(p.second);
		pend.push_back(p.first);
	}
	if (extra != -1) //Actually I dont think we even have to add it here, maybe good for debug clarity? But extra is more important in the newPend section
		pend.push_back(extra);

	//DEBUG - could there be a nicer way to handle all of these debug things.. maybe we can find similarities with other debug parts and make a separate function out of them?
	DEBUG_PRINT(printVector, "Main Chain", main, 0);
	DEBUG_PRINT(printVector, "Pend Chain", pend, 1);

	//Repeat steps 1 & 2 as long as we have more than 1 elements in the main chain.
	std::vector<int> sortedMain = doMagic(main);
	//At this point, we would either have 1 element in the main chain (as we are going up the recursion levels) or we would have sorted main chain as we are climbing up the recursion and sorting as we go.

	//Adjust the pend chain's order to match with the new sorted main chain! So ensure, that the pairs match.
	std::vector<int> newPend;
	for (size_t i = 0; i < sortedMain.size(); ++i)
	{
		for (size_t x = 0; x < datu.size(); ++x)
		{
			if (sortedMain[i] == datu[x].second)
			{
				newPend.push_back(datu[x].first);
				break ;
			}
		}
	}
	//If there was an unpaired element, add that to the pend chain.
	if (extra != -1)
		newPend.push_back(extra);
	pend = newPend;
	DEBUG_PRINT(printPairs, "Pair Reminder", datu, extra); //Reminder of the pairs.. :)
	DEBUG_PRINT(printVector, "Sorted Main Chain", sortedMain, 0);
	DEBUG_PRINT(printVector, "Sorted Pend Chain", pend, 0);

	//Find the optimized insertion order.
	std::vector<int> sequence = getInsertionOrder(pend.size());
	DEBUG_PRINT(printVector, "Insertion Order", sequence, 0);	

	//Use Binary search together with Jacobsthal's sequence in order to insert the pend chain's elements into main chain.
	int ceiling;
	for (size_t i = 0; i < pend.size(); ++i)
	{
		if (i == 0)
		{
			sortedMain.insert(sortedMain.begin(), pend[0]);
			continue;
		}
		ceiling = i + 1; //later
		if (extra != -1 && pend.begin() + i + 1 == pend.end())
			ceiling = sortedMain.size() - 1;
		int index = binarySearch(sortedMain, pend[sequence[i] - 1], ceiling);
		sortedMain.insert(sortedMain.begin() + index, pend[sequence[i] - 1]);
	}
	DEBUG_PRINT(printVector, "Combined Main Chain", sortedMain, 1);
	//Return the sorted main in order to proceed going up in recursion or return the completely sorted main chain!
	return sortedMain;
}

