#include "../include/PmergeMe.hpp"
#include <bits/stdc++.h>

int PmergeMe::binarySearch(std::vector<int> &numbers, int x, int ceiling)
{
	int low = 0;
	while (low <= ceiling)
	{
		int mid = low + (ceiling - low) / 2;
		if (numbers[mid] < x)
			low = mid + 1;
		else
			ceiling = mid - 1;
	}
	return low;
}

std::vector<int> PmergeMe::doMagic(std::vector<int> numbers)
{
	if (numbers.size() <= 1) //This is where we stop the recursive call because if main chain has one left, we are done and we start going back
		return numbers; // and we need the main chain to be returned
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

		std::cout << "[ " << datu.back().first << " ], [ " <<  datu.back().second << " ] " << std::endl;	
	}
	if (numbers.size() % 2 == 1)
		extra = numbers[numbers.size() - 1];
	std::cout << "Extra :" << extra << std::endl;

	std::vector<int> main;
	std::vector<int> pend;
	for (auto &p: datu) //loop through 
	{
		main.push_back(p.second);
		pend.push_back(p.first);
	}
	if (extra != -1)
		pend.push_back(extra);

	std::cout << "Main Chain: ";
	for (auto i: main)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
	std::cout << "Pend Chain: ";
	for (auto i: pend)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
	//THEN WE START AGAIN THE NEXT LAYER!
	std::vector<int> sortedMain = doMagic(main); // then once the main vector size is 1, it returns and does the REST of the function level by level. And this catches the sorted main function so far... Eventually on top stage we get the sorte main and this returns the sorted main


	std::cout << "NEW MAIN: ";
	for (auto i: sortedMain)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;

	std::vector<int> newPend;
	std::cout << "NEW PEND: ";
	for (size_t i = 0; i < sortedMain.size(); ++i)
	{
		for (size_t x = 0; x < datu.size(); ++x)
		{
			if (sortedMain[i] == datu[x].second)
			{
				newPend.push_back(datu[x].first);
				std::cout << newPend.back() << " ";
				break ;
			}
		}
		// auto it = std::find(datu.begin(), datu.end(), main[i]);
//		newPend.push_back(it->first);
//		std::cout << newPend[i] << " ";
	}
	if (extra != -1)
	{
		newPend.push_back(extra);
		std::cout << newPend.back() << " ";		
	}
	std::cout << std::endl;
	pend = newPend;
	//Now we need to rearrange the pend chain to match...


	int ceiling;
	for (size_t i = 0; i < pend.size(); ++i)
	{
		if (i == 0)
		{
			sortedMain.insert(sortedMain.begin(), pend[0]);
			continue;
		}
		ceiling = i + 1;
		if (extra != -1 && pend.begin() + i + 1 == pend.end())
			ceiling = 0;
		int index = binarySearch(sortedMain, pend[i], ceiling);
		sortedMain.insert(sortedMain.begin() + index, pend[i]);
	}

	std::cout << "New Combined Main: " << std::endl;;
	for (auto i: sortedMain)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
	return sortedMain;
}

