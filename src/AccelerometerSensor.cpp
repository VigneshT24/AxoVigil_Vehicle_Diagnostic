#include "AccelerometerSensor.hpp"

VehicleAccelerometerSensor::VehicleAccelerometerSensor() : 
    accelerationX(0.0), accelerationY(0.0), accelerationZ(0.0),
    biasX(0.0), biasY(0.0), biasZ(0.0), noiseLevel(0.0) {
}

void VehicleAccelerometerSensor::setAcceleration(double x, double y, double z) {
    accelerationX = x;
    accelerationY = y;
    accelerationZ = z;
}

double VehicleAccelerometerSensor::getAccelerationX() const {
    return accelerationX + biasX + generateNoise(noiseLevel);
}

double VehicleAccelerometerSensor::getAccelerationY() const {
    return accelerationY + biasY + generateNoise(noiseLevel);
}

double VehicleAccelerometerSensor::getAccelerationZ() const {
    return accelerationZ + biasZ + generateNoise(noiseLevel);
}

void VehicleAccelerometerSensor::setBias(double xBias, double yBias, double zBias) {
    biasX = xBias;
    biasY = yBias;
    biasZ = zBias;
}

void VehicleAccelerometerSensor::setNoiseLevel(double new_noise_level) {
    noiseLevel = new_noise_level;
}