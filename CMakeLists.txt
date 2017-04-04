cmake_minimum_required(VERSION 3.6)
project(emergent_robot)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -lpthread")

## Include project source code
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
## Set the OpenCV HomeDir and library files
find_package(OpenCV REQUIRED)
set(LIBS ${OpenCV_LIBS})

## Setup aseba library and source files, including qt4 dbus which is requried
find_package(Qt4 COMPONENTS QtDBus QtCore REQUIRED)
## Contains every qt core module include headers e.g QtDBus
include_directories(${QT_INCLUDE_DIR})
## Setup project source files
set(SOURCE_FILES ${SOURCE_FILES} include/video/VideoAnalyser.h)
set(SOURCE_FILES ${SOURCE_FILES} include/video/VideoHandler.h)
set(SOURCE_FILES ${SOURCE_FILES} include/detector/Detector.h)
set(SOURCE_FILES ${SOURCE_FILES} include/detector/DetectorFactory.h)
set(SOURCE_FILES ${SOURCE_FILES} include/detector/RobotDetector.h)
set(SOURCE_FILES ${SOURCE_FILES} include/controller/RobotControllerFactory.h)
set(SOURCE_FILES ${SOURCE_FILES} include/controller/RobotController.h)
set(SOURCE_FILES ${SOURCE_FILES} include/controller/ThymioController.h)
set(SOURCE_FILES ${SOURCE_FILES} include/FrameStructure.h)
set(SOURCE_FILES ${SOURCE_FILES} include/SharedFrame.h)
set(SOURCE_FILES ${SOURCE_FILES} include/SharedQueue.h)
set(SOURCE_FILES ${SOURCE_FILES} src/controller/RobotControllerFactory.cpp)
set(SOURCE_FILES ${SOURCE_FILES} src/controller/ThymioController.cpp)
set(SOURCE_FILES ${SOURCE_FILES} src/video/VideoHandler.cpp)
set(SOURCE_FILES ${SOURCE_FILES} src/video/VideoAnalyser.cpp)
set(SOURCE_FILES ${SOURCE_FILES} src/detector/DetectorFactory.cpp)
set(SOURCE_FILES ${SOURCE_FILES} src/detector/RobotDetector.cpp)
set(SOURCE_FILES ${SOURCE_FILES} src/SharedQueue.cpp)
set(SOURCE_FILES ${SOURCE_FILES} src/SharedFrame.cpp)
set(SOURCE_FILES ${SOURCE_FILES} src/main.cpp)

## Create the executable "emergent_robot" while linking in the required library files
add_executable(emergent_robot ${SOURCE_FILES})
target_link_libraries(emergent_robot ${LIBS} lib_asebaclient)
