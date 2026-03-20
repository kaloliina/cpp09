#pragma once

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
	std::vector<int> winners; ///mysteryyy!
	std::vector<std::pair<int, int>> datuliini;
	std::unordered_map<int, int> losers;
//	int extra;
	std::stack<int> stack;
	PmergeMe() = default;
	PmergeMe(PmergeMe& copy) = default;
	PmergeMe& operator=(PmergeMe& src) = default;
	~PmergeMe() = default;

	std::vector<int> doMagic(std::vector<int> numbers);
	int binarySearch(std::vector<int> &numbers, int x, int ceiling);
};
