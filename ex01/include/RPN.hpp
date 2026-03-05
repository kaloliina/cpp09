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

class RPN
{
	public:
	std::stack<int> stack;
	RPN() = default;
	RPN(RPN& copy) = default;
	RPN& operator=(RPN& src) = default;
	~RPN() = default;
};
