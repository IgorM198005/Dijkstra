cmake_minimum_required(VERSION 2.8)

PROJECT(DijkstraApp)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE DijkstraApp.cpp dijkstra.cpp graph_serialization.cpp)
set(HEADERS dijkstra.h graph_serialization.h nexception.h vertex.h)

add_executable(DijkstraApp ${SOURCE} ${HEADERS})