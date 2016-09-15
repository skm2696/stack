#include "Stack.hpp"
#include <catch.hpp>
SCENARIO("Stack: operator==", "[op==]") {
	stack<int> a, b;
	a.push(5);
	a.push(3);
	a.push(5);
	b.push(5);
	b.push(3);
	b.push(5);
	REQUIRE(a == b);
}
SCENARIO("Stack: operator=", "[op=]") {
	stack<int> a;
	a.push(1);
	stack<int> b;
	b = a;
	REQUIRE(b == a);
}
