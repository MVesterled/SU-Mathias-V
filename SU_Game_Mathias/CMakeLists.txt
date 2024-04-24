cmake_minimum_required(VERSION 3.14)

project(SU_Game_Mathias LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Sql REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

add_executable(SU_Game_Mathias
  main.cpp Hero.h Hero.cpp Fjende.h Fjende.cpp Karekter.h Karekter.cpp Controller.h Controller.cpp
)
target_link_libraries(SU_Game_Mathias  Qt5::Core Qt5::Sql)
target_link_libraries(SU_Game_Mathias Qt${QT_VERSION_MAJOR}::Core)
