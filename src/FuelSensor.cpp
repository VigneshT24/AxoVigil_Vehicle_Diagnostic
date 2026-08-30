#include "FuelSensor.hpp"
#include <iostream>

VehicleFuelSensor::VehicleFuelSensor() : 
    fuelLiters(0.0), tankCapacityLiters(2000.0),
    bias(0.0), sloshNoise(0.0)
{}

void VehicleFuelSensor::setFuelLiters(double new_liters) {
    fuelLiters = new_liters;
}

void VehicleFuelSensor::setTankCapacity(double new_liters) {
    tankCapacityLiters = new_liters;
}

double VehicleFuelSensor::getFuelLiters() const {
    return fuelLiters + bias + generateNoise(sloshNoise);
}

double VehicleFuelSensor::getFuelPercentage() const {
    return (fuelLiters / tankCapacityLiters) * 100;
}

void VehicleFuelSensor::setBias(double new_bias) {
    bias = new_bias;
}

void VehicleFuelSensor::setSloshNoise(double new_noise) {
    sloshNoise = new_noise;
}

bool VehicleFuelSensor::isLowFuel() const {
    if ((fuelLiters / tankCapacityLiters) <= 0.05) {
        return true;
    }
    return false;
}