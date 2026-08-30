#pragma once
#include "GeneralSensor.hpp"

class VehicleAccelerometerSensor : protected VehicleGeneralSensor {
    private:
        double accelerationX;
        double accelerationY;
        double accelerationZ;

        double biasX;
        double biasY;
        double biasZ;

        double noiseLevel;
    
    public:
        VehicleAccelerometerSensor();

        void setAcceleration(double x, double y, double z);

        double getAccelerationX() const;
        double getAccelerationY() const;
        double getAccelerationZ() const;

        void setBias(double xBias, double yBias, double zBias);
        void setNoiseLevel(double new_noise_level);
};