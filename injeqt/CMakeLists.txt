set(injeqt_SRCS
    Injector.cpp
    ScriptRunner.cpp
    Tools.cpp
    )

# Building
include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    )

add_library(injeqt SHARED ${injeqt_SRCS})

target_link_libraries(injeqt Qt5::Core Qt5::Widgets Qt5::Qml)
