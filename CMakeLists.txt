cmake_minimum_required(VERSION 3.10)

SET(CMAKE_BUILD_TYPE Release)
project(brain_dump_cxx)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

add_executable(sigill_cannot_kill_me sigill_cannot_kill_me.cpp)
add_executable(nonlocal_control_flow_dodging_exception nonlocal_control_flow.cpp)

install(TARGETS sigill_cannot_kill_me DESTINATION bin)
install(TARGETS nonlocal_control_flow_dodging_exception DESTINATION bin)