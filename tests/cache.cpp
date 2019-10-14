#include <catch2/catch.hpp>
#include <cstring>
#include "ex2.h"

void print_bytes(uint8_t *ptr, size_t n)
{
	for(int i = 0; i < n; i++) {
		std::cout << int(ptr[i]) << " ";
	}
	std::cout << std::endl;
}

TEST_CASE("Cache", "[cache]") {
	VInMemoryCache cache(5);

	size_t n = 0;

	uint8_t bytes[100];
	generate_bytes(bytes, 10);
	cache.put("test1", bytes, 10);

	REQUIRE(std::memcmp(cache.get("test1", &n), bytes, n) == 0);

	generate_bytes(bytes, 20);

	REQUIRE(std::memcmp(cache.get("test1", &n), bytes, n) != 0);

	cache.put("test2", bytes, 20);

	REQUIRE(std::memcmp(cache.get("test2", &n), bytes, n) == 0);
}


TEST_CASE("Cache LRU", "[cache]") {
	VInMemoryCache cache(5);
	size_t n = 0;

	uint8_t bytes[100];
	generate_bytes(bytes, 10);

	cache.put("test1", bytes, 10);
	cache.put("test2", bytes, 10);
	cache.put("test3", bytes, 10);
	cache.put("test4", bytes, 10);
	cache.put("test5", bytes, 10);
	cache.put("test6", bytes, 10);

	// It would be evicted
	REQUIRE(!cache.keyInCache("test1"));

	(void)cache.get("test2", &n);

	cache.put("test7", bytes, 10);

	REQUIRE(cache.keyInCache("test2"));
	REQUIRE(!cache.keyInCache("test3"));

}

