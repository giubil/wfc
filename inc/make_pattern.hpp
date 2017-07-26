#ifndef MAKE_PATTERN_HPP
#define MAKE_PATTERN_HPP

#include "definitions.hh"

template<typename Fun>
Pattern make_pattern(int n, const Fun& fun)
{
	Pattern result(n * n);
	for (auto dy : irange(n)) {
		for (auto dx : irange(n)) {
			result[dy * n + dx] = fun(dx, dy);
		}
	}
	return result;
};

#endif /* MAKE_PATTERN_HPP */