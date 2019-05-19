cmake_minimum_required(VERSION 3.10)
project(injeqt
    VERSION 0.1.0
    DESCRIPTION "Inject code in a Qt app")

# Dependencies
find_package(Qt5 CONFIG REQUIRED Core Widgets Qml)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Woverloaded-virtual")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(injeqt)
add_subdirectory(testapp)
