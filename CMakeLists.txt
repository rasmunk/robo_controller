cmake_minimum_required(VERSION 3.0.2)
set(PROJECT_NAME )
project(emergent_controller)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -lpthread")

## Include project source code
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
## Set the OpenCV HomeDir and library files
find_package(OpenCV REQUIRED)
set(LIBS ${OpenCV_LIBS})
## load asebaclient library
set(LIBS ${LIBS} asebaclient)

## including qt4 dbus which is requried by asebaclient
find_package(Qt4 COMPONENTS QtDBus QtCore REQUIRED)
set(LIBS ${LIBS} ${QT_QTCORE_LIBRARIES} ${QT_QTDBUS_LIBRARIES})
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
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${LIBS})

install(TARGETS ${PROJECT_NAME} EXPORT EmergentControllerConfig
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

install(DIRECTORY res DESTINATION share/${PROJECT_NAME}
        PATTERN "res/images/*"
        PATTERN "res/config/*"
        PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
        GROUP_EXECUTE GROUP_READ)

install(DIRECTORY res/scripts DESTINATION lib/systemd/system
        PATTERN "res/scripts/*"
        PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
        GROUP_EXECUTE GROUP_READ)