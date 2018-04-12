//
// Created by Rasmus Munk on 12/04/2018.
//

#include <QCoreApplication>
#include <QThread>
#include <QTimer>
#include <include/controller/ThymioController.h>
#include <include/manager/RobotManager.h>

using namespace std;

void RobotManager::add(std::shared_ptr<RobotController> robot_controller,
    Controller_type controller_type)
{
    _controllers.emplace_back(make_pair(robot_controller, controller_type));
}

void RobotManager::run()
{
    std::vector<Controller_type> thymio_types{ ThymioBasic, ThymioEmergent,
        ThymioObstacleAvoidance };
    for (auto& controller : _controllers) {
        bool is_thymio = (std::find(thymio_types.begin(), thymio_types.end(),
                              controller.second)
            != thymio_types.end());
        if (is_thymio) {
            auto thymioController = dynamic_cast<ThymioController*>(controller.first.get());
            thymioController->start();
            //q_threads.emplace_back(make_unique<QThread>());
            //thymioController->moveToThread(q_threads.back().get());
        }

        /*for (auto& thread : q_threads) {
            QTimer::singleShot(300000, thread.get(), SLOT(quit()));
            q_threads.back()->start();
            thread->start();
        }*/
    }
}
