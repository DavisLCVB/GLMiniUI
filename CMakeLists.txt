cmake_minimum_required(VERSION 3.20)
project(GLMiniUI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /permissive- /W4")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od /Zi")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra  -pedantic -Wno-error=unknown-pragmas")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
endif()

set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(EXE_NAME "demo")

find_package(GLUT REQUIRED)
find_package(Freetype REQUIRED)
find_package(OpenGL REQUIRED)

link_directories(${GLUT_LIBRARY_DIRS})
link_directories(${FREETYPE_LIBRARY_DIRS})
link_directories(${OPENGL_LIBRARY_DIRS})

set(SOURCES
    source/label.cpp
    source/buttons.cpp
    source/utils.cpp
    source/globals.cpp
)
add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC
    ${GLUT_INCLUDE_DIRS}
    ${FREETYPE_INCLUDE_DIRS}
    ${INCLUDE_DIR}
)
target_link_libraries(${PROJECT_NAME} ${GLUT_LIBRARIES} ${FREETYPE_LIBRARIES} ${OPENGL_LIBRARIES})

add_executable(${EXE_NAME} examples/demo.cpp)
target_include_directories(${EXE_NAME} PRIVATE
    ${GLUT_INCLUDE_DIRS}
    ${FREETYPE_INCLUDE_DIRS}
    ${INCLUDE_DIR}
)
target_link_libraries(${EXE_NAME} PRIVATE ${PROJECT_NAME})
