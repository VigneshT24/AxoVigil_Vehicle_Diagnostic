#pragma once
#include "GeneralSensor.hpp"

class VehicleBrakePressureSensor : protected VehicleGeneralSensor {
    private:
        double FrontBrakePressure;
        double RearBrakePressure;


        double pressureBias;
        double noiseLevel;

        double maximumPressure;
    
    public:
        VehicleBrakePressureSensor();

        void setFrontBrakePressure(double new_pressure);
        void setRearBrakePressure(double new_pressure);

        double getFrontBrakePressure() const;
        double getRearBrakePressure() const;

        double getAverageBrakePressure() const;

        void setPressureBias(double new_bias);
        void setNoiseLevel(double new_noise);

        bool isWithinSensorRange() const;
};