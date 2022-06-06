cmake_minimum_required (VERSION 3.1)
project (traffic-sim)

find_package(Boost REQUIRED)

add_executable(Sim
    Car.cpp
    Crossroad.cpp
    FrameParser.cpp
    Lane.cpp
    MapParser.cpp
    Model.cpp
    Road.cpp
    TrafficLight.cpp
    World.cpp
    main.cpp
)

set_property(TARGET Sim PROPERTY CXX_STANDARD 11)

# fixed in boost 1.76 (https://github.com/boostorg/property_tree/issues/51)
target_compile_definitions(Sim PRIVATE BOOST_BIND_GLOBAL_PLACEHOLDERS)
target_include_directories(Sim PUBLIC Boost::boost)

add_subdirectory(MISS_Dispnew)

