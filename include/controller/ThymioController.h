//
// Created by Rasmus Munk on 27/01/2017.
//

#ifndef EMERGENT_ROBOT_THYMIOCONTROLLER_H
#define EMERGENT_ROBOT_THYMIOCONTROLLER_H
#include <include/controller/RobotController.h>
#include <asebaclient/dbusinterface.h>
#include <include/detector/Detector.h>
#include <thread>
#include <atomic>
#include <include/configuration/AsebaRobotConfiguration.h>

class ThymioController : public RobotController {
protected:
    std::thread _runner;
    std::unique_ptr<std::atomic_flag> _keep_running = std::make_unique<std::atomic_flag>(true);
    std::shared_ptr<Detector> _shared_detector;
    std::unique_ptr<Aseba::DBusInterface> _thymio_interface;
    std::unique_ptr<QCoreApplication> _core_application;

    void quit();

    // TODO -> implement default copy and move operations
public:
    ThymioController();
    ~ThymioController() { this->quit(); };
    void start() override;
    void stop() override;
    void callback_keepalive(const Values& event_values); // Used to indicate to the robot that it should keep on running
    void set_shared_detector(std::shared_ptr<Detector>);

private:
    void process_events();
 };

#endif //EMERGENT_ROBOT_THYMIOCONTROLLER_H
