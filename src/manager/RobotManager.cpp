//
// Created by Rasmus Munk on 12/04/2018.
//

#include <QCoreApplication>
#include <QThread>
#include <QTimer>
#include <include/controller/ThymioController.h>
#include <include/manager/RobotManager.h>
#include <include/util/ea/Gene.h>

using namespace std;
using namespace std::placeholders;

RobotManager::RobotManager()
{
    char* argv[] = { "program name", "arg1", "arg2", NULL };
    int argc = sizeof(argv) / sizeof(char*) - 1;
    _qcore_application = make_unique<QCoreApplication>(argc, argv);
}

void RobotManager::add(
    std::shared_ptr<RobotController> robot_controller, Controller_type controller_type)
{
    _controllers.emplace_back(make_pair(robot_controller, controller_type));
}

void RobotManager::run_qt()
{
    while (_keep_running.test_and_set()) {
        // Wait for new events -> process them when they are registered
        _qcore_application->processEvents(
            QEventLoop::WaitForMoreEvents | QEventLoop::EventLoopExec);
    }
}

void RobotManager::run()
{
    std::vector<Controller_type> thymio_types{ ThymioBasic, ThymioEmergent,
        ThymioObstacleAvoidance };
    for (auto& controller : _controllers) {
        bool is_thymio = (std::find(thymio_types.begin(), thymio_types.end(), controller.second)
            != thymio_types.end());
        if (is_thymio) {
            auto thymioController = dynamic_cast<ThymioController*>(controller.first.get());
            thymioController->start();
            _q_threads.emplace_back(make_unique<QThread>());
            thymioController->moveToThread(_q_threads.back().get());
        }
    }

    if (!_q_threads.empty()) {
        // Fire them up
        for (auto& thread : _q_threads) {
            thread->start();
        }
        // Process qt events in the manager_runner
        _manager_runner = thread(&RobotManager::run_qt, this);
    }
}

void RobotManager::stop()
{
    cout << "Stopping" << endl;
    for (auto& thread : _q_threads) {
        thread->quit();
    }

    // return to this thread
    _keep_running.clear();
    if (_manager_runner.joinable()) {
        _manager_runner.join();
    }
    cout << "Stopped" << endl;
}