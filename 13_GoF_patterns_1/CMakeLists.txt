cmake_minimum_required(VERSION 3.7)

project(otus-cpp-gof1 CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # for clangd integration

include(${PROJECT_SOURCE_DIR}/cmake/conan.cmake)
conan_cmake_run(
  CONANFILE conanfile.txt
  BASIC_SETUP
  CMAKE_TARGETS # individual targets to link to
  BUILD
    missing 
)

file(GLOB LOGGER_MULTI_SRCS "singleton/logger_multi/*.cpp")
add_executable(logger_multi ${LOGGER_MULTI_SRCS})

file(GLOB LOGGER_SINGLETON_SRCS "singleton/logger_singleton/*.cpp")
add_executable(logger_singleton ${LOGGER_SINGLETON_SRCS})

file(GLOB OBJECT_POOL_SRCS "object_pool/*.cpp")
add_executable(object_pool ${OBJECT_POOL_SRCS})
target_link_libraries(object_pool CONAN_PKG::asio CONAN_PKG::benchmark)

file(GLOB FACTORY_METHOD_SRCS "factory_method/*.cpp")
add_executable(factory_method ${FACTORY_METHOD_SRCS})

file(GLOB ABSTRACT_FACTORY_SRCS "abstract_factory/*.cpp")
add_executable(abstract_factory ${ABSTRACT_FACTORY_SRCS})
target_link_libraries(abstract_factory CONAN_PKG::fmt)

file(GLOB PROTOTYPE_SRCS "prototype/*.cpp")
add_executable(prototype ${PROTOTYPE_SRCS})
target_link_libraries(prototype CONAN_PKG::fmt)

file(GLOB BUILDER_SRCS "builder/*.cpp")
add_executable(builder ${BUILDER_SRCS})

file(GLOB DEPENDENCY_INJECTION_SRCS "dependency_injection/*.cpp")
add_executable(dependency_injection ${DEPENDENCY_INJECTION_SRCS})
target_link_libraries(dependency_injection CONAN_PKG::asio CONAN_PKG::gtest)

file(GLOB LAZY_INITIALIZATION_SRCS "lazy_initialization/*.cpp")
add_executable(lazy_initialization ${LAZY_INITIALIZATION_SRCS})
target_link_libraries(lazy_initialization CONAN_PKG::asio)

get_directory_property(ALL_BUILDSYSTEM_TARGETS BUILDSYSTEM_TARGETS)
foreach(target ${ALL_BUILDSYSTEM_TARGETS})
    message("Configuring target: ${target}")
    target_compile_features(${target} PUBLIC cxx_std_20)
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
        CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(${target} PUBLIC 
            -g
            -Wall
            -Wextra
            -Werror
            -pedantic
        )
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(${target} PUBLIC
            /W4
            /WX
            /analyze
        )
    endif()
endforeach()
