# Documentation at https://cmake.org

# Minimum CMake version requirements
cmake_minimum_required(VERSION 3.1)

# Project name and the languages the project is using
# CXX -> CPP
# C -> C
project(cmake LANGUAGES CXX)

# Executable
add_executable(${PROJECT_NAME} main.cpp)

function(print var)
	# wtf is this ${${abc}} syntax ?!?!
	message("${var} :: ${${var}}")
endfunction()

# Print stuff to the terminal
print(PROJECT_NAME)