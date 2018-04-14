//
// Created by Rasmus Munk on 27/01/2017.
//

// Relies on the provided Aseba medulla DBUS interface library which was
// generated from
// https://github.com/aseba-community/aseba/tree/master/examples/clients/cpp-qt-dbus

#include <asebaclient/support/AeslProgram.h>
#include <include/controller/ThymioController.h>
#include <iostream>

using namespace std;
using namespace std::placeholders;
using namespace ENU;

// Copies the current state of the object instance in a new thread and executes
// the flocking function

ThymioController::ThymioController(const RobotConfig& robotConfig)
{
    _aseba_interface = make_unique<AsebaInterface>(QString::fromStdString(robotConfig.get("ip")),
        QString::fromStdString(robotConfig.get("port")));
    if (_aseba_interface == nullptr) {
        throw runtime_error{ "Failed to initialize the Aseba Interface connection" };
    }
    auto aesl_program = make_unique<AeslProgram>(robotConfig.get("aesl_file"));
    _aseba_interface->sink(move(aesl_program));

    connect(_aseba_interface.get(), SIGNAL(configured()), this, SLOT(setup()));
    connect(_aseba_interface.get(), SIGNAL(incommingUserMessage(const Message&)), this,
        SLOT(process_messages(const Message&)));
    _aseba_interface->start();
}

// defines behaviour -> setup _actions callbacks
void ThymioController::setup() {}

void ThymioController::start() {}

void ThymioController::stop()
{
    _aseba_interface->sendEvent("Stop");
    _aseba_interface->stop();
}

void ThymioController::process_messages(const Message& message)
{
    auto key = Aseba::WStringToUTF8(message.namedValue().name);
    if (_actions.find(key) != _actions.end()) {
        _actions[key]();
    }
}

void ThymioController::set_shared_detector(shared_ptr<Detector> shared_detector)
{
    _shared_detector = shared_detector;
}
