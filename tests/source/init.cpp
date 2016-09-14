#include "stack.hpp"
#include <catch.hpp>
SCENARIO("Stack: operator=", "[op=]") {
	stack<size_t> a;
	a.push(1);
	stack<size_t> b;
	b = a;
	REQUIRE(b == a);
}
