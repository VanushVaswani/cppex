set(TARGET_NAME tests)

add_executable(${TARGET_NAME}
	main.cpp
	stack.cpp
	cache.cpp
	string.cpp
)

target_link_libraries(${TARGET_NAME}
	PUBLIC cppexlib
)

target_include_directories(${TARGET_NAME}
	PUBLIC ../externals/Catch2/single_include
)
