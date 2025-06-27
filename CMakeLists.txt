cmake_minimum_required(VERSION 3.16)
project(TouchstoneViewer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)

add_executable(${PROJECT_NAME}
    main.cpp
    src/TouchstoneParser.cpp
    src/DataModel.cpp
    src/PlotItem.cpp
    resources/qml.qrc
)

target_include_directories(${PROJECT_NAME} PRIVATE src)

target_link_libraries(${PROJECT_NAME}
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
)