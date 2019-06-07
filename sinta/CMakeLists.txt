include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    )

configure_file(config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)

add_library(sintalib SHARED
    Injector.cpp
    ScriptRunner.cpp
    Tools.cpp
    )

target_link_libraries(sintalib Qt5::Core Qt5::Widgets Qt5::Qml)

add_executable(sinta main.cpp)
target_link_libraries(sinta Qt5::Core)
