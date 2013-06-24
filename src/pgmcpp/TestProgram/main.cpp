#include "ProgramUtils.h"

#include <string>
#include <random>
#include <vector>
#include <tuple>
#include <functional>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

void TimeIt(string text, int repeatCount, std::function<void ()> f)
{
	auto start = clock();
	for (int i = 0; i < repeatCount; i++)
		f();
	auto stop = clock();
	auto ms = 1000.0 * static_cast<double>(stop - start) / static_cast<double>(CLOCKS_PER_SEC * repeatCount);
	cout << text << " " << ms << endl;
}

void run(int argc, char* argv[])
{
	std::string junk;
	std::getline(std::cin, junk);
	return;
}

int main(int argc, char* argv[])
{
	return ProgramUtils::run(argc, argv, run);
}
