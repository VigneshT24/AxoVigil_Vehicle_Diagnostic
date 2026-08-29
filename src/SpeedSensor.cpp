#include "SpeedSensor.hpp"

VehicleSpeedSensor::VehicleSpeedSensor() : speed(0.0) {}

void VehicleSpeedSensor::setSpeed(double new_speed) {
    speed = new_speed;
}

double VehicleSpeedSensor::getSpeed() const {
    return speed;
}