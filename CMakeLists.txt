cmake_minimum_required(VERSION 3.5)

project(assignment7_2__1_QC LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(assignment7_2__1_QC main.cpp)

include(GNUInstallDirs)
install(TARGETS assignment7_2__1_QC
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
