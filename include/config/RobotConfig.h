//
// Created by Rasmus Munk on 12/04/2018.
//

#ifndef EMERGENT_CONTROLLER_ROBOTCONFIG_H
#define EMERGENT_CONTROLLER_ROBOTCONFIG_H

#include <map>
#include <string>

class RobotConfig {
private:
    std::map<const std::string, std::string> _values;

public:
    const std::string& get(const std::string& key) const { return _values.at(key); }
    void set(const std::string& key, const std::string& value) { _values[key] = value; }

    void parse_config(const std::string){

    };
};

#endif // EMERGENT_CONTROLLER_ROBOTCONFIG_H
