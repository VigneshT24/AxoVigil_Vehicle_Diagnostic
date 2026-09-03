#pragma once
#include "GeneralSensor.hpp"

class VehicleBatterySensor : protected VehicleGeneralSensor {
    private:
        double voltage;
        double current;
        double temperature;

        double voltageBias;
        double currentBias;
        double temperatureBias;

        double voltageNoise;
        double currentNoise;
        double temperatureNoise;
    
    public:
        VehicleBatterySensor();

        double getVoltage() const;
        double getCurrent() const;
        double getTemperature() const;

        void setVoltage(double new_voltage);
        void setCurrent(double new_current);
        void setTemperature(double new_temperature);

        void setVoltageBias(double vBias);
        void setCurrentBias(double cBias);
        void setTemperatureBias(double tBias);

        void setVoltageNoise(double new_noise);
        void setCurrentNoise(double new_noise);
        void setTemperatureNoise(double new_noise);
};