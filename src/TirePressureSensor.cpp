#include "TirePressureSensor.hpp"

VehicleTirePressureSensor::VehicleTirePressureSensor() : 
    frontLeftPressure(0.0), frontRightPressure(0.0), rearLeftPressure(0.0),
    rearRightPressure(0.0), frontLeftTemperature(0.0), frontRightTemperature(0.0),
    rearLeftTemperature(0.0), rearRightTemperature(0.0), pressureBias(0.0), pressureNoise(0.0)
{}

void VehicleTirePressureSensor::setFrontLeftPressure(double new_fl_pressure) {
    frontLeftPressure = new_fl_pressure;
}

void VehicleTirePressureSensor::setFrontRightPressure(double new_fr_pressure) {
    frontRightPressure = new_fr_pressure;
}

void VehicleTirePressureSensor::setRearLeftPressure(double new_rl_pressure) {
    rearLeftPressure = new_rl_pressure;
}

void VehicleTirePressureSensor::setRearRightPressure(double new_rr_pressure) {
    rearRightPressure = new_rr_pressure;
}

void VehicleTirePressureSensor::setFrontLeftTemperature(double new_fl_temp) {
    frontLeftTemperature = new_fl_temp;
}

void VehicleTirePressureSensor::setFrontRightTemperature(double new_fr_temp) {
    frontRightTemperature = new_fr_temp;
}

void VehicleTirePressureSensor::setRearLeftTemperature(double new_rl_temp) {
    rearLeftTemperature = new_rl_temp;
}

void VehicleTirePressureSensor::setRearRightTemperature(double new_rr_temp) {
    rearRightTemperature = new_rr_temp;
}

double VehicleTirePressureSensor::getFrontLeftPressure() const {
    return frontLeftPressure;
}

double VehicleTirePressureSensor::getFrontRightPressure() const {
    return frontRightPressure;
}

double VehicleTirePressureSensor::getRearLeftPressure() const {
    return rearLeftPressure;
}

double VehicleTirePressureSensor::getRearRightPressure() const {
    return rearRightPressure;
}

double VehicleTirePressureSensor::getFrontLeftTemperature() const {
    return frontLeftTemperature;
}

double VehicleTirePressureSensor::getFrontRightTemperature() const {
    return frontRightTemperature;
}

double VehicleTirePressureSensor::getRearLeftTemperature() const {
    return rearLeftTemperature;
}

double VehicleTirePressureSensor::getRearRightTemperature() const {
    return rearRightTemperature;
}

void VehicleTirePressureSensor::setPressureBias(double new_bias) {
    pressureBias = new_bias;
}

void VehicleTirePressureSensor::setPressureNoise(double new_noise) {
    pressureNoise = new_noise;
}