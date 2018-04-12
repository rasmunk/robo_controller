//
// Created by Rasmus Munk on 27/01/2017.
//

#ifndef EMERGENT_ROBOT_THYMIOCONTROLLER_H
#define EMERGENT_ROBOT_THYMIOCONTROLLER_H

#include <asebaclient/AsebaInterface.h>
#include <asebaclient/support/Message.h>
#include <include/configuration/AsebaRobotConfiguration.h>
#include <include/controller/RobotController.h>
#include <include/detector/Detector.h>

class ThymioController : public QObject, public RobotController {
    Q_OBJECT
protected:
    std::shared_ptr<Detector> _shared_detector;
    std::unique_ptr<ENU::AsebaInterface> _aseba_interface;
    std::map<std::string, std::function<void()>> _actions;

protected slots:
    // Defines behaviour -> _actions callbacks
    virtual void setup();
    void process_messages(const ENU::Message& message);

public:
    ThymioController(const RobotConfig&);
    ~ThymioController() { this->stop(); };
    void start() override;
    void stop() override;
    void set_shared_detector(std::shared_ptr<Detector>);
};

#endif // EMERGENT_ROBOT_THYMIOCONTROLLER_H
