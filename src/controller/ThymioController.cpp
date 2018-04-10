//
// Created by Rasmus Munk on 27/01/2017.
//

// Relies on the provided Aseba medulla DBUS interface library which was generated from https://github.com/aseba-community/aseba/tree/master/examples/clients/cpp-qt-dbus

#include <iostream>
#include <include/controller/ThymioController.h>

using namespace std;
using namespace std::placeholders;

// Copies the current state of the object instance in a new thread and executes the flocking function

ThymioController::ThymioController() {
    char** argv;
    int argc;
    _core_application = make_unique<QCoreApplication>(argc, argv);
    if (_core_application == nullptr) {
        throw runtime_error{"Failed to initialize QCoreApplication"};
    }
    _thymio_interface = make_unique<Aseba::DBusInterface>();
    if (_thymio_interface == nullptr) {
        throw runtime_error{"Failed to initialize the Thymio Interface connection"};
    }
    if (!_thymio_interface->checkConnection()) {
        throw runtime_error("Failed to establish Thymio DBus connection");
    }
}

void ThymioController::start() {
    assert(_core_application != NULL);
    assert(_thymio_interface != NULL);
    _runner = thread(&ThymioController::process_events, this);
}

// TODO -> switch to notify condition instead of test and set
void ThymioController::stop()
{
    (*_keep_running).clear();
}

void ThymioController::quit()
{
    this->stop();
    if (_runner.joinable())
    {
        _runner.join();
    }
}

// TODO -> switch to notify condition instead of test and set
void ThymioController::process_events() {
    while((*_keep_running).test_and_set())
    {
        // Wait for new events -> process them when they are registered
        _core_application->processEvents(QEventLoop::WaitForMoreEvents | QEventLoop::EventLoopExec);
    }
}

// Keep the robot alive -> send heartbeat
void ThymioController::callback_keepalive(const Values& event_values)
{
    _thymio_interface->sendEventName("KeepAlive", Values({}));
}

void ThymioController::set_shared_detector(shared_ptr<Detector> shared_detector)
{
    _shared_detector = shared_detector;
}

