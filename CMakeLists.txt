cmake_minimum_required(VERSION 3.1)

project(otus_multithreading CXX)

add_executable(count_primes count_primes.cpp)
add_executable(ex1 ex1.cpp)
add_executable(ex2_tickets ex2_tickets.cpp)
add_executable(ex3_bank ex3_bank.cpp)
add_executable(producer_consumer.naive producer_consumer.naive.cpp)
add_executable(producer_consumer.cv producer_consumer.cv.cpp)

set(TARGETS 
    count_primes
    ex1
    ex2_tickets
    ex3_bank
    producer_consumer.naive
    producer_consumer.cv
)

foreach(target ${TARGETS})
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
        CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(${target} PRIVATE "-Wall;-Wextra;-Werror;-pedantic")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(${target} PRIVATE "/W4;/WX")
    endif()
    target_compile_features(${target} PUBLIC cxx_std_17)
endforeach(target IN ${TARGETS})
