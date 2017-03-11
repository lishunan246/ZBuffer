cmake_minimum_required(VERSION 2.8.11)

project( ZBuffer )

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

find_package(Boost)

include_directories(${Boost_INCLUDE_DIRS})
# Find the QtWidgets library
find_package(Qt5Widgets)

find_package(Qt5 COMPONENTS Quick Core Network)

qt5_add_resources(RESOURCES qml.qrc)

add_executable( ZBuffer main.cpp ObjLoader.cpp ObjLoader.h Obj.cpp Obj.h ImageProvider.cpp ImageProvider.h common.cpp common.h ${RESOURCES})

qt5_use_modules(ZBuffer Quick Core Network)

# Use the Widgets module from Qt 5.
target_link_libraries(ZBuffer Qt5::Widgets)
