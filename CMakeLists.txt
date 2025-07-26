cmake_minimum_required(VERSION 3.50)

set(CMAKE_CXX_STANDARD 20)

project(${PROJECT_NAME} LANGUAGE CXX)

include_directories(include)

find_package(PkgConfig REQUIRED)
pkg_check_modules(ASSIMP REQUIRED assimp)
pkg_check_modules(ASSIMP REQUIRED glfw3)

project(main)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)
add_executable(${CMAKE_PROJECT_NAME} ${SRC_FILES} lib/glad/glad.c)
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -g)

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE ${GLFW_INCLUDE_DIRS} ${ASSIMP_INCLUDE_DIRS}
          ${CMAKE_CURRENT_SOURCE_DIR}/include
          ${CMAKE_CURRENT_SOURCE_DIR}/lib/glad)

target_link_libraries(${PROJECT_NAME} ${ASSIMP_LIBRARIES} ${GLFW_LIBRARIES} dl)
