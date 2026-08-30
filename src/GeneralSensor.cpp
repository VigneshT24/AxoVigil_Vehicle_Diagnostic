#include <cstdlib>
#include <ctime>
#include "GeneralSensor.hpp"

double VehicleGeneralSensor::generateNoise(double noiseLevel) const {
    double randomValue = static_cast<double>(std::rand()) / RAND_MAX;
    return (randomValue * 2.0 - 1.0) * noiseLevel;
}