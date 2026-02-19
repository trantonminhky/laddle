#pragma once

#include <stdexcept>
#include <string>

struct assert_error : std::runtime_error {
	using std::runtime_error::runtime_error;
};
#define swag_assert(expr) \
	do { \
		auto&& val = expr; \
		if (!val) \
		{ \
			throw assert_error("Assertion failed: " + std::string(#expr) + " at " + __FILE__ + ":" + std::to_string(__LINE__)); \
		} \
	} while (0)
