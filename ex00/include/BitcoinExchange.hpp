#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <bits/stdc++.h>
#include <algorithm>
#include <chrono>
/*templates in C++ are powerful tools for creating generic classes or functions.
This allows us to write code that works for any data type without rewriting it for each type.

Key features:
- Avoid code duplication by allowing one function or class to work with multiple data types, mainly
allowing generic functions and classes.
- Provide type safety, unlike using void *pointers or macros
- Can be specialized for specific data types when needed
*/

class BitcoinExchange
{
	public:
	std::map<std::string, float> data;
	BitcoinExchange();
	BitcoinExchange(BitcoinExchange& copy) = default;
	BitcoinExchange& operator=(BitcoinExchange& src) = default;
	~BitcoinExchange() = default;
};
