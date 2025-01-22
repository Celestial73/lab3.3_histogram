cmake_minimum_required(VERSION 3.26)
project(lab3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required Qt components
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# Enable automatic processing of MOC, RCC, and UIC files
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

qt_standard_project_setup()

# Add the executable with the WIN32 flag for GUI applications
add_executable(
        lab3 WIN32  # Add WIN32 to indicate this is a GUI app
        main.cpp
        utility/GUI.h
        data/DataGenerator.cpp
        tests/TestHashTable.hpp
)

# Link the required Qt libraries
target_link_libraries(lab3 PRIVATE Qt6::Core Qt6::Widgets)
