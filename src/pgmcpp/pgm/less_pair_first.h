#pragma once

#include <functional>

namespace pgm
{
	template <typename Pair>
	struct less_pair_first
	{
		typedef bool result_type;
		typedef Pair first_argument_type;
		typedef Pair second_argument_type;
		bool operator()(Pair const& a, Pair const& b) const
		{
			std::less<typename Pair::first_type> less;
			return less(a.first, b.first);
		}
	};
}