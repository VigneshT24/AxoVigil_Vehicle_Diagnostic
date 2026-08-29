#include "TemperatureSensor.hpp"

VehicleTemperatureSensor::VehicleTemperatureSensor() : 
    coolantTemperature(0.0), ambientTemperature(0.0), bias(0.0),
    noiseLevel(0.0), minimumTemperature(0.0), maximumTemperature(0.0) {
}

void VehicleTemperatureSensor::setCoolantTemperature(double cTemp) {
    coolantTemperature = cTemp;
}

void VehicleTemperatureSensor::setAmbientTemperature(double aTemp) {
    ambientTemperature = aTemp;
}

double VehicleTemperatureSensor::getCoolantTemperature() const {
    return coolantTemperature;
}

double VehicleTemperatureSensor::getAmbientTemperature() const {
    return ambientTemperature;
}

void VehicleTemperatureSensor::setBias(double new_bias) {
    bias = new_bias;
}

void VehicleTemperatureSensor::setNoiseLevel(double new_noise_level) {
    noiseLevel = new_noise_level;
}

bool VehicleTemperatureSensor::isWithinSensorRange() const {
    return;
}