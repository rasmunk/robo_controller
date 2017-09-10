//
// Created by Rasmus Munk on 29/08/2017.
//

#include <QtCore/qglobal.h>

class Thymio {
public:
    const static qint16 normal_speed = 300;
    const static qint16 max_speed = 500;
    const static qint16 min_speed = -500;
    const static qint16 max_proximity = 5000;
    const static qint16 min_proximity = 1000; // threshold in which the thymio detectes an object
};