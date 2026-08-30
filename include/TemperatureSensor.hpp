#pragma once
#include "GeneralSensor.hpp"

class VehicleTemperatureSensor : protected VehicleGeneralSensor {
    private:
        double coolantTemperature;
        double ambientTemperature;
        double bias;
        double noiseLevel;
        double minimumTemperature;
        double maximumTemperature;
    
    public:
        VehicleTemperatureSensor();

        void setCoolantTemperature(double cTemp);
        void setAmbientTemperature(double aTemp);

        double getCoolantTemperature() const;
        double getAmbientTemperature() const;

        void setBias(double new_bias);
        void setNoiseLevel(double new_noise_level);

        bool isWithinSensorRange() const;
};