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

RobotManager::RobotManager() {
    char *argv[] = {"program name", "arg1", "arg2", NULL};
    int argc = sizeof(argv) / sizeof(char *) - 1;
    _qcore_application = make_unique<QCoreApplication>(argc, argv);
    // GOGOGO
    _manager_runner = thread(&RobotManager::process_qt_events, this);
}

void RobotManager::process_qt_events() {
    while (_keep_running.test_and_set()) {
        // Wait for new events -> process them when they are registered
        _qcore_application->processEvents(
                QEventLoop::WaitForMoreEvents | QEventLoop::EventLoopExec);

    }
}

void RobotManager::stop() {
    for (auto &thread : _q_threads) {
        thread->quit();
    }

    // return to this thread
    _keep_running.clear();
    if (_manager_runner.joinable()) {
        _manager_runner.join();
    }
}

void RobotManager::spawn_controller(const RobotController& controller, Controller_type
controller_type, const RobotServiceClient& robot_service_client) {
    if (robot_service_client.Add(controller, controller_type)) {
        cout << "Robot spawned" << endl;
    } else {
        cout << "Failed to spawn robot" << endl;
    }
}


// Executes robot
void RobotManager::run_controller(shared_ptr<RobotController> robot_controller, Controller_type
controller_type) {

    _controllers.emplace_back(make_pair(robot_controller, controller_type));
    bool is_thymio = (std::find(thymio_types.begin(), thymio_types.end(), controller_type)
                      != thymio_types.end());
    if (is_thymio) {
        auto thymio_controller = dynamic_cast<ThymioController *>(robot_controller.get());
        _q_threads.emplace_back(make_unique<QThread>());
        thymio_controller->moveToThread(_q_threads.back().get());
        _q_threads.back()->start();
    }

}
