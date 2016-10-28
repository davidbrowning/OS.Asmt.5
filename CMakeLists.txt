cmake_minimum_required(VERSION 2.8.9)
project(asmt3)
set(CMAKE_CXX_FLAGS "-std=c++11 -pthread -O3 ${CMAKE_CXX_FLAGS}")
add_executable(main 
	queue_test.cpp
	)
