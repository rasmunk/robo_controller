//
// Created by Rasmus Munk on 27/01/2017.
//

#ifndef EMERGENT_ROBOT_THYMIOCONTROLLER_H
#define EMERGENT_ROBOT_THYMIOCONTROLLER_H

#include <include/controller/RobotController.h>
#include <asebaclient/AsebaInterface.h>
#include <asebaclient/support/Message.h>
#include <include/detector/Detector.h>
#include <include/configuration/AsebaRobotConfiguration.h>

class ThymioController : public RobotController, public QObject {

    Q_OBJECT
protected:
    std::shared_ptr<Detector> _shared_detector;
    std::unique_ptr<ENU::AsebaInterface> _aseba_interface;
    std::map<std::string, std::function<void()>> _actions;
    // Define what sort of actions the controller should setup
    virtual void setup() = 0;

public:
    ThymioController();
    ~ThymioController() { this->stop(); };
    void start() override;
    void stop() override;
    void set_shared_detector(std::shared_ptr<Detector>);

private:

    void process_messages(const ENU::Message& message);
 };

#endif //EMERGENT_ROBOT_THYMIOCONTROLLER_H
