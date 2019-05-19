set(testapp_SRCS
    main.cpp
    MainWindow.cpp
    MainWindow.ui
    )

# Building
include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    )

add_executable(testapp ${testapp_SRCS})

target_link_libraries(testapp Qt5::Core Qt5::Widgets)
