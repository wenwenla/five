CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
PROJECT (five)
SET (CMAKE_CXX_STANDARD 11)

include_directories(include)

find_package(Boost COMPONENTS system thread REQUIRED)

add_executable(five main.cpp src/Board.cpp src/GameState.cpp src/RLMsg.cpp src/RLServer.cpp)
target_link_libraries(five ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY})