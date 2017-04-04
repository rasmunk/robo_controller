//
// Created by Rasmus Munk on 27/01/2017.
//

#ifndef EMERGENT_ROBOT_THYMIOCONTROLLER_H
#define EMERGENT_ROBOT_THYMIOCONTROLLER_H
#include <include/controller/RobotController.h>
#include <aseba/include/dbusinterface.h>
#include <thread>
#include <atomic>


class ThymioController : public RobotController {
private:
    std::thread _runner;
    std::unique_ptr<std::atomic_flag> _keep_running = std::make_unique<std::atomic_flag>(true);
    std::shared_ptr<Detector> _shared_detector;
    std::unique_ptr<Aseba::DBusInterface> _thymio_interface;
    std::unique_ptr<QCoreApplication> _core_application;
    const qint16 normal_speed = 300;
    void quit();
    void flocking();
    void callback_avoid(const Values& event_values); // Callback function for the thymio -> has seen an obstacle
    void callback_clear(const Values& event_values); // sees nothing -> passes the current speed
    void callback_falling(const Values& event_values); // about to fall

public:
    ThymioController() {};
    ~ThymioController() { this->quit(); };
    void start() override;
    void stop() override;
    void set_shared_detector(std::shared_ptr<Detector>) override;
 };

#endif //EMERGENT_ROBOT_THYMIOCONTROLLER_H
