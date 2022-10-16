 cmake_minimum_required(VERSION 3.0)

project(pod7) 

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMake") 

find_package(Hidapi REQUIRED)
find_package(Boost COMPONENTS program_options CONFIG REQUIRED)
find_package(DBusCpp REQUIRED)

add_executable(pod7 
    pod7_adaptor.hpp
    DBusPOD7Workers.cpp  main.cpp)

target_link_libraries(pod7 ${HIDAPI_LIBRARIES} ${Boost_LIBRARIES} ${DBUSCPP_LIBRARIES})

install(TARGETS pod7 RUNTIME DESTINATION bin)

