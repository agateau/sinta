cmake_minimum_required(VERSION 3.10)
project(appshot
    VERSION 0.1.0
    DESCRIPTION "Test scripted app screenshots")

# Dependencies
find_package(Qt5 CONFIG REQUIRED Core Widgets Qml)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# Sources
set(appshot_SRCS
    main.cpp
    MainWindow.cpp
    MainWindow.ui
    ScriptRunner.cpp
    Tools.cpp
    )

# Building
include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Woverloaded-virtual")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
set(CMAKE_CXX_STANDARD 17)
add_executable(appshot ${appshot_SRCS})

target_link_libraries(appshot Qt5::Core Qt5::Widgets Qt5::Qml)

# Install
install(TARGETS appshot
    DESTINATION bin
    )
