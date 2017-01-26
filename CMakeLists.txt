cmake_minimum_required(VERSION 2.8.4)
project(ass3Client)

message(STATUS "start running cmake...")
#-Wall -Weffc++

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Weffc++ -std=c++11 ")

set(Boost_INCLUDE_DIR "C:/Program Files/boost/include/boost-1_63/")
set(Boost_LIBRARY_DIR "C:/Program Files/boost/lib/")

set(BOOST_ROOT "C:/Program Files/boost_1_63_0/")

find_package(Boost 1.63.0 COMPONENTS filesystem system thread REQUIRED)

if(Boost_FOUND)

    LINK_DIRECTORIES(${Boost_LIBRARY_DIR})

    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
   message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

endif()

add_executable(ass3Client
        src/MainClient.cpp src/KeyBoardProtocol.cpp include/KeyBoardProtocol.h
        src/SocketProtocol.cpp include/SocketProtocol.h
        src/ConnectionHandler.cpp include/ConnectionHandler.h
        src/packet.cpp include/packet.h)

if(Boost_FOUND)
    target_link_libraries(ass3Client ${Boost_LIBRARIES} ws2_32)

endif()