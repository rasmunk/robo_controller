//
// Created by Rasmus Munk on 12/04/2018.
//

#ifndef EMERGENT_CONTROLLER_ROBOTMANAGER_H
#define EMERGENT_CONTROLLER_ROBOTMANAGER_H

#include <QCoreApplication>
#include <QThread>
#include <include/controller/RobotController.h>
#include <include/controller/RobotControllerFactory.h>
#include <thread>
#include <vector>
#include <QThreadPool>
#include <include/network/RobotServiceClient.h>

class RobotManager {
private:
    std::vector<Controller_type> thymio_types{ThymioBasic, ThymioEmergent,
                                              ThymioObstacleAvoidance};
    // Pin controllers
    std::vector<std::pair<std::shared_ptr<RobotController>, Controller_type>> _controllers;
    // Thymio controllers require a eventloop to exchange signals with the simulator
    std::unique_ptr<QCoreApplication> _qcore_application;
    std::atomic_flag _keep_running;

    std::vector<std::unique_ptr<QThread>> _q_threads;
    std::thread _manager_runner;

    void process_qt_events();
    void stop();

public:
    RobotManager();
    ~RobotManager() { this->stop(); }
    void spawn_controller(const RobotController&, Controller_type,
                          const RobotServiceClient&);
    void run_controller(std::shared_ptr<RobotController> robot_controller, Controller_type);
};

#endif // EMERGENT_CONTROLLER_ROBOTMANAGER_H
