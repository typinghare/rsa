cmake_minimum_required(VERSION 3.27)
project(rsa)
set(CMAKE_CXX_STANDARD 20)

add_executable(rsa
        src/main.cpp
        src/rsa.hpp
        src/rsa.cpp
        src/rsa_infant.hpp
)
target_link_libraries(rsa gmp)