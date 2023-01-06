cmake_minimum_required(VERSION 3.16.9)

project(root-reflex CXX)

include_directories(include)

find_package(ROOT)

file(GLOB sources ${CMAKE_SOURCE_DIR}/src/MyObject.cc)
file(GLOB headers ${CMAKE_SOURCE_DIR}/include/*.h)

file(GLOB reflex_cl ${CMAKE_SOURCE_DIR}/src/classes.h)
file(GLOB reflex_sel ${CMAKE_SOURCE_DIR}/src/classes_def.xml)
set(CMAKE_ROOTTEST_NOROOTMAP OFF)
reflex_generate_dictionary(libroot-reflex ${headers} ${reflex_cl} SELECTION ${reflex_sel})

add_library(root-reflex SHARED ${sources} ${headers} libroot-reflex.cxx)
target_link_libraries(root-reflex ${ROOT_LIBRARIES})
target_include_directories(root-reflex PUBLIC ${CMAKE_SOURCE_DIR} ${ROOT_INCLUDE_DIRS})

add_executable(root-reflex-main ${CMAKE_SOURCE_DIR}/src/main.cc)
target_link_libraries(root-reflex-main root-reflex)
