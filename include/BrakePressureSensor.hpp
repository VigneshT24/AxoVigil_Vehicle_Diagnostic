#pragma once

class VehicleBrakePressureSensor {
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
        double geTRearBrakePressure() const;

        double getAverageBrakePressure() const;

        void setPressureBias(double new_bias);
        void setNoiseLevel(double new_noise);

        bool isWithinSensorRange() const;
};