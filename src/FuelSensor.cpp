#include "FuelSensor.hpp"

VehicleFuelSensor::VehicleFuelSensor() : 
    fuelLiters(0.0), tankCapacityLiters(0.0),
    bias(0.0), sloshNoise(0.0)
{}

void VehicleFuelSensor::setActualFuelLiters(double new_liters) {
    fuelLiters = new_liters;
}

void VehicleFuelSensor::setTankCapacity(double new_liters) {
    tankCapacityLiters = new_liters;
}

double VehicleFuelSensor::getFuelLiters() const {
    return fuelLiters;
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
    if ((fuelLiters / tankCapacityLiters) < 0.05) {
        return true;
    }
    return false;
}