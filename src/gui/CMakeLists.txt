project(popgenlibqt)
cmake_minimum_required(VERSION 2.6)

# Allow relative paths for libraries (they are part of the project anyway)
cmake_policy(SET CMP0015 NEW)

find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ../)
link_directories(../ ../../../HandyTools/src /usr)

# Set the C++ sources
set(popgenlibqt_src mainwindow.cpp main.cpp)
qt4_automoc(${popgenlibqt_src})
add_executable(popgenlibqt ${popgenlibqt_src})
target_link_libraries(popgenlibqt ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} HandyTools PopGenLib gsl gslcblas)
