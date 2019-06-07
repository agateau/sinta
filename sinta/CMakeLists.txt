include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    )

configure_file(config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)

# sintalib
add_library(sintalib SHARED
    Injector.cpp
    ScriptRunner.cpp
    Tools.cpp
    )

target_link_libraries(sintalib Qt5::Core Qt5::Widgets Qt5::Qml)

install(TARGETS sintalib DESTINATION lib)

# sinta
add_executable(sinta main.cpp)
target_link_libraries(sinta Qt5::Core)
install(TARGETS sinta DESTINATION bin)
