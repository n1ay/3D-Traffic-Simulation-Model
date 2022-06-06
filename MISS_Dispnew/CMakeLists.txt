
find_package(Boost REQUIRED)
find_package(OpenGL REQUIRED COMPONENTS GLX OpenGL)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)
find_package(X11 REQUIRED)

add_executable(Vis
    src/GEng.cpp
    src/ObjectStorage.cpp
    src/SimData.cpp
    src/SimMap.cpp
    src/main.cpp
)

set_property(TARGET Vis PROPERTY CXX_STANDARD 14)

# fixed in boost 1.76 (https://github.com/boostorg/property_tree/issues/51)
target_compile_definitions(Vis PRIVATE BOOST_BIND_GLOBAL_PLACEHOLDERS)

target_include_directories(Vis PUBLIC Boost::boost OpenGL::GL OpenGL::GLX GLEW::glew glm::glm X11::X11)
target_link_libraries(Vis OpenGL::GL OpenGL::GLX GLEW::glew X11::X11)

