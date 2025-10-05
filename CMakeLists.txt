cmake_minimum_required(VERSION 4.1)
project(qt_process VERSION 1.5.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)


add_executable(process_key_events WIN32 
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${PROJECT_SOURCE_DIR}/src/process.cpp
)

target_include_directories(process_key_events PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

target_precompile_headers(process_key_events PRIVATE ${PROJECT_SOURCE_DIR}/include/pch.h)
target_link_libraries(process_key_events Qt6::Core Qt6::Gui Qt6::Widgets)