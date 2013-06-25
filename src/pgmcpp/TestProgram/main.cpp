#include <pgmcpp/pgm/table_factor.h>

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
	map<char, size_t> vars;
	vars.insert(make_pair('X', 3));
	vars.insert(make_pair('Y', 2));
	vars.insert(make_pair('Z', 4));
	vector<double> vals;
	pgm::table_factor<char, double> F(move(vars), move(vals));

	for (size_t x = 0; x < 3; ++x)
	for (size_t y = 0; y < 2; ++y)
	for (size_t z = 0; z < 4; ++z)
	{
		map<char, size_t> assignment;
		assignment.insert(make_pair('X', x));
		assignment.insert(make_pair('Y', y));
		assignment.insert(make_pair('Z', z));
		auto index = F.assignment_to_index(assignment);
		cout << "(" << x << "," << y << "," << z << ") -> " << index;
		assignment = F.index_to_assignment(index);
		cout << " -> (" << x << "," << y << "," << z << ")" << endl;
	}

	string junk;
	getline(std::cin, junk);
	return;
}

int main(int argc, char* argv[])
{
	return ProgramUtils::run(argc, argv, run);
}
