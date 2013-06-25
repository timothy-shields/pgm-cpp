#pragma once

#include <utility>
#include <map>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>

#include "less_pair_first.h"

namespace pgm
{

template <typename Key, typename Value>
class table_factor
{
private:
	typedef std::pair<const Key, std::size_t> var;
	typedef std::map<Key, std::size_t> var_map;
	typedef less_pair_first<var> less_var;

	std::map<Key, std::size_t> vars;
	std::vector<Value> vals;

	void resize()
	{
		auto product = std::accumulate(
			vars.cbegin(), vars.cend(), static_cast<std::size_t>(1),
			[](std::size_t p, var const& v){ return p * v.second; });
		vals.resize(product);
	}

public:
	table_factor()
	{
	}

	table_factor(std::map<Key, std::size_t>&& vars, std::vector<double>&& vals)
		: vars(std::forward<std::map<Key, std::size_t>>(vars))
		, vals(std::forward<std::vector<Value>>(vals))
	{
	}

	std::size_t size() const
	{
		return vals.size();
	}

	Value& at(std::size_t index)
	{
		return vals[index];
	}

	Value const& at(std::size_t index) const
	{
		return vals[index];
	}

	Value& at(var_map const& assignment)
	{
		return vals[assignment_to_index(assignment)];
	}

	Value const& at(var_map const& assignment) const
	{
		return vals[assignment_to_index(assignment)];
	}

	std::size_t assignment_to_index(std::map<Key, std::size_t> const& assignment) const
	{
		std::size_t index = 0;
		std::size_t prod = 1;
		std::for_each(vars.crbegin(), vars.crend(), [&](var const& v)
		{
			auto const& key = v.first;
			auto card = v.second;
			index += (assignment.at(key) * prod);
			prod *= card;
		});
		return index;
	}

	var_map index_to_assignment(std::size_t index) const
	{
		var_map assignment;
		std::size_t prod = size();
		std::for_each(vars.cbegin(), vars.cend(), [&](var const& v)
		{
			auto const& key = v.first;
			auto card = v.second;
			prod /= card;
			auto i = index / prod;
			assignment.insert(std::make_pair(key, i));
			index -= prod * i;
		});
		return assignment;
	}

	table_factor<Key, Value> operator*(table_factor<Key, Value> const& B)
	{
		auto const& A = *this;
		if (A.vars.empty())
			return B;
		if (B.vars.empty())
			return A;
		table_factor<Key, Value> C;
		std::set_union(
			A.vars.begin(), A.vars.end(),
			B.vars.begin(), B.vars.end(),
			std::inserter(C.vars, C.vars.end()));
		C.resize();
		for (auto index = 0; index < C.size(); ++index)
		{
			auto assignment = C.index_to_assignment(index);
			C.vals[index] = A.at(assignment) * B.at(assignment);
		}
		return C;
	}
};

}