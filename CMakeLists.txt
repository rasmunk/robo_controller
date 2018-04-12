cmake_minimum_required(VERSION 3.1.0)
project(emergent_controller)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_ext")


find_package(LibXml2 REQUIRED)
include_directories(${LIBXML2_INCLUDE_DIR})

# Prepare for QT
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

## Set the OpenCV HomeDir and library files
find_package(OpenCV REQUIRED)
set(LIBS ${OpenCV_LIBS})
## load asebaclient library
set(LIBS ${LIBS} asebaclient)

## including qt5 dbus,core which is requried by asebaclient
set(Qt5_DIR /usr/local/opt/qt/lib/cmake/Qt5/)
find_package(Qt5 CONFIG REQUIRED DBus Core)

#Protobufs
find_package(Protobuf REQUIRED)
find_package(GRPC REQUIRED)
add_subdirectory(messages)

## Setup project source files
set(SOURCE_FILES ${SOURCE_FILES} include/configuration/RobotConfiguration.h)
#set(SOURCE_FILES ${SOURCE_FILES} include/configuration/AsebaRobotConfiguration.h)
set(SOURCE_FILES ${SOURCE_FILES} include/configuration/EmergentRobotConfiguration.h)
set(SOURCE_FILES ${SOURCE_FILES} include/controller/RobotController.h)
set(SOURCE_FILES ${SOURCE_FILES} include/controller/RobotControllerFactory.h)
set(SOURCE_FILES ${SOURCE_FILES} include/controller/ThymioController.h)
#set(SOURCE_FILES ${SOURCE_FILES} include/controller/ThymioEmergentController.h)
set(SOURCE_FILES ${SOURCE_FILES} include/controller/ThymioOAController.h)
set(SOURCE_FILES ${SOURCE_FILES} include/detector/Detector.h)
set(SOURCE_FILES ${SOURCE_FILES} include/detector/DetectorFactory.h)
set(SOURCE_FILES ${SOURCE_FILES} include/detector/RobotDetector.h)
set(SOURCE_FILES ${SOURCE_FILES} include/robot/Thymio.h)
set(SOURCE_FILES ${SOURCE_FILES} include/network/RobotServer.h)
set(SOURCE_FILES ${SOURCE_FILES} include/network/SimulationServiceImpl.h)
set(SOURCE_FILES ${SOURCE_FILES} include/util/ea/Gene.h)
set(SOURCE_FILES ${SOURCE_FILES} include/util/env/Environment.h)
set(SOURCE_FILES ${SOURCE_FILES} include/util/neuralnetworks/Elman.h)
set(SOURCE_FILES ${SOURCE_FILES} include/util/neuralnetworks/LayeredNeuralNetwork.h)
set(SOURCE_FILES ${SOURCE_FILES} include/util/neuralnetworks/MLP.h)
set(SOURCE_FILES ${SOURCE_FILES} include/util/neuralnetworks/NeuralNetwork.h)
set(SOURCE_FILES ${SOURCE_FILES} include/util/neuralnetworks/NeuralNetworkException.h)
set(SOURCE_FILES ${SOURCE_FILES} include/util/neuralnetworks/Perceptron.h)
set(SOURCE_FILES ${SOURCE_FILES} include/util/neuralnetworks/ReservoirNeuralNetwork.h)
set(SOURCE_FILES ${SOURCE_FILES} include/video/VideoAnalyser.h)
set(SOURCE_FILES ${SOURCE_FILES} include/video/VideoHandler.h)
set(SOURCE_FILES ${SOURCE_FILES} include/FrameStructure.h)
set(SOURCE_FILES ${SOURCE_FILES} include/SharedFrame.h)
set(SOURCE_FILES ${SOURCE_FILES} include/SharedQueue.h)

set(SOURCE_FILES ${SOURCE_FILES} src/configuration/EmergentRobotConfiguration.cpp)
set(SOURCE_FILES ${SOURCE_FILES} src/controller/RobotControllerFactory.cpp)
set(SOURCE_FILES ${SOURCE_FILES} src/controller/ThymioController.cpp)
#set(SOURCE_FILES ${SOURCE_FILES} src/controller/ThymioEmergentController.cpp)
set(SOURCE_FILES ${SOURCE_FILES} src/controller/ThymioOAController.cpp)
set(SOURCE_FILES ${SOURCE_FILES} src/detector/DetectorFactory.cpp)
set(SOURCE_FILES ${SOURCE_FILES} src/detector/RobotDetector.cpp)
set(SOURCE_FILES ${SOURCE_FILES} src/network/RobotServer.cpp)
set(SOURCE_FILES ${SOURCE_FILES} src/network/SimulationServiceImpl.cpp)
set(SOURCE_FILES ${SOURCE_FILES} src/util/ea/Gene.cpp)
set(SOURCE_FILES ${SOURCE_FILES} src/util/env/Environment.cpp)
set(SOURCE_FILES ${SOURCE_FILES} src/util/neuralnetworks/Elman.cpp)
set(SOURCE_FILES ${SOURCE_FILES} src/util/neuralnetworks/LayeredNeuralNetwork.cpp)
set(SOURCE_FILES ${SOURCE_FILES} src/util/neuralnetworks/MLP.cpp)
set(SOURCE_FILES ${SOURCE_FILES} src/util/neuralnetworks/NeuralNetwork.cpp)
set(SOURCE_FILES ${SOURCE_FILES} src/util/neuralnetworks/NeuralNetworkException.cpp)
set(SOURCE_FILES ${SOURCE_FILES} src/util/neuralnetworks/Perceptron.cpp)
set(SOURCE_FILES ${SOURCE_FILES} src/util/neuralnetworks/ReservoirNeuralNetwork.cpp)
set(SOURCE_FILES ${SOURCE_FILES} src/video/VideoHandler.cpp)
set(SOURCE_FILES ${SOURCE_FILES} src/video/VideoAnalyser.cpp)
set(SOURCE_FILES ${SOURCE_FILES} src/SharedQueue.cpp)
set(SOURCE_FILES ${SOURCE_FILES} src/SharedFrame.cpp)
set(SOURCE_FILES ${SOURCE_FILES} src/main.cpp)

## Create the executable "emergent_robot" while linking in the required library files
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${LIBS} Qt5::Core Qt5::DBus messages asebaclient ${LIBXML2_LIBRARIES})

install(TARGETS ${PROJECT_NAME} EXPORT EmergentControllerConfig
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)

install(DIRECTORY res DESTINATION share/${PROJECT_NAME}
        PATTERN "res/images/*"
        PATTERN "res/config/*"
        PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
        GROUP_EXECUTE GROUP_READ
)

install(DIRECTORY res/scripts DESTINATION lib/systemd/system
        PATTERN "res/scripts/*"
        PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
        GROUP_EXECUTE GROUP_READ
)
