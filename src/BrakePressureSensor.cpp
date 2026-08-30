#include "BrakePressureSensor.hpp"


VehicleBrakePressureSensor::VehicleBrakePressureSensor() : 
    FrontBrakePressure(0.0), RearBrakePressure(0.0),
    pressureBias(0.0), noiseLevel(0.0), maximumPressure(0.0)
{}

void VehicleBrakePressureSensor::setFrontBrakePressure(double new_f_pressure) {
    FrontBrakePressure = new_f_pressure;
}

void VehicleBrakePressureSensor::setRearBrakePressure(double new_r_pressure) {
    RearBrakePressure = new_r_pressure;
}

double VehicleBrakePressureSensor::getFrontBrakePressure() const {
    return FrontBrakePressure + pressureBias + generateNoise(noiseLevel);
}

double VehicleBrakePressureSensor::geTRearBrakePressure() const {
    return RearBrakePressure + pressureBias + generateNoise(noiseLevel);
}

double VehicleBrakePressureSensor::getAverageBrakePressure() const {
    return (FrontBrakePressure + RearBrakePressure) / 2.0;
}

void VehicleBrakePressureSensor::setPressureBias(double new_bias) {
    pressureBias = new_bias;
}

void VehicleBrakePressureSensor::setNoiseLevel(double new_noise) {
    noiseLevel = new_noise;
}

bool VehicleBrakePressureSensor::isWithinSensorRange() const {
    return (FrontBrakePressure >= 0.0 && FrontBrakePressure < maximumPressure) 
    && (RearBrakePressure >= 0.0 && RearBrakePressure < maximumPressure);
}