#include "BatterySensor.hpp"

VehicleBatterySensor::VehicleBatterySensor() : 
    voltage(0.0), current(0.0), temperature(0.0),
    voltageBias(0.0), currentBias(0.0), temperatureBias(0.0),
    voltageNoise(0.0), currentNoise(0.0), temperatureNoise(0.0) 
{}

double VehicleBatterySensor::getVoltage() const {
    return voltage + voltageBias + generateNoise(voltageNoise);
}

double VehicleBatterySensor::getCurrent() const {
    return current + currentBias + generateNoise(currentNoise);
}

double VehicleBatterySensor::getTemperature() const {
    return temperature + temperatureBias + generateNoise(temperatureNoise);
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

void VehicleBatterySensor::setVoltageNoise(double new_noise) {
    voltageNoise = new_noise;
}

void VehicleBatterySensor::setCurrentNoise(double new_noise) {
    currentNoise = new_noise;
}

void VehicleBatterySensor::setTemperatureNoise(double new_noise) {
    temperatureNoise = new_noise;
}