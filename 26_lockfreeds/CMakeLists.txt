cmake_minimum_required(VERSION 3.14)

project(otus-cpp-lockfreeds CXX)

find_package(Boost REQUIRED)

file(GLOB SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

foreach(src_file ${SRC_FILES})
    get_filename_component(target ${src_file} NAME_WLE)
    add_executable(${target} ${src_file})
    list(APPEND TARGETS ${target})
    message("target added: ${target}")
endforeach(src_file ${SRC_FILES})

target_include_directories(is_prime.service.lockfree PUBLIC ${Boost_INCLUDE_DIRS})
target_compile_options(is_prime.service.lockfree PUBLIC
    -Wno-ambiguous-reversed-operator
)

target_include_directories(is_prime.service.lockfree.better PUBLIC ${Boost_INCLUDE_DIRS})
target_compile_options(is_prime.service.lockfree.better PUBLIC
    -Wno-ambiguous-reversed-operator
)
foreach(target ${TARGETS})
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
        CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(${target} PRIVATE 
            -O2
            -march=native
            -g
            -Wall
            -Wextra
            -Werror
            -pedantic
        )
        target_link_libraries(${target} PUBLIC pthread)
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(${target} PRIVATE
            /EHsc
            /O2
            /W4
            /WX
            -D_SILENCE_CXX20_OLD_SHARED_PTR_ATOMIC_SUPPORT_DEPRECATION_WARNING
        )
    endif()
    target_compile_features(${target} PUBLIC cxx_std_20)
endforeach(target IN ${TARGETS})
