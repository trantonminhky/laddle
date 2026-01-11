#include <stdexcept>

struct assert_error : std::runtime_error {
	using std::runtime_error::runtime_error;
};
#define swag_assert(expr) { \
	auto&& val = expr; \
	if (!val) \
	{ \
		throw assert_error(#expr); \
	} \
}
