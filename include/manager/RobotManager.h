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

class RobotManager {
private:
    std::vector<std::pair<std::shared_ptr<RobotController>, Controller_type>> _controllers;

    // Thymio controllers require a eventloop to exchange signals with the simulator
    std::unique_ptr<QCoreApplication> _qcore_application;
    std::atomic_flag _keep_running;

    std::vector<std::unique_ptr<QThread>> _q_threads;
    std::thread _manager_runner;

    void run_qt();

public:
    RobotManager();
    ~RobotManager() { this->stop(); }
    void add(std::shared_ptr<RobotController> robot_controller, Controller_type);
    void run();
    void stop();
};

#endif // EMERGENT_CONTROLLER_ROBOTMANAGER_H
