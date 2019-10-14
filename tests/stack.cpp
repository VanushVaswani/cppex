#include <catch2/catch.hpp>
#include "ex1.h"

TEST_CASE( "Basic Stack", "[stack]" ) {

	VStack<int> stk(10);

	REQUIRE( stk.empty() == true );

	stk.push(5);
	REQUIRE( stk.empty() == false );

	REQUIRE(stk.pop() == 5);
	REQUIRE( stk.empty() == true );

	stk.push(10);
	stk.push(20);
	stk.push(30);

	REQUIRE(stk.pop() == 30);
	REQUIRE(stk.pop() == 20);
	REQUIRE(stk.pop() == 10);

	REQUIRE(stk.empty() == true);
}

TEST_CASE("Max Stack", "[stack]") {
	MaxVStack<int> stk;

	REQUIRE(stk.empty() == true);

	stk.push(10);
	stk.push(15);
	stk.push(30);

	REQUIRE(stk.max() == 30);
	REQUIRE(stk.pop() == 30);
	REQUIRE(stk.max() == 15);
	REQUIRE(stk.pop() == 15);
	stk.push(1);

	REQUIRE(stk.max() == 10);
	REQUIRE(stk.pop() == 1);
	REQUIRE(stk.pop() == 10);
	REQUIRE(stk.empty() == true);

	stk.push(10);
	stk.push(50);
	stk.push(11);

	REQUIRE(stk.max() == 50);
}
