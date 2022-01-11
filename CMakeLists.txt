cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)

# Give me warnings as much as possible
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wnon-virtual-dtor -pedantic -Wcast-align -Wnull-dereference")

# We don't use exceptions and RTTI
set(CMAKE_CXX_FLAGS "-fno-exceptions -fno-rtti")

project(todo)

find_package(fmt REQUIRED)
find_package(LLVM REQUIRED)

add_executable(td main.cpp)

target_link_libraries(
	td
	PRIVATE
	LLVMSupport
	fmt::fmt
)

install (TARGETS td
    DESTINATION /usr/local/bin)

#enable_testing()
#add_subdirectory(tests)
#add_test(NAME test COMMAND ${CMAKE_BINARY_DIR}/bin/test_todo)
