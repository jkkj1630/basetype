CMAKE_MINIMUM_REQUIRED(VERSION 3.7)
PROJECT(basetype)
#PROJECT(WaveDecode)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "-fPIC ${CMAKE_CXX_FLAGS}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

INCLUDE_DIRECTORIES(./)
INCLUDE_DIRECTORIES(./algor)
AUX_SOURCE_DIRECTORY(./algor algor)
INCLUDE_DIRECTORIES(./base)
AUX_SOURCE_DIRECTORY(./base base)
add_library(basetype
    ${algor}
    ${base}
)

