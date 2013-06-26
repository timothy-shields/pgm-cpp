#pragma once

#include <cmath>

namespace pgm
{

template <typename T>
class log
{
private:
  T log_val;
	log()
		: log_val(0)
	{
	}
public:
	log(T const& val)
		: log_val(std::log<T>(val))
	{
	}
	log(log<T> const& val)
		: log_val(val.log_val)
	{
	}
	operator T() const
	{
		return std::exp<T>(log_val);
	}
	log<T> operator*(log<T> const& rhs)
	{
		log C;
		C.log_val = log_val + rhs.log_val;
		return C;
	}
	log<T> operator/(log<T> const& rhs)
	{
		log C;
		C.log_val = log_val - rhs.log_val;
		return C;
	}
	T operator+(log<T> const& rhs)
	{
		return std::exp<T>(log_val) + std::exp<T>(rhs.log_val);
	}
	T operator-(log<T> const& rhs)
	{
		return std::exp<T>(log_val) - std::exp<T>(rhs.log_val);
	}
};

}
