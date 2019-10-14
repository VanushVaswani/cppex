set(TARGET_NAME cppexlib)

add_library(${TARGET_NAME} INTERFACE
)

target_include_directories(${TARGET_NAME}
	INTERFACE .
)
