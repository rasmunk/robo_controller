//
// Created by Rasmus Munk on 12/04/2018.
//

#include <include/manager/RobotManager.h>
#include <QCoreApplication>
#include <QThread>
#include <QTimer>
#include <include/controller/ThymioOAController.h>

using namespace std;

void RobotManager::add(std::unique_ptr<RobotController> robot_controller, Controller_type controller_type) {
    _controllers.push_back(make_pair(robot_controller, controller_type));
}

void RobotManager::run() {

    /*for (auto& controller : _controllers) {
        if (controller.second == Thymio) {
            auto thymioController = dynamic_cast<ThymioController *>(controllers.back().get());
            thymioController->start();
            q_threads.emplace_back(make_unique<QThread>());
            thymioController->moveToThread(q_threads.back().get());
        }
    }

    for (auto &thread : q_threads) {
        QTimer::singleShot(300000, thread.get(), SLOT(quit()));
        q_threads.back()->start();
        thread->start();
    }*/
}