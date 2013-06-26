#pragma once

#include <utility>
#include <map>
#include <set>
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
	typedef std::pair<Key const, std::size_t> var;
	typedef std::map<Key, std::size_t> var_map;
	typedef less_pair_first<var> less_var;

	std::map<Key, std::size_t> vars;
	std::vector<Value> vals;

	static var_map get_var_map(std::set<Key> const& keys)
	{
		var_map map;
		std::transform(
			keys.begin(), keys.end(),
			std::inserter(map, map.end()),
			[](Key const& v){ return std::make_pair(v, static_cast<std::size_t>(0)); });
		return map;
	}

	std::size_t compute_size() const
	{
		return std::accumulate(
			vars.cbegin(), vars.cend(), static_cast<std::size_t>(1),
			[](std::size_t p, var const& v){ return p * v.second; });
	}

	void resize()
	{
		vals.resize(compute_size());
	}

	void resize(Value const& value)
	{
		vals.resize(compute_size(), value);
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

	bool empty() const
	{
		return vars.empty();
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

	Value& operator[](std::size_t index)
	{
		return at(index);
	}

	Value const& operator[](std::size_t index) const
	{
		return at(index);
	}

	Value& operator[](var_map const& assignment)
	{
		return at(assignment);
	}

	Value const& operator[](var_map const& assignment) const
	{
		return at(assignment);
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

	static table_factor<Key, Value> factor_product(table_factor<Key, Value> const& A, table_factor<Key, Value> const& B)
	{
		if (A.empty())
			return B;
		if (B.empty())
			return A;
		table_factor<Key, Value> R;
		std::set_union(
			A.vars.begin(), A.vars.end(),
			B.vars.begin(), B.vars.end(),
			std::inserter(R.vars, R.vars.end()));
		R.resize();
		for (auto index = 0; index < R.size(); ++index)
		{
			auto assignment = R.index_to_assignment(index);
			R[index] = A[assignment] * B[assignment];
		}
		return R;
	}

	static table_factor<Key, Value> factor_marginalize(table_factor<Key, Value> const& F, std::set<Key> const& vars)
	{
		if (F.empty() || vars.empty())
			return F;
		table_factor<Key, Value> R;
		auto vars_map = get_var_map(vars);
		less_pair_first<var> less;
		std::set_difference(
			F.vars.begin(), F.vars.end(),
			vars_map.begin(), vars_map.end(),
			std::inserter(R.vars, R.vars.end()),
			less);
		R.resize();
		for (auto index = 0; index < F.size(); ++index)
		{
			auto assignment = F.index_to_assignment(index);
			R.at(assignment) += F.vals[index];
		}
		return R;
	}

	table_factor<Key, Value> operator*(table_factor<Key, Value> const& B) const
	{
		auto const& A = *this;
		return factor_product(A, B);
	}

	table_factor<Key, Value> marginalize(std::set<Key> const& vars) const
	{
		auto const& F = *this;
		return factor_marginalize(F, vars);
	}
};

}
