#pragma once

#ifdef DEBUG
	#define DEBUG_PRINT(func, ...) func(__VA_ARGS__)
#else
	#define DEBUG_PRINT(func, ...) do {} while (0)
#endif

#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <bits/stdc++.h>
#include <algorithm>
#include <chrono>
#include <stack>
#include <regex.h>

class PmergeMe
{
	private:

	public:
	std::vector<int> chain; ///mysteryyy!
	size_t numberOfElements;
//	int extra;
	std::stack<int> stack;
	PmergeMe() = default;
	PmergeMe(PmergeMe& copy) = default;
	PmergeMe& operator=(PmergeMe& src) = default;
	~PmergeMe() = default;

	void	parseAndStore(int argc, char *argv[]);
	std::vector<int> doMagic(std::vector<int> numbers);
	int binarySearch(std::vector<int> &numbers, int x, int ceiling);
	void	printVector(const std::string& message, const std::vector<int> chain, bool newLine);
	void	printPairs(const std::string& message, const std::vector<std::pair<int, int>> pairs, int extra);
};
