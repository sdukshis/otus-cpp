cmake_minimum_required(VERSION 3.5)

project(gof)

add_executable(abstract_factory abstract_factory.cpp)
set_target_properties(abstract_factory PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    )

add_executable(builder builder.cpp)
set_target_properties(builder PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    )

add_executable(dependency_injection dependency_injection.cpp)
set_target_properties(dependency_injection PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    )

add_executable(factory_method factory_method.cpp)
set_target_properties(factory_method PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    )

add_executable(lazy_initialization lazy_initialization.cpp)
set_target_properties(lazy_initialization PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    )

add_executable(multiton multiton.cpp)
set_target_properties(multiton PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    )

add_executable(object_pool object_pool.cpp)
set_target_properties(object_pool PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    )

add_executable(prototype prototype.cpp)
set_target_properties(prototype PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    )

add_executable(singleton singleton.cpp)
set_target_properties(singleton PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    )
