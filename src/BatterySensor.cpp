#include "BatterySensor.hpp"

VehicleBatterySensor::VehicleBatterySensor() : 
    voltage(0.0), current(0.0), temperature(0.0),
    voltageBias(0.0), currentBias(0.0), temperatureBias(0.0),
    noiseLevel(0.0) {
}

double VehicleBatterySensor::getVoltage() const {
    return voltage + voltageBias + generateNoise(noiseLevel);
}

double VehicleBatterySensor::getCurrent() const {
    return current + currentBias + generateNoise(noiseLevel);
}

double VehicleBatterySensor::getTemperature() const {
    return temperature + temperatureBias + generateNoise(noiseLevel);
}

void VehicleBatterySensor::setVoltage(double new_voltage) {
    voltage = new_voltage;
}

void VehicleBatterySensor::setCurrent(double new_current) {
    current = new_current;
}

void VehicleBatterySensor::setTemperature(double new_temperature) {
    temperature = new_temperature;
}

void VehicleBatterySensor::setVoltageBias(double vBias) {
    voltageBias = vBias;
}

void VehicleBatterySensor::setCurrentBias(double cBias) {
    currentBias = cBias;
}

void VehicleBatterySensor::setTemperatureBias(double tBias) {
    temperatureBias = tBias;
}

void VehicleBatterySensor::setNoiseLevel(double new_noise_level) {
    noiseLevel = new_noise_level;
}