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

void print(pgm::table_factor<char, double> const& F)
{
	for (size_t index = 0; index < F.size(); ++index)
	{
		auto assignment = F.index_to_assignment(index);
		bool first = true;
		std::for_each(assignment.begin(), assignment.end(), [&](std::pair<const char, std::size_t> const& v)
		{
			if (!first)
				cout << ",";
			cout << v.first << "=" << v.second;
			first = false;
		});
		cout << ": " << F.at(index) << endl;
	}
}

void run(int argc, char* argv[])
{
	map<char, size_t> varsF;
	varsF.insert(make_pair('X', 3));
	varsF.insert(make_pair('Y', 2));
	varsF.insert(make_pair('Z', 4));
	vector<double> valsF(3*2*4);
	pgm::table_factor<char, double> F(move(varsF), move(valsF));

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

	cout << endl;

	map<char, size_t> varsG;
	varsG.insert(make_pair('X', 2));
	varsG.insert(make_pair('Y', 2));
	vector<double> valsG;
	valsG.push_back(1);
	valsG.push_back(2);
	valsG.push_back(3);
	valsG.push_back(4);
	pgm::table_factor<char, double> G(move(varsG), move(valsG));

	cout << "G(X,Y): " << endl;
	print(G);
	cout << endl;

	map<char, size_t> varsH;
	varsH.insert(make_pair('Y', 2));
	varsH.insert(make_pair('Z', 2));
	vector<double> valsH;
	valsH.push_back(10);
	valsH.push_back(200);
	valsH.push_back(3000);
	valsH.push_back(40000);
	pgm::table_factor<char, double> H(move(varsH), move(valsH));


	cout << "H(Y,Z): " << endl;
	print(H);
	cout << endl;

	auto K = G * H;

	cout << "K(X,Y,Z) = G(X,Y) * H(Y,Z): " << endl;
	print(K);
	cout << endl;

	std::set<char> S;
	S.insert('Y');
	S.insert('X');
	auto M = K.marginalize(S);

	cout << "M(X,Z) = sum_Z { K(X,Y,Z) }:" << endl;
	print(M);
	cout << endl;

	if (argc > 1)
	{
		string junk;
		getline(std::cin, junk);
	}
	return;
}

int main(int argc, char* argv[])
{
	return ProgramUtils::run(argc, argv, run);
}
