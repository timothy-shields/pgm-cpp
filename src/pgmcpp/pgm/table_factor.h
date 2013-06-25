#pragma once

#include <utility>
#include <map>
#include <vector>
#include <algorithm>
#include <iterator>

#include "less_pair_first.h"

namespace pgm
{

template <typename Key, typename Value>
class table_factor
{
	friend table_factor operator*(table_factor const&, table_factor const&);

private:
	typedef std::pair<const Key, std::size_t> var;
	typedef std::map<Key, std::size_t> var_map;
	typedef less_pair_first<var> less_var;

	std::map<Key, std::size_t> vars;
	std::vector<Value> vals;

public:
	table_factor(std::map<Key, std::size_t>&& vars, std::vector<double>&& vals)
		: vars(std::forward<std::map<Key, std::size_t>>(vars))
		, vals(std::forward<std::vector<Value>>(vals))
	{
	}

	std::size_t assignment_to_index(std::map<Key, std::size_t> const& assignment)
	{
		std::size_t index = 0;
		std::size_t prod = 1;
		std::for_each(vars.rbegin(), vars.rend(), [&](var& v)
		{
			auto const& key = v.first;
			auto card = v.second;
			index += (assignment.at(key) * prod);
			prod *= card;
		});
		return index;
	}

	std::vector<std::size_t> index_to_assignment(std::size_t index)
	{
		std::vector<std::size_t> assignment;
		return assignment;
	}
};

//template <typename Key>
//table_factor<Key> operator*(table_factor<Key> const& A, table_factor<Key> const& B)
//{
//	if (A.vars.empty())
//		return B;
//	if (B.vars.empty())
//		return A;
//	factor<Key> C;
//	std::set_union(
//		A.vars.begin(), A.vars.end(),
//		B.vars.begin(), B.vars.end(),
//		std::inserter(C.vars, C.vars.end()));
//	std::for_each(
//}

}