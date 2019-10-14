#include <catch2/catch.hpp>
#include <ex3.h>


TEST_CASE("String", "[string]") {

	VString test_str{"This is a test"};

	REQUIRE(!std::strncmp(test_str.c_string(), "This is a test", test_str.length()));
	REQUIRE(std::strncmp(test_str.c_string(), "jdksfjsdkf", test_str.length()));

	// Copy initialization

	VString new_str{test_str};
	REQUIRE(new_str.length() == test_str.length());
	REQUIRE(!std::strncmp(new_str.c_string(), test_str.c_string(), test_str.length()));

	// Copy assignment

	VString another_str{"This is another string"};
	new_str = another_str;

	REQUIRE(new_str.length() == another_str.length());
	REQUIRE(!std::strncmp(new_str.c_string(), another_str.c_string(), new_str.length()));

}
