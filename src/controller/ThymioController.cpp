//
// Created by Rasmus Munk on 27/01/2017.
//

// Relies on the provided Aseba medulla DBUS interface library which was generated from https://github.com/aseba-community/aseba/tree/master/examples/clients/cpp-qt-dbus

#include <iostream>
#include <asebaclient/support/AeslProgram.h>
#include <include/controller/ThymioController.h>

using namespace std;
using namespace std::placeholders;
using namespace ENU;

// Copies the current state of the object instance in a new thread and executes the flocking function

ThymioController::ThymioController() {
    char** argv;
    int argc;
    _aseba_interface = make_unique<AsebaInterface>("sdfsfs", "sdfdsfsd");
    if (_aseba_interface == nullptr) {
        throw runtime_error{"Failed to initialize the Aseba Interface connection"};
    }
    auto aesl_program = make_unique<AeslProgram>("sdfsdfdsf");
    _aseba_interface->sink(move(aesl_program));

    connect(_aseba_interface.get(), SIGNAL(configured()), this, SLOT(setup()));
    connect(_aseba_interface.get(), SIGNAL(incommingUserMessage(const Message&)),
                                           this, SLOT(process_message(const Message&)));
}

void ThymioController::start() {
    assert(_aseba_interface != NULL);
    _aseba_interface->start();
}

void ThymioController::stop()
{
    _aseba_interface->sendEvent("Stop");
    _aseba_interface->stop();
}

// Call submitted message event
// requires that the Message name is already registered as a called function pointer in _actions
// override setup() to configure this
void ThymioController::process_messages(const Message& message) {
    auto key = Aseba::WStringToUTF8(message.namedValue().name);
    if (_actions.find(key) != _actions.end())
    {
        _actions[key]();
    }
}

void ThymioController::set_shared_detector(shared_ptr<Detector> shared_detector)
{
    _shared_detector = shared_detector;
}

