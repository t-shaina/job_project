cmake_minimum_required(VERSION 3.5)

project(untitled2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Gui)
find_package(Qt6 REQUIRED COMPONENTS Network)
#find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS  Widgets Core Gui Network)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    start_page.h
    start_page.cpp
    socket_adapter.cpp
    socket_adapter.h
    client_socket_adapter.cpp
    client_socket_adapter.h
    app_page.cpp
    app_page.h
    registration_page.cpp
    registration_page.h
    template_behavour.cpp
    template_behavour.h
    creator.cpp
    creator.h
    json_creator.cpp
    json_creator.h
    billet_widget.cpp
    billet_widget.h
    app_page_painter.cpp
    app_page_painter.h
    symbols_inspector.cpp
    symbols_inspector.h
    combo_box.cpp
    combo_box.h
    line_edit.cpp
    line_edit.h
    text_edit.cpp
    text_edit.h
    spin_box.cpp
    spin_box.h
    push_button.cpp
    push_button.h
    films_table_view.cpp
    films_table_view.h
    menu.cpp
    menu.h
    buffer.cpp
    buffer.h
    dialog.cpp
    dialog.h
)

qt_add_executable(untitled2
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

target_link_libraries(untitled2 PRIVATE Qt6::Widgets)
target_link_libraries(untitled2 PRIVATE Qt6::Core)
target_link_libraries(untitled2 PRIVATE Qt6::Gui)
target_link_libraries(untitled2 PRIVATE Qt6::Network)

set_target_properties(untitled2 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS untitled2
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

#if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(untitled2)
#endif()
