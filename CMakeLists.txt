cmake_minimum_required(VERSION 3.20)
project(GLMiniUI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra  -pedantic -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(INCLUDE_DIR "./include")
set(EXE_NAME "demo")

# Optional in case of custom installation
# set(FREETYPE_INCLUDE_DIRS "/ruta/a/freetype/include")
# set(FREETYPE_LIBRARY "/ruta/a/freetype/lib/libfreetype.a | freetype.lib")
# set(GLUT_INCLUDE_DIRS "/ruta/a/glut/include")
# set(GLUT_LIBRARY "/ruta/a/glut/lib/libglut.a | glut32.lib")
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(Freetype REQUIRED)
set(FREETYPE_USE_STATIC_LIBS TRUE)
set(SOURCES
    source/label.cpp
    source/buttons.cpp
    source/utils.cpp
    source/globals.cpp
)
add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC
    ${OPENGL_INCLUDE_DIR}
    ${FREETYPE_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIRS}
    ${INCLUDE_DIR}
)
target_link_libraries(${PROJECT_NAME} PUBLIC
    ${OPENGL_LIBRARIES}
    freetype
    GLUT::GLUT
)

add_executable(${EXE_NAME} examples/demo.cpp)
target_include_directories(${EXE_NAME} PRIVATE
    ${INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
    ${FREETYPE_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIRS}
)
target_link_libraries(${EXE_NAME} PRIVATE ${PROJECT_NAME})
